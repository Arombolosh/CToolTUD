#include "DGNB_Environment.h"

#define Macro_VariableToString(Variable) (void(Variable),#Variable)


namespace DGNB {

// double Environment::score() {
// 	double sumEnvironment = 0;

// 	// summing up all environment categories including their individual weighing factors

// 	sumEnvironment += m_para_PW[PW_Env1_1].get_value()/100 * m_env1_1.score();
// 	sumEnvironment += m_para_PW[PW_Env1_2].get_value()/100 * m_env1_2.score();
// 	sumEnvironment += m_para_PW[PW_Env1_3].get_value()/100 * m_env1_3.score();
// 	sumEnvironment += m_para_PW[PW_Env2_2].get_value()/100 * m_env2_2.score();
// 	sumEnvironment += m_para_PW[PW_Env2_3].get_value()/100 * m_env2_3.score();
// 	sumEnvironment += m_para_PW[PW_Env2_4].get_value()/100 * m_env2_4.score();

// 	return sumEnvironment;

// }

int Environment::grading(const double & envTotal) {
	double envScore = envTotal;
	int environmentGrading = 0;				// default failed

	if (envScore >= 390) {
		environmentGrading = 4;				// 65% of 600 pts for Platinum
	} else if (envScore >= 300) {
		environmentGrading = 3;				// 50% of 600 pts for Gold
	} else if (envScore >= 210) {
		environmentGrading = 2;				// 35% of 600 pts for Silver
	} else {
		environmentGrading = 1;				// Bronze
	}

	return environmentGrading;
}

void Environment::setUsageType(const Utilities::UsageType &ut) {
	m_env1_1 = Env1_1(ut);
	m_env1_2 = Env1_2(ut);
	m_env1_3 = Env1_3(ut);
	m_env2_2 = Env2_2(ut);
	m_env2_3 = Env2_3(ut);
	m_env2_4 = Env2_4(ut);
	//m_env1_1.m_env1_1_1 = Env1_1::Env1_1_1(ut);
}

std::vector<double> Environment::score() {
	std::vector<double>		scoreVec(6);

	scoreVec[0] = m_env1_1.score();
	scoreVec[1] = m_env1_2.score();
	scoreVec[2] = m_env1_3.score();
	scoreVec[3] = m_env2_2.score();
	scoreVec[4] = m_env2_3.score();
	scoreVec[5] = m_env2_4.score();

	return scoreVec;
}

std::vector<bool> Environment::minimumRequirementsMet(){
	std::vector<bool> minReqMet = {false, true, false, true, true, true};

	minReqMet[0] = (m_env1_1.m_env1_1_2.minimumRequirementsMet() ? true : false);
	minReqMet[2] = (m_env1_3.m_env1_3_2.minimumRequirementsMet() ? true : false);


	return minReqMet;
}

std::vector<bool> Environment::platinumRequirementsMet(){
	std::vector<bool> platReqMet = {false, false, true, false, true, false};

	platReqMet[0] = (m_env1_1.m_env1_1_2.platinumRequirementsMet() ? true : false);
	platReqMet[1] = (m_env1_2.m_env1_2_1.platinumRequirementsMet() ? true : false);
	platReqMet[3] = (m_env2_2.score() >= 40 ? true : false);
	platReqMet[5] = (m_env2_4.m_env2_4_2.score() >= 25 ? true : false);

	return platReqMet;
}

#if 0
void Environment::readInputValuesFromXML(const TiXmlElement *element) {
	FUNCID(Project::readInputValuesFromXML);

	TiXmlDocument doc;

	// we use a handle so that NULL pointer checks are done during the query functions
	TiXmlHandle xmlHandleDoc(&doc);

	// read root element
	TiXmlElement * xmlElem = xmlHandleDoc.FirstChildElement().Element();
	if (!xmlElem)
		return; // empty file?

	std::string rootnode = xmlElem->Value();
	std::string parentXmlTag = "DGNB_Input";
	if (rootnode != parentXmlTag)
		throw IBK::Exception( IBK::FormatString("Expected '%1' as root node in XML file.").arg(parentXmlTag), FUNC_ID);

	// search for mandatory elements
	// reading elements
	const TiXmlElement * c = xmlElem->FirstChildElement();
	while (c) {
		const std::string & cName = c->ValueStr();
		if (cName == "Environment") {
			const TiXmlElement * c2 = c->FirstChildElement();
			while (c2) {
				const std::string & c2Name = c2->ValueStr();
				if (c2Name == "Env1_1"){
					m_env1_1.readInputValuesFromXML(c2);
				}
				else if (c2Name == "Env1_2"){
					m_env1_2.readInputValuesFromXML(c2);
				}
				else if (c2Name == "Env1_3"){
					m_env1_3.readInputValuesFromXML(c2);
				}
				else if (c2Name == "Env2_2"){
					m_env2_2.readInputValuesFromXML(c2);
				}
				else if (c2Name == "Env2_3"){
					m_env2_3.readInputValuesFromXML(c2);
				}
				else if (c2Name == "Env2_4"){
					m_env2_4.readInputValuesFromXML(c2);
				}
				//				IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()),
				//									 IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
				c2 = c2->NextSiblingElement();
			}
		}
		c = c->NextSiblingElement();
	}
}


void Environment::readReferenceValuesFromXML(const TiXmlElement *element) {
	FUNCID(Project::readReferenceValuesFromXML);

	TiXmlDocument doc;

	// we use a handle so that NULL pointer checks are done during the query functions
	TiXmlHandle xmlHandleDoc(&doc);

	// read root element
	TiXmlElement * xmlElem = xmlHandleDoc.FirstChildElement().Element();
	if (!xmlElem)
		return; // empty file?

	std::string rootnode = xmlElem->Value();
	std::string parentXmlTag = "DGNB_Reference";
	if (rootnode != parentXmlTag)
		throw IBK::Exception( IBK::FormatString("Expected '%1' as root node in XML file.").arg(parentXmlTag), FUNC_ID);

	// search for mandatory elements
	// reading elements
	const TiXmlElement * c = xmlElem->FirstChildElement();
	while (c) {
		const std::string & cName = c->ValueStr();
		if (cName == "Environment") {
			const TiXmlElement * c2 = c->FirstChildElement();
			while (c2) {
				const std::string & c2Name = c2->ValueStr();
				if (c2Name == "Env1_1"){
					//Env1_1 obj;
					m_env1_1.readReferenceValuesFromXML(c2);
				}
				else if (c2Name == "Env1_3"){
					//Env1_3 obj;
					m_env1_3.readReferenceValuesFromXML(c2);
				}
				else if (c2Name == "Env2_2"){
					//Env2_2 obj;
					m_env2_2.readReferenceValuesFromXML(c2);
				}
				//				IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()),
				//									 IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
				c2 = c2->NextSiblingElement();
			}
		}
		c = c->NextSiblingElement();
	}
}
#endif

} // namespace DGNB
