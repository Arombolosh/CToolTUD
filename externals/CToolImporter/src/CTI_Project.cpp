#include "CTI_Project.h"

#include <fstream>
#include <utility>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <IBK_Path.h>
#include <IBK_physics.h>

namespace CTI {


void Project::readJSon2(QString &filePath) {
	FUNCID(Project::readJSon2);

	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) 		{
		IBK::Exception(IBK::FormatString("File '%1' does not exist!.").arg(filePath.toStdString()),FUNC_ID);
		return;
	}

	// read content
	QString content = file.readAll();
	file.close();

	// create QJsonDocument
	QJsonDocument jsonDoc = QJsonDocument::fromJson(content.toUtf8());

	// check reading
	if (jsonDoc.isNull()){
		IBK::Exception(IBK::FormatString("JSon-Doc is not valid!."),FUNC_ID);
		return;
	}

	// get JSON-object
	QJsonObject jsonObj = jsonDoc.object();
	if(jsonObj.contains("geo")){
		if(!jsonObj["geo"].isNull() && jsonObj["geo"].isObject()){

			QJsonObject geo = jsonObj["geo"].toObject();

			if(geo.contains("lat") && geo["lat"].isDouble())
				m_latitude = jsonObj["geo"].toObject()["lat"].toDouble();
			if(jsonObj["geo"].toObject().contains("lon") && jsonObj["geo"].toObject()["lon"].isDouble())
				m_longitude = jsonObj["geo"].toObject()["lon"].toDouble();
		}
	}

	if(jsonObj.contains("id") && jsonObj["id"].isString()){
		m_id = jsonObj["id"].toString().toStdString();
	}

	if(jsonObj.contains("segments") && jsonObj["segments"].isArray()) {
		QJsonArray segments = jsonObj["segments"].toArray();

		for(unsigned int i=0; i<segments.size(); ++i){
			m_rooms.push_back(Room());
			Room &r = m_rooms.back();
			r.read(segments[i].toObject());
			r.m_id = i+1;
		}


	}

}

void Project::exportVicus(const IBK::Path &filename) {
#if 0

	unsigned int id=1;
	VICUS::Project prj;

	prj.m_buildings.push_back(VICUS::Building());
	VICUS::Building &b = prj.m_buildings.back();
	b.m_displayName = "Building";
	b.m_id = ++id;

	b.m_buildingLevels.push_back(VICUS::BuildingLevel());
	VICUS::BuildingLevel &bl = b.m_buildingLevels.back();
	bl.m_displayName = "GroundFloor";
	bl.m_id = ++id;

	for(unsigned int i=0; i<m_rooms.size(); ++i){
		bl.m_rooms.push_back(VICUS::Room());
		VICUS::Room &r = bl.m_rooms.back();
		Room & rJson = m_rooms[i];

		r.m_displayName = QString::fromStdString(rJson.m_name);
		r.m_id = ++id;

		for(unsigned int j=0; j<rJson.m_surfaces.size(); ++j){
			Surface &sJson = rJson.m_surfaces[j];
			VICUS::Surface s;

			s.m_id = ++id;
			s.m_displayName = QString::fromStdString(sJson.m_name);
			s.setPolygon3D(sJson.m_polygon);

			r.m_surfaces.push_back(s);
		}
	}

	prj.writeXML(filename);
#endif
}

