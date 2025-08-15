#include "DGNB_Process.h"


namespace DGNB {


void Process::setUsageType(const Utilities::UsageType &ut) {
	m_pro1_1 = Pro1_1(ut);
	m_pro1_4 = Pro1_4(ut);
	m_pro1_6 = Pro1_6(ut);
	m_pro2_1 = Pro2_1(ut);
	m_pro2_3 = Pro2_3(ut);
	m_pro2_5 = Pro2_5(ut);
	//m_eco1_1.m_eco1_1_1 = Eco1_1::Eco1_1_1(ut);
}

// double Process::score() {
// 	double sumProcess = 0;

// 	// summing up all process categories including their individual weighing factors
// 	sumProcess += m_para_PW[PW_Pro1_1].get_value()/100 * m_pro1_1.score();
// 	sumProcess += m_para_PW[PW_Pro1_4].get_value()/100 * m_pro1_4.score();
// 	sumProcess += m_para_PW[PW_Pro1_6].get_value()/100 * m_pro1_6.score();
// 	sumProcess += m_para_PW[PW_Pro2_1].get_value()/100 * m_pro2_1.score();
// 	sumProcess += m_para_PW[PW_Pro2_3].get_value()/100 * m_pro2_3.score();
// 	sumProcess += m_para_PW[PW_Pro2_5].get_value()/100 * m_pro2_5.score();

// 	return sumProcess;
// }

int Process::grading() {
	int proGrading = 0;             // default Failed
	// this is not currently used as a requirement for Process as it is for Environment, Economy and Socioculture
	/*!
	if (minimumRequirementsMet()){
		if (platinumRequirementsMet() && score() >= 390) {
			proGrading = 4;             // 65% of 600 pts for Platinum
		} else if (score() >= 300) {
			proGrading = 3;             // 50% of 600 pts for Gold
		} else if (score() >= 210) {
			proGrading = 2;             // 35% of 600 pts for Silver
		} else
			proGrading = 1;             // Bronze
	}
	*/
	return proGrading;
}

std::vector<bool> Process::minimumRequirementsMet() {
	std::vector<bool> minReqMet = {true, true, true, true, false, true};

	minReqMet[4] = ((m_pro2_3.m_pro2_3_1.score() > 0 && m_pro2_3.m_pro2_3_5.score() > 0) ? true : false);

	return minReqMet;
}

std::vector<bool> Process::platinumRequirementsMet() {
	std::vector<bool> platReqMet = {true, true, true, true, false, true};

	platReqMet[4] = ((m_pro2_3.m_pro2_3_4.score() > 0 && m_pro2_3.m_pro2_3_5.score() > 0) ? true : false);

	return platReqMet;
}

} // DGNB_Process
