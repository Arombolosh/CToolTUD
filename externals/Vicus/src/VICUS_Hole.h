#ifndef VICUS_HoleH
#define VICUS_HoleH

#include "VICUS_CodeGenMacros.h"
#include "VICUS_Object.h"
#include "VICUS_Polygon2D.h"

namespace VICUS {

/*! Represents a surface hole and its associated properties. */
class Hole : public Object {
public:
	VICUS_READWRITE

	/*! Type-info string. */
	const char * typeinfo() const override { return "Hole"; }

	/*! C'tor */
	Hole() {}

	/*! Sets the Hole Polygon. */
	void setHolePolygon(const Polygon2D &holePolygon) {
		m_holePolygon = holePolygon;
	}

	//:inherited	unsigned int		m_id = INVALID_ID;	// XML:A:required
	//:inherited	QString				m_displayName;		// XML:A

	/*! Hole geometry relative to parent geometry. */
	Polygon2D							m_holePolygon;						// XML:E
};

}
#endif // VICUS_SURFACEHOLE_H
