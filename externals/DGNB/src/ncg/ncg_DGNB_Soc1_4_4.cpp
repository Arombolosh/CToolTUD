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

#include <DGNB_Soc1_4_4.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Soc1_4_4::readXML(const TiXmlElement * element) {
	FUNCID(Soc1_4_4::readXML);

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
					DGS_OfficeEducationAssembly1And2Healthcare ftype = (DGS_OfficeEducationAssembly1And2Healthcare)KeywordList::Enumeration("Soc1_4_4::DGS_OfficeEducationAssembly1And2Healthcare", f.name());
					m_flag_DGSOEA12Hc[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					DGS_ConvenienceStore ftype = (DGS_ConvenienceStore)KeywordList::Enumeration("Soc1_4_4::DGS_ConvenienceStore", f.name());
					m_flag_DGSCS[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					DGS_Logistics ftype = (DGS_Logistics)KeywordList::Enumeration("Soc1_4_4::DGS_Logistics", f.name());
					m_flag_DGSL[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					DGS_Production ftype = (DGS_Production)KeywordList::Enumeration("Soc1_4_4::DGS_Production", f.name());
					m_flag_DGSP[ftype] = f; success=true;
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
					ptype = (para_t)KeywordList::Enumeration("Soc1_4_4::para_t", p.name);
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Soc1_4_4' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Soc1_4_4' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Soc1_4_4::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Soc1_4_4");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_DGSOEA12Hc; ++i) {
		if (!m_flag_DGSOEA12Hc[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_DGSOEA12Hc[i].name(), m_flag_DGSOEA12Hc[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_DGSCS; ++i) {
		if (!m_flag_DGSCS[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_DGSCS[i].name(), m_flag_DGSCS[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_DGSL; ++i) {
		if (!m_flag_DGSL[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_DGSL[i].name(), m_flag_DGSL[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_DGSP; ++i) {
		if (!m_flag_DGSP[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_DGSP[i].name(), m_flag_DGSP[i].isEnabled() ? "true" : "false");
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
