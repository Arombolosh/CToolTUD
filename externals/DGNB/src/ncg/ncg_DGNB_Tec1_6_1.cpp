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

#include <DGNB_Tec1_6_1.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Tec1_6_1::readXML(const TiXmlElement * element) {
	FUNCID(Tec1_6_1::readXML);

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
					CC_ProjectIncludesDemolition ftype = (CC_ProjectIncludesDemolition)KeywordList::Enumeration("Tec1_6_1::CC_ProjectIncludesDemolition", f.name());
					m_flag_CCPID161[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					SSAPPD_Analysis ftype = (SSAPPD_Analysis)KeywordList::Enumeration("Tec1_6_1::SSAPPD_Analysis", f.name());
					m_flag_SSAPPDA[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					SSAPPD_CircularEconomyBonusStockPreservationOrUse ftype = (SSAPPD_CircularEconomyBonusStockPreservationOrUse)KeywordList::Enumeration("Tec1_6_1::SSAPPD_CircularEconomyBonusStockPreservationOrUse", f.name());
					m_flag_SSAPPDCEBSPU[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					SSAPPD_DemolitionJustification ftype = (SSAPPD_DemolitionJustification)KeywordList::Enumeration("Tec1_6_1::SSAPPD_DemolitionJustification", f.name());
					m_flag_SSAPPDDJ[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					SSAPPD_DemolitionExecution ftype = (SSAPPD_DemolitionExecution)KeywordList::Enumeration("Tec1_6_1::SSAPPD_DemolitionExecution", f.name());
					m_flag_SSAPPDDE[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					SSAPPD_DemolitionAlternativeCertification ftype = (SSAPPD_DemolitionAlternativeCertification)KeywordList::Enumeration("Tec1_6_1::SSAPPD_DemolitionAlternativeCertification", f.name());
					m_flag_SSAPPDDAC[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					SSAPPD_CircularEconomyBonusReuseOnSite ftype = (SSAPPD_CircularEconomyBonusReuseOnSite)KeywordList::Enumeration("Tec1_6_1::SSAPPD_CircularEconomyBonusReuseOnSite", f.name());
					m_flag_SSAPPDCERS[ftype] = f; success=true;
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Tec1_6_1' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Tec1_6_1' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Tec1_6_1::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Tec1_6_1");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_CCPID161; ++i) {
		if (!m_flag_CCPID161[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CCPID161[i].name(), m_flag_CCPID161[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_SSAPPDA; ++i) {
		if (!m_flag_SSAPPDA[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_SSAPPDA[i].name(), m_flag_SSAPPDA[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_SSAPPDCEBSPU; ++i) {
		if (!m_flag_SSAPPDCEBSPU[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_SSAPPDCEBSPU[i].name(), m_flag_SSAPPDCEBSPU[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_SSAPPDDJ; ++i) {
		if (!m_flag_SSAPPDDJ[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_SSAPPDDJ[i].name(), m_flag_SSAPPDDJ[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_SSAPPDDE; ++i) {
		if (!m_flag_SSAPPDDE[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_SSAPPDDE[i].name(), m_flag_SSAPPDDE[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_SSAPPDDAC; ++i) {
		if (!m_flag_SSAPPDDAC[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_SSAPPDDAC[i].name(), m_flag_SSAPPDDAC[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_SSAPPDCERS; ++i) {
		if (!m_flag_SSAPPDCERS[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_SSAPPDCERS[i].name(), m_flag_SSAPPDCERS[i].isEnabled() ? "true" : "false");
		}
	}
	return e;
}

} // namespace DGNB
