/***************************************************************************
	File                 : EmfEngine.h
	Project              : EmfEngine Commercial
	--------------------------------------------------------------------
	Copyright            : (C) 2009 - 2016 by Ion Vasilief
	Email (use @ for *)  : ion_vasilief*yahoo.fr
	Description          : Enables the export of QPainter grafics to
						   Windows Enhanced Metafiles (.emf)
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

#ifndef EMFENGINE_H
#define EMFENGINE_H

#include <QPaintDevice>
#include <QPaintEngine>

#include <windows.h>

#ifdef NOMINMAX
namespace Gdiplus
{
	using std::min;
	using std::max;
};
#endif

#include <gdiplus.h>

#ifdef EMFENGINE_DLL
#  ifdef EMFENGINE_DLL_BUILD
#    define EMFENGINELIB_EXPORT Q_DECL_EXPORT
#  else
#    define EMFENGINELIB_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define EMFENGINELIB_EXPORT
#endif

wchar_t* qStringToWideChar(const QString& s, int *size = 0);

class EmfPaintEngine : public QPaintEngine
{
public:
	//! Constructor used in order to copy the metafile to clipboard.
	EmfPaintEngine();

	//! Constructor used in order to save the metafile as 'fileName'. The file format is automatically guessed from the file suffix.
	EmfPaintEngine(const QString& fileName);
	//! Constructor used in order to store the metafile to a memory buffer of size 'memSize'.
	EmfPaintEngine(unsigned long memSize);
	~EmfPaintEngine(){}
	virtual bool begin(QPaintDevice*);
	virtual bool end();
	virtual void updateState( const QPaintEngineState & ) {}
	virtual void drawEllipse(const QRectF &);
	virtual void drawImage(const QRectF& r, const QImage& im, const QRectF& sr) {drawPixmap(r,QPixmap::fromImage(im),sr);}
	virtual QPaintEngine::Type type() const {return QPaintEngine::User;}
	virtual void drawPoints ( const QPointF * points, int pointCount );
	virtual void drawLines ( const QLineF * , int );
	virtual void drawPath ( const QPainterPath & path );
	virtual void drawPolygon ( const QPointF * , int , PolygonDrawMode );
	virtual void drawTextItem ( const QPointF & , const QTextItem & );
	virtual void drawRects ( const QRectF * , int );
	virtual void drawPixmap ( const QRectF &, const QPixmap &, const QRectF &);
	virtual void drawTiledPixmap(const QRectF &, const QPixmap &, const QPointF &);
	virtual void drawImage(const QRectF &, const QImage &, const QRectF &, Qt::ImageConversionFlags);

	//! Returns the content of the metafile.
	QByteArray data(){return d_byteArray;}
	//! Returns the size of the metafile (in bytes).
	unsigned int metafileSize(){return d_metafile_size;}
	//! Gets a Windows handle to the result metafile. The handle may be NULL. This method sets the metafile object to an invalid state.
	HENHMETAFILE metaFileHandle(){return hMetaFileResult;}

	bool copyToClipboard();

	Gdiplus::Graphics *graphicsObject(){return d_grx;}

	// TODO: Needs to be implemented in none GDIplus objects.
	//       Also, may want to create a specific constructor that takes the font list.
	void setFontFiles(const QStringList &fontFiles);

private:
	Gdiplus::GraphicsPath *convertPath(const QPainterPath & path);
	bool convertToWmf();
	void freeMemory();
	void init();

	IStream* stream;
	HGLOBAL pMem;
	Gdiplus::Metafile *metafile;
	Gdiplus::Graphics *d_grx;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	//! The pointer to the GDIplus PrivateFontCollection object
	Gdiplus::PrivateFontCollection *mPrivateFontCollection;
	//! The list of application private font file names (full path)
	QStringList mFontFiles;

	//! Converts the current QPen of the painter to a GDI+ Pen structure
	Gdiplus::Pen *convertPen(const QPainter*);

	//! Converts a QBrush to a GDI+ Brush structure
	Gdiplus::Brush *convertBrush(const QBrush&, Gdiplus::GraphicsPath * = NULL);
	//! Converts a QRadialGradient or a QConicalGradient brush to a GDI+ texture brush
	Gdiplus::TextureBrush* gradientTextureBrush(const QBrush&, Gdiplus::GraphicsPath * = NULL);
	//! Constructs a texture brush based on pixmap pix
	Gdiplus::TextureBrush *textureBrush(QPixmap, QColor);
	//! Get the current FontFamily
	Gdiplus::FontFamily *getFontFamily(const QString &);
	//! Creates a new Gdiplus::Matrix based on a QTransform
	Gdiplus::Matrix *convertTransform(const QTransform&);
	//!Returns the transformation matrix combining the current window/viewport and world transformation combined with painter->deviceTransform().
	QTransform combinedTransform();
	void writeToByteArray();

	//! Name of the output metafile
	QString fname;
	//! Data stored in memory in case we don't want to write directly to a file on disk
	QByteArray d_byteArray;
	//! Size of the memory buffer
	unsigned long d_mem_size;
	//! Size of the metafile in bytes
	unsigned int d_metafile_size;
	//! Windows handle to the result metafile
	HENHMETAFILE hMetaFileResult;

	void setClipping();
	void resetClipping();
};

class EMFENGINELIB_EXPORT EmfPaintDevice : public QPaintDevice
{
public:
	//! Constructor to be used in order to save an .emf/.wmf image file.
	/*!
	\param size the size of the output image
	\param fileName the name of the output file. The file format is automatically guessed from the suffix.
	*/
	EmfPaintDevice(const QSize& size, const QString& fileName);
	//! Constructor to be used in order to store the metafile to a memory buffer.
	/*!
	\param size the size of the output image
	\param memSize the size allocated for the buffer (in bytes).
	*/
	EmfPaintDevice(const QSize& size, unsigned long memSize);
	//! Constructor to be used in order to copy the metafile to clipboard.
	/*!
	\param size the size of the emf image
	*/
	EmfPaintDevice(const QSize& size);

	~EmfPaintDevice();
	virtual QPaintEngine * paintEngine () const;

	// TODO: May want to create a specific constructor that takes the font list.
	//! Specifes a list of private font file names (full path) to be used by the application.
	void setFontFiles(const QStringList &fontNames);
	//! Returns the content of the metafile.
	QByteArray data(){return engine->data();}
	//! Returns the size of the metafile (in bytes).
	unsigned int metafileSize(){return engine->metafileSize();}
	//! Gets a Windows handle to the result metafile. The handle may be NULL. This method sets the metafile object to an invalid state.
	HENHMETAFILE metaFileHandle(){return engine->metaFileHandle();}

	double dpiX() const;
	double dpiY() const;

protected:
	virtual int metric ( PaintDeviceMetric ) const;

private:
	//! Size in pixels
	QSize d_size;

	EmfPaintEngine* engine;
};
#endif
