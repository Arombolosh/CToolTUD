#include "DGNB_Env2_4_3.h"

namespace DGNB {

double DGNB::Env2_4_3::score() {
	double env2_4_3 = 0, env2_4_3_1 = 0;
	int bdosVNEIPSCounter = 0;

	for (unsigned int i = 0; i <NUM_BDOSVNEIPS; ++i)
		bdosVNEIPSCounter += (m_flag_BDOSVNEIPS[(BDOS_VegetationNoEmploymentOfInvasivePlantSpecies)i].isEnabled() ? 1 : 0);

	// summing up points
	// Env2.4.3.1
	if (bdosVNEIPSCounter > 1)
		env2_4_3 += 7;

	// Env2.4.3.2a assigning +8 points for biodiversity supporting concept
	env2_4_3_1 += (m_flag_BDOSVNEIPS[(BDOS_VegetationEmploymentOfDiverseLocalSpeciesSuitedToSite)0].isEnabled() ? 8 : 0);
	// TODO Dirk - Im Katalog auf S 152 bzw 165ff - Wenn ich das richtig verstehe, kommt die Zahl hierfür aus einem externen Berechnungstool?
	// Env2.4.3.2b assigning +1 to +20 points given as entered by user
	if (m_flag_BDOSVNEIPS[(BDOS_VegetationEmploymentOfDiverseLocalSpeciesSuitedToSite)1].isEnabled()){
		env2_4_3_1 += m_para[(P_CurrentValue_env2_4_3BDOSVEDLSSS_SelectionIsLocalDiverseAndSuitedToSitePointResult)].get_value();
	}
	env2_4_3 += std::min<double>(20,env2_4_3_1);

	return env2_4_3;
}

double DGNB::Env2_4_3::scoreBonus() {
	double env2_4_3A2030Bonus = (m_flag_BDOSVNEIPS[(BDOS_VegetationAgenda2030BonusPreservationOfVegetationWithHighEcologicalValue)0].isEnabled() ? 5 : 0);
	return env2_4_3A2030Bonus;
}



} // namespace DGNB
