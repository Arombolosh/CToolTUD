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

#include <DGNB_Tec1_6.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>

#include <tinyxml.h>

namespace DGNB {

void Tec1_6::readXML(const TiXmlElement * element) {
	FUNCID(Tec1_6::readXML);

	try {
		// search for mandatory elements
		// reading elements
		const TiXmlElement * c = element->FirstChildElement();
		while (c) {
			const std::string & cName = c->ValueStr();
			if (cName == "Tec1_6_1")
				m_tec1_6_1.readXML(c);
			else if (cName == "Tec1_6_2")
				m_tec1_6_2.readXML(c);
			else if (cName == "Tec1_6_3")
				m_tec1_6_3.readXML(c);
			else {
				IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			c = c->NextSiblingElement();
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Tec1_6' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Tec1_6' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Tec1_6::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Tec1_6");
	parent->LinkEndChild(e);


	m_tec1_6_1.writeXML(e);

	m_tec1_6_2.writeXML(e);

	m_tec1_6_3.writeXML(e);
	return e;
}

} // namespace DGNB
