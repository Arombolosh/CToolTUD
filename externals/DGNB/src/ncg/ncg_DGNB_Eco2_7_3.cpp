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

#include <DGNB_Eco2_7_3.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Eco2_7_3::readXML(const TiXmlElement * element) {
	FUNCID(Eco2_7_3::readXML);

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
					PPBIM_Preparation ftype = (PPBIM_Preparation)KeywordList::Enumeration("Eco2_7_3::PPBIM_Preparation", f.name());
					m_flag_PPBIMP[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					PPBIM_Creation ftype = (PPBIM_Creation)KeywordList::Enumeration("Eco2_7_3::PPBIM_Creation", f.name());
					m_flag_PPBIMC[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					PPBIM_SustainabilityOptimisationWithBIM ftype = (PPBIM_SustainabilityOptimisationWithBIM)KeywordList::Enumeration("Eco2_7_3::PPBIM_SustainabilityOptimisationWithBIM", f.name());
					m_flag_PPBIMSO[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					PPBIM_CircularEconomyBIM2FMOperatorConcept ftype = (PPBIM_CircularEconomyBIM2FMOperatorConcept)KeywordList::Enumeration("Eco2_7_3::PPBIM_CircularEconomyBIM2FMOperatorConcept", f.name());
					m_flag_PPBIMCEBIM2FMOC[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					PPBIM_Agenda2030SustainabilityCheck ftype = (PPBIM_Agenda2030SustainabilityCheck)KeywordList::Enumeration("Eco2_7_3::PPBIM_Agenda2030SustainabilityCheck", f.name());
					m_flag_PPBIMA2030SC[ftype] = f; success=true;
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Eco2_7_3' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Eco2_7_3' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Eco2_7_3::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Eco2_7_3");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_PPBIMP; ++i) {
		if (!m_flag_PPBIMP[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_PPBIMP[i].name(), m_flag_PPBIMP[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_PPBIMC; ++i) {
		if (!m_flag_PPBIMC[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_PPBIMC[i].name(), m_flag_PPBIMC[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_PPBIMSO; ++i) {
		if (!m_flag_PPBIMSO[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_PPBIMSO[i].name(), m_flag_PPBIMSO[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_PPBIMCEBIM2FMOC; ++i) {
		if (!m_flag_PPBIMCEBIM2FMOC[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_PPBIMCEBIM2FMOC[i].name(), m_flag_PPBIMCEBIM2FMOC[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_PPBIMA2030SC; ++i) {
		if (!m_flag_PPBIMA2030SC[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_PPBIMA2030SC[i].name(), m_flag_PPBIMA2030SC[i].isEnabled() ? "true" : "false");
		}
	}
	return e;
}

} // namespace DGNB
