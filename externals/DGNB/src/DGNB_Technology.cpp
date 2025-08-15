#include "DGNB_Technology.h"


namespace DGNB {


void Technology::setUsageType(const Utilities::UsageType &ut) {
	m_tec1_3 = Tec1_3(ut);
	m_tec1_4 = Tec1_4(ut);
	m_tec1_6 = Tec1_6(ut);
	m_tec3_1 = Tec3_1(ut);
}

// double Technology::score() {
// 	double sumTechnology = 0;

// 	// summing up all technology categories including their individual weighing factors
// 	sumTechnology += m_para_PW[PW_Tec1_3].get_value()/100 * m_tec1_3.score();
// 	sumTechnology += m_para_PW[PW_Tec1_4].get_value()/100 * m_tec1_4.score();
// 	sumTechnology += m_para_PW[PW_Tec1_6].get_value()/100 * m_tec1_6.score();
// 	sumTechnology += m_para_PW[PW_Tec3_1].get_value()/100 * m_tec3_1.score();

// 	return sumTechnology;
// }

int Technology::grading() {
	int tecGrading = 0;				// default Failed
	// this is not currently used as a requirement for Technology as it is for Environment, Economy and Socioculture
	/*!
	if (minimumRequirementsMet()){
		if (platinumRequirementsMet() && score() >= 260) {
			tecGrading = 4;             // 65% of 400 pts for Platinum
		} else if (score() >= 200) {
			tecGrading = 3;             // 50% of 400 pts for Gold
		} else if (score() >= 140) {
			tecGrading = 2;             // 35% of 400 pts for Silver
		} else
			tecGrading = 1;             // Bronze
	}
	*/
	return tecGrading;
}

std::vector<bool> Technology::minimumRequirementsMet() {
	std::vector<bool> minReqMet = {true, true, false, true};

	minReqMet[2] = ((m_tec1_6.m_tec1_6_3.minimumRequirementsMet() || m_tec1_6.score() >= 20) ? true : false);

	return minReqMet;
}

std::vector<bool> Technology::platinumRequirementsMet() {
	std::vector<bool> platReqMet = {true, false, false, false};

	// PV on roof
	platReqMet[1] = (m_tec1_4.m_tec1_4_5.platinumRequirementsMet() ? true : false);

	if (m_tec1_6.m_tec1_6_1.m_flag_CCPID161[(DGNB::Tec1_6_1::CCPID161_DemolitionOrPartialDemolition)].isEnabled())	// if project includes demolition
		platReqMet[2] = ((m_tec1_6.m_tec1_6_1.platinumRequirementsMet() && m_tec1_6.score() >= 40) ? true : false);
	else																											// if project does not include demolition
		platReqMet[2] = (m_tec1_6.score() >= 40 ? true : false);

	platReqMet[3] = (m_tec3_1.score() >= 40 ? true : false);

	return platReqMet;
}

} // DGNB_Technology
