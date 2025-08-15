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

#include <DGNB_Env1_1_2.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Env1_1_2::readXML(const TiXmlElement * element) {
	FUNCID(Env1_1_2::readXML);

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
					LCCO2_DisclosureOfLifeCycleBalances ftype = (LCCO2_DisclosureOfLifeCycleBalances)KeywordList::Enumeration("Env1_1_2::LCCO2_DisclosureOfLifeCycleBalances", f.name());
					m_flag_LCCO2DISC[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					LCCO2_InterpolationOfEvaluationResultBasedOnReferenceValue ftype = (LCCO2_InterpolationOfEvaluationResultBasedOnReferenceValue)KeywordList::Enumeration("Env1_1_2::LCCO2_InterpolationOfEvaluationResultBasedOnReferenceValue", f.name());
					m_flag_LCCO2IER[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					LCCO2Agenda2030_LifeCycleClimateProtectionAgenda ftype = (LCCO2Agenda2030_LifeCycleClimateProtectionAgenda)KeywordList::Enumeration("Env1_1_2::LCCO2Agenda2030_LifeCycleClimateProtectionAgenda", f.name());
					m_flag_LCCO2A2030LCCPA[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					LCCO2Agenda2030_ClimateProtectionThroughSufficiency ftype = (LCCO2Agenda2030_ClimateProtectionThroughSufficiency)KeywordList::Enumeration("Env1_1_2::LCCO2Agenda2030_ClimateProtectionThroughSufficiency", f.name());
					m_flag_LCCO2A2030CPTS[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					LCCO2BalanceFrameworkOperation_ClimateProtectionAgendaClimateNeutralOperation ftype = (LCCO2BalanceFrameworkOperation_ClimateProtectionAgendaClimateNeutralOperation)KeywordList::Enumeration("Env1_1_2::LCCO2BalanceFrameworkOperation_ClimateProtectionAgendaClimateNeutralOperation", f.name());
					m_flag_LCCO2BFO[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					LCCO2BalanceFrameworkStructure_CO2ReducedConstructionPhase ftype = (LCCO2BalanceFrameworkStructure_CO2ReducedConstructionPhase)KeywordList::Enumeration("Env1_1_2::LCCO2BalanceFrameworkStructure_CO2ReducedConstructionPhase", f.name());
					m_flag_LCCO2BFSCO2RCP[ftype] = f; success=true;
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
					ptype = (para_t)KeywordList::Enumeration("Env1_1_2::para_t", p.name);
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Env1_1_2' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Env1_1_2' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Env1_1_2::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Env1_1_2");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_LCCO2DISC; ++i) {
		if (!m_flag_LCCO2DISC[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_LCCO2DISC[i].name(), m_flag_LCCO2DISC[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_LCCO2IER; ++i) {
		if (!m_flag_LCCO2IER[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_LCCO2IER[i].name(), m_flag_LCCO2IER[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_LCCO2A2030LCCPA; ++i) {
		if (!m_flag_LCCO2A2030LCCPA[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_LCCO2A2030LCCPA[i].name(), m_flag_LCCO2A2030LCCPA[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_LCCO2A2030CPTS; ++i) {
		if (!m_flag_LCCO2A2030CPTS[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_LCCO2A2030CPTS[i].name(), m_flag_LCCO2A2030CPTS[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_LCCO2BFO; ++i) {
		if (!m_flag_LCCO2BFO[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_LCCO2BFO[i].name(), m_flag_LCCO2BFO[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_LCCO2BFSCO2RCP; ++i) {
		if (!m_flag_LCCO2BFSCO2RCP[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_LCCO2BFSCO2RCP[i].name(), m_flag_LCCO2BFSCO2RCP[i].isEnabled() ? "true" : "false");
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
