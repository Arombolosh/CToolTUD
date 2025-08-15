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

#include <DGNB_Env1_1_1.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Env1_1_1::readXML(const TiXmlElement * element) {
	FUNCID(Env1_1_1::readXML);

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
					CO2EarlyStage_OperatingEvaluation ftype = (CO2EarlyStage_OperatingEvaluation)KeywordList::Enumeration("Env1_1_1::CO2EarlyStage_OperatingEvaluation", f.name());
					m_flag_ESOE[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CO2EarlyStage_FurtherVariants ftype = (CO2EarlyStage_FurtherVariants)KeywordList::Enumeration("Env1_1_1::CO2EarlyStage_FurtherVariants", f.name());
					m_flag_ESFV[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CO2PlanningStage_OperatingEvaluation ftype = (CO2PlanningStage_OperatingEvaluation)KeywordList::Enumeration("Env1_1_1::CO2PlanningStage_OperatingEvaluation", f.name());
					m_flag_PSOE[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CO2PlanningStage_FurtherVariants ftype = (CO2PlanningStage_FurtherVariants)KeywordList::Enumeration("Env1_1_1::CO2PlanningStage_FurtherVariants", f.name());
					m_flag_PSFV[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CO2PlanningStage_EmissionOptimization ftype = (CO2PlanningStage_EmissionOptimization)KeywordList::Enumeration("Env1_1_1::CO2PlanningStage_EmissionOptimization", f.name());
					m_flag_PSEO[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CO2Agenda2030_IntegrationOfPreexistingBuilding ftype = (CO2Agenda2030_IntegrationOfPreexistingBuilding)KeywordList::Enumeration("Env1_1_1::CO2Agenda2030_IntegrationOfPreexistingBuilding", f.name());
					m_flag_A2030IPB[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CO2Agenda2030MobilityOptimization ftype = (CO2Agenda2030MobilityOptimization)KeywordList::Enumeration("Env1_1_1::CO2Agenda2030MobilityOptimization", f.name());
					m_flag_A2030MO[ftype] = f; success=true;
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Env1_1_1' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Env1_1_1' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Env1_1_1::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Env1_1_1");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_CO2ESOE; ++i) {
		if (!m_flag_ESOE[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_ESOE[i].name(), m_flag_ESOE[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CO2ESFV; ++i) {
		if (!m_flag_ESFV[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_ESFV[i].name(), m_flag_ESFV[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CO2PSOE; ++i) {
		if (!m_flag_PSOE[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_PSOE[i].name(), m_flag_PSOE[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CO2PSFV; ++i) {
		if (!m_flag_PSFV[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_PSFV[i].name(), m_flag_PSFV[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CO2PSEO; ++i) {
		if (!m_flag_PSEO[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_PSEO[i].name(), m_flag_PSEO[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CO2A2030IPB; ++i) {
		if (!m_flag_A2030IPB[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_A2030IPB[i].name(), m_flag_A2030IPB[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CO2A2030MO; ++i) {
		if (!m_flag_A2030MO[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_A2030MO[i].name(), m_flag_A2030MO[i].isEnabled() ? "true" : "false");
		}
	}
	return e;
}

} // namespace DGNB
