#include "CTI_Room.h"

#include <QJsonArray>

namespace CTI {



void Room::read(const QJsonObject &data) {

	if(data.contains("name") && data["name"].isString())
		m_name = data["name"].toString().toStdString();

	if(m_name.empty()){
		m_name = "Room";
	}

	if(data.contains("zone") && data["zone"].isString())
		m_zoneTemplate = data["zone"].toString().toStdString();

	if(data.contains("area") && data["area"].isDouble())
		m_area = data["area"].toDouble();

	if(data.contains("volume") && data["volume"].isDouble())
		m_volume = data["volume"].toDouble();

	if(data.contains("floor") && data["floor"].isObject()){

		Surface s;

		s.read(data["floor"].toObject(), Surface::T_Floor);
		if(s.isValid())
			m_surfaces.push_back(s);
	}

	if(data.contains("ceiling") && data["ceiling"].isObject()){

		Surface s;

		s.read(data["ceiling"].toObject(), Surface::T_Ceiling);
		if(s.isValid())
			m_surfaces.push_back(s);
	}

	if(data.contains("walls") && data["walls"].isArray()){

		QJsonArray walls = data["walls"].toArray();

		for(unsigned int i=0; i<walls.size(); ++i){
			Surface s;
			s.read(walls[i].toObject(), Surface::T_Wall);
			if(s.isValid())
				m_surfaces.push_back(s);
		}
	}
}


} // namespace CTI
