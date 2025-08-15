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

#include <DGNB_Eco2_6_2.h>
#include <DGNB_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <DGNB_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace DGNB {

void Eco2_6_2::readXML(const TiXmlElement * element) {
	FUNCID(Eco2_6_2::readXML);

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
					ACC_QuantitativeEvaluationOfMeasures ftype = (ACC_QuantitativeEvaluationOfMeasures)KeywordList::Enumeration("Eco2_6_2::ACC_QuantitativeEvaluationOfMeasures", f.name());
					m_flag_ACCQEM[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					ACC_QualityOfImplementedAdaptationMeasures ftype = (ACC_QualityOfImplementedAdaptationMeasures)KeywordList::Enumeration("Eco2_6_2::ACC_QualityOfImplementedAdaptationMeasures", f.name());
					m_flag_ACCQIAM[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					ACC_GeneralResilienceToElementalDamages ftype = (ACC_GeneralResilienceToElementalDamages)KeywordList::Enumeration("Eco2_6_2::ACC_GeneralResilienceToElementalDamages", f.name());
					m_flag_ACCGRED[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				try {
					ACC_Agenda2030HeadLoad ftype = (ACC_Agenda2030HeadLoad)KeywordList::Enumeration("Eco2_6_2::ACC_Agenda2030HeadLoad", f.name());
					m_flag_ACCA2030HL[ftype] = f; success=true;
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Eco2_6_2' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Eco2_6_2' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Eco2_6_2::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Eco2_6_2");
	parent->LinkEndChild(e);


	for (int i=0; i<NUM_ACCQEM; ++i) {
		if (!m_flag_ACCQEM[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_ACCQEM[i].name(), m_flag_ACCQEM[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_ACCQIAM; ++i) {
		if (!m_flag_ACCQIAM[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_ACCQIAM[i].name(), m_flag_ACCQIAM[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_ACCGRED; ++i) {
		if (!m_flag_ACCGRED[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_ACCGRED[i].name(), m_flag_ACCGRED[i].isEnabled() ? "true" : "false");
		}
	}

	for (int i=0; i<NUM_ACCA2030HL; ++i) {
		if (!m_flag_ACCA2030HL[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flag_ACCA2030HL[i].name(), m_flag_ACCA2030HL[i].isEnabled() ? "true" : "false");
		}
	}
	return e;
}

} // namespace DGNB
