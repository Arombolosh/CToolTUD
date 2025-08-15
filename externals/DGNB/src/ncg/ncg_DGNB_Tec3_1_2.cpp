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

#include <DGNB_Tec3_1_2.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Tec3_1_2::readXML(const TiXmlElement * element) {
	FUNCID(Tec3_1_2::readXML);

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
					I_PedestrianInfrastructure ftype = (I_PedestrianInfrastructure)KeywordList::Enumeration("Tec3_1_2::I_PedestrianInfrastructure", f.name());
					m_flag_IPI[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					I_BicycleInfrastructure ftype = (I_BicycleInfrastructure)KeywordList::Enumeration("Tec3_1_2::I_BicycleInfrastructure", f.name());
					m_flag_IBI[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					I_MotorisedIndividualTransport ftype = (I_MotorisedIndividualTransport)KeywordList::Enumeration("Tec3_1_2::I_MotorisedIndividualTransport", f.name());
					m_flag_IMIT[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					I_Agenda2030MobilityManagementConcept ftype = (I_Agenda2030MobilityManagementConcept)KeywordList::Enumeration("Tec3_1_2::I_Agenda2030MobilityManagementConcept", f.name());
					m_flag_IA2030MMC[ftype] = f; success=true;
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Tec3_1_2' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Tec3_1_2' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Tec3_1_2::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Tec3_1_2");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_IPI; ++i) {
		if (!m_flag_IPI[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_IPI[i].name(), m_flag_IPI[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_IBI; ++i) {
		if (!m_flag_IBI[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_IBI[i].name(), m_flag_IBI[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_IMIT; ++i) {
		if (!m_flag_IMIT[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_IMIT[i].name(), m_flag_IMIT[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_IA2030MMC; ++i) {
		if (!m_flag_IA2030MMC[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_IA2030MMC[i].name(), m_flag_IA2030MMC[i].isEnabled() ? "true" : "false");
		}
	}
	return e;
}

} // namespace DGNB
