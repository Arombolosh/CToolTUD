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

#include <DGNB_Pro1_6_1.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Pro1_6_1::readXML(const TiXmlElement * element) {
	FUNCID(Pro1_6_1::readXML);

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
					CEV_PreemptiveExaminationOfVariantsOrPlanningCompetition ftype = (CEV_PreemptiveExaminationOfVariantsOrPlanningCompetition)KeywordList::Enumeration("Pro1_6_1::CEV_PreemptiveExaminationOfVariantsOrPlanningCompetition", f.name());
					m_flag_CEVPEVPC[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CEV_ConceptAssignmentMannerAndScopeOfMethod ftype = (CEV_ConceptAssignmentMannerAndScopeOfMethod)KeywordList::Enumeration("Pro1_6_1::CEV_ConceptAssignmentMannerAndScopeOfMethod", f.name());
					m_flag_CEVCAMSM[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CEV_ConceptAssignmentQualityEnsurance ftype = (CEV_ConceptAssignmentQualityEnsurance)KeywordList::Enumeration("Pro1_6_1::CEV_ConceptAssignmentQualityEnsurance", f.name());
					m_flag_CEVCAQE[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CEV_MultipleAssignmentsScopeOfMethod ftype = (CEV_MultipleAssignmentsScopeOfMethod)KeywordList::Enumeration("Pro1_6_1::CEV_MultipleAssignmentsScopeOfMethod", f.name());
					m_flag_CEVMASM[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CEV_MultipleAssignmentsQualityEnsurance ftype = (CEV_MultipleAssignmentsQualityEnsurance)KeywordList::Enumeration("Pro1_6_1::CEV_MultipleAssignmentsQualityEnsurance", f.name());
					m_flag_CEVMAQE[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CEV_MultipleAssignmentsImplementationOfAnAwardWinningDesign ftype = (CEV_MultipleAssignmentsImplementationOfAnAwardWinningDesign)KeywordList::Enumeration("Pro1_6_1::CEV_MultipleAssignmentsImplementationOfAnAwardWinningDesign", f.name());
					m_flag_CEVMAIAWD[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CEV_PlanningCompetitionScopeAndQualityOfMethod ftype = (CEV_PlanningCompetitionScopeAndQualityOfMethod)KeywordList::Enumeration("Pro1_6_1::CEV_PlanningCompetitionScopeAndQualityOfMethod", f.name());
					m_flag_CEVPCSQM[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CEV_PlanningCompetitionMannerOfCompetitionMethod ftype = (CEV_PlanningCompetitionMannerOfCompetitionMethod)KeywordList::Enumeration("Pro1_6_1::CEV_PlanningCompetitionMannerOfCompetitionMethod", f.name());
					m_flag_CEVPCMCM[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CEV_PlanningCompetitionImplementationOfAnAwardWinningDesign ftype = (CEV_PlanningCompetitionImplementationOfAnAwardWinningDesign)KeywordList::Enumeration("Pro1_6_1::CEV_PlanningCompetitionImplementationOfAnAwardWinningDesign", f.name());
					m_flag_CEVPCIAWD[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					CEV_PlanningCompetitionCommissioningOfAwardWinnersPlanningTeam ftype = (CEV_PlanningCompetitionCommissioningOfAwardWinnersPlanningTeam)KeywordList::Enumeration("Pro1_6_1::CEV_PlanningCompetitionCommissioningOfAwardWinnersPlanningTeam", f.name());
					m_flag_CEVPCCAWPT[ftype] = f; success=true;
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Pro1_6_1' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Pro1_6_1' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Pro1_6_1::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Pro1_6_1");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_CEVPEVPC; ++i) {
		if (!m_flag_CEVPEVPC[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CEVPEVPC[i].name(), m_flag_CEVPEVPC[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CEVCAMSM; ++i) {
		if (!m_flag_CEVCAMSM[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CEVCAMSM[i].name(), m_flag_CEVCAMSM[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CEVCAQE; ++i) {
		if (!m_flag_CEVCAQE[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CEVCAQE[i].name(), m_flag_CEVCAQE[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CEVMASM; ++i) {
		if (!m_flag_CEVMASM[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CEVMASM[i].name(), m_flag_CEVMASM[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CEVMAQE; ++i) {
		if (!m_flag_CEVMAQE[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CEVMAQE[i].name(), m_flag_CEVMAQE[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CEVMAIAWD; ++i) {
		if (!m_flag_CEVMAIAWD[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CEVMAIAWD[i].name(), m_flag_CEVMAIAWD[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CEVPCSQM; ++i) {
		if (!m_flag_CEVPCSQM[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CEVPCSQM[i].name(), m_flag_CEVPCSQM[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CEVPCMCM; ++i) {
		if (!m_flag_CEVPCMCM[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CEVPCMCM[i].name(), m_flag_CEVPCMCM[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CEVPCIAWD; ++i) {
		if (!m_flag_CEVPCIAWD[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CEVPCIAWD[i].name(), m_flag_CEVPCIAWD[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_CEVPCCAWPT; ++i) {
		if (!m_flag_CEVPCCAWPT[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_CEVPCCAWPT[i].name(), m_flag_CEVPCCAWPT[i].isEnabled() ? "true" : "false");
		}
	}
	return e;
}

} // namespace DGNB
