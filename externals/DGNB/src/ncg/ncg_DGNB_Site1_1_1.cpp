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

#include <DGNB_Site1_1_1.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Site1_1_1::readXML(const TiXmlElement * element) {
	FUNCID(Site1_1_1::readXML);

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
					CR_ConductionOfAnalysis ftype = (CR_ConductionOfAnalysis)KeywordList::Enumeration("Site1_1_1::CR_ConductionOfAnalysis", f.name());
					m_flag_CRCA[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CR_Screening ftype = (CR_Screening)KeywordList::Enumeration("Site1_1_1::CR_Screening", f.name());
					m_flag_CRS[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CR_SettingTheEvaluationPeriod ftype = (CR_SettingTheEvaluationPeriod)KeywordList::Enumeration("Site1_1_1::CR_SettingTheEvaluationPeriod", f.name());
					m_flag_CRSEP[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CR_ActingOnTheEvaluation ftype = (CR_ActingOnTheEvaluation)KeywordList::Enumeration("Site1_1_1::CR_ActingOnTheEvaluation", f.name());
					m_flag_CRAT[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CR_Agenda2030ClimateProtectionGoal ftype = (CR_Agenda2030ClimateProtectionGoal)KeywordList::Enumeration("Site1_1_1::CR_Agenda2030ClimateProtectionGoal", f.name());
					m_flag_CRA2030CPG[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CR_DataBasis ftype = (CR_DataBasis)KeywordList::Enumeration("Site1_1_1::CR_DataBasis", f.name());
					m_flag_CRDB[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CR_ResultApplication ftype = (CR_ResultApplication)KeywordList::Enumeration("Site1_1_1::CR_ResultApplication", f.name());
					m_flag_CRRA[ftype] = f; success=true;
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Site1_1_1' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Site1_1_1' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Site1_1_1::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Site1_1_1");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_CRCA; ++i) {
		if (!m_flag_CRCA[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CRCA[i].name(), m_flag_CRCA[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CRS; ++i) {
		if (!m_flag_CRS[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CRS[i].name(), m_flag_CRS[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CRSEP; ++i) {
		if (!m_flag_CRSEP[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CRSEP[i].name(), m_flag_CRSEP[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CRAT; ++i) {
		if (!m_flag_CRAT[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CRAT[i].name(), m_flag_CRAT[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CRA2030CPG; ++i) {
		if (!m_flag_CRA2030CPG[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CRA2030CPG[i].name(), m_flag_CRA2030CPG[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CRDB; ++i) {
		if (!m_flag_CRDB[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CRDB[i].name(), m_flag_CRDB[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CRRA; ++i) {
		if (!m_flag_CRRA[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CRRA[i].name(), m_flag_CRRA[i].isEnabled() ? "true" : "false");
		}
	}
	return e;
}

} // namespace DGNB
