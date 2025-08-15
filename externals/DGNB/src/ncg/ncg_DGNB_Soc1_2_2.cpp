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

#include <DGNB_Soc1_2_2.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Soc1_2_2::readXML(const TiXmlElement * element) {
	FUNCID(Soc1_2_2::readXML);

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
					IH_AirChangeFrequencyOfficeEducationHotelAssemblyHealthcare ftype = (IH_AirChangeFrequencyOfficeEducationHotelAssemblyHealthcare)KeywordList::Enumeration("Soc1_2_2::IH_AirChangeFrequencyOfficeEducationHotelAssemblyHealthcare", f.name());
					m_flag_IHACFOEHAH[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					IH_AirChangeFrequencyShoppingCenterCommercialBuildingConvenienceStore ftype = (IH_AirChangeFrequencyShoppingCenterCommercialBuildingConvenienceStore)KeywordList::Enumeration("Soc1_2_2::IH_AirChangeFrequencyShoppingCenterCommercialBuildingConvenienceStore", f.name());
					m_flag_IHACFSCCBCS[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					IH_AirChangeFrequencyResidential ftype = (IH_AirChangeFrequencyResidential)KeywordList::Enumeration("Soc1_2_2::IH_AirChangeFrequencyResidential", f.name());
					m_flag_IHACFR[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					IH_AirChangeLogisticsAndProduction ftype = (IH_AirChangeLogisticsAndProduction)KeywordList::Enumeration("Soc1_2_2::IH_AirChangeLogisticsAndProduction", f.name());
					m_flag_IHACFLP[ftype] = f; success=true;
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
					ptype = (para_t)KeywordList::Enumeration("Soc1_2_2::para_t", p.name);
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Soc1_2_2' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Soc1_2_2' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Soc1_2_2::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Soc1_2_2");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_IHACFOEHAH; ++i) {
		if (!m_flag_IHACFOEHAH[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_IHACFOEHAH[i].name(), m_flag_IHACFOEHAH[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_IHACFSCCBCS; ++i) {
		if (!m_flag_IHACFSCCBCS[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_IHACFSCCBCS[i].name(), m_flag_IHACFSCCBCS[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_IHACFR; ++i) {
		if (!m_flag_IHACFR[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_IHACFR[i].name(), m_flag_IHACFR[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_IHACFLP; ++i) {
		if (!m_flag_IHACFLP[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_IHACFLP[i].name(), m_flag_IHACFLP[i].isEnabled() ? "true" : "false");
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