unsigned int Project::createAndAddWindow(const Surface::SubSurface &ss, unsigned int &id,
										 NANDRAD::Project &prj, NANDRAD::EmbeddedObject &embObj){
	FUNCID(createAndAddWindow);

	NANDRAD::WindowGlazingSystem glazing;
	glazing.m_displayName = "Glazing";

	glazing.m_modelType = NANDRAD::WindowGlazingSystem::MT_Simple;

	NANDRAD::LinearSplineParameter spline;
	spline.m_interpolationMethod = NANDRAD::LinearSplineParameter::I_LINEAR;
	spline.m_name = "SHGC";
	std::vector<double> angles;
	std::vector<double> values;
	for (unsigned int i=0; i<10; ++i)
		angles.push_back(i*10); // in Deg
	// from 0 to 90 deg
	values = std::vector<double> {1,1,1,1,0.98,0.94,0.86,0.69,0.37,0};

	// scale by nominal SHGC
	for (double & v : values)
		v *= ss.m_shgc;
	spline.m_xUnit.set("Deg");
	spline.m_yUnit.set("---");
	spline.m_values.setValues(angles, values);

	// ToDo Stephan ist das richtig das hier direkt der U-Wert angesetzt wird
	NANDRAD::KeywordList::setParameter(glazing.m_para, "WindowGlazingSystem::para_t", NANDRAD::WindowGlazingSystem::P_ThermalTransmittance
									   , ss.m_uValue);
	NANDRAD::KeywordList::setParameter(glazing.m_para, "WindowGlazingSystem::para_t", NANDRAD::WindowGlazingSystem::P_SHGCHemis
									   , ss.m_shgc);

	glazing.m_splinePara[NANDRAD::WindowGlazingSystem::SP_SHGC] = spline;

	unsigned int glazId = 0;
	bool isEqual = false;
	for(const NANDRAD::WindowGlazingSystem glaz : prj.m_windowGlazingSystems){
		if(glaz.m_modelType != glazing.m_modelType)
			continue;
		if(!IBK::nearly_equal<3>(glaz.m_para[NANDRAD::WindowGlazingSystem::P_ThermalTransmittance].get_value(),
				glaz.m_para[NANDRAD::WindowGlazingSystem::P_ThermalTransmittance].get_value())
							)
			continue;
		if(glaz.m_splinePara[NANDRAD::WindowGlazingSystem::SP_SHGC] !=
				glazing.m_splinePara[NANDRAD::WindowGlazingSystem::SP_SHGC])
			continue;
		glazId = glaz.m_id;
		isEqual = true;
	}

	// if id is 0 then create new glazing system
	if(glazId == 0){
		glazing.m_id = ++id;
		glazId = glazing.m_id;
		prj.m_windowGlazingSystems.push_back(glazing);
	}

	NANDRAD::EmbeddedObjectWindow win;

	NANDRAD::WindowFrame frame;

	if(ss.m_frameFraction > 0){
		//frame.m_lambda
		frame.m_thickness.set("Thickness", ss.m_thicknessFrame, IBK::Unit("m"));
		double area = ss.m_polygon.polyline().area(1) * ss.m_frameFraction;
		frame.m_area.set("Area", area, IBK::Unit("m2"));

		NANDRAD::Material m;
		m.m_displayName = "WindowMaterialFrame";
		NANDRAD::KeywordList::setParameter(m.m_para, "Material::para_t", NANDRAD::Material::P_Conductivity, ss.m_conductivityFrame);
		NANDRAD::KeywordList::setParameter(m.m_para, "Material::para_t", NANDRAD::Material::P_Density, 500);
		NANDRAD::KeywordList::setParameter(m.m_para, "Material::para_t", NANDRAD::Material::P_HeatCapacity, 1500);

		unsigned int matId =0;
		for(const NANDRAD::Material &mN : prj.m_materials){
			if(!IBK::nearly_equal<3>(m.m_para[NANDRAD::Material::P_Conductivity].get_value(),
									mN.m_para[NANDRAD::Material::P_Conductivity].get_value()) ||
					!IBK::nearly_equal<3>(m.m_para[NANDRAD::Material::P_Density].get_value(),
									mN.m_para[NANDRAD::Material::P_Density].get_value()) ||
					!IBK::nearly_equal<3>(m.m_para[NANDRAD::Material::P_HeatCapacity].get_value(),
									mN.m_para[NANDRAD::Material::P_HeatCapacity].get_value()))
				continue;
			matId = mN.m_id;
		}

		if(matId == 0){
			m.m_id = ++id;
			matId = m.m_id;
			prj.m_materials.push_back(m);
		}

		frame.m_materialId = matId;
		win.m_frame = frame;
	}

	win.m_glazingSystemId = glazId;

	//NANDRAD::EmbeddedObject embObj;
	embObj.m_displayName = ss.m_name;
	embObj.m_id = ++id;
	embObj.m_window = win;
	NANDRAD::KeywordList::setParameter(embObj.m_para, "EmbeddedObject::para_t", NANDRAD::EmbeddedObject::P_Area,
									   ss.m_polygon.polyline().area(1));

	return embObj.m_id;
}
unsigned int Project::createAndAddConstruction(const std::vector<Surface::Layer> &layers,
											   unsigned int &id, NANDRAD::Project &prj){
	FUNCID(Project::createAndAddConstruction);

	NANDRAD::ConstructionType constr;

	constr.m_displayName = "construction_" + IBK::val2string(prj.m_constructionTypes.size());

	for(const Surface::Layer &l : layers){

		NANDRAD::Material mat;
		mat.m_displayName = /*"mat" + IBK::val2string(prj.m_materials.size());*/ l.m_name;
		NANDRAD::KeywordList::setParameter(mat.m_para, "Material::para_t", NANDRAD::Material::P_Conductivity, l.m_conductivity);
		NANDRAD::KeywordList::setParameter(mat.m_para, "Material::para_t", NANDRAD::Material::P_Density, l.m_density);
		NANDRAD::KeywordList::setParameter(mat.m_para, "Material::para_t", NANDRAD::Material::P_HeatCapacity, l.m_specHeat);

		// check if material already exist in db
		bool foundMat = false;
		unsigned int matId = 0;
		for(const NANDRAD::Material &m : prj.m_materials){
			if(m.m_para[NANDRAD::Material::P_Conductivity].value == mat.m_para[NANDRAD::Material::P_Conductivity].value &&
				m.m_para[NANDRAD::Material::P_Density].value == mat.m_para[NANDRAD::Material::P_Density].value &&
					m.m_para[NANDRAD::Material::P_HeatCapacity].value == mat.m_para[NANDRAD::Material::P_HeatCapacity].value){
				foundMat = true;
				matId = m.m_id;
				break;
			}
		}
		if(!foundMat){
			mat.m_id = ++id;
			matId = mat.m_id;
			prj.m_materials.push_back(mat);
		}
		if(matId == 0)
			IBK::Exception(IBK::FormatString("Material not found!"), FUNC_ID);

		NANDRAD::MaterialLayer mLay(l.m_thickness,matId);
		constr.m_materialLayers.push_back(mLay);
	}

	// check if construction already exist
	bool isConstrEqual = false;
	for(const NANDRAD::ConstructionType &ct : prj.m_constructionTypes){
		if(ct.m_materialLayers.size() != constr.m_materialLayers.size())
			continue;
		bool equalLayers = true;
		for(unsigned int i=0; i<ct.m_materialLayers.size(); ++i){
			const NANDRAD::MaterialLayer &ml = ct.m_materialLayers[i];
			if(ml != constr.m_materialLayers[i]){
				equalLayers = false;
				break;
			}
		}
		if(equalLayers){
			isConstrEqual = true;
			return ct.m_id;
		}

	}

	if(!isConstrEqual){
		constr.m_id = ++id;
		prj.m_constructionTypes.push_back(constr);
		return constr.m_id;
	}

	return 0;
}

