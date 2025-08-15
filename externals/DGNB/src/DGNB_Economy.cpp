#include "DGNB_Economy.h"


namespace DGNB {


void Economy::setUsageType(const Utilities::UsageType &ut) {
	m_eco1_1 = Eco1_1(ut);
	m_eco2_4 = Eco2_4(ut);
	m_eco2_6 = Eco2_6(ut);
	m_eco2_7 = Eco2_7(ut);
	//m_eco1_1.m_eco1_1_1 = Eco1_1::Eco1_1_1(ut);
}

// double Economy::score() {
// 	double sumEconomy = 0;

// 	// summing up all economy categories including their individual weighing factors
// 	sumEconomy += m_para_PW[PW_Eco1_1].get_value()/100 * m_eco1_1.score();
// 	sumEconomy += m_para_PW[PW_Eco2_4].get_value()/100 * m_eco2_4.score();
// 	sumEconomy += m_para_PW[PW_Eco2_6].get_value()/100 * m_eco2_6.score();
// 	sumEconomy += m_para_PW[PW_Eco2_7].get_value()/100 * m_eco2_7.score();

// 	return sumEconomy;
// }

int Economy::grading(const double & ecoTotal) {
	int economyGrading = 0;				// default Failed
	double ecoScore = ecoTotal;

	if (ecoScore >= 260) {
		economyGrading = 4;				// 65% of 400 pts for Platinum
	} else if (ecoScore >= 200) {
		economyGrading = 3;				// 50% of 400 pts for Gold
	} else if (ecoScore >= 140) {
		economyGrading = 2;				// 35% of 400 pts for Silver
	} else
		economyGrading = 1;				// Bronze

	return economyGrading;
}

std::vector<bool> Economy::minimumRequirementsMet(){
	std::vector<bool> minReqMet = {true, true, false, true};

	minReqMet[2] = (m_eco2_6.m_eco2_6_2.minimumRequirementsMet() ? true : false);

	return minReqMet;
}

std::vector<bool> Economy::platinumRequirementsMet(){
	std::vector<bool> platReqMet = {true, true, false, true};

	platReqMet[2] = (m_eco2_6.m_eco2_6_2.platinumRequirementsMet() ? true : false);

	return platReqMet;
}

#if 0
void Economy::readReferenceValuesFromXML(const TiXmlElement *element) {
	// read reference values from file
	m_eco1_1.m_eco1_1_3.m_referenceValue_eco1_1_3netLCCPerBuildingType[0] = 0;
	m_eco1_1.m_eco1_1_3.m_referenceValue_eco1_1_3netLCCPerBuildingType[1] = 1;
	m_eco1_1.m_eco1_1_3.m_referenceValue_eco1_1_3netLCCPerBuildingType[2] = 2;
	m_eco1_1.m_eco1_1_3.m_referenceValue_eco1_1_3netLCCPerBuildingType[3] = 3;
	m_eco1_1.m_eco1_1_3.m_referenceValue_eco1_1_3netLCCPerBuildingType[4] = 4;
	m_eco1_1.m_eco1_1_3.m_referenceValue_eco1_1_3netLCCPerBuildingType[5] = 5;
	m_eco1_1.m_eco1_1_3.m_referenceValue_eco1_1_3netLCCPerBuildingType[6] = 6;
	m_eco1_1.m_eco1_1_3.m_referenceValue_eco1_1_3netLCCPerBuildingType[7] = 7;
	m_eco1_1.m_eco1_1_3.m_referenceValue_eco1_1_3netLCCPerBuildingType[8] = 8;
	m_eco1_1.m_eco1_1_3.m_referenceValue_eco1_1_3netLCCPerBuildingType[9] = 9;
	m_eco1_1.m_eco1_1_3.m_referenceValue_eco1_1_3netLCCPerBuildingType[10] = 10;
	m_eco1_1.m_eco1_1_3.m_referenceValue_eco1_1_3netLCCPerBuildingType[11] = 11;
	double netLCCPerBuildingType [11][12]{
		//offices: 0 - average, raised representational requirements, -,  -
		{7595, 5838, 4522, 7767, 6406, 5087, 0, 0, 0, 0, 0, 0},
		//education: 1 - kindergarden, school, institute, -
		{7599, 6093, 4581, 7218, 5759, 4288, 9336, 7685, 6213, 0, 0, 0},
		//residential: 2 - residential buildings with 6+ units, -, -, -
		{5097, 4117, 3368, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		//hotel: 3 - standard (0-3 stars), noble (4+ stars), -, -
		{9713, 7577, 4856, 10165, 7974, 5601, 0, 0, 0, 0, 0, 0},
		//convenience store: 4 - standard, -, -, -
		{4672, 3730, 2697, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		//shopping center: 5 - standard, -, -, -
		{7045, 5739, 4263, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		//commercial building: 6 - retail park, commercial building, -, -
		{5813, 4762, 3477, 6847, 5717, 4419, 0, 0, 0, 0, 0, 0},
		//logistics: 7 - low requirements, high requirements, alt: low req by ceiling height, alt: high req by ceiling height
		{2627, 2073, 1756, 3022, 2300, 1960, 263, 207, 176, 302, 230, 196},
		//production: 8 - low requirements, high requirements, alt: low req by ceiling height, alt: high req by ceiling height
		{2627, 2073, 1756, 3022, 2300, 1960, 263, 207, 176, 302, 230, 196},
		//assembly: 9 - standard, -, -, -
		{8369, 6792, 4778, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		//healthcare: 10 - type 1 (rehabilitation, psychosomatic), type 2 (hospitals, university hospitals - in relation to reference building), -, -
		{10165, 8137, 5764, 1.24, 1.00, 0.90, 0, 0, 0, 0, 0, 0},
	};
	m_eco1_1.m_eco1_1_3.m_referenceValue_eco1_1_3BRLCCC_HealthCareTypeII = 0;

}

void Economy::readInputValuesFromXML(const TiXmlElement *element) {
	// read Input Values from file

	m_eco1_1.m_eco1_1_2.m_currentValue_eco1_1_2EECBOCEBR_NumberOfCircularEconomySolutionsForReuse = 0;
	m_eco1_1.m_eco1_1_3.m_currentValue_eco1_1_3usageIDFlag = 4;
	m_eco1_1.m_eco1_1_3.m_currentValue_eco1_1_3BRLCCC_NetLifeCycleCosts = 20000;
	m_eco1_1.m_eco1_1_3.m_currentValue_eco1_1_3BRLCCC_CSAnnualEnergyConsumptionPerMeterRefrigeratedDC = 4000;

}
#endif

} // Economy
