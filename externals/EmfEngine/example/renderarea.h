/***************************************************************************
	File                 : renderarea.h
	Project              : EmfEngine Commercial
	--------------------------------------------------------------------
	Copyright            : (C) 2009 - 2014 by Ion Vasilief
	Email (use @ for *)  : ion_vasilief*yahoo.fr
	Description          : Test the export of QPainter grafics to
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

#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>

class RenderArea : public QWidget
{
public:
	enum Shape {Line, Polyline, Polygon, Rect, RoundedRect, Ellipse, Arc, Chord, Pie, Path, Text, Pixmap, TiledPixmap};

	RenderArea(QWidget *parent = 0);
	void draw(QPainter *painter);

protected:
	void paintEvent(QPaintEvent *event);
};

#endif