double Project::inclination(const IBKMK::Polygon3D &poly, int digits) const {
	double inc = std::acos(poly.normal().m_z) / IBK::DEG2RAD;

	inc = std::round(inc*IBK::f_pow10(digits))/IBK::f_pow10(digits);
	return inc;
}


double Project::orientation(const IBKMK::Polygon3D &poly, int digits) const {
	double val = 90 - std::atan2(poly.normal().m_y, poly.normal().m_x) / IBK::DEG2RAD;
	if (val<0)
		val += 360;

	// round value to n digits
	val = std::round(val*IBK::f_pow10(digits))/IBK::f_pow10(digits);

	return  val;
}

void Project::exportNandrad(const IBK::Path &filename) {

	FUNCID(Project::exportNandrad);

	NANDRAD::Project prj;

	prj.initDefaults();
	unsigned int id=1;

	//pair< Zone id, name of surface> , uuid
	std::map<std::pair<unsigned int, std::string>, std::string>	zoneIdAndSurfaceNameToUUID;

	std::map<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>> surfaceAndRoomIDToConnectedSurfaceAndRoomID;

	NANDRAD::ObjectList objListVentilationZones, objListThermostatZones;

	enum ZoneTemplate{
		ZT_Residential,
		ZT_unheated
	};

	std::map<ZoneTemplate, std::vector<unsigned int>>	zoneTemplateToRoomIds;

	// *** create active zones ***
	NANDRAD::Zone z;
	for(const Room &r : m_rooms){
		// create NANDRAD zone
		z.m_displayName = r.m_name;

		if(IBK::tolower_string(r.m_zoneTemplate) == "residential"){
			zoneTemplateToRoomIds[ZT_Residential].push_back(r.m_id);
			objListThermostatZones.m_filterID.m_ids.insert(r.m_id);
			objListVentilationZones.m_filterID.m_ids.insert(r.m_id);
		}

		if(IBK::tolower_string(r.m_zoneTemplate) == "unheated")
			zoneTemplateToRoomIds[ZT_unheated].push_back(r.m_id);


		z.m_id = r.m_id;
		z.m_type = NANDRAD::Zone::ZT_Active;
		NANDRAD::KeywordList::setParameter(z.m_para, "Zone::para_t", NANDRAD::Zone::P_Volume, r.m_volume);
		NANDRAD::KeywordList::setParameter(z.m_para, "Zone::para_t", NANDRAD::Zone::P_Area, r.m_area);
		prj.m_zones.push_back(z);

		// check and remember connected surfaces
		for(const Surface &s : r.m_surfaces){
			zoneIdAndSurfaceNameToUUID[std::make_pair(id, s.m_name)] = "";

			unsigned int connectedRoomID = INVALID_ID;
			if(s.m_connectedID == INVALID_ID)
				continue;

			for(unsigned int idxOtherRoom = 0; idxOtherRoom < m_rooms.size(); ++idxOtherRoom){
				if(r.m_id == m_rooms[idxOtherRoom].m_id)
					continue;
				for(unsigned int idxOtherSurface = 0; idxOtherSurface < m_rooms[idxOtherRoom].m_surfaces.size(); ++idxOtherSurface){
					if(m_rooms[idxOtherRoom].m_surfaces[idxOtherSurface].m_id == s.m_connectedID){
						connectedRoomID = m_rooms[idxOtherRoom].m_id;
						break;
					}
				}
				if(connectedRoomID != INVALID_ID)
					break;
			}

			std::pair<unsigned int, unsigned int> connectedSurfaceAndRoomID = std::make_pair(s.m_connectedID, connectedRoomID);
			surfaceAndRoomIDToConnectedSurfaceAndRoomID[std::make_pair(s.m_id, r.m_id)] = connectedSurfaceAndRoomID;
		}
		++id;
	}

	std::set<unsigned int>	usedSurfaces;
	std::map<double, NANDRAD::Zone> constTempToZone;

	// *** create construction instances ***
	for(const Room &r : m_rooms){
		for(const Surface &s : r.m_surfaces){

			// this surface is already used
			if(usedSurfaces.find(s.m_id) != usedSurfaces.end())
				continue;

			// mark id as used
			usedSurfaces.insert(s.m_id);

			// check if we have a linked surface and
			bool foundOtherSurface = s.m_connectedID != INVALID_ID;

			// mark also linked surface as used
			if(foundOtherSurface)
				usedSurfaces.insert(s.m_connectedID);

			unsigned int connectedRoomID = INVALID_ID;
			if(foundOtherSurface){
				// get room id of connected room
				for(std::map<std::pair<unsigned int, unsigned int>,
					std::pair<unsigned int, unsigned int>>::iterator it=surfaceAndRoomIDToConnectedSurfaceAndRoomID.begin();
							it!=surfaceAndRoomIDToConnectedSurfaceAndRoomID.end();
							++it){
					if(it->second.first == s.m_connectedID){
						connectedRoomID = it->second.second;
						//it->second.second = r.m_id;
						break;
					}
				}
				if(connectedRoomID == INVALID_ID)
					throw IBK::Exception(IBK::FormatString("Connected room not found!"), FUNC_ID);
			}

			// check for construction parameters, if not existing in this surface check connected surface
			bool foundConstruction = !s.m_layers.empty();
			bool insideIsOtherRoom = s.m_layers.empty();
			std::vector<Surface::Layer>	layers;

			unsigned int idxOtherRoom=0;
			unsigned int idxOtherSurface=0;
			// find construction layer because only one surface has construction layers
			if(s.m_connectedID != INVALID_ID){
				for(; idxOtherRoom < m_rooms.size(); ++idxOtherRoom){
					const Room &otherRoom = m_rooms[idxOtherRoom];
					if(otherRoom.m_id == connectedRoomID){
						for(; idxOtherSurface < otherRoom.m_surfaces.size(); ++idxOtherSurface){
							const Surface &otherSurface = otherRoom.m_surfaces[idxOtherSurface];
							if(otherSurface.m_id == s.m_connectedID){
								if(foundConstruction) {
									layers = s.m_layers;
									break;
								}
								if(otherSurface.m_layers.empty())
									throw IBK::Exception(IBK::FormatString("Connected surface and this surface have no constructions!"), FUNC_ID);
								layers = otherSurface.m_layers;
								break;
							}
						}
						break;
					}
				}
			}
			else
				layers = s.m_layers;



			if(layers.empty())
				throw IBK::Exception(IBK::FormatString("No layers were found for the construction!"), FUNC_ID);

//			std::pair<unsigned int, std::string>	otherSurfaceEntry;
//			if(!s.m_uuid.empty()) {

//				// add uuid
//				usedSurfaces.insert(s.m_uuid);

//				if(zoneIdAndSurfaceNameToUUID.find(std::make_pair(r.m_id, s.m_name)) != zoneIdAndSurfaceNameToUUID.end()){
//					std::string uuid = zoneIdAndSurfaceNameToUUID[std::make_pair(r.m_id, s.m_name)];
//					if(usedSurfaces.find(uuid) != usedSurfaces.end())
//						continue;
//					// find other side -> there must be a second entry with same uuid
//					for(const auto &obj : zoneIdAndSurfaceNameToUUID){
//						if(obj.second == uuid){
//							otherSurfaceEntry = obj.first;
//							foundOtherSurface = true;
//							break;
//						}
//					}
//				}
//			}

			unsigned int idConstr = createAndAddConstruction(layers, id, prj);
			// >0 is valid
			if(id > 0) {
				NANDRAD::ConstructionInstance ci;
				ci.m_id = ++id;
				ci.m_displayName = r.m_name + "." + s.m_name;
				NANDRAD::KeywordList::setParameter(ci.m_para, "ConstructionInstance::para_t",
												   NANDRAD::ConstructionInstance::P_Area, s.m_polygon.polyline().area());
				NANDRAD::KeywordList::setParameter(ci.m_para, "ConstructionInstance::para_t",
												   NANDRAD::ConstructionInstance::P_Orientation, orientation(s.m_polygon, 1));
				NANDRAD::KeywordList::setParameter(ci.m_para, "ConstructionInstance::para_t",
												   NANDRAD::ConstructionInstance::P_Inclination, inclination(s.m_polygon, 1));
				ci.m_constructionTypeId = idConstr;



				// this is a linked construction instance
				if(foundOtherSurface){
					// check which side is side A

					Surface s1 = s;
					if(insideIsOtherRoom)
						s1 = m_rooms[idxOtherRoom].m_surfaces[idxOtherSurface];

					NANDRAD::Interface interfaceA;
					if(s1.m_interfaceA.m_heatConvectionCoeff > 0) {
						interfaceA.m_heatConduction.m_modelType = NANDRAD::InterfaceHeatConduction::MT_Constant;
						NANDRAD::KeywordList::setParameter(interfaceA.m_heatConduction.m_para, "InterfaceHeatConduction::para_t",
														   NANDRAD::InterfaceHeatConduction::P_HeatTransferCoefficient,
														   s1.m_interfaceA.m_heatConvectionCoeff);

						// innen nehmen wir erstmal keine emissivity an
						if(s1.m_interfaceA.m_emissivity > 0 && false){
							NANDRAD::KeywordList::setParameter(interfaceA.m_longWaveEmission.m_para, "InterfaceLongWaveEmission::para_t",
															   NANDRAD::InterfaceLongWaveEmission::P_Emissivity,
															   s1.m_interfaceA.m_emissivity);
							interfaceA.m_longWaveEmission.m_modelType = NANDRAD::InterfaceLongWaveEmission::MT_Constant;
						}

						// innen nehmen wir erstmal keine short wave an
						if(s1.m_interfaceA.m_shortWaveAbsorption > 0 && false) {
							NANDRAD::KeywordList::setParameter(interfaceA.m_solarAbsorption.m_para, "InterfaceSolarAbsorption::para_t",
															   NANDRAD::InterfaceSolarAbsorption::P_AbsorptionCoefficient,
															   s1.m_interfaceA.m_shortWaveAbsorption);
							interfaceA.m_solarAbsorption.m_modelType = NANDRAD::InterfaceSolarAbsorption::MT_Constant;
						}

						interfaceA.m_id = 1;
						interfaceA.m_zoneId = insideIsOtherRoom ? m_rooms[idxOtherRoom].m_id : r.m_id;
						ci.m_interfaceA = interfaceA;
					}


					NANDRAD::Interface interfaceB;
					if(s1.m_interfaceB.m_heatConvectionCoeff > 0) {
						interfaceB.m_heatConduction.m_modelType = NANDRAD::InterfaceHeatConduction::MT_Constant;
						NANDRAD::KeywordList::setParameter(interfaceB.m_heatConduction.m_para, "InterfaceHeatConduction::para_t",
														   NANDRAD::InterfaceHeatConduction::P_HeatTransferCoefficient,
														   s1.m_interfaceB.m_heatConvectionCoeff);

						// innen nehmen wir erstmal keine emissivity an
						if(s1.m_interfaceB.m_emissivity > 0 && false){
							NANDRAD::KeywordList::setParameter(interfaceB.m_longWaveEmission.m_para, "InterfaceLongWaveEmission::para_t",
															   NANDRAD::InterfaceLongWaveEmission::P_Emissivity,
															   s1.m_interfaceB.m_emissivity);
							interfaceB.m_longWaveEmission.m_modelType = NANDRAD::InterfaceLongWaveEmission::MT_Constant;
						}

						// innen nehmen wir erstmal keine short wave an
						if(s1.m_interfaceB.m_shortWaveAbsorption > 0 && false) {
							NANDRAD::KeywordList::setParameter(interfaceB.m_solarAbsorption.m_para, "InterfaceSolarAbsorption::para_t",
															   NANDRAD::InterfaceSolarAbsorption::P_AbsorptionCoefficient,
															   s1.m_interfaceB.m_shortWaveAbsorption);
							interfaceB.m_solarAbsorption.m_modelType = NANDRAD::InterfaceSolarAbsorption::MT_Constant;
						}

						interfaceB.m_id = 2;
						interfaceB.m_zoneId = !insideIsOtherRoom ? m_rooms[idxOtherRoom].m_id : r.m_id;

						ci.m_interfaceB = interfaceB;
					}
				}
				else {
					NANDRAD::Interface interfaceA;
					if(s.m_interfaceA.m_heatConvectionCoeff > 0) {
						interfaceA.m_heatConduction.m_modelType = NANDRAD::InterfaceHeatConduction::MT_Constant;
						NANDRAD::KeywordList::setParameter(interfaceA.m_heatConduction.m_para, "InterfaceHeatConduction::para_t",
														   NANDRAD::InterfaceHeatConduction::P_HeatTransferCoefficient,
														   s.m_interfaceA.m_heatConvectionCoeff);

						// innen nehmen wir erstmal keine emissivity an
						if(s.m_interfaceA.m_emissivity > 0 && false){
							NANDRAD::KeywordList::setParameter(interfaceA.m_longWaveEmission.m_para, "InterfaceLongWaveEmission::para_t",
															   NANDRAD::InterfaceLongWaveEmission::P_Emissivity,
															   s.m_interfaceA.m_emissivity);
							interfaceA.m_longWaveEmission.m_modelType = NANDRAD::InterfaceLongWaveEmission::MT_Constant;
						}

						// innen nehmen wir erstmal keine short wave an
						if(s.m_interfaceA.m_shortWaveAbsorption > 0 && false) {
							NANDRAD::KeywordList::setParameter(interfaceA.m_solarAbsorption.m_para, "InterfaceSolarAbsorption::para_t",
															   NANDRAD::InterfaceSolarAbsorption::P_AbsorptionCoefficient,
															   s.m_interfaceA.m_shortWaveAbsorption);
							interfaceA.m_solarAbsorption.m_modelType = NANDRAD::InterfaceSolarAbsorption::MT_Constant;
						}

						interfaceA.m_id = 1;
						interfaceA.m_zoneId = r.m_id;
						ci.m_interfaceA = interfaceA;
					}

					NANDRAD::Interface interfaceB;
					if(s.m_interfaceB.m_heatConvectionCoeff > 0) {
						interfaceB.m_heatConduction.m_modelType = NANDRAD::InterfaceHeatConduction::MT_Constant;
						NANDRAD::KeywordList::setParameter(interfaceB.m_heatConduction.m_para, "InterfaceHeatConduction::para_t",
														   NANDRAD::InterfaceHeatConduction::P_HeatTransferCoefficient,
														   s.m_interfaceB.m_heatConvectionCoeff);

						// has passive or ground zone if outside temperature exist
						if(s.m_interfaceB.m_hasOutsideTemperature){
							//check if zone already exist
							if(constTempToZone.find(s.m_interfaceB.m_outsideTemperature) == constTempToZone.end()){
								// create ground zone with const temperature
								NANDRAD::Zone z;
								z.m_displayName = "GroundZone T=" + IBK::val2string(s.m_interfaceB.m_outsideTemperature);
								z.m_id = ++id;
								z.m_type = NANDRAD::Zone::ZT_Constant;
								z.m_para->set("Temperature", s.m_interfaceB.m_outsideTemperature, IBK::Unit("C"));
								constTempToZone[s.m_interfaceB.m_outsideTemperature] = z;
								prj.m_zones.push_back(z);
							}
							interfaceB.m_zoneId = constTempToZone[s.m_interfaceB.m_outsideTemperature].m_id;

						}
						else {
							if(s.m_interfaceB.m_emissivity > 0){
								NANDRAD::KeywordList::setParameter(interfaceB.m_longWaveEmission.m_para, "InterfaceLongWaveEmission::para_t",
																   NANDRAD::InterfaceLongWaveEmission::P_Emissivity,
																   s.m_interfaceB.m_emissivity);
								interfaceB.m_longWaveEmission.m_modelType = NANDRAD::InterfaceLongWaveEmission::MT_Constant;
							}

							if(s.m_interfaceB.m_shortWaveAbsorption > 0) {
								NANDRAD::KeywordList::setParameter(interfaceB.m_solarAbsorption.m_para, "InterfaceSolarAbsorption::para_t",
																   NANDRAD::InterfaceSolarAbsorption::P_AbsorptionCoefficient,
																   s.m_interfaceB.m_shortWaveAbsorption);
								interfaceB.m_solarAbsorption.m_modelType = NANDRAD::InterfaceSolarAbsorption::MT_Constant;
							}
							interfaceB.m_zoneId = 0;

						}


						interfaceB.m_id = 2;

						ci.m_interfaceB = interfaceB;
					}
				}

				// add sub surface to construction instance
				for(Surface::SubSurface ss : s.m_subSurfaces){

					if(!ss.isValid())
						continue;

					NANDRAD::EmbeddedObject embObj;
					unsigned int embObjId = createAndAddWindow(ss, id, prj, embObj);

					ci.m_embeddedObjects.push_back(embObj);
				}

				prj.m_constructionInstances.push_back(ci);
			}
		}
	}

	// *** Location ***

	NANDRAD::Location &loc = prj.m_location;

	loc.m_climateFilePath = IBK::Path("${Project Directory}/Klima/TRY2015_510327137440_Jahr.dat");
	NANDRAD::KeywordList::setParameter(loc.m_para, "Location::para_t", NANDRAD::Location::P_Albedo, 0.2);
	NANDRAD::KeywordList::setParameter(loc.m_para, "Location::para_t", NANDRAD::Location::P_Longitude, m_longitude);
	NANDRAD::KeywordList::setParameter(loc.m_para, "Location::para_t", NANDRAD::Location::P_Latitude, m_latitude);
	loc.m_flags->set("PerezDiffuseRadiationModel", true);
	loc.m_timeZone = 1;

	std::vector<std::pair<double,double>> incliOrient{std::make_pair(.0,.0),std::make_pair(90,.0),std::make_pair(90,90),std::make_pair(90,180),std::make_pair(90,270)};
	for(auto iO : incliOrient){
		NANDRAD::Sensor sen;

		sen.createSensor(++id, iO.second, iO.first);

		loc.m_sensors.push_back(sen);
	}

	prj.m_projectInfo.m_comment = "Created by Dirk Weiss dirk.weiss@tu-dresden.de";

	// *** Schedules ***

	std::string nameThermostat = "Residential Thermostat";
	std::string nameVentilation = "Residential Inf + Vent";

	NANDRAD::Schedule schedule;
	schedule.m_type = NANDRAD::Schedule::ST_ALLDAYS;

	NANDRAD::DailyCycle dc;
	dc.m_interpolation = NANDRAD::DailyCycle::IT_Constant;
	dc.m_timePoints = std::vector<double>{0,6,23};
	dc.m_values.m_values["HeatingSetpointSchedule [C]"] = std::vector<double>{17,21,17};

	schedule.m_dailyCycles.push_back(dc);

	dc.m_timePoints = std::vector<double>{0};
	dc.m_values.m_values.clear();
	dc.m_values.m_values["CoolingSetpointSchedule [C]"] = std::vector<double>{200};
	schedule.m_dailyCycles.push_back(dc);

	prj.m_schedules.m_scheduleGroups[nameThermostat].push_back(schedule);

	schedule.m_dailyCycles.clear();
	dc.m_timePoints = std::vector<double>{0,6,23};
	dc.m_values.m_values.clear();
	dc.m_values.m_values["VentilationRateSchedule [1/h]"] = std::vector<double>{0.1,0.6,0.1};
	schedule.m_dailyCycles.push_back(dc);

	prj.m_schedules.m_scheduleGroups[nameVentilation].push_back(schedule);

	// *** Outputs ***

	NANDRAD::OutputGrid outGrid;

	outGrid.m_name = "Hourly";
	outGrid.m_intervals.push_back(NANDRAD::Interval());
	NANDRAD::KeywordList::setParameter(outGrid.m_intervals.back().m_para, "Interval::para_t", NANDRAD::Interval::P_Start, 0);
	NANDRAD::KeywordList::setParameter(outGrid.m_intervals.back().m_para, "Interval::para_t", NANDRAD::Interval::P_StepSize, 1);
	prj.m_outputs.m_grids.push_back(outGrid);

	NANDRAD::OutputDefinition outDef;
	outDef.m_objectListName = "All Zones";
	outDef.m_quantity = "AirTemperature";
	outDef.m_gridName = outGrid.m_name;
	outDef.m_fileName = outDef.m_quantity;
	prj.m_outputs.m_definitions.push_back(outDef);

	outDef = NANDRAD::OutputDefinition();
	outDef.m_objectListName = "All Zones";
	outDef.m_quantity = "OperativeTemperature";
	outDef.m_fileName = outDef.m_quantity;
	outDef.m_gridName = outGrid.m_name;
	prj.m_outputs.m_definitions.push_back(outDef);

	outDef = NANDRAD::OutputDefinition();
	outDef.m_objectListName = "All Zones";
	outDef.m_quantity = "IdealHeatingLoad";
	outDef.m_fileName = outDef.m_quantity;
	outDef.m_gridName = outGrid.m_name;
	prj.m_outputs.m_definitions.push_back(outDef);

	outDef = NANDRAD::OutputDefinition();
	outDef.m_objectListName = "All Zones";
	outDef.m_quantity = "IdealCoolingLoad";
	outDef.m_fileName = outDef.m_quantity;
	outDef.m_gridName = outGrid.m_name;
	prj.m_outputs.m_definitions.push_back(outDef);

	outDef = NANDRAD::OutputDefinition();
	outDef.m_objectListName = "All Zones";
	outDef.m_quantity = "LightingElectricalPower";
	outDef.m_gridName = outGrid.m_name;
	prj.m_outputs.m_definitions.push_back(outDef);

	outDef = NANDRAD::OutputDefinition();
	outDef.m_objectListName = "All Zones";
	outDef.m_quantity = "EquipmentElectricalPower";
	outDef.m_gridName = outGrid.m_name;
	prj.m_outputs.m_definitions.push_back(outDef);

	outDef = NANDRAD::OutputDefinition();
	outDef.m_objectListName = "All Zones";
	outDef.m_quantity = "ConvectivePersonHeatLoad";
	outDef.m_gridName = outGrid.m_name;
	prj.m_outputs.m_definitions.push_back(outDef);

	// *** Outputs Location ***

	outDef = NANDRAD::OutputDefinition();
	outDef.m_objectListName = "Location";
	outDef.m_quantity = "Temperature";
	outDef.m_gridName = outGrid.m_name;
	prj.m_outputs.m_definitions.push_back(outDef);

	outDef = NANDRAD::OutputDefinition();
	outDef.m_objectListName = "Location";
	outDef.m_quantity = "SWRadDirectNormal";
	outDef.m_gridName = outGrid.m_name;
	prj.m_outputs.m_definitions.push_back(outDef);

	outDef = NANDRAD::OutputDefinition();
	outDef.m_objectListName = "Location";
	outDef.m_quantity = "SWRadDiffuseHorizontal";
	outDef.m_gridName = outGrid.m_name;
	prj.m_outputs.m_definitions.push_back(outDef);

	// *** Outputs Construction Instances ***

	outDef = NANDRAD::OutputDefinition();
	outDef.m_objectListName = "ConstructionInstances";
	outDef.m_quantity = "FluxHeatConductionA";
	outDef.m_gridName = outGrid.m_name;
	prj.m_outputs.m_definitions.push_back(outDef);

	outDef = NANDRAD::OutputDefinition();
	outDef.m_objectListName = "ConstructionInstances";
	outDef.m_quantity = "FluxHeatConductionB";
	outDef.m_gridName = outGrid.m_name;
	prj.m_outputs.m_definitions.push_back(outDef);

	outDef = NANDRAD::OutputDefinition();
	outDef.m_objectListName = "ConstructionInstances";
	outDef.m_quantity = "SurfaceTemperatureA";
	outDef.m_gridName = outGrid.m_name;
	prj.m_outputs.m_definitions.push_back(outDef);

	outDef = NANDRAD::OutputDefinition();
	outDef.m_objectListName = "ConstructionInstances";
	outDef.m_quantity = "SurfaceTemperatureB";
	outDef.m_gridName = outGrid.m_name;
	prj.m_outputs.m_definitions.push_back(outDef);

	// *** ObjLists ***

	NANDRAD::ObjectList objList;
	objList.m_name = "All Zones";
	objList.m_filterID.setEncodedString("*");
	objList.m_referenceType = NANDRAD::ModelInputReference::MRT_ZONE;
	prj.m_objectLists.push_back(objList);

	objList = NANDRAD::ObjectList();
	objList.m_name = "Location";
	objList.m_filterID.setEncodedString("*");
	objList.m_referenceType = NANDRAD::ModelInputReference::MRT_LOCATION;
	prj.m_objectLists.push_back(objList);

	objList = NANDRAD::ObjectList();
	objList.m_name = "ConstructionInstances";
	objList.m_filterID.setEncodedString("*");
	objList.m_referenceType = NANDRAD::ModelInputReference::MRT_CONSTRUCTIONINSTANCE;
	prj.m_objectLists.push_back(objList);

	if(!objListThermostatZones.m_filterID.m_ids.empty()){
		objListThermostatZones.m_referenceType = NANDRAD::ModelInputReference::MRT_ZONE;
		objListThermostatZones.m_name = nameThermostat;
		prj.m_objectLists.push_back(objListThermostatZones);

		// add thermostat model
		NANDRAD::Thermostat thermo;
		thermo.m_id = ++id;
		thermo.m_displayName = "Residential Thermostat";
		thermo.m_modelType = NANDRAD::Thermostat::MT_Scheduled;
		thermo.m_zoneObjectList = nameThermostat;
		thermo.m_para[NANDRAD::Thermostat::P_TemperatureTolerance].set("TemperatureTolerance", 0.1, IBK::Unit("K"));
		thermo.m_temperatureType = NANDRAD::Thermostat::TT_AirTemperature;
		thermo.m_controllerType = NANDRAD::Thermostat::CT_Analog;

		prj.m_models.m_thermostats.push_back(thermo);

		// add ideal heating cooling
		NANDRAD::IdealHeatingCoolingModel idealHeatCool;
		idealHeatCool.m_id = ++id;
		idealHeatCool.m_displayName = "Residential Ideal Heat Cool";
		idealHeatCool.m_zoneObjectList = nameThermostat;
		idealHeatCool.m_para[NANDRAD::IdealHeatingCoolingModel::P_MaxHeatingPowerPerArea].set("MaxHeatingPowerPerArea", 50, IBK::Unit("W/m2"));
		idealHeatCool.m_para[NANDRAD::IdealHeatingCoolingModel::P_MaxCoolingPowerPerArea].set("MaxCoolingPowerPerArea", 50, IBK::Unit("W/m2"));
		prj.m_models.m_idealHeatingCoolingModels.push_back(idealHeatCool);
	}
	if(!objListVentilationZones.m_filterID.m_ids.empty()){
		objListVentilationZones.m_referenceType = NANDRAD::ModelInputReference::MRT_ZONE;
		objListVentilationZones.m_name = nameVentilation;
		prj.m_objectLists.push_back(objListVentilationZones);

		// add ventilation model
		NANDRAD::NaturalVentilationModel natVent;
		natVent.m_id = ++id;
		natVent.m_modelType = NANDRAD::NaturalVentilationModel::MT_Scheduled;
		natVent.m_zoneObjectList = nameVentilation;
		prj.m_models.m_naturalVentilationModels.push_back(natVent);
	}

	prj.writeXML(filename);

}

