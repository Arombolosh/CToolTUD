#include "CTI_Surface.h"

#include <IBK_StringUtils.h>

#include <QJsonArray>

namespace CTI {


void Surface::read(const QJsonObject &data, Type type) {




	switch (type) {
		case CTI::Surface::T_Wall:		m_name = "Wall";		break;
		case CTI::Surface::T_Ceiling:	m_name = "Roof";		break;
		case CTI::Surface::T_Floor:		m_name = "Floor";		break;
		case CTI::Surface::NUM_T:
		break;
	}

	if(data.contains("name") && data["name"].isString()){
		m_name = data["name"].toString().toStdString();
	}

	if(data.contains("SurfaceID") && data["SurfaceID"].isDouble())
		m_id = (unsigned int)data["SurfaceID"].toInt();

	if(data.contains("ConnectedSurfaceID") && data["ConnectedSurfaceID"].isDouble())
		m_connectedID = (unsigned int)data["ConnectedSurfaceID"].toInt();

	// geometry
	if(data.contains("facet") && data["facet"].isArray()){
		QJsonArray facet = data["facet"].toArray();

		std::vector<IBKMK::Vector3D>	poly;

		for(int i=0; i<facet.size(); ++i){
			if(!facet[i].isArray() || facet[i].toArray().size() != 3)
				continue;
			QJsonArray point = facet[i].toArray();

			IBKMK::Vector3D vec{point[0].toDouble(), point[1].toDouble(), point[2].toDouble()};

			vec *= 0.001;				// mm -> m
			poly.push_back(vec);
		}
		m_polygon = IBKMK::Polygon3D(poly);
	}

	// windows
	if(data.contains("EmbeddedObjects") && data["EmbeddedObjects"].isArray()){
		QJsonArray embObjs = data["EmbeddedObjects"].toArray();
		for (int i=0; i < embObjs.size(); ++i){
			QJsonObject embObj = embObjs[i].toObject();

			SubSurface ss;
			if(embObj.contains("name") && embObj["name"].isString())
				ss.m_name = embObj["name"].toString().toStdString();

			double uValue = 0;

			// Calculate frame thickness and conductivity frame with standard values
			// assumption 0.1 frame conductivity --> calculate thickness of frame (with Rsi and Rse)

			if(embObj.contains("uValue") && embObj["uValue"].isDouble())
				ss.m_uValue = embObj["uValue"].toDouble();

			if(ss.m_uValue > 0.01){
				ss.m_conductivityFrame = 0.1;
				ss.m_thicknessFrame = (1/ss.m_uValue - 0.04 - 0.13) * ss.m_conductivityFrame;
			}

			// if(embObj.contains("conductivityFrame") && embObj["conductivityFrame"].isDouble())
			// 	ss.m_conductivityFrame = embObj["conductivityFrame"].toDouble();
			// if(embObj.contains("thicknessFrame") && embObj["thicknessFrame"].isDouble())
			// 	ss.m_thicknessFrame = embObj["thicknessFrame"].toDouble();
			// if(embObj.contains("uGlass") && embObj["uGlass"].isDouble())
			// 	ss.m_uValue = embObj["uGlass"].toDouble();


			if(embObj.contains("SHGC") && embObj["SHGC"].isDouble())
				ss.m_shgc = embObj["SHGC"].toDouble();
			if(embObj.contains("FrameFraction") && embObj["FrameFraction"].isDouble())
				ss.m_frameFraction = embObj["FrameFraction"].toDouble();
			if(embObj.contains("facet") && embObj["facet"].isArray()){
				QJsonArray facetWin = embObj["facet"].toArray();

				// geometry window
				std::vector<IBKMK::Vector3D>	polyWin;
				for(int i=0; i<facetWin.size(); ++i){
					if(!facetWin[i].isArray() || facetWin[i].toArray().size() != 3)
						continue;
					QJsonArray pointWin = facetWin[i].toArray();

					IBKMK::Vector3D vec{pointWin[0].toDouble(), pointWin[1].toDouble(), pointWin[2].toDouble()};

					vec *= 0.001;	// mm -> m
					polyWin.push_back(vec);
				}
				ss.m_polygon = IBKMK::Polygon3D(polyWin);
			}

			if(ss.isValid())
				m_subSurfaces.push_back(ss);
		}
	}

	// construction parameters
	if(data.contains("profile") && data["profile"].isObject()){
		QJsonObject profile = data["profile"].toObject();
		if(profile.contains("layers") && profile["layers"].isArray()){
			QJsonArray layers = profile["layers"].toArray();
			m_layers = std::vector<Layer>((size_t)layers.size());
			for(unsigned int i=0; i<(size_t)layers.size(); ++i){
				Layer l;

				int idx = -1;
				if(!layers[i].isObject())
					continue;

				QJsonObject jsonLayer = layers[i].toObject();

				if(jsonLayer.contains("name") && jsonLayer["name"].isString())
					l.m_name = jsonLayer["name"].toString().toStdString();
				if(jsonLayer.contains("idx") && jsonLayer["idx"].isDouble() )
					idx = jsonLayer["idx"].toInt();
				if(jsonLayer.contains("density") && jsonLayer["density"].isDouble() )
					l.m_density = jsonLayer["density"].toDouble();
				if(jsonLayer.contains("specHeatCapacity") && jsonLayer["specHeatCapacity"].isDouble() )
					l.m_specHeat = jsonLayer["specHeatCapacity"].toDouble();
				if(jsonLayer.contains("heatConductivity") && jsonLayer["heatConductivity"].isDouble() )
					l.m_conductivity = jsonLayer["heatConductivity"].toDouble();
				if(jsonLayer.contains("thickness") && jsonLayer["thickness"].isDouble() )
					l.m_thickness = jsonLayer["thickness"].toDouble() * 0.001;

				if(l.isValid() && idx < layers.size() && idx >= 0)
					m_layers[idx] = l;
			}
		}
		if(profile.contains("inside") && profile["inside"].isObject()){
			QJsonObject inside = profile["inside"].toObject();
			if(inside.contains("heatConvectionCoeff"))
				m_interfaceA.m_heatConvectionCoeff = inside["heatConvectionCoeff"].toDouble();

			// das muss wieder raus ist falsch in der json
			if(inside.contains("heatTransferCoefficient"))
				m_interfaceB.m_heatConvectionCoeff = inside["heatTransferCoefficient"].toDouble();

			if(inside.contains("emissivity"))
				m_interfaceA.m_emissivity = inside["emissivity"].toDouble();
			if(inside.contains("shortWaveAbsorption")){
				m_interfaceA.m_shortWaveAbsorption = inside["shortWaveAbsorption"].toDouble();
				m_interfaceA.m_hasOutsideTemperature = true;
			}
		}
		if(profile.contains("outside") && profile["outside"].isObject()){
			QJsonObject outside = profile["outside"].toObject();
			if(outside.contains("heatConvectionCoeff"))
				m_interfaceB.m_heatConvectionCoeff = outside["heatConvectionCoeff"].toDouble();

			// das muss wieder raus ist falsch in der json
			if(outside.contains("heatTransferCoefficient"))
				m_interfaceB.m_heatConvectionCoeff = outside["heatTransferCoefficient"].toDouble();

			if(outside.contains("emissivity"))
				m_interfaceB.m_emissivity = outside["emissivity"].toDouble();
			if(outside.contains("shortWaveAbsorption"))
				m_interfaceB.m_shortWaveAbsorption = outside["shortWaveAbsorption"].toDouble();
			if(outside.contains("constTemperature")){
				m_interfaceB.m_outsideTemperature = outside["constTemperature"].toDouble();
				m_interfaceB.m_hasOutsideTemperature = true;
			}
		}
	}
}

bool Surface::isValid() {
	return m_polygon.isValid();
}

bool Surface::SubSurface::isValid() {
	if(m_name.empty())
		return false;
	if(!m_polygon.isValid())
		return false;
	if(m_shgc < 0 || m_shgc > 1)
		return false;
	if(m_uValue <= 0)
		return false;
	if(m_frameFraction < 0 || m_frameFraction > 1)
		return false;
	if(m_frameFraction > 0 && m_conductivityFrame <= 0)
		return false;
	if(m_frameFraction > 0 && m_thicknessFrame <= 0)
		return false;
	return true;
}


} // namespace CTI
