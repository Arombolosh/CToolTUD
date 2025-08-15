#include "DGNB_Eco1_1_2.h"

namespace DGNB {
	
double DGNB::Eco1_1_2::score() {
	// assigning 10 pts for either normal or alternative certification
	double eco1_1_2 = (m_flag_EECBOBEB[(EECBOBEB_BuildingUpToInnovationClauseStandards)].isEnabled() || m_flag_EECBOBEB[(EECBOBEB_AltBuildingReceivedKFWFundingForEnergyEfficiencyClassAOrBetter)].isEnabled() ? 10 : 0);

	return eco1_1_2;
} // Eco1.1.2

double DGNB::Eco1_1_2::scoreBonus() {
	double  eco1_1_2CEBonus = 0;
	/*! Eco1.1.2.2. Circular Economy Bonus */
	if (m_flag_EECBOCEBR[(EECBOCEBR_CircularEconomySolutionsForReuseSubmitted)].isEnabled())
		eco1_1_2CEBonus += 5 * m_para[(P_CurrentValue_eco1_1_2EECBOCEBR_NumberOfCircularEconomySolutionsForReuse)].get_value();
	eco1_1_2CEBonus +=  (m_flag_EECBOCEBR[(EECBOCEBR_LCCModelIncludesEndOfLifeCosts)].isEnabled() ? 5 : 0);
	eco1_1_2CEBonus +=  (m_flag_EECBOCEBR[(EECBOCEBR_DocumentationOfRawMaterialValue)].isEnabled() ? 5 : 0);

	// capping eco1_1_2CEBonus at 10 pts
	eco1_1_2CEBonus = std::min<double>(10, eco1_1_2CEBonus);

	return eco1_1_2CEBonus;
} // Eco1.1.2 Circular Economy Bonus

} // namespace DGNB
