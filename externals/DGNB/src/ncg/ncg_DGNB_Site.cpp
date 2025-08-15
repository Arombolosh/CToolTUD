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

#include <DGNB_Site.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Site::readXML(const TiXmlElement * element) {
	FUNCID(Site::readXML);

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
					pwtype = (para_weights)KeywordList::Enumeration("Site::para_weights", p.name);
					m_para_PW[pwtype] = p; success = true;
				}
				catch (...) { /* intentional fail */  }
				para_goals pgtype;
				try {
					pgtype = (para_goals)KeywordList::Enumeration("Site::para_goals", p.name);
					m_para_PG[pgtype] = p; success = true;
				}
				catch (...) { /* intentional fail */  }
				if (!success)
					IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_NAME).arg(p.name).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			else if (cName == "Site1_1")
				m_site1_1.readXML(c);
			else if (cName == "Site1_3")
				m_site1_3.readXML(c);
			else if (cName == "Site1_4")
				m_site1_4.readXML(c);
			else {
				IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			c = c->NextSiblingElement();
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Site' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Site' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Site::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Site");
	parent->LinkEndChild(e);


	m_site1_1.writeXML(e);

	m_site1_3.writeXML(e);

	m_site1_4.writeXML(e);

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
