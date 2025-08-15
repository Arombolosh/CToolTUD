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

#include <DGNB_Soc1_1_2.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Soc1_1_2::readXML(const TiXmlElement * element) {
	FUNCID(Soc1_1_2::readXML);

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
					RH_RelativeHumidityHeatingPeriod ftype = (RH_RelativeHumidityHeatingPeriod)KeywordList::Enumeration("Soc1_1_2::RH_RelativeHumidityHeatingPeriod", f.name());
					m_flag_RHHP[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					RH_RelativeHumidityCoolingPeriod ftype = (RH_RelativeHumidityCoolingPeriod)KeywordList::Enumeration("Soc1_1_2::RH_RelativeHumidityCoolingPeriod", f.name());
					m_flag_RHCP[ftype] = f; success=true;
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Soc1_1_2' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Soc1_1_2' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Soc1_1_2::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Soc1_1_2");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_RHHP; ++i) {
		if (!m_flag_RHHP[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_RHHP[i].name(), m_flag_RHHP[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_RHCP; ++i) {
		if (!m_flag_RHCP[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_RHCP[i].name(), m_flag_RHCP[i].isEnabled() ? "true" : "false");
		}
	}
	return e;
}

} // namespace DGNB
