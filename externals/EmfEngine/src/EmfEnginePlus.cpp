/***************************************************************************
	File                 : EmfEnginePlus.cpp
	Project              : EmfEngine Commercial
	--------------------------------------------------------------------
	Copyright            : (C) 2009 - 2016 by Ion Vasilief
	Email (use @ for *)  : ion_vasilief*yahoo.fr
	Description          : Enables the export of QPainter grafics to
						   Windows Enhanced Metafiles (.emf) by using GDI+ calls
 ***************************************************************************/
/***************************************************************************
 *
 *  Commercial Usage
 *
 *  Licensees holding valid EmfEngine Commercial licenses may use this file in
 *  accordance with the EmfEngine Commercial License Agreement provided
 *  with the Software or, alternatively, in accordance with the terms
 *  contained in a written agreement between you and ProIndep Serv S.r.l.
 *
 ***************************************************************************/

#include "EmfEngine.h"
#include <QFontDatabase>
#include <QDir>
#include <QBuffer>
#if (QT_VERSION >= 0x050F00)
	#include <QPainterPath>
#endif

using namespace Gdiplus;

inline int ARGB2Pixel(int alpha, int r, int g, int b){
	if (alpha > 255)
		alpha = 255;
	else if (alpha < 0)
		alpha = 0;

	if (r > 255)
		r = 255;
	else if (r < 0)
		r = 0;

	if (g > 255)
		g = 255;
	else if (g < 0)
		g = 0;

	if (b > 255)
		b = 255;
	else if (b < 0)
		b = 0;

	// shift r and g to encode
	r = (r << 16);
	g = (g << 8 );
	return (((alpha << 24 )&0xff000000) | r | g| b);
}

// Given a QImage - get an integer encoded data of the pixels
int * image2PixelData(const QImage& image, double opacity)
{
	// get width and height of Bitmap
	int width = image.width();
	int height = image.height();

	// make sure these are valid
	if (width *height <= 0)
		return NULL;

	// allocate memory for pixel data
	int *pixelData_ARGB = new int[width*height];
	if (pixelData_ARGB == NULL)
		return NULL;

	// get the pixel values from the image and encode into the array allocated above.
	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; ++x ){
			QRgb p = image.pixel(x, y);
			pixelData_ARGB[y*width + x] = ARGB2Pixel(qRound(opacity*qAlpha(p)), qRed(p), qGreen(p), qBlue(p));
		}
	}

	// return the pixel data array
	return (pixelData_ARGB);
}

Bitmap * PixelData2BitMap(int width, int height, int *pixData_ARGB)
{
	// create a temporary Bitmap
	Bitmap *bitmap = new Bitmap(width, height, PixelFormat32bppARGB);

	BitmapData bmData;
	Rect rect(0, 0, width, height);
	bitmap->LockBits(&rect, ImageLockModeRead | ImageLockModeWrite, PixelFormat32bppARGB, &bmData);

	int stride = bmData.Stride;
	BYTE *p = (BYTE *)((void *)bmData.Scan0);
	int nOffset = stride - width*4;// bytes to skip at end of each row

	for (int y = 0; y < height;y++){
		for (int x = 0; x < width; ++x ){// GDI lies about RGB - internally it's BGR
			int pixel = pixData_ARGB[y*width+x];
			p[3] = (BYTE) ((pixel >> 24) & 0xff);// alpha
			p[2] = (BYTE) ((pixel >> 16) & 0xff);// pixel red
			p[1] = (BYTE) ((pixel >> 8 ) & 0xff);// pixel green
			p[0] = (BYTE) ((pixel      ) & 0xff);// pixel blue
			p += 4;
		}
		p += nOffset;
	}
	bitmap->UnlockBits(&bmData);
	return bitmap;
}

Bitmap* pixToBitmap(const QPixmap& pix, double opacity)
{
	QImage image = pix.toImage();
	return PixelData2BitMap(image.width(), image.height(), image2PixelData(image, opacity));
}

wchar_t* qStringToWideChar(const QString& s, int *size)
{
	int length = s.length();
	wchar_t *ws = (wchar_t *)malloc((length + 1)*sizeof(wchar_t));
	if (!ws){
		qWarning("EmfEngine: Not enough memory.");
		if (size)
			*size = -1;
		return 0;
	}
	int sz = s.toWCharArray(ws);
	if (size)
		*size = sz;
	ws[length] = '\0'; // Manually put terminating character
	return ws;
}

EmfPaintEngine::EmfPaintEngine() : QPaintEngine(QPaintEngine::AllFeatures),
fname(""),
d_mem_size(0)
{
	init();
}

EmfPaintEngine::EmfPaintEngine(unsigned long memSize) : QPaintEngine(QPaintEngine::AllFeatures),
d_mem_size(memSize)
{
	init();
}

