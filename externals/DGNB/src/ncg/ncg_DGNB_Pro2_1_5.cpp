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

#include <DGNB_Pro2_1_5.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Pro2_1_5::readXML(const TiXmlElement * element) {
	FUNCID(Pro2_1_5::readXML);

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
					C_ExternalSignageAndInformation ftype = (C_ExternalSignageAndInformation)KeywordList::Enumeration("Pro2_1_5::C_ExternalSignageAndInformation", f.name());
					m_flag_CESI[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					C_ExternalCommunicationWithResidents ftype = (C_ExternalCommunicationWithResidents)KeywordList::Enumeration("Pro2_1_5::C_ExternalCommunicationWithResidents", f.name());
					m_flag_CECR[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					C_InternalSharingOfInformation ftype = (C_InternalSharingOfInformation)KeywordList::Enumeration("Pro2_1_5::C_InternalSharingOfInformation", f.name());
					m_flag_CISI[ftype] = f; success=true;
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Pro2_1_5' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Pro2_1_5' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Pro2_1_5::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Pro2_1_5");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_CESI; ++i) {
		if (!m_flag_CESI[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CESI[i].name(), m_flag_CESI[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CECR; ++i) {
		if (!m_flag_CECR[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CECR[i].name(), m_flag_CECR[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CISI; ++i) {
		if (!m_flag_CISI[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CISI[i].name(), m_flag_CISI[i].isEnabled() ? "true" : "false");
		}
	}
	return e;
}

} // namespace DGNB
