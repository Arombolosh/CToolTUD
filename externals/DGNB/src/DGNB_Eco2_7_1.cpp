#include "DGNB_Eco2_7_1.h"

namespace DGNB {
	
double DGNB::Eco2_7_1::score() {
	double scoreEco2_7_1 = 0, scoreEco2_7_1_2 = 0;

	// assigning up to +45/+27 pts for Eco2.7.1.1 depending on selection
	if (m_flag_DCBCPD[(DCB_CurrentPlanningData)0].isEnabled()) {
		scoreEco2_7_1 += (m_flag_DCBCPD[(DCB_CurrentPlanningData)1].isEnabled() ? 25 : 0);
		scoreEco2_7_1 += (m_flag_DCBCPD[(DCB_CurrentPlanningData)2].isEnabled() ? 20 : 0);
	} else {
		scoreEco2_7_1 += (m_flag_DCBCPD[(DCB_CurrentPlanningData)1].isEnabled() ? 15 : 0);
		scoreEco2_7_1 += (m_flag_DCBCPD[(DCB_CurrentPlanningData)2].isEnabled() ? 12 : 0);
	}

	// assigning up to +20/+15 pts for Eco2.7.1.2 depending on selection
	if (m_flag_DCBCSBD[(DCB_CompleteSustainabilityBuildingDocumentation)0].isEnabled()) {
		scoreEco2_7_1_2 += (m_flag_DCBCSBD[(DCB_CompleteSustainabilityBuildingDocumentation)1].isEnabled() ? 20 : 0);
		scoreEco2_7_1_2 += (m_flag_DCBCSBD[(DCB_CompleteSustainabilityBuildingDocumentation)2].isEnabled() ? 20 : 0);
		scoreEco2_7_1 += std::min<double>(20, scoreEco2_7_1_2);
	} else {
		scoreEco2_7_1_2 += (m_flag_DCBCSBD[(DCB_CompleteSustainabilityBuildingDocumentation)1].isEnabled() ? 15 : 0);
		scoreEco2_7_1_2 += (m_flag_DCBCSBD[(DCB_CompleteSustainabilityBuildingDocumentation)2].isEnabled() ? 15 : 0);
		scoreEco2_7_1 += std::min<double>(15, scoreEco2_7_1_2);
	}
	return scoreEco2_7_1;
}

double DGNB::Eco2_7_1::scoreBonus() {
	double scoreEco2_7_1Bonus = 0;

	//assigning up to +5 bonus pts for Eco2.7.1.3
	scoreEco2_7_1Bonus += (m_flag_DCBCEBDBUM[(DCB_CircularEconomyDataBasisForUrbanMines)0].isEnabled() ? 5 : 0);
	//assigning up to +5 bonus pts for Eco2.7.1.4
	scoreEco2_7_1Bonus += (m_flag_DCBA2030DF[(DCB_Agenda2030DigitalFootprint)0].isEnabled() ? 5 : 0);

	return scoreEco2_7_1Bonus;
}

} // namespace DGNB
