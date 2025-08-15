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

#include <DGNB_Eco2_6_3.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Eco2_6_3::readXML(const TiXmlElement * element) {
	FUNCID(Eco2_6_3::readXML);

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
					MAFERS_CompensationMeasuresAirQuality ftype = (MAFERS_CompensationMeasuresAirQuality)KeywordList::Enumeration("Eco2_6_3::MAFERS_CompensationMeasuresAirQuality", f.name());
					m_flag_ASBCSA[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					MAFERS_CompensationMeasuresNoise ftype = (MAFERS_CompensationMeasuresNoise)KeywordList::Enumeration("Eco2_6_3::MAFERS_CompensationMeasuresNoise", f.name());
					m_flag_MAFERSCMN[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					MAFERS_RadonRiskReduction ftype = (MAFERS_RadonRiskReduction)KeywordList::Enumeration("Eco2_6_3::MAFERS_RadonRiskReduction", f.name());
					m_flag_MAFERSRRR[ftype] = f; success=true;
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Eco2_6_3' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Eco2_6_3' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Eco2_6_3::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Eco2_6_3");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_ASBCSA; ++i) {
		if (!m_flag_ASBCSA[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_ASBCSA[i].name(), m_flag_ASBCSA[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_MAFERSCMN; ++i) {
		if (!m_flag_MAFERSCMN[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_MAFERSCMN[i].name(), m_flag_MAFERSCMN[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_MAFERSRRR; ++i) {
		if (!m_flag_MAFERSRRR[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_MAFERSRRR[i].name(), m_flag_MAFERSRRR[i].isEnabled() ? "true" : "false");
		}
	}
	return e;
}

} // namespace DGNB
