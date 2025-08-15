/***************************************************************************
	File                 : EmfPaintDevicePlus.cpp
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
#include <QApplication>
#include <QDesktopWidget>

EmfPaintDevice::EmfPaintDevice(const QSize& s, const QString& fileName) : QPaintDevice(),
d_size(s)
{
	engine = new EmfPaintEngine(fileName);
}

EmfPaintDevice::EmfPaintDevice(const QSize& s, unsigned long memSize) : QPaintDevice(),
d_size(s)
{
	engine = new EmfPaintEngine(memSize);
}

EmfPaintDevice::EmfPaintDevice(const QSize& s) : QPaintDevice(),
d_size(s)
{
	engine = new EmfPaintEngine();
}

EmfPaintDevice::~EmfPaintDevice()
{
	delete engine;
}

void EmfPaintDevice::setFontFiles(const QStringList &fontFiles)
{
	if (engine)
		engine->setFontFiles(fontFiles);
}

QPaintEngine * EmfPaintDevice::paintEngine () const
{
	return engine;
}

double EmfPaintDevice::dpiX() const {
	if (engine) {
		Gdiplus::Graphics* graph = engine->graphicsObject();
		if(graph)
			return graph->GetDpiX();
	}
	return 0;
}

double EmfPaintDevice::dpiY() const {
	if (engine) {
		Gdiplus::Graphics* graph = engine->graphicsObject();
		if(graph)
			return graph->GetDpiY();
	}
	return 0;
}


int EmfPaintDevice::metric ( PaintDeviceMetric metric ) const
{
	switch (metric){
		case QPaintDevice::PdmWidth:
			return d_size.width();
		case QPaintDevice::PdmHeight:
			return d_size.height();
		case QPaintDevice::PdmWidthMM:
			return int(25.4*d_size.width()/engine->graphicsObject()->GetDpiX());
		case QPaintDevice::PdmHeightMM:
			return int(25.4*d_size.height()/engine->graphicsObject()->GetDpiY());
		case QPaintDevice::PdmNumColors:
			return 65536;//should it be millions?
		case QPaintDevice::PdmDepth:
			return 32;
		case QPaintDevice::PdmDpiX:
		case QPaintDevice::PdmPhysicalDpiX:
			return int(engine->graphicsObject()->GetDpiX());
		case QPaintDevice::PdmDpiY:
		case QPaintDevice::PdmPhysicalDpiY:
			return int(engine->graphicsObject()->GetDpiY());
	#if QT_VERSION >= 0x050000
		case QPaintDevice::PdmDevicePixelRatio:
			return (int)qApp->devicePixelRatio();
	#endif
	#if QT_VERSION >= 0x050600
		case QPaintDevice::PdmDevicePixelRatioScaled:
			return (int)QApplication::desktop()->devicePixelRatioF();
	#endif
		default:
			qWarning ("EmfPaintDevice::Unknown metric asked");
			return 0;
	}
}
