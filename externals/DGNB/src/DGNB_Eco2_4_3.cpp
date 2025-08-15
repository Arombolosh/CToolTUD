#include "DGNB_Eco2_4_3.h"

namespace DGNB {
	
double DGNB::Eco2_4_3::score() {
	double scoreEco2_4_3 = 0;
	double currentEco2_4_3DegreeOfUseOrTenancy = m_para[(P_CurrentValue_eco2_4_3DegreeOfUseOrTenancy)].get_value();
	// assigning up to 10 pts for Eco2.4.3.1
	if (m_usageType != 10 && m_flag_DUTTCDUT[(DUTTCDUT_ResultsSubmitted)].isEnabled() == true && currentEco2_4_3DegreeOfUseOrTenancy >= 50)
		scoreEco2_4_3 += 1 + (0.18*(currentEco2_4_3DegreeOfUseOrTenancy-50));
	return scoreEco2_4_3;
}

double DGNB::Eco2_4_3::scoreBonus() {
	double scoreEco2_4_3Bonus = 0;

	// assigning 10 bonus pts for Eco2.4.3.2
	scoreEco2_4_3Bonus += (m_flag_DUTTCCEUT[(DUTTCCEUT_AtLeastOneUserOrTenantContributesToCircularEconomy)].isEnabled() ? 10 : 0);
	return scoreEco2_4_3Bonus;
}

} // namespace DGNB
