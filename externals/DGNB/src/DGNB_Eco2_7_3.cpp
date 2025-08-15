#include "DGNB_Eco2_7_3.h"

namespace DGNB {
	
double DGNB::Eco2_7_3::score() {
	double scoreEco2_7_3 = 0;


	// assigning up to +0/+10 pts for Eco2.7.3.1 depending on selection
	if (m_flag_PPBIMP[(PPBIM_Preparation)0].isEnabled() == false) {
		scoreEco2_7_3 += (m_flag_PPBIMP[(PPBIM_Preparation)1].isEnabled() ? 2 : 0);
		scoreEco2_7_3 += (m_flag_PPBIMP[(PPBIM_Preparation)2].isEnabled() ? 2 : 0);
		scoreEco2_7_3 += (m_flag_PPBIMP[(PPBIM_Preparation)3].isEnabled() ? 2 : 0);
		scoreEco2_7_3 += (m_flag_PPBIMP[(PPBIM_Preparation)4].isEnabled() ? 2 : 0);
		scoreEco2_7_3 += (m_flag_PPBIMP[(PPBIM_Preparation)5].isEnabled() ? 2 : 0);
	}

	// assigning up to +0/+6 pts for Eco2.7.3.2 depending on selection
	if (m_flag_PPBIMC[(PPBIM_Creation)0].isEnabled() == false) {
		scoreEco2_7_3 += (m_flag_PPBIMC[(PPBIM_Creation)1].isEnabled() ? 2 : 0);
		scoreEco2_7_3 += (m_flag_PPBIMC[(PPBIM_Creation)2].isEnabled() ? 2 : 0);
		scoreEco2_7_3 += (m_flag_PPBIMC[(PPBIM_Creation)3].isEnabled() ? 2 : 0);
	}

	// assigning up to +0/+2 pts for Eco2.7.3.3 depending on selection
	if (m_flag_PPBIMSO[(PPBIM_SustainabilityOptimisationWithBIM)0].isEnabled() == false) {
		scoreEco2_7_3 += (m_flag_PPBIMSO[(PPBIM_SustainabilityOptimisationWithBIM)1].isEnabled() ? 2 : 0);
	}

	return scoreEco2_7_3;
}

double DGNB::Eco2_7_3::scoreBonus() {
	double scoreEco2_7_3Bonus = 0;


	// assigning up to +5 bonus pts for Eco2.7.3.4
	scoreEco2_7_3Bonus += (m_flag_PPBIMCEBIM2FMOC[(PPBIM_CircularEconomyBIM2FMOperatorConcept)0].isEnabled() ? 5 : 0);
	// assigning up to +5 bonus pts for Eco2.7.3.5
	scoreEco2_7_3Bonus += (m_flag_PPBIMA2030SC[(PPBIM_Agenda2030SustainabilityCheck)0].isEnabled() ? 5 : 0);

	return scoreEco2_7_3Bonus;
}

} // namespace DGNB
