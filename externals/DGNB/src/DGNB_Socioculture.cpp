#include "DGNB_Socioculture.h"


namespace DGNB {


void Socioculture::setUsageType(const Utilities::UsageType &ut) {
	m_soc1_1 = Soc1_1(ut);
	m_soc1_2 = Soc1_2(ut);
	m_soc1_3 = Soc1_3(ut);
	m_soc1_4 = Soc1_4(ut);
	m_soc1_6 = Soc1_6(ut);
	m_soc2_1 = Soc2_1(ut);
	//m_eco1_1.m_eco1_1_1 = Eco1_1::Eco1_1_1(ut);
}

// double SocioculturalFunctional::score() {
// 	double sumSociocultural = 0;

// 	// summing up all sociocultural / functional categories including their individual weighing factors
// 	sumSociocultural += m_para_PW[PW_Soc1_1].get_value()/100 * m_soc1_1.score();
// 	sumSociocultural += m_para_PW[PW_Soc1_2].get_value()/100 * m_soc1_2.score();
// 	sumSociocultural += m_para_PW[PW_Soc1_3].get_value()/100 * m_soc1_3.score();
// 	sumSociocultural += m_para_PW[PW_Soc1_4].get_value()/100 * m_soc1_4.score();
// 	sumSociocultural += m_para_PW[PW_Soc1_6].get_value()/100 * m_soc1_6.score();
// 	sumSociocultural += m_para_PW[PW_Soc2_1].get_value()/100 * m_soc2_1.score();

// 	return sumSociocultural;
// }

int Socioculture::grading(const double & socTotal) {
	int socGrading = 0;				// default Failed
	double socScore = socTotal;

	if (socScore >= 390)
		socGrading = 4;				// 65% of 600 pts for Platinum
	else if (socScore >= 300)
		socGrading = 3;				// 50% of 600 pts for Gold
	else if (socScore >= 210)
		socGrading = 2;				// 35% of 600 pts for Silver
	else
		socGrading = 1;				// Bronze

	return socGrading;
}

std::vector<bool> Socioculture::minimumRequirementsMet() {
	std::vector<bool> minReqMet = {true, false, true, true, true, false};

	minReqMet[1] = (m_soc1_2.m_soc1_2_1.minimumRequirementsMet() ? true : false);
	minReqMet[5] = (m_soc2_1.m_soc2_1_1.minimumRequirementsMet() ? true : false);

	return minReqMet;
}

std::vector<bool> Socioculture::platinumRequirementsMet() {
	std::vector<bool> platReqMet = {true, false, true, true, true, true};

	// Soc1.2
	// this has to return "true" if mechanical aeration is used and the tvoc and formaldehyde values are below the threshold OR the building has no mechanical aeration
	if (m_soc1_2.m_soc1_2_2.m_para[(Soc1_2_2::P_CurrentValue_soc1_2_2_1_a_PercentageOfMechanicalAeration)].get_value() > 0)
		if (m_soc1_2.m_soc1_2_1.platinumRequirementsMet()) {
			platReqMet[1] = true;
		} else platReqMet[1] = false;
	else
		platReqMet[1] = true;

	return platReqMet;
}

} // DGNB_SocioculturalFunctional
