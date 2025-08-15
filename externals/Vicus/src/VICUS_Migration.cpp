#include "VICUS_Migration.h"

#include <functional>
#include <tinyxml.h>

#include <IBK_Version.h>
#include <IBK_messages.h>
#include <IBK_Exception.h>

#include <NANDRAD_Utilities.h>
#include "VICUS_Constants.h"

namespace VICUS {

bool Migration::migrateProject(TiXmlElement * rootElement, IBK::Version & srcVersion, Project &prj) {
	FUNCID(Migration::migrateProject);
	// check for original version
	const TiXmlAttribute * versionAttrib = TiXmlAttribute::attributeByName(rootElement, "fileVersion");
	if (versionAttrib == nullptr)
		throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(rootElement->Row()).arg(
			IBK::FormatString("Missing required 'version' attribute.") ), FUNC_ID);

	std::string version = versionAttrib->ValueStr();
	unsigned int major, minor;
	bool validVersion = IBK::Version::extractMajorMinorVersionNumber(version, major, minor);
	if (!validVersion)
		throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(rootElement->Row()).arg(
			IBK::FormatString("Invalid 'version' attribute, expected <major>.<minor>.") ), FUNC_ID);

	srcVersion = IBK::Version(major, minor);
	IBK::Version currentVersion(VICUS::VERSION); // no check for validity here - we expect us as coders to use the correct format!
	if (srcVersion >= currentVersion)
		return false;

	IBK::Version newVersion = srcVersion;
	// now process the cascade
	try {

		if (newVersion == IBK::Version(1,0)) 			migrateVersion_1_0(rootElement, newVersion, prj);
		if (newVersion == IBK::Version(1,1)) 			migrateVersion_1_1(rootElement, newVersion, prj);

	} catch (IBK::Exception & ex) {
		throw IBK::Exception(ex, "Error migrating project.", FUNC_ID);
	}

	return newVersion != srcVersion;
}


void Migration::migrateVersion_1_0(TiXmlElement * rootElement, IBK::Version & newVersion, Project &/*prj*/) {
	FUNCID(Migration::migrateVersion_1_0);
	IBK::IBK_Message("Migrating project from Version 1.0 to 1.1.\n", IBK::MSG_PROGRESS, FUNC_ID);

	// TODO : modify DOM in-place
#if 0
	// example: lookup network
	TiXmlNode * node = rootElement->FirstChildElement("Project");
	node = node->FirstChildElement("GeometricNetworks");
	node = node->FirstChildElement("Network");
	node = node->FirstChildElement("Nodes");

	// take the first element, create a clone from it
	TiXmlNode * firstNetworkNode = node->FirstChild();

	std::unique_ptr<TiXmlNode> copyFirstNetworkNode( firstNetworkNode->Clone() ); // created a clone
	node->RemoveChild(node->FirstChild()); // will delete firstNetworkNode
	// now re-insert as last node
	TiXmlNode * lastChild = node->LastChild();

	node->InsertBeforeChild(lastChild, *copyFirstNetworkNode); // copies child
#endif

	// done with conversion, we are now at version 1.1
	TiXmlAttribute * versionAttrib = const_cast<TiXmlAttribute *>(TiXmlAttribute::attributeByName(rootElement, "fileVersion"));
	versionAttrib->SetValue("1.1");
	newVersion = IBK::Version(1,1);
}


