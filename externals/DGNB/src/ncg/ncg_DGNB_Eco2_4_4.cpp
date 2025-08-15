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

#include <DGNB_Eco2_4_4.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Eco2_4_4::readXML(const TiXmlElement * element) {
	FUNCID(Eco2_4_4::readXML);

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
					SE_RatioOfUsableSpaceToGroundSpace ftype = (SE_RatioOfUsableSpaceToGroundSpace)KeywordList::Enumeration("Eco2_4_4::SE_RatioOfUsableSpaceToGroundSpace", f.name());
					m_flag_SERUSGS[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					SE_MultipleUseOfSpace ftype = (SE_MultipleUseOfSpace)KeywordList::Enumeration("Eco2_4_4::SE_MultipleUseOfSpace", f.name());
					m_flag_SEMUS[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					SE_Agenda2030BonusSufficiency ftype = (SE_Agenda2030BonusSufficiency)KeywordList::Enumeration("Eco2_4_4::SE_Agenda2030BonusSufficiency", f.name());
					m_flag_SEA2030S[ftype] = f; success=true;
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
					ptype = (para_t)KeywordList::Enumeration("Eco2_4_4::para_t", p.name);
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Eco2_4_4' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Eco2_4_4' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Eco2_4_4::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Eco2_4_4");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_SERUSGS; ++i) {
		if (!m_flag_SERUSGS[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_SERUSGS[i].name(), m_flag_SERUSGS[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_SEMUS; ++i) {
		if (!m_flag_SEMUS[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_SEMUS[i].name(), m_flag_SEMUS[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_SEA2030S; ++i) {
		if (!m_flag_SEA2030S[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_SEA2030S[i].name(), m_flag_SEA2030S[i].isEnabled() ? "true" : "false");
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
