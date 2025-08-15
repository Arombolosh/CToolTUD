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

#include <DGNB_Eco2_7_1.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Eco2_7_1::readXML(const TiXmlElement * element) {
	FUNCID(Eco2_7_1::readXML);

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
					DCB_CurrentPlanningData ftype = (DCB_CurrentPlanningData)KeywordList::Enumeration("Eco2_7_1::DCB_CurrentPlanningData", f.name());
					m_flag_DCBCPD[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					DCB_CompleteSustainabilityBuildingDocumentation ftype = (DCB_CompleteSustainabilityBuildingDocumentation)KeywordList::Enumeration("Eco2_7_1::DCB_CompleteSustainabilityBuildingDocumentation", f.name());
					m_flag_DCBCSBD[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					DCB_CircularEconomyDataBasisForUrbanMines ftype = (DCB_CircularEconomyDataBasisForUrbanMines)KeywordList::Enumeration("Eco2_7_1::DCB_CircularEconomyDataBasisForUrbanMines", f.name());
					m_flag_DCBCEBDBUM[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					DCB_Agenda2030DigitalFootprint ftype = (DCB_Agenda2030DigitalFootprint)KeywordList::Enumeration("Eco2_7_1::DCB_Agenda2030DigitalFootprint", f.name());
					m_flag_DCBA2030DF[ftype] = f; success=true;
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Eco2_7_1' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Eco2_7_1' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Eco2_7_1::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Eco2_7_1");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_DCBCPD; ++i) {
		if (!m_flag_DCBCPD[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_DCBCPD[i].name(), m_flag_DCBCPD[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_DCBCSBD; ++i) {
		if (!m_flag_DCBCSBD[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_DCBCSBD[i].name(), m_flag_DCBCSBD[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_DCBCEDBUM; ++i) {
		if (!m_flag_DCBCEBDBUM[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_DCBCEBDBUM[i].name(), m_flag_DCBCEBDBUM[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_DCBA2030DF; ++i) {
		if (!m_flag_DCBA2030DF[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_DCBA2030DF[i].name(), m_flag_DCBA2030DF[i].isEnabled() ? "true" : "false");
		}
	}
	return e;
}

} // namespace DGNB