void Migration::migrateVersion_1_1(TiXmlElement * rootElement, IBK::Version & newVersion, Project &prj) {
	FUNCID(Migration::migrateVersion_1_1);
	IBK::IBK_Message("Migrating project from Version 1.1 to 1.2.\n", IBK::MSG_PROGRESS, FUNC_ID);

	// TODO : modify DOM in-place
	// for example, move


	// // *** CHIILD-SURFACE MIGRATION ***
	// TiXmlNode * node = rootElement->FirstChildElement("Project");
	// node = node->FirstChildElement("Buildings");

	// In der alten Version waren die ChildSurfaces hierarchisch unter den Surfaces als Kind-XML-Tags abgelegt
	// Beispiel:
	// <Surface>
	// 	<ChildSurfaces>
	// 		<Surface>
	// 			<ChildSurfaces>
	// 				...
	// 			</ChildSurfaces>
	// 		</Surface>
	// 	</ChildSurfaces>
	// </Surface>
	//
	// in der neuen Version gibt es nur eine Ebene mit ChildSurfaces
	// <Surface>
	//     <Polygon3D></Polygon3D>
	// </Surface>


	std::map<TiXmlNode *, std::vector<TiXmlNode *>> surfacesToChilds;
	std::function<const TiXmlElement*(TiXmlNode*, std::vector<std::string>, int)> readNodes = [&](TiXmlNode * node, std::vector<std::string> names, int depth) -> const TiXmlElement * {
		TiXmlElement *c = node->FirstChildElement();
		while (c) {
			const std::string &cName = c->ValueStr();
			if (cName == names[depth]) {
				if (cName == "ChildSurfaces")
					names.push_back("Surface");
				++depth;
				if (depth > 10 && cName == "Surface")
					surfacesToChilds[c->Parent()->Parent()].push_back(c);
				const TiXmlElement *result = readNodes(c, names, depth);  // Recursively read child nodes
				if (result) return result;  // If a match is found deeper, return it
				--depth;
			}
			c = c->NextSiblingElement();
		}
		return nullptr;  // No matching node found
	};

	std::vector<std::string> names = {"Project", "Buildings", "Building", "BuildingLevels",
									  "BuildingLevel", "Rooms", "Room", "Surfaces", "Surface", "ChildSurfaces"};
	int depth = 0;
	readNodes(rootElement, names, depth);

	std::function<TiXmlNode*(TiXmlNode *node)> findRoom = [&findRoom](TiXmlNode *node) -> TiXmlNode * {
		if (node == nullptr)
			return nullptr;

		TiXmlNode *parentNode = node->Parent();
		if (parentNode->ValueStr() == "Room")
			return parentNode;
		else
			return findRoom(parentNode);
	};

	std::map<unsigned int, std::set<unsigned int>> idMapping;
	for (std::map<TiXmlNode *, std::vector<TiXmlNode *>>::iterator it = surfacesToChilds.begin(); it != surfacesToChilds.end(); ++it ) {
		TiXmlNode *parentSurfaceNode = it->first;

		// reading attributes
		unsigned int parentID;
		const TiXmlAttribute * attrib = parentSurfaceNode->ToElement()->FirstAttribute();
		while (attrib) {
			const std::string & attribName = attrib->NameStr();
			if (attribName == "id")
				parentID = NANDRAD::readPODAttributeValue<unsigned int>(parentSurfaceNode->ToElement(), attrib);
			attrib = attrib->Next();
		}

		TiXmlNode *roomNode = findRoom(parentSurfaceNode);
		// room.readXML(roomNode->ToElement());
		for (TiXmlNode *childSurface : it->second) {
			TiXmlNode *newSurf = childSurface->Clone();
			TiXmlNode *surfacesNode = roomNode->FirstChildElement("Surfaces");
			surfacesNode->LinkEndChild(newSurf->ToElement());

			// reading attributes
			const TiXmlAttribute * attrib = newSurf->ToElement()->FirstAttribute();
			unsigned int childID;
			while (attrib) {
				const std::string & attribName = attrib->NameStr();
				if (attribName == "id")
					childID = NANDRAD::readPODAttributeValue<unsigned int>(newSurf->ToElement(), attrib);
				attrib = attrib->Next();
			}

			idMapping[parentID].insert(childID);
		}
	}

	prj.m_childSurfaceMapping = idMapping;

	for (std::map<TiXmlNode *, std::vector<TiXmlNode *>>::iterator it = surfacesToChilds.begin(); it != surfacesToChilds.end(); ++it ) {
		TiXmlNode *parentSurfaceNode = it->first;
		TiXmlNode *childs = parentSurfaceNode->FirstChildElement("ChildSurfaces");
		parentSurfaceNode->RemoveChild(childs);
	}

	// done with conversion, we are now at version 1.2
	TiXmlAttribute * versionAttrib = const_cast<TiXmlAttribute *>(TiXmlAttribute::attributeByName(rootElement, "fileVersion"));
	versionAttrib->SetValue("1.2");
	newVersion = IBK::Version(1,2);
}

} // namespace VICUS
