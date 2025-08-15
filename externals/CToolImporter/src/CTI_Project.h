#ifndef CTI_ProjectH
#define CTI_ProjectH

#include "CTI_Room.h"

#include <limits>

// #include <VICUS_Project.h>

#include <NANDRAD_Project.h>

#include <QString>


namespace IBK {
class Path;
}

namespace CTI {


/*! Contains all input data from json file (C-Tool) that describes a room with walls, floor, ceiling, usage, HVAC etc.
	The room description references constructions, window and shading types from the database.

	C-Tool program
	https://fb-ifb-bauplaner.htwk-leipzig.de/ui/gui.html

	Cloud Link
	https://speicherwolke.uni-leipzig.de/index.php/s/TATMkyKRqHJY4Bf
*/
class Project
{
public:

	void readJSon2(QString &filePath);

	void exportVicus(const IBK::Path &filename);

	void exportNandrad(const IBK::Path &filename);

	void test(QString pathToJson);

	// geo data
	double					m_latitude;
	double					m_longitude;

	std::string				m_id;

	std::vector<Room>		m_rooms;

private:

	/*! Create and add construction to NANDRAD project. Returns id of this construction if new otherwise existing.
		id input is the current id which will be increased if a new object and not an existing object is created.
	*/
	unsigned int createAndAddConstruction(const std::vector<Surface::Layer> &layers, unsigned int &id, NANDRAD::Project &prj);

	/*! Create and add emb. obj. window to NANDRAD project. Returns id of this construction if new otherwise existing.
		id input is the current id which will be increased if a new object and not an existing object is created.
	*/
	unsigned int createAndAddWindow(const Surface::SubSurface &ss, unsigned int &id, NANDRAD::Project &prj, NANDRAD::EmbeddedObject &embObj);

	double inclination(const IBKMK::Polygon3D &poly, int digits) const;

	double orientation(const IBKMK::Polygon3D &poly, int digits) const;
	//std::vector<NANDRAD::ConstructionType>	m_constructionTypes;
	//std::vector<NANDRAD::Material>			m_materials;
};

} // namespace CTI

#endif // CTI_ProjectH
