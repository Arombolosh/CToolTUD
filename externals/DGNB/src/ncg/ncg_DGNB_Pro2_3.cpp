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

#include <DGNB_Pro2_3.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>

#include <tinyxml.h>

namespace DGNB {

void Pro2_3::readXML(const TiXmlElement * element) {
	FUNCID(Pro2_3::readXML);

	try {
		// search for mandatory elements
		// reading elements
		const TiXmlElement * c = element->FirstChildElement();
		while (c) {
			const std::string & cName = c->ValueStr();
			if (cName == "Pro2_3_1")
				m_pro2_3_1.readXML(c);
			else if (cName == "Pro2_3_2")
				m_pro2_3_2.readXML(c);
			else if (cName == "Pro2_3_3")
				m_pro2_3_3.readXML(c);
			else if (cName == "Pro2_3_4")
				m_pro2_3_4.readXML(c);
			else if (cName == "Pro2_3_5")
				m_pro2_3_5.readXML(c);
			else if (cName == "Pro2_3_6")
				m_pro2_3_6.readXML(c);
			else if (cName == "Pro2_3_7")
				m_pro2_3_7.readXML(c);
			else {
				IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			c = c->NextSiblingElement();
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Pro2_3' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Pro2_3' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Pro2_3::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Pro2_3");
	parent->LinkEndChild(e);


	m_pro2_3_1.writeXML(e);

	m_pro2_3_2.writeXML(e);

	m_pro2_3_3.writeXML(e);

	m_pro2_3_4.writeXML(e);

	m_pro2_3_5.writeXML(e);

	m_pro2_3_6.writeXML(e);

	m_pro2_3_7.writeXML(e);
	return e;
}

} // namespace DGNB
