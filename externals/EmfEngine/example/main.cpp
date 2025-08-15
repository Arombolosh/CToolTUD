/***************************************************************************
File                 : main.cpp
Project              : EmfEngine Commercial
--------------------------------------------------------------------
Copyright            : (C) 2009 - 2014 by Ion Vasilief
Email (use @ for *)  : ion_vasilief*yahoo.fr
Description          : Test the export of QPainter grafics to
					   Windows Enhanced Metafiles (.emf) by using GDI+ calls
****************************************************************************/
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
#include "renderarea.h"
#include <EmfEngine.h>
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	RenderArea area;

	area.setGeometry(100, 100, 600, 500);
	area.show();

	//store emf image to clipboard
	EmfPaintDevice emf0(QSize(600, 500));
	QPainter paint;
	paint.begin(&emf0);
	area.draw(&paint);
	paint.end();

	//save graphics to WMF format
	EmfPaintDevice emf1(QSize(600, 500), "example.wmf");
	paint.begin(&emf1);
	area.draw(&paint);
	paint.end();

	EmfPaintDevice emf2(QSize(600, 500), 1024 * 256);//allocates a memory buffer (256 kilobytes)
	paint.begin(&emf2);
	area.draw(&paint);
	paint.end();

	QByteArray ba = emf2.data();

	//create an EMF file from the byte array in memory
	QFile file("example.emf");
	file.open(QIODevice::WriteOnly);
	file.write(ba);
	file.close();

	printf("Metafile size is: %d bytes\n", (int)emf2.metafileSize());
	printf("QByteArray size is: %d bytes\n", (int)ba.size());

	return app.exec();
}
