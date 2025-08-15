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

#include <DGNB_Env1_3_2.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Env1_3_2::readXML(const TiXmlElement * element) {
	FUNCID(Env1_3_2::readXML);

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
					RRM_CompanyResponsibilityForResourceManagement ftype = (RRM_CompanyResponsibilityForResourceManagement)KeywordList::Enumeration("Env1_3_2::RRM_CompanyResponsibilityForResourceManagement", f.name());
					m_flag_RRMCRRM[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					RRM_UsageOfResponsiblyWonProductsSecondaryResources ftype = (RRM_UsageOfResponsiblyWonProductsSecondaryResources)KeywordList::Enumeration("Env1_3_2::RRM_UsageOfResponsiblyWonProductsSecondaryResources", f.name());
					m_flag_RRMRRWPSR[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					RRM_PercentageOfWoodMaterialsFromSustainableForestry ftype = (RRM_PercentageOfWoodMaterialsFromSustainableForestry)KeywordList::Enumeration("Env1_3_2::RRM_PercentageOfWoodMaterialsFromSustainableForestry", f.name());
					m_flag_RRMPWMSF[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					RRM_PRCEWMPS ftype = (RRM_PRCEWMPS)KeywordList::Enumeration("Env1_3_2::RRM_PRCEWMPS", f.name());
					m_flag_RRMPRCEWMPS[ftype] = f; success=true;
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
					ptype = (para_t)KeywordList::Enumeration("Env1_3_2::para_t", p.name);
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Env1_3_2' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Env1_3_2' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Env1_3_2::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Env1_3_2");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_RRMCRRM; ++i) {
		if (!m_flag_RRMCRRM[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_RRMCRRM[i].name(), m_flag_RRMCRRM[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_RRMRRWPSR; ++i) {
		if (!m_flag_RRMRRWPSR[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_RRMRRWPSR[i].name(), m_flag_RRMRRWPSR[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_RRMPWMSF; ++i) {
		if (!m_flag_RRMPWMSF[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_RRMPWMSF[i].name(), m_flag_RRMPWMSF[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_RRMPRCEWMPS; ++i) {
		if (!m_flag_RRMPRCEWMPS[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_RRMPRCEWMPS[i].name(), m_flag_RRMPRCEWMPS[i].isEnabled() ? "true" : "false");
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
