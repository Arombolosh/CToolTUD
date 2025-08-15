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

#include <DGNB_Env1_2_1.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Env1_2_1::readXML(const TiXmlElement * element) {
	FUNCID(Env1_2_1::readXML);

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
					EFM_A ftype = (EFM_A)KeywordList::Enumeration("Env1_2_1::EFM_A", f.name());
					m_flag_EFMA[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					EFM_BResidentialCommercial ftype = (EFM_BResidentialCommercial)KeywordList::Enumeration("Env1_2_1::EFM_BResidentialCommercial", f.name());
					m_flag_EFMBRC[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					EFM_BShoppingCenter ftype = (EFM_BShoppingCenter)KeywordList::Enumeration("Env1_2_1::EFM_BShoppingCenter", f.name());
					m_flag_EFMBSC[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					EFM_Agenda2030 ftype = (EFM_Agenda2030)KeywordList::Enumeration("Env1_2_1::EFM_Agenda2030", f.name());
					m_flag_EFMA2030[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					EFM_ExtraPointsForQS123 ftype = (EFM_ExtraPointsForQS123)KeywordList::Enumeration("Env1_2_1::EFM_ExtraPointsForQS123", f.name());
					m_flag_EFMEPQS123[ftype] = f; success=true;
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
					ptype = (para_t)KeywordList::Enumeration("Env1_2_1::para_t", p.name);
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Env1_2_1' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Env1_2_1' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Env1_2_1::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Env1_2_1");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_EFMA; ++i) {
		if (!m_flag_EFMA[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_EFMA[i].name(), m_flag_EFMA[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_EFMBRC; ++i) {
		if (!m_flag_EFMBRC[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_EFMBRC[i].name(), m_flag_EFMBRC[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_EFMBSC; ++i) {
		if (!m_flag_EFMBSC[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_EFMBSC[i].name(), m_flag_EFMBSC[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_EFMA2030; ++i) {
		if (!m_flag_EFMA2030[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_EFMA2030[i].name(), m_flag_EFMA2030[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_EFMEPQS123; ++i) {
		if (!m_flag_EFMEPQS123[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_EFMEPQS123[i].name(), m_flag_EFMEPQS123[i].isEnabled() ? "true" : "false");
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
