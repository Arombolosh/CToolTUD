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

#include <DGNB_Economy.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Economy::readXML(const TiXmlElement * element) {
	FUNCID(Economy::readXML);

	try {
		// search for mandatory elements
		// reading elements
		const TiXmlElement * c = element->FirstChildElement();
		while (c) {
			const std::string & cName = c->ValueStr();
			if (cName == "IBK:Parameter") {
				IBK::Parameter p;
				NANDRAD::readParameterElement(c, p);
				bool success = false;
				para_weights pwtype;
				try {
					pwtype = (para_weights)KeywordList::Enumeration("Economy::para_weights", p.name);
					m_para_PW[pwtype] = p; success = true;
				}
				catch (...) { /* intentional fail */  }
				para_goals pgtype;
				try {
					pgtype = (para_goals)KeywordList::Enumeration("Economy::para_goals", p.name);
					m_para_PG[pgtype] = p; success = true;
				}
				catch (...) { /* intentional fail */  }
				if (!success)
					IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_NAME).arg(p.name).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			else if (cName == "Eco1_1")
				m_eco1_1.readXML(c);
			else if (cName == "Eco2_4")
				m_eco2_4.readXML(c);
			else if (cName == "Eco2_6")
				m_eco2_6.readXML(c);
			else if (cName == "Eco2_7")
				m_eco2_7.readXML(c);
			else {
				IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			c = c->NextSiblingElement();
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Economy' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Economy' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Economy::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Economy");
	parent->LinkEndChild(e);


	m_eco1_1.writeXML(e);

	m_eco2_4.writeXML(e);

	m_eco2_6.writeXML(e);

	m_eco2_7.writeXML(e);

	for (unsigned int i=0; i<NUM_PW; ++i) {
		if (!m_para_PW[i].name.empty()) {
			TiXmlElement::appendIBKParameterElement(e, m_para_PW[i].name, m_para_PW[i].IO_unit.name(), m_para_PW[i].get_value(m_para_PW[i].IO_unit));
		}
	}

	for (unsigned int i=0; i<NUM_PG; ++i) {
		if (!m_para_PG[i].name.empty()) {
			TiXmlElement::appendIBKParameterElement(e, m_para_PG[i].name, m_para_PG[i].IO_unit.name(), m_para_PG[i].get_value(m_para_PG[i].IO_unit));
		}
	}
	return e;
}

} // namespace DGNB