EmfPaintEngine::EmfPaintEngine(const QString& f) : QPaintEngine(QPaintEngine::AllFeatures),
fname(f)
{
	init();
}

void EmfPaintEngine::init()
{
	stream = NULL;
	mPrivateFontCollection = NULL;
	hMetaFileResult = NULL;
}

void EmfPaintEngine::setFontFiles(const QStringList &fontFiles)
{
	// TODO: Need to add support for adding to an existing PrivateFontCollection.
	mFontFiles = fontFiles;
}

bool EmfPaintEngine::begin(QPaintDevice* p)
{
	setPaintDevice(p);

	if (!fname.isEmpty()){
	#ifdef QT_NO_STL
		wchar_t *wfname = qStringToWideChar(fname);
		if (!wfname)
			return false;
	#endif
	}

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);	// Initialize GDI+.

	if (!mFontFiles.isEmpty()){
		mPrivateFontCollection = new PrivateFontCollection();

		int filesCount = mFontFiles.size();
		for (int i = 0; i < filesCount; i++){
			wchar_t *wpath = qStringToWideChar(mFontFiles[i]);
			if (!wpath)
				continue;
			mPrivateFontCollection->AddFontFile(wpath);
			free(wpath);
		}
	}

	if (!fname.isEmpty()){
		if (fname.endsWith(".wmf", Qt::CaseInsensitive))
			metafile = new Metafile(GetDC(NULL), RectF(0, 0, paintDevice()->width(), paintDevice()->height()), MetafileFrameUnitPixel);
		else {
	#ifdef QT_NO_STL
		metafile = new Metafile(wfname, GetDC(NULL), RectF(0, 0, paintDevice()->width(), paintDevice()->height()), MetafileFrameUnitPixel);
		free(wfname);
	#else
		metafile = new Metafile(fname.toStdWString().c_str(), GetDC(NULL), RectF(0, 0, paintDevice()->width(), paintDevice()->height()), MetafileFrameUnitPixel);
	#endif
		}
	} else if (d_mem_size){
		pMem = GlobalAlloc(GMEM_MOVEABLE, d_mem_size);
		HRESULT hr = CreateStreamOnHGlobal(pMem, TRUE, &stream);
		if (SUCCEEDED(hr))
			metafile = new Metafile(stream, GetDC(NULL), RectF(0, 0, paintDevice()->width(), paintDevice()->height()), MetafileFrameUnitPixel);
	} else
		metafile = new Metafile(GetDC(NULL), RectF(0, 0, paintDevice()->width(), paintDevice()->height()), MetafileFrameUnitPixel);

	d_grx = new Graphics(metafile);
	d_grx->SetCompositingQuality(CompositingQualityHighQuality);
	d_grx->SetInterpolationMode(InterpolationModeHighQualityBicubic);
#ifdef HAVE_ANTIALIASED_TEXT
	d_grx->SetTextRenderingHint(TextRenderingHintAntiAlias);
#endif

	if (metafile && d_grx)
		return true;

	return false;
}

