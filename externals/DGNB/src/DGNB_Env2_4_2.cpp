#include "DGNB_Env2_4_2.h"

namespace DGNB {

double DGNB::Env2_4_2::score() {
	double env2_4_2 = 0;
	double currentEnv2_4_2PercentageOfBiodiversitySupportingOutdoorArea = m_para[(P_CurrentValue_env2_4_2BDOSBBSA_PercentageOfBiodiversitySupportingOutdoorArea)].get_value();
	double currentEnv2_4_2PercentageOfGreenRoof = m_para[(P_CurrentValue_env2_4_2BDOSBGR_PercentageOfGreenRoof)].get_value();
	double currentEnv2_4_2BFFOfSite = m_para[(P_CurrentValue_env2_4_2BDOSBAFA2030VB_BFFOfSite)].get_value();

	// TODO DGNB no points for less than 40 % right?
	// assigning up to 20 points for biodiversity supporting area

	if (m_flag_BDOSBBSA[(BDOSBBSA_ResultsSubmitted)].isEnabled()){
		if (40 <= currentEnv2_4_2PercentageOfBiodiversitySupportingOutdoorArea)
			env2_4_2 += 15 + std::min<double>(5, 5*((currentEnv2_4_2PercentageOfBiodiversitySupportingOutdoorArea-40)/60));
	}
	// assinging up to 7 points for green roof
	if (m_flag_BDOSBGR[(BDOSBGR_ResultsSubmitted)].isEnabled()){
		if (50 <= currentEnv2_4_2PercentageOfGreenRoof)
			env2_4_2 += 5 + std::min<double>(2, 2*((currentEnv2_4_2PercentageOfGreenRoof-50)/20));
	}

	// Env2.4.2.3 and Env2.4.2.4 assigning points for BFF
	if (m_flag_BDOSBAFA2030VB[(BDOSBAFA2030VB_ResultsSubmitted)].isEnabled()){
		switch (m_usageType) {
			case Utilities::UT_Residential: {
				if (currentEnv2_4_2BFFOfSite <= 0.6)
					env2_4_2 += 20 * (currentEnv2_4_2BFFOfSite / 0.6);
				else {
					env2_4_2 += 20;
				}
				break;
			}
			case Utilities::UT_Education:			//(fall through)
			case Utilities::UT_Healthcare: {		// healthcare
				if (currentEnv2_4_2BFFOfSite <= 0.4)
					env2_4_2 += 20 * (currentEnv2_4_2BFFOfSite / 0.4);
				else {
					env2_4_2 += 20;
				}
				break;
			}
			default : {	 // every other usage type
				if (currentEnv2_4_2BFFOfSite <= 0.3)
					env2_4_2 += 20 * (currentEnv2_4_2BFFOfSite / 0.3);
				else {
					env2_4_2 += 20;
				}
				break;
			}
		} // switch
	}

	// Env2.4.2.5 Assigning 5 and 2 pts respectively for biotope structure diversity factors
	env2_4_2 += (m_flag_BDOSDS[(BDOSDS_StructureTypesEmbeddedInBiodiversitySupportingConcept)].isEnabled() ? 5 : 0);
	env2_4_2 += (m_flag_BDOSDS[(BDOSDS_TwoBiotopeStructureTypesAvailable)].isEnabled() ? 2 : 0);

	return env2_4_2;
}

double DGNB::Env2_4_2::scoreBonus() {
	double env2_4_2A2030Bonus = 0;

	// Env2.4.2.3 and Env2.4.2.4 assigning points for BFF
	double currentEnv2_4_2BFFOfSite = m_para[(P_CurrentValue_env2_4_2BDOSBAFA2030VB_BFFOfSite)].get_value();

	if (m_flag_BDOSBAFA2030VB[(BDOSBAFA2030VB_ResultsSubmitted)].isEnabled()){
		switch (m_usageType) {
			case Utilities::UT_Residential: {   // living
				if (currentEnv2_4_2BFFOfSite > 0.6)
					env2_4_2A2030Bonus += std::min<double>(5, std::floor((currentEnv2_4_2BFFOfSite - 0.6) / 0.05));
				break;
			}
			case Utilities::UT_Education:			// fall through
			case Utilities::UT_Healthcare: {		// healthcare
				if (currentEnv2_4_2BFFOfSite > 0.4)
					env2_4_2A2030Bonus += std::min<double>(5, std::floor((currentEnv2_4_2BFFOfSite - 0.4) / 0.05));
				break;
			}
			default : {	 // every other usage type
				if (currentEnv2_4_2BFFOfSite > 0.3)
					env2_4_2A2030Bonus += std::min<double>(5, std::floor((currentEnv2_4_2BFFOfSite - 0.3) / 0.05));
				break;
			}
		} // switch
	}

	// Env2.4.2.6 Assigning 5 bonus pts for soil quality improvement
	env2_4_2A2030Bonus += (m_flag_BDOSDS[(BDOSA2030FS_EmploymentOfSOTAMethodsForImprovementOfSoilQualityAndCultivationOfHumus)].isEnabled() ? 5 : 0);

	return env2_4_2A2030Bonus;
}



} // namespace DGNB
