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

#include <DGNB_Pro2_1_6.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Pro2_1_6::readXML(const TiXmlElement * element) {
	FUNCID(Pro2_1_6::readXML);

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
					RCWU_DataTransparency ftype = (RCWU_DataTransparency)KeywordList::Enumeration("Pro2_1_6::RCWU_DataTransparency", f.name());
					m_flag_RCWUDT[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					RCWU_Concept ftype = (RCWU_Concept)KeywordList::Enumeration("Pro2_1_6::RCWU_Concept", f.name());
					m_flag_RCWUC[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					RCWU_InstructionOfOperators ftype = (RCWU_InstructionOfOperators)KeywordList::Enumeration("Pro2_1_6::RCWU_InstructionOfOperators", f.name());
					m_flag_RCWUIO[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					RCWU_ExaminationOfImplementation ftype = (RCWU_ExaminationOfImplementation)KeywordList::Enumeration("Pro2_1_6::RCWU_ExaminationOfImplementation", f.name());
					m_flag_RCWUEI[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					RCEU_DataTransparency ftype = (RCEU_DataTransparency)KeywordList::Enumeration("Pro2_1_6::RCEU_DataTransparency", f.name());
					m_flag_RCEUDT[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					RCEU_Concept ftype = (RCEU_Concept)KeywordList::Enumeration("Pro2_1_6::RCEU_Concept", f.name());
					m_flag_RCEUC[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					RCEU_InstructionOfOperators ftype = (RCEU_InstructionOfOperators)KeywordList::Enumeration("Pro2_1_6::RCEU_InstructionOfOperators", f.name());
					m_flag_RCEUIO[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					RCEU_ExaminationOfImplementation ftype = (RCEU_ExaminationOfImplementation)KeywordList::Enumeration("Pro2_1_6::RCEU_ExaminationOfImplementation", f.name());
					m_flag_RCEUEI[ftype] = f; success=true;
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Pro2_1_6' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Pro2_1_6' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Pro2_1_6::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Pro2_1_6");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_RCWUDT; ++i) {
		if (!m_flag_RCWUDT[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_RCWUDT[i].name(), m_flag_RCWUDT[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_RCWUC; ++i) {
		if (!m_flag_RCWUC[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_RCWUC[i].name(), m_flag_RCWUC[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_RCWUIO; ++i) {
		if (!m_flag_RCWUIO[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_RCWUIO[i].name(), m_flag_RCWUIO[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_RCWUEI; ++i) {
		if (!m_flag_RCWUEI[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_RCWUEI[i].name(), m_flag_RCWUEI[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_RCEUDT; ++i) {
		if (!m_flag_RCEUDT[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_RCEUDT[i].name(), m_flag_RCEUDT[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_RCEUC; ++i) {
		if (!m_flag_RCEUC[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_RCEUC[i].name(), m_flag_RCEUC[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_RCEUIO; ++i) {
		if (!m_flag_RCEUIO[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_RCEUIO[i].name(), m_flag_RCEUIO[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_RCEUEI; ++i) {
		if (!m_flag_RCEUEI[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_RCEUEI[i].name(), m_flag_RCEUEI[i].isEnabled() ? "true" : "false");
		}
	}
	return e;
}

} // namespace DGNB