bool EmfPaintEngine::convertToWmf()
{
	hMetaFileResult = metafile->GetHENHMETAFILE();
	// Determine the size of the buffer that will receive the converted records
	UINT size = Metafile::EmfToWmfBits(hMetaFileResult, 0, NULL, MM_ANISOTROPIC, EmfToWmfBitsFlagsEmbedEmf);
	BYTE* buffer = new BYTE[size];// Allocate a buffer to receive the converted records
	// Convert the EMF records to WMF records
	Metafile::EmfToWmfBits(hMetaFileResult, size, buffer, MM_ANISOTROPIC, EmfToWmfBitsFlagsEmbedEmf);
	//DeleteEnhMetaFile(hMetaFileResult);
	HMETAFILE hmf = SetMetaFileBitsEx(size, buffer);// Get a handle to the converted metafile.
	if (!hmf)
		return false;

	freeMemory();

#ifdef QT_NO_STL
	wchar_t *wfname = qStringToWideChar(fname);
	if (!wfname)
		return false;
	if (CopyMetaFile(hmf, wfname) != NULL){
#else
	if (CopyMetaFileW(hmf, fname.toStdWString().c_str()) != NULL){
#endif
		DeleteMetaFile(hmf);
		delete[] buffer;
		return true;
	}
	return false;
}

bool EmfPaintEngine::copyToClipboard()
{
	if (OpenClipboard(0)){
		EmptyClipboard();
		SetClipboardData(CF_ENHMETAFILE, hMetaFileResult);
		CloseClipboard();
		freeMemory();
		return true;
	}

	return false;
}

bool EmfPaintEngine::end()
{
	delete d_grx;

	MetafileHeader metaHeader;
	metafile->GetMetafileHeader(&metaHeader);
	d_metafile_size = metaHeader.GetMetafileSize();

	if (fname.isEmpty()){
		hMetaFileResult = metafile->GetHENHMETAFILE();
		if (!stream)
			return copyToClipboard();
	}

	if (fname.endsWith(".wmf", Qt::CaseInsensitive))
		return convertToWmf();

	if (stream)
		writeToByteArray();

	freeMemory();
	return true;
}

void EmfPaintEngine::freeMemory()
{
	delete metafile;

	if (mPrivateFontCollection)
		delete mPrivateFontCollection;

	GdiplusShutdown(gdiplusToken);
}

void EmfPaintEngine::writeToByteArray()
{
	unsigned long ul;
	const unsigned long size = 1024;
	char buf[size];

	// reset the stream pointer to the front
	LARGE_INTEGER lSeek = {0};
	stream->Seek(lSeek, STREAM_SEEK_SET, NULL);

	QBuffer buffer(&d_byteArray);
	buffer.open(QIODevice::WriteOnly);
	do {
		HRESULT hr = stream->Read(buf, size, &ul);
		if (SUCCEEDED(hr)){
			int arraySize = d_byteArray.size();
			if (arraySize + ul < d_metafile_size)
				buffer.write(buf, ul);
			else {
				buffer.write(buf, d_metafile_size - arraySize);
				break;
			}
		} else
			break;
	} while (ul > 0);

	GlobalFree(pMem);
}

void EmfPaintEngine::drawPoints(const QPointF * points, int pointCount)
{
	setClipping();

	QPen pen = painter()->pen();
	REAL lw = pen.widthF();
	QColor color = pen.color();
	SolidBrush *br = new SolidBrush(Color(color.alpha(), color.red(), color.green(), color.blue()));

	QTransform m = combinedTransform();
	for (int i = 0; i < pointCount; i++) {
		QPointF p = m.map(points[i]);
		d_grx->FillRectangle(br, RectF(p.x(), p.y(), lw, lw));
	}

	delete br;
	resetClipping();
}

void EmfPaintEngine::drawLines(const QLineF * lines, int lineCount)
{
	setClipping();

	Pen *pen = convertPen(painter());

	QTransform m = combinedTransform();
	for (int i = 0; i < lineCount; i++){
		QPointF p1 = m.map(lines[i].p1());
		QPointF p2 = m.map(lines[i].p2());

		PointF wp1(p1.x(), p1.y());
		PointF wp2(p2.x(), p2.y());

		d_grx->DrawLine(pen, wp1, wp2);
	}

	delete pen;
	resetClipping();
}

void EmfPaintEngine::drawPolygon(const QPointF * points, int pointCount, PolygonDrawMode mode)
{
	setClipping();

	QTransform m = combinedTransform();
	Pen *pen = convertPen(painter());
	Qt::BrushStyle brushStyle = painter()->brush().style();

	if (mode == QPaintEngine::PolylineMode){
		int chunkSize = 256, chunks = pointCount/chunkSize, count = 0;
		PointF *pts = new PointF[chunks ? chunkSize : pointCount];
		for (int i = 0; i < chunks; i++){
			for (int j = 0; j < chunkSize; j++){
				QPointF p = m.map(points[count + j]);
				pts[j] = PointF(p.x(), p.y());
			}
			d_grx->DrawLines(pen, pts, chunkSize);
			count += chunkSize;
		}
		// draw remaining lines
		int remainingPoints = pointCount - count;
		for (int i = 0; i < remainingPoints; i++){
			QPointF p = m.map(points[count + i]);
			pts[i] = PointF(p.x(), p.y());
		}
		d_grx->DrawLines(pen, pts, remainingPoints);
		delete[] pts;
	} else {
		PointF *pts = new PointF[pointCount];
		for (int i = 0; i < pointCount; i++){
			QPointF p = m.map(points[i]);
			pts[i] = PointF(p.x(), p.y());
		}

		if (brushStyle != Qt::NoBrush){
			GraphicsPath path;
			path.AddPolygon(pts, pointCount);

			Brush *brush = convertBrush(painter()->brush(), &path);
			if (mode == QPaintEngine::OddEvenMode)
				d_grx->FillPolygon(brush, pts, pointCount, FillModeAlternate);
			else if (mode == QPaintEngine::WindingMode)
				d_grx->FillPolygon(brush, pts, pointCount, FillModeWinding);
			else
				d_grx->FillPolygon(brush, pts, pointCount);
			delete brush;
		}
		d_grx->DrawPolygon(pen, pts, pointCount);
		delete [] pts;
	}

	delete pen;
	resetClipping();
}

FontFamily *EmfPaintEngine::getFontFamily(const QString &family)
{
	FontFamily *fontFamily = NULL;

	wchar_t *wfamily = qStringToWideChar(family);
	if (wfamily){
		if (mPrivateFontCollection){
			fontFamily = new FontFamily(wfamily, mPrivateFontCollection);
			if (!fontFamily->IsAvailable()){
				delete fontFamily;
				fontFamily = NULL;
			}
		}

		if (!fontFamily)
			fontFamily = new FontFamily(wfamily);

		free(wfamily);
	} else
		fontFamily = new FontFamily();

	return fontFamily;
}

void EmfPaintEngine::drawTextItem(const QPointF & p, const QTextItem & textItem)
{
	QFont f = textItem.font();

	// Use the QFontInfo to determine the font to use. It will return
	// the font that Qt will use (in cases where the font specified by the user doesn't exist).
	QFontInfo fontInfo(f);
	QString family = fontInfo.family();

	FontFamily *fontFamily = getFontFamily(family);
	if (!fontFamily->IsAvailable()){
		qWarning("EmfEngine::drawTextItem(): font family '%s' is not available.", family.toLatin1().constData());

		if (fontFamily){
			delete fontFamily;
			fontFamily = 0;
		}

		InstalledFontCollection installedFontCollection;
		int count = installedFontCollection.GetFamilyCount();
		if (!count)
			return;

		FontFamily *pFontFamily = new FontFamily[count];
		int found = 0;
		installedFontCollection.GetFamilies(count, pFontFamily, &found);
		if (!found){
			delete [] pFontFamily;
			return;
		}

		WCHAR familyName[LF_FACESIZE];
		pFontFamily->GetFamilyName(familyName);

		fontFamily = new FontFamily(familyName);

		qWarning("Font replaced with: '%ls'", familyName);
		delete [] pFontFamily;
	}

	INT fontStyle = FontStyleRegular;
	if (f.italic())
		fontStyle = fontStyle | FontStyleItalic;
	if (f.bold())
		fontStyle = fontStyle | FontStyleBold;

	// The underline/strikeout rendering is done by Qt internally.
	// QPainter::drawTextItem  performs an additional rendering call after calling drawTextItem() on the engine object, see:
	// drawTextItemDecoration(this, p, ti.fontEngine, ti.underlineStyle, ti.flags, ti.width.toReal(), ti.charFormat);
	/*if (f.underline())
		fontStyle = fontStyle | FontStyleUnderline;
	if (f.strikeOut())
		fontStyle = fontStyle | FontStyleStrikeout;*/

	QString text = textItem.text();
	switch (f.capitalization()){
		case QFont::MixedCase:
			break;
		case QFont::AllUppercase:
		case QFont::SmallCaps:
			text = text.toUpper();
		break;
		case QFont::AllLowercase:
			text = text.toLower();
		break;
		case QFont::Capitalize:
			if (text.size() == 1)
				text = text.toUpper();
		break;
	}

	int size = text.size();
	wchar_t *wtext = qStringToWideChar(text, &size);
	if (!wtext)
		return;

	setClipping();

	QColor c = painter()->pen().color();
	SolidBrush brush(Color(c.alpha(), c.red(), c.green(), c.blue()));

	Gdiplus::Matrix *m = convertTransform(combinedTransform());
	d_grx->SetTransform(m);
	delete m;

	int height = QFontMetrics(f).boundingRect(text).height();
	double textWidth = textItem.width();
	PointF origin = PointF(p.x(), ((f.capitalization() == QFont::SmallCaps) && (text.size() > 1)) ? p.y() - 0.75*height : p.y() - 0.85*height);
	RectF layoutRect = RectF(origin.X, origin.Y, textWidth, height);

	StringFormat format;
	format.SetFormatFlags(StringFormatFlagsNoWrap|StringFormatFlagsNoFitBlackBox|StringFormatFlagsNoClip|StringFormatFlagsMeasureTrailingSpaces);
	format.SetAlignment(StringAlignmentCenter);
	format.SetLineAlignment(StringAlignmentNear);
	format.SetTrimming(StringTrimmingNone);
	format.SetTabStops(0, 0, 0);

	CharacterRange charRanges[1] = {CharacterRange(0, size)};
	format.SetMeasurableCharacterRanges(1, charRanges);

	Region *pCharRangeRegion = new Region;

	double fontSize = f.pointSizeF();
	bool pointsFont = (fontSize != -1);
	#ifndef HAVE_FIXED_FONT_SIZE
	if (pointsFont){
		RectF boundRect = RectF(origin.X, origin.Y, textWidth, height);
		if (boundRect.Width >= textWidth){
			double fUpperFontSize = fontSize;
			double fLowerFontSize = 1.0f;
			double fCurrentFontSize = 0.5*(fUpperFontSize + fLowerFontSize);
			while (fUpperFontSize - fLowerFontSize > 0.01f){
				Font font(fontFamily, fCurrentFontSize, fontStyle, UnitPoint);
				d_grx->MeasureCharacterRanges(wtext, -1, &font, layoutRect, &format, 1, pCharRangeRegion);
				pCharRangeRegion->GetBounds(&boundRect, d_grx);

				if (boundRect.Width >= textWidth)
					fUpperFontSize = fCurrentFontSize;
				else
					fLowerFontSize = fCurrentFontSize;

				fCurrentFontSize = 0.5*(fUpperFontSize + fLowerFontSize);
			}
			fontSize = fCurrentFontSize;
		}
		//qWarning("Output font size is: %.2f instead of: %.2f", fontSize, f.pointSizeF());
	}
	#endif

	Font *font = pointsFont ? new Font(fontFamily, double(fontSize), fontStyle, UnitPoint) :
							  new Font(fontFamily, double(f.pixelSize()), fontStyle, UnitPixel);

	d_grx->MeasureCharacterRanges(wtext, -1, font, layoutRect, &format, 1, pCharRangeRegion);
	pCharRangeRegion->GetBounds(&layoutRect, d_grx);
	delete pCharRangeRegion;

	d_grx->DrawString(wtext, size, font, layoutRect, &format, &brush);
	free(wtext);

	d_grx->ResetTransform();

	delete font;
	delete fontFamily;

	resetClipping();
}

void EmfPaintEngine::drawRects(const QRectF * rects, int rectCount)
{
	setClipping();

	Pen *pen = convertPen(painter());
	Qt::BrushStyle brushStyle = painter()->brush().style();

	QTransform m = combinedTransform();
	for (int i = 0; i < rectCount; i++){
		PointF *pts = new PointF[4];

		QPolygonF poly(rects[i]);
		for (int j = 0; j < 4; j++){
			QPointF p = m.map(poly[j]);
			pts[j] = PointF(p.x(), p.y());
		}

		GraphicsPath path;
		path.AddPolygon(pts, 4);

		if (brushStyle != Qt::NoBrush){
			Brush *brush = convertBrush(painter()->brush(), &path);
			d_grx->FillPath(brush, &path);
			delete brush;
		}

		d_grx->DrawPath(pen, &path);
		delete [] pts;
	}

	resetClipping();
	delete pen;
}

void EmfPaintEngine::drawEllipse(const QRectF & rect)
{
	setClipping();

	QRectF r = combinedTransform().mapRect(rect);
	RectF rf((REAL)r.left(), (REAL)r.top(), (REAL)r.width(), (REAL)r.height());

	if (painter()->brush().style() != Qt::NoBrush){
		Brush *brush = convertBrush(painter()->brush());
		d_grx->FillEllipse(brush, rf);
		delete brush;
	}

	Pen *pen = convertPen(painter());
	d_grx->DrawEllipse(pen, rf);
	delete pen;

	resetClipping();
}

void EmfPaintEngine::drawPath(const QPainterPath& path)
{
	setClipping();

	GraphicsPath *wpath = convertPath(path);
	if (!wpath)
		return;

	if (painter()->brush().style() != Qt::NoBrush){
		Brush *brush = convertBrush(painter()->brush(), wpath);
		d_grx->FillPath(brush, wpath);
		delete brush;
	}

	int count = path.elementCount();
	if (count && (path.elementAt(0).operator QPointF() == path.elementAt(count - 1).operator QPointF()))
		wpath->Outline();

	Pen *pen = convertPen(painter());
	d_grx->DrawPath(pen, wpath);
	delete pen;

	delete wpath;
	resetClipping();
}

void EmfPaintEngine::drawPixmap(const QRectF &r, const QPixmap &pm, const QRectF &sr)
{
	setClipping();

	QTransform m = combinedTransform();
	QPolygonF poly = m.map(QPolygonF() << r.topLeft() << r.topRight() << r.bottomRight() << r.bottomLeft());

	PointF destPoints[] = {
		PointF(poly.at(0).x(), poly.at(0).y()), // destination for upper-left point of original
		PointF(poly.at(1).x(), poly.at(1).y()), // destination for upper-right point of original
		PointF(poly.at(3).x(), poly.at(3).y())};// destination for lower-left point of original

	Bitmap *bm = pixToBitmap(pm.copy(sr.toAlignedRect()), painter()->opacity());
	d_grx->DrawImage(bm, destPoints, 3);
	delete bm;

	resetClipping();
}

void EmfPaintEngine::drawTiledPixmap(const QRectF& r, const QPixmap& pix, const QPointF& p)
{
	setClipping();

	QTransform m = combinedTransform();
	QRectF mr = m.mapRect(r);

	double w = (double)pix.width(), h = (double)pix.height();
	QSizeF sz = QSizeF(w, h);

	Bitmap *bm = pixToBitmap(pix.copy(QRectF(QPointF(0, 0), sz).toAlignedRect()), painter()->opacity());

	int rx = ceil(mr.width()/w), ry = ceil(mr.height()/h);
	double x0 = mr.x() + p.x(), y0 = mr.y() + p.y();
	for (int i = 0; i < ry; i++){
		double y = y0 + i*h;
		for (int j = 0; j < rx; j++){
			QRectF dr = QRectF(QPointF(x0 + j*w, y), sz);
			QPolygonF poly = QPolygonF() << dr.topLeft() << dr.topRight() << dr.bottomRight() << dr.bottomLeft();
			PointF destPoints[] = {PointF(poly.at(0).x(), poly.at(0).y()),
								PointF(poly.at(1).x(), poly.at(1).y()),
								PointF(poly.at(3).x(), poly.at(3).y())};
			d_grx->DrawImage(bm, destPoints, 3);
		}
	}

	delete bm;

	resetClipping();
}

TextureBrush * EmfPaintEngine::textureBrush(QPixmap pix, QColor brushColor)
{
	// If the brush uses a monochrome bitmap then use the brush color to create a colored image from it
	if (pix.isQBitmap()){
		QImage srcBitmap = pix.toImage();
		QImage colorImage(srcBitmap.size(), QImage::Format_RGB32);
		// Build the colored image by iterating all source pixels
		for (int y = 0; y < srcBitmap.height(); y++){
			for (int x = 0; x < srcBitmap.width(); x++){
				// Replace all color1 pixels with the brush color
				QRgb pixel = srcBitmap.pixel(x, y);
				if (pixel == QColor(Qt::color1).rgb())
					pixel = brushColor.rgb();

				colorImage.setPixel(x, y, pixel);
			}
		}
		pix = QPixmap::fromImage(colorImage);
	}

	Bitmap *bm = pixToBitmap(pix, painter()->opacity());
	TextureBrush *tb = new TextureBrush(bm);
	delete bm;
	return tb;
}

void EmfPaintEngine::drawImage(const QRectF & r, const QImage & image, const QRectF & sr, Qt::ImageConversionFlags flags)
{
	drawPixmap(r, QPixmap::fromImage(image, flags), sr);
}

void EmfPaintEngine::setClipping()
{
	if (painter()->testRenderHint(QPainter::Antialiasing))
		d_grx->SetSmoothingMode(SmoothingModeAntiAlias);

	if (painter()->hasClipping()){
		GraphicsPath *path = convertPath(painter()->clipPath());
		if(path == nullptr)
			return;

		Region region(path);// Set the clipping region of the Graphics object
		d_grx->SetClip(&region);
		delete path;
	}
}

void EmfPaintEngine::resetClipping()
{
	d_grx->ResetClip();
	d_grx->SetSmoothingMode(SmoothingModeDefault);
}

Pen *EmfPaintEngine::convertPen(const QPainter *painter)
{
	QPen pen = painter->pen();
	if (pen.style() == Qt::NoPen || pen.color() == Qt::transparent)
		return new Pen(Color::Transparent);

	QTransform transform = combinedTransform();
	double scaleFactor = fabs(qMax(transform.m11(), transform.m22()));
	double width = (scaleFactor != 1.0) ? scaleFactor*pen.widthF() : pen.widthF();

	QColor color = pen.color();
	Pen *wpen = new Pen(Color(color.alpha(), color.red(), color.green(), color.blue()), width);

	DashStyle style = DashStyleSolid;
	switch (pen.style()){
		case Qt::SolidLine:
			style = DashStyleSolid;
		break;

		case Qt::DashLine:
			style = DashStyleDash;
		break;

		case Qt::DotLine:
			style = DashStyleDot;
		break;

		case Qt::DashDotLine:
			style = DashStyleDashDot;
		break;

		case Qt::DashDotDotLine:
			style = DashStyleDashDotDot;
		break;

		case Qt::CustomDashLine:
		{
			style = DashStyleCustom;
			QVector<qreal> pattern = pen.dashPattern();
			int count = 0, pCount = pattern.count();
			for (int i = 0; i < pCount; i++){
				if (pattern.at(i) > 0)//avoid zero elements
					count++;
			}

			REAL *dashVals = new REAL[count];
			int aux = 0;
			for (int i = 0; i < pCount; i++){
				if (pattern.at(i) > 0)
					dashVals[aux++] = pattern.at(i);
			}

			wpen->SetDashPattern(dashVals, count);
			delete [] dashVals;
			break;
		}

		default:
		break;
	}
	wpen->SetDashStyle(style);
	wpen->SetDashOffset(pen.dashOffset());

	LineCap capStyle = LineCapFlat;
	DashCap dashStyle = DashCapFlat;
	switch (pen.capStyle()){
		case Qt::FlatCap:
		break;

		case Qt::SquareCap:
			capStyle = LineCapSquare;
		break;

		case Qt::RoundCap:
			capStyle = LineCapRound;
			dashStyle = DashCapRound;
		break;

		default:
		break;
	}
	wpen->SetStartCap(capStyle);
	wpen->SetEndCap(capStyle);
	wpen->SetDashCap(dashStyle);

	LineJoin joinStyle = LineJoinMiter;
	switch (pen.joinStyle()){
		case Qt::MiterJoin:
		break;

		case Qt::BevelJoin:
			joinStyle = LineJoinBevel;
		break;

		case Qt::RoundJoin:
			joinStyle = LineJoinRound;
		break;

		case Qt::SvgMiterJoin:
			joinStyle = LineJoinMiter;
		break;

		default:
			break;
	}
	wpen->SetLineJoin(joinStyle);

	if (joinStyle == LineJoinMiter)
		wpen->SetMiterLimit(pen.miterLimit());

	if (pen.brush().style() != Qt::NoBrush)
		wpen->SetBrush(convertBrush(pen.brush()));

	return wpen;
}

Gdiplus::TextureBrush* EmfPaintEngine::gradientTextureBrush(const QBrush& brush, GraphicsPath *origPath)
{
	double x = 0, y = 0, w = 0, h = 0;
	if (origPath){
		RectF rect;//Get the path's bounding rectangle.
		origPath->GetBounds(&rect);
		x = rect.GetLeft();
		y = rect.GetTop();
		w = rect.Width;
		h = rect.Height;
	}

	QPixmap pix = QPixmap((int)w, (int)h);
	QPainter paint(&pix);
	paint.setTransform(combinedTransform());
	paint.translate(-x, -y);
	paint.fillRect(QRectF(0, 0, x + w, y + h), brush);
	paint.end();

	TextureBrush *pBrush = new TextureBrush(pixToBitmap(pix, painter()->opacity()));
	pBrush->TranslateTransform(x, y);
	return pBrush;
}

Brush *EmfPaintEngine::convertBrush(const QBrush& brush, GraphicsPath *origPath)
{
	QColor c = brush.color();
	Color color(c.alpha(), c.red(), c.green(), c.blue());

	switch (brush.style()){
		case Qt::NoBrush:
			return new SolidBrush(Color::Transparent);
		break;
		case Qt::SolidPattern:
			return new SolidBrush(color);
		break;
		case Qt::Dense1Pattern:
			return new HatchBrush(HatchStyle10Percent, Color::White, color);
		break;
		case Qt::Dense2Pattern:
			return new HatchBrush(HatchStyle20Percent, Color::White, color);
		break;
		case Qt::Dense3Pattern:
			return new HatchBrush(HatchStyle30Percent, Color::White, color);
		break;
		case Qt::Dense4Pattern:
			return new HatchBrush(HatchStyle50Percent, Color::White, color);
		break;
		case Qt::Dense5Pattern:
			return new HatchBrush(HatchStyle60Percent, Color::White, color);
		break;
		case Qt::Dense6Pattern:
			return new HatchBrush(HatchStyle75Percent, Color::White, color);
		break;
		case Qt::Dense7Pattern:
			return new HatchBrush(HatchStyle80Percent, Color::White, color);
		break;
		case Qt::HorPattern:
			return new HatchBrush(HatchStyleHorizontal, color, Color::Transparent);
		break;
		case Qt::VerPattern:
			return new HatchBrush(HatchStyleVertical, color, Color::Transparent);
		break;
		case Qt::CrossPattern:
			return new HatchBrush(HatchStyleCross, color, Color::Transparent);
		break;
		case Qt::BDiagPattern:
			return new HatchBrush(HatchStyleBackwardDiagonal, color, Color::Transparent);
		break;
		case Qt::FDiagPattern:
			return new HatchBrush(HatchStyleForwardDiagonal, color, Color::Transparent);
		break;
		case Qt::DiagCrossPattern:
			return new HatchBrush(HatchStyleDiagonalCross, color, Color::Transparent);
		break;

		case Qt::LinearGradientPattern:
		{
			const QLinearGradient *qtgradient = (const QLinearGradient *)brush.gradient();
			QGradientStops stops = qtgradient->stops();
			QColor fc = stops.first().second;
			QColor lc = stops.last().second;
			QPointF sp = qtgradient->start();
			QPointF ep = qtgradient->finalStop();

			PointF start, end;
			QGradient::CoordinateMode mode = qtgradient->coordinateMode();
			if (mode == QGradient::ObjectBoundingMode){
				if (origPath){
					RectF rect;
					origPath->GetBounds(&rect);//Get the path's bounding rectangle.
					double x = rect.GetLeft(), y = rect.GetTop();
					double w = rect.Width, h = rect.Height;
					start = PointF(x + w*sp.x(), y + h*sp.y());
					end = PointF(x + w*ep.x(), y + h*ep.y());
				}
			} else if (mode == QGradient::StretchToDeviceMode){
				double w = paintDevice()->width(), h = paintDevice()->height();
				start = PointF(w*sp.x(), h*sp.y());
				end = PointF(w*ep.x(), h*ep.y());
			} else if (mode == QGradient::LogicalMode){
				QTransform m = combinedTransform();
				sp = m.map(sp);
				ep = m.map(ep);
				start = PointF(sp.x(), sp.y());
				end = PointF(ep.x(), ep.y());
			}

			LinearGradientBrush *linGrBrush = new LinearGradientBrush(start, end,
							Color(fc.alpha(), fc.red(), fc.green(), fc.blue()),
							Color(lc.alpha(), lc.red(), lc.green(), lc.blue()));

			int count = stops.count();
			REAL *positions = new REAL[count];
			Color *colors = new Color[count];
			for (int i = 0; i < count; i++){
				QGradientStop stop = stops.at(i);
				positions[i] = stop.first;
				QColor c = stop.second;
				colors[i] = Color(c.alpha(), c.red(), c.green(), c.blue());
			}
			linGrBrush->SetInterpolationColors(colors, positions, count);
			if (qtgradient->spread() == QGradient::ReflectSpread)
				linGrBrush->SetWrapMode(WrapModeTileFlipXY);
			delete [] colors;
			delete [] positions;
			return linGrBrush;
		}
		break;

		case Qt::ConicalGradientPattern:
			return gradientTextureBrush(brush, origPath);
		break;

		case Qt::RadialGradientPattern:
		{
			const QRadialGradient *qtgradient = (const QRadialGradient *)brush.gradient();
			if (qtgradient->spread() == QGradient::ReflectSpread)
				return gradientTextureBrush(brush, origPath);
			else {
				QGradientStops stops = qtgradient->stops();

				QTransform m = combinedTransform();
				QPointF center = m.map(qtgradient->center());
				QPointF focalPoint = m.map(qtgradient->focalPoint());
				REAL radius = qtgradient->radius();
				REAL diameter = 2*qtgradient->radius();

				GraphicsPath path;
				path.AddEllipse(center.x() - radius, center.y() - radius, diameter, diameter);

				// Use the path to construct a brush.
				PathGradientBrush *pthGrBrush = new PathGradientBrush(&path);
				pthGrBrush->SetCenterPoint(PointF(focalPoint.x(), focalPoint.y()));

				int count = stops.count();
				Color *colors = new Color[count];
				REAL *interpPositions = new REAL[count];
				for (int i = 0; i < count; i++){
					QGradientStop stop = stops[i];
					interpPositions[i] = stop.first;
					QColor sc = stop.second;
					colors[count - i - 1] = Color(sc.alpha(), sc.red(), sc.green(), sc.blue());
				}
				pthGrBrush->SetInterpolationColors(colors, interpPositions, count);
				if (origPath){
					SolidBrush br(colors[0]);
					d_grx->FillPath(&br, origPath);
				}
				delete [] colors;
				delete [] interpPositions;
				return pthGrBrush;
			}
		}
		break;

		case Qt::TexturePattern:
		{
			TextureBrush *pBrush = textureBrush(brush.texture(), brush.color());
			//First apply the brush transformation to our GDI+ brush
			Gdiplus::Matrix *m = convertTransform(brush.transform());//???Should toAffine() be used instead???;
			pBrush->SetTransform(m);
			delete m;
			//Then apply the painter transformation to our GDI+ brush
			m = convertTransform(combinedTransform());
			pBrush->MultiplyTransform(m, MatrixOrderAppend);
			delete m;
			return pBrush;
		}
		break;

		default:
		break;
	}

	return new SolidBrush(color);
}

Gdiplus::Matrix* EmfPaintEngine::convertTransform(const QTransform& m)
{
	return new Gdiplus::Matrix(m.m11(), m.m12(), m.m21(), m.m22(), m.dx(), m.dy());
}

GraphicsPath* EmfPaintEngine::convertPath(const QPainterPath& path)
{
	int points = path.elementCount();
	if (!points)
		return 0;

	if (path.elementAt(points - 1).type == QPainterPath::MoveToElement)
		points--;

	PointF *pts = new PointF[points];
	BYTE *types = new BYTE[points];

	QTransform m = combinedTransform();
	for (int i = 0; i < points; i++){
		QPainterPath::Element el = path.elementAt(i);
		QPointF p = m.map(QPointF(el.x, el.y));
		pts[i] = PointF(p.x(), p.y());

		switch(el.type){
			case QPainterPath::MoveToElement:
				types[i] = PathPointTypeStart;
			break;

			case QPainterPath::LineToElement:
				types[i] = PathPointTypeLine;
			break;

			case QPainterPath::CurveToElement:
				types[i] = PathPointTypeBezier;
			break;

			case QPainterPath::CurveToDataElement:
				types[i] = PathPointTypeBezier;
			break;
		}
	}

	GraphicsPath *wpath = new GraphicsPath(pts, types, points, (Gdiplus::FillMode)path.fillRule());

	delete [] pts;
	delete [] types;
	return wpath;
}

QTransform EmfPaintEngine::combinedTransform()
{
	QTransform ct = painter()->combinedTransform(), dt = painter()->deviceTransform();
	return (dt != ct) ? dt*ct : ct;
}
