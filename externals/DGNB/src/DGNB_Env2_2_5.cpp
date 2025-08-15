#include "DGNB_Env2_2_5.h"

namespace DGNB {

double DGNB::Env2_2_5::scoreBonus() {
	double env2_2_5 = 0;
	int dwdwwvDWSCounter = 0;
	double currentEnv2_2TotalDeviation = m_para[(P_CurrentValue_env2_2DWDWWVSC_WaterEconomyTotalDeviation)].get_value();
	double currentEnv2_2DeviationFromEvaporation = m_para[(P_CurrentValue_env2_2DWDWWVSC_DeviationFromEvaporationPortion)].get_value();
	double currentEnv2_2DeviationFromInfiltration = m_para[(P_CurrentValue_env2_2DWDWWVSC_DeviationFromInfiltrationPortion)].get_value();

	/*! Env2_2_5_1 Agenda 2030 Bonus - Climate Protection Goal: Contribution to Sponge City */
	if (m_flag_DWDWWVSC[(DWDWWVSC_ResultsSubmitted)].isEnabled()) {
		if (m_flag_DWDWWVSC[(DWDWWVSC_UndercuttingTheDrainagePortion)].isEnabled()){
			env2_2_5 += 1;
			if (m_flag_DWDWWVSC[(DWDWWVSC_InfiltrationPossible)].isEnabled()){
				if (currentEnv2_2DeviationFromInfiltration >= 5)	// deviation in Percent
					env2_2_5 += 1;
				if (currentEnv2_2DeviationFromEvaporation >= 5)		// deviation in Percent
					env2_2_5 += 1;
			} else {
				if ((currentEnv2_2DeviationFromEvaporation + currentEnv2_2DeviationFromInfiltration) > 5)	// deviation in Percent
					env2_2_5 += 1;
			}
		}
		else {
			if (currentEnv2_2DeviationFromInfiltration <= 5)		// deviation in Percent
				env2_2_5 += 1;
			if (currentEnv2_2DeviationFromEvaporation <= 5)			// deviation in Percent
				env2_2_5 += 1;
		}
		if (currentEnv2_2TotalDeviation <= 10)						// deviation in Percent
			env2_2_5 += 2;
	}

	/*! Env2_2_5_2 Agenda 2030 Bonus - Climate Protection Goal: Drinking Water Sanitation */
	for(unsigned int i=0; i<NUM_DWDWWVDWS; ++i)
		dwdwwvDWSCounter += (m_flag_DWDWWVDWS[(DWDWWV_DrinkingWaterSanitation)i].isEnabled() ? 1 : 0);

	if (dwdwwvDWSCounter > 3)
		env2_2_5 += 5;

	return env2_2_5;
}   // Env2.2.5



} // namespace DGNB
