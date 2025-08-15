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

#include <DGNB_Tec1_4_4.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Tec1_4_4::readXML(const TiXmlElement * element) {
	FUNCID(Tec1_4_4::readXML);

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
					IS_StateAndUpgradability ftype = (IS_StateAndUpgradability)KeywordList::Enumeration("Tec1_4_4::IS_StateAndUpgradability", f.name());
					m_flag_ISSU[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					IS_IntegratedFunctionsInSuperordinateSystems ftype = (IS_IntegratedFunctionsInSuperordinateSystems)KeywordList::Enumeration("Tec1_4_4::IS_IntegratedFunctionsInSuperordinateSystems", f.name());
					m_flag_ISIFSS[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					IS_PlanningOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings ftype = (IS_PlanningOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings)KeywordList::Enumeration("Tec1_4_4::IS_PlanningOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings", f.name());
					m_flag_ISPITSMQDS[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					IS_ImplementationOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings ftype = (IS_ImplementationOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings)KeywordList::Enumeration("Tec1_4_4::IS_ImplementationOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings", f.name());
					m_flag_ISIITSMQDS[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsQuarterSolution ftype = (IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsQuarterSolution)KeywordList::Enumeration("Tec1_4_4::IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsQuarterSolution", f.name());
					m_flag_ISIEIQDSQS[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsNetworkableEnergySystem ftype = (IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsNetworkableEnergySystem)KeywordList::Enumeration("Tec1_4_4::IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsNetworkableEnergySystem", f.name());
					m_flag_ISIITSMQNES[ftype] = f; success=true;
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Tec1_4_4' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Tec1_4_4' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Tec1_4_4::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Tec1_4_4");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_ISSU; ++i) {
		if (!m_flag_ISSU[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_ISSU[i].name(), m_flag_ISSU[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_ISIFSS; ++i) {
		if (!m_flag_ISIFSS[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_ISIFSS[i].name(), m_flag_ISIFSS[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_ISPITSMQDS; ++i) {
		if (!m_flag_ISPITSMQDS[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_ISPITSMQDS[i].name(), m_flag_ISPITSMQDS[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_ISIITSMQDS; ++i) {
		if (!m_flag_ISIITSMQDS[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_ISIITSMQDS[i].name(), m_flag_ISIITSMQDS[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_ISIEIQDSQS; ++i) {
		if (!m_flag_ISIEIQDSQS[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_ISIEIQDSQS[i].name(), m_flag_ISIEIQDSQS[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_ISIITSMQNES; ++i) {
		if (!m_flag_ISIITSMQNES[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_ISIITSMQNES[i].name(), m_flag_ISIITSMQNES[i].isEnabled() ? "true" : "false");
		}
	}
	return e;
}

} // namespace DGNB
