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

#include <DGNB_Tec1_6_2.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Tec1_6_2::readXML(const TiXmlElement * element) {
	FUNCID(Tec1_6_2::readXML);

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
					CC_ProjectIncludesDemolition ftype = (CC_ProjectIncludesDemolition)KeywordList::Enumeration("Tec1_6_2::CC_ProjectIncludesDemolition", f.name());
					m_flag_CCPID162[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CCCP_GoalAndFocusDefinition ftype = (CCCP_GoalAndFocusDefinition)KeywordList::Enumeration("Tec1_6_2::CCCP_GoalAndFocusDefinition", f.name());
					m_flag_CCCPGFD[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CCCP_ProjectRelatedCircularDesignConceptsEarlyPhase ftype = (CCCP_ProjectRelatedCircularDesignConceptsEarlyPhase)KeywordList::Enumeration("Tec1_6_2::CCCP_ProjectRelatedCircularDesignConceptsEarlyPhase", f.name());
					m_flag_CCCPPRCDCEP[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CCCP_ProjectRelatedCircularDesignConceptsApprovalAndExecutionPhase ftype = (CCCP_ProjectRelatedCircularDesignConceptsApprovalAndExecutionPhase)KeywordList::Enumeration("Tec1_6_2::CCCP_ProjectRelatedCircularDesignConceptsApprovalAndExecutionPhase", f.name());
					m_flag_CCCPPRCDCAEP[ftype] = f; success=true;
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Tec1_6_2' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Tec1_6_2' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Tec1_6_2::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Tec1_6_2");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_CCPID162; ++i) {
		if (!m_flag_CCPID162[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CCPID162[i].name(), m_flag_CCPID162[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CCCPGFD; ++i) {
		if (!m_flag_CCCPGFD[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CCCPGFD[i].name(), m_flag_CCCPGFD[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CCCPPRCDCEP; ++i) {
		if (!m_flag_CCCPPRCDCEP[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CCCPPRCDCEP[i].name(), m_flag_CCCPPRCDCEP[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CCCPPRCDCAEP; ++i) {
		if (!m_flag_CCCPPRCDCAEP[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CCCPPRCDCAEP[i].name(), m_flag_CCCPPRCDCAEP[i].isEnabled() ? "true" : "false");
		}
	}
	return e;
}

} // namespace DGNB
