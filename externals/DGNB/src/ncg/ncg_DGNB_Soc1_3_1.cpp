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

#include <DGNB_Soc1_3_1.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Soc1_3_1::readXML(const TiXmlElement * element) {
	FUNCID(Soc1_3_1::readXML);

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
					ORSR_HealthcareHotelAssembly ftype = (ORSR_HealthcareHotelAssembly)KeywordList::Enumeration("Soc1_3_1::ORSR_HealthcareHotelAssembly", f.name());
					m_flag_ORSRHcHA[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					ORSR_Office ftype = (ORSR_Office)KeywordList::Enumeration("Soc1_3_1::ORSR_Office", f.name());
					m_flag_ORSRO[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					ORSR_Residential ftype = (ORSR_Residential)KeywordList::Enumeration("Soc1_3_1::ORSR_Residential", f.name());
					m_flag_ORSRR[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					BAM_OfficeEducationHotelAssemblyHealthcareResidential ftype = (BAM_OfficeEducationHotelAssemblyHealthcareResidential)KeywordList::Enumeration("Soc1_3_1::BAM_OfficeEducationHotelAssemblyHealthcareResidential", f.name());
					m_flag_BAMOEHAHcR[ftype] = f; success=true;
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Soc1_3_1' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Soc1_3_1' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Soc1_3_1::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Soc1_3_1");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_ORSRHcHA; ++i) {
		if (!m_flag_ORSRHcHA[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_ORSRHcHA[i].name(), m_flag_ORSRHcHA[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_ORSRO; ++i) {
		if (!m_flag_ORSRO[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_ORSRO[i].name(), m_flag_ORSRO[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_ORSRR; ++i) {
		if (!m_flag_ORSRR[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_ORSRR[i].name(), m_flag_ORSRR[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_BAMOEHAHcR; ++i) {
		if (!m_flag_BAMOEHAHcR[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_BAMOEHAHcR[i].name(), m_flag_BAMOEHAHcR[i].isEnabled() ? "true" : "false");
		}
	}
	return e;
}

} // namespace DGNB
