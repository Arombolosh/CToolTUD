/*	The NANDRAD data model library.

	Copyright (c) 2012-today, Institut für Bauklimatik, TU Dresden, Germany

	Primary authors:
	  Andreas Nicolai  <andreas.nicolai -[at]- tu-dresden.de>
	  Anne Paepcke     <anne.paepcke -[at]- tu-dresden.de>

	This library is part of SIM-VICUS (https://github.com/ghorwin/SIM-VICUS)

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 3 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.
*/

#include <DGNB_Site1_3_3.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Site1_3_3::readXML(const TiXmlElement * element) {
	FUNCID(Site1_3_3::readXML);

	try {
		// search for mandatory elements
		// reading elements
		const TiXmlElement * c = element->FirstChildElement();
		while (c) {
			const std::string & cName = c->ValueStr();
			if (cName == "IBK:Flag") {
				IBK::Flag f;
				NANDRAD::readFlagElement(c, f);
				bool success = false;
				try {
					BT_CycleTrackWithin500Meters ftype = (BT_CycleTrackWithin500Meters)KeywordList::Enumeration("Site1_3_3::BT_CycleTrackWithin500Meters", f.name());
					m_flag_BTCT500M[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					BT_Connection ftype = (BT_Connection)KeywordList::Enumeration("Site1_3_3::BT_Connection", f.name());
					m_flag_BTC[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					BT_RelationToBuilding ftype = (BT_RelationToBuilding)KeywordList::Enumeration("Site1_3_3::BT_RelationToBuilding", f.name());
					m_flag_BTRB[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				if (!success)
					IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_NAME).arg(f.name()).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			else {
				IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			c = c->NextSiblingElement();
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Site1_3_3' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Site1_3_3' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Site1_3_3::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Site1_3_3");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_BTCT500M; ++i) {
		if (!m_flag_BTCT500M[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_BTCT500M[i].name(), m_flag_BTCT500M[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_BTC; ++i) {
		if (!m_flag_BTC[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_BTC[i].name(), m_flag_BTC[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_BTRB; ++i) {
		if (!m_flag_BTRB[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_BTRB[i].name(), m_flag_BTRB[i].isEnabled() ? "true" : "false");
		}
	}
	return e;
}

} // namespace DGNB
