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

#include <DGNB_Site1_1_3.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Site1_1_3::readXML(const TiXmlElement * element) {
	FUNCID(Site1_1_3::readXML);

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
					EEI_SurroundingNoise ftype = (EEI_SurroundingNoise)KeywordList::Enumeration("Site1_1_3::EEI_SurroundingNoise", f.name());
					m_flag_EEISN[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					EEI_AirQuality ftype = (EEI_AirQuality)KeywordList::Enumeration("Site1_1_3::EEI_AirQuality", f.name());
					m_flag_EEIAQ[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					EEI_Radon ftype = (EEI_Radon)KeywordList::Enumeration("Site1_1_3::EEI_Radon", f.name());
					m_flag_EEIR[ftype] = f; success=true;
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Site1_1_3' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Site1_1_3' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Site1_1_3::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Site1_1_3");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_EEISN; ++i) {
		if (!m_flag_EEISN[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_EEISN[i].name(), m_flag_EEISN[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_EEIAQ; ++i) {
		if (!m_flag_EEIAQ[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_EEIAQ[i].name(), m_flag_EEIAQ[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_EEIR; ++i) {
		if (!m_flag_EEIR[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_EEIR[i].name(), m_flag_EEIR[i].isEnabled() ? "true" : "false");
		}
	}
	return e;
}

} // namespace DGNB
