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

#include <DGNB_Tec3_1_3.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Tec3_1_3::readXML(const TiXmlElement * element) {
	FUNCID(Tec3_1_3::readXML);

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
					IAFS_BicycleTrafficAndElectricBicycles ftype = (IAFS_BicycleTrafficAndElectricBicycles)KeywordList::Enumeration("Tec3_1_3::IAFS_BicycleTrafficAndElectricBicycles", f.name());
					m_flag_IAFSBTEB[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					IAFS_MotorisedIndividualTransport ftype = (IAFS_MotorisedIndividualTransport)KeywordList::Enumeration("Tec3_1_3::IAFS_MotorisedIndividualTransport", f.name());
					m_flag_IAFSMIT[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					IAFS_IntegrationOfLoadingOrTankStations ftype = (IAFS_IntegrationOfLoadingOrTankStations)KeywordList::Enumeration("Tec3_1_3::IAFS_IntegrationOfLoadingOrTankStations", f.name());
					m_flag_IAFSILTS[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					IAFS_Agenda2030ClimateProtectionGoals ftype = (IAFS_Agenda2030ClimateProtectionGoals)KeywordList::Enumeration("Tec3_1_3::IAFS_Agenda2030ClimateProtectionGoals", f.name());
					m_flag_IAFSA2030CPG[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				if (!success)
					IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_NAME).arg(f.name()).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			else if (cName == "IBK:Parameter") {
				IBK::Parameter p;
				NANDRAD::readParameterElement(c, p);
				bool success = false;
				para_t ptype;
				try {
					ptype = (para_t)KeywordList::Enumeration("Tec3_1_3::para_t", p.name);
					m_para[ptype] = p; success = true;
				}
				catch (...) { /* intentional fail */  }
				if (!success)
					IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_NAME).arg(p.name).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			else {
				IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			c = c->NextSiblingElement();
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Tec3_1_3' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Tec3_1_3' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Tec3_1_3::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Tec3_1_3");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_IAFSBTEB; ++i) {
		if (!m_flag_IAFSBTEB[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_IAFSBTEB[i].name(), m_flag_IAFSBTEB[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_IAFSMIT; ++i) {
		if (!m_flag_IAFSMIT[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_IAFSMIT[i].name(), m_flag_IAFSMIT[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_IAFSILTS; ++i) {
		if (!m_flag_IAFSILTS[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_IAFSILTS[i].name(), m_flag_IAFSILTS[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_IAFSA2030CPG; ++i) {
		if (!m_flag_IAFSA2030CPG[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_IAFSA2030CPG[i].name(), m_flag_IAFSA2030CPG[i].isEnabled() ? "true" : "false");
		}
	}

	for (unsigned int i=0; i<NUM_P; ++i) {
		if (!m_para[i].name.empty()) {
			TiXmlElement::appendIBKParameterElement(e, m_para[i].name, m_para[i].IO_unit.name(), m_para[i].get_value(m_para[i].IO_unit));
		}
	}
	return e;
}

} // namespace DGNB