void Project::test(QString pathToJson) {
	//IBK::Path filename("/home/dirk/git/EconomicEfficiencyCalculation/externals/CToolImporter/data/sim_export.json");
	//IBK::Path filename("/home/dirk/git/EconomicEfficiencyCalculation/externals/CToolImporter/data/sim_vicus_222024.json");
	//IBK::Path filename("/home/dirk/git/EconomicEfficiencyCalculation/externals/CToolImporter/data/sim_vicus_3132024.json");
//	IBK::Path filename("/home/dirk/git/EconomicEfficiencyCalculation/externals/CToolImporter/data/sim_vicus_1542024.json");
	//IBK::Path filename("/home/dirk/git/EconomicEfficiencyCalculation/externals/CToolImporter/data/sim_vicus_1642024O.json");
	//IBK::Path filename("/home/dirk/git/EconomicEfficiencyCalculation/externals/CToolImporter/data/242017sim_vicus.json");
	// IBK::Path filename("/home/dirk/git/EconomicEfficiencyCalculation/externals/CToolImporter/data/240729sim_vicus.json");
	//IBK::Path filename("/home/dirk/git/EconomicEfficiencyCalculation/externals/CToolImporter/data/sim_vicus_20240912_simple_windows.json");
	// IBK::Path filename("/home/dirk/git/EconomicEfficiencyCalculation/externals/CToolImporter/data/sim_vicus_20241220_simple_windows.json");
<<<<<<< HEAD
	IBK::Path filename(pathToJson.toStdString());
=======
	//IBK::Path filename("/home/dirk/git/EconomicEfficiencyCalculation/externals/CToolImporter/data/sim_vicus_20250707.json");
	//IBK::Path filename("/home/dirk/git/EconomicEfficiencyCalculation/externals/CToolImporter/data/sim_vicus_253107_windowsNoComment.json");	// mit fenstern
	IBK::Path filename("/home/dirk/git/EconomicEfficiencyCalculation/externals/CToolImporter/data/sim_vicus_250801.json");	// mit fenstern
>>>>>>> origin/main

	// QString filename2 = QString::fromStdString(filename.str());
	readJSon2(pathToJson);

	try {
		exportVicus(filename.withoutExtension() + ".vicus");
		exportNandrad(filename.withoutExtension() + ".nandrad");
	}  catch (IBK::Exception &ex) {
		// TODO
		int x=0;
	}
}

} // namespace CTI
