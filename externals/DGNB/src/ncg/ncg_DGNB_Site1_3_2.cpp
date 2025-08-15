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

#include <DGNB_Site1_3_2.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Site1_3_2::readXML(const TiXmlElement * element) {
	FUNCID(Site1_3_2::readXML);

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
					PT_Stations ftype = (PT_Stations)KeywordList::Enumeration("Site1_3_2::PT_Stations", f.name());
					m_flag_PTS[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					PT_DistanceToNextTrainStationWithAtLeastHourlyDepartures ftype = (PT_DistanceToNextTrainStationWithAtLeastHourlyDepartures)KeywordList::Enumeration("Site1_3_2::PT_DistanceToNextTrainStationWithAtLeastHourlyDepartures", f.name());
					m_flag_PTDTSHD[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					PT_Intervals ftype = (PT_Intervals)KeywordList::Enumeration("Site1_3_2::PT_Intervals", f.name());
					m_flag_PTI[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					PT_RelationToBuilding ftype = (PT_RelationToBuilding)KeywordList::Enumeration("Site1_3_2::PT_RelationToBuilding", f.name());
					m_flag_PTRB[ftype] = f; success=true;
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Site1_3_2' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Site1_3_2' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Site1_3_2::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Site1_3_2");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_PTS; ++i) {
		if (!m_flag_PTS[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_PTS[i].name(), m_flag_PTS[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_PTDTSHD; ++i) {
		if (!m_flag_PTDTSHD[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_PTDTSHD[i].name(), m_flag_PTDTSHD[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_PTI; ++i) {
		if (!m_flag_PTI[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_PTI[i].name(), m_flag_PTI[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_PTRB; ++i) {
		if (!m_flag_PTRB[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_PTRB[i].name(), m_flag_PTRB[i].isEnabled() ? "true" : "false");
		}
	}
	return e;
}

} // namespace DGNB
