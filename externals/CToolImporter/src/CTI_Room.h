#ifndef CTI_RoomH
#define CTI_RoomH

#include <QJsonObject>

#include "CTI_Surface.h"

namespace CTI {

class Room
{
public:

	void read(const QJsonObject &data);

	unsigned int				m_id;
	std::string					m_name;
	std::string					m_zoneTemplate;
	double						m_area;				// floor area of room in m2
	double						m_volume;			// m3
	std::vector<Surface>		m_surfaces;

};

} // namespace CTI

#endif // CTI_RoomH
