#ifndef DGNB_Env2_2_5H
#define DGNB_Env2_2_5H
#include "DGNB_Utilities.h"

namespace DGNB {
	
/*! Env2_2_5 Agenda 2030 Bonus - Climate Protection Goal */
class Env2_2_5 {
	public:

	/*! Basic parameters. */
	enum para_t {
		/*! Env2_2DWDWWVSC_WaterEconomyTotalDeviation */
		P_CurrentValue_env2_2DWDWWVSC_WaterEconomyTotalDeviation,					// Keyword: CurrentValue_env2_2DWDWWVSC_WaterEconomyTotalDeviation				[---]	// ToDo Einheit % SO oder anders?
		/*! Env2_2DWDWWVSC_DeviationFromEvaporationPortion */
		P_CurrentValue_env2_2DWDWWVSC_DeviationFromEvaporationPortion,				// Keyword: CurrentValue_env2_2DWDWWVSC_DeviationFromEvaporationPortion			[---]	// ToDo Einheit % SO oder anders?
		/*! Env2_2DWDWWVSC_DeviationFromInfiltrationPortion */
		P_CurrentValue_env2_2DWDWWVSC_DeviationFromInfiltrationPortion,				// Keyword: CurrentValue_env2_2DWDWWVSC_DeviationFromInfiltrationPortion		[---]	// ToDo Einheit % SO oder anders?
		NUM_P
	};

	/*! Env2_2_5_1 Agenda 2030 Bonus - Climate Protection Goal: Contribution to Sponge City */
	enum DWDWWV_ContributionToSpongeCity {							// max +10
		DWDWWVSC_ResultsSubmitted,									// Keyword: DWDWWVSC_ResultsSubmitted
		DWDWWVSC_InfiltrationPossible,								// Keyword: DWDWWVSC_InfiltrationPossible
				// if not: evaporation = evaporation + infiltration
		DWDWWVSC_UndercuttingTheDrainagePortion,					// Keyword: DWDWWVSC_UndercuttingTheDrainagePortion
				// less than normal drainage portion: evaporation and infiltration deviations are allowed to be greater
		NUM_DWDWWVSC
	};

	/*! Env2_2_5_2 Agenda 2030 Bonus - Climate Protection Goal: Drinking Water Sanitation */
	enum DWDWWV_DrinkingWaterSanitation {							// max +5
		DWDWWVDWS_LowEnergyDrinkingWaterManagementSystem,			// Keyword: DWDWWVDWS_LowEnergyDrinkingWaterManagementSystem
		DWDWWVDWS_ObservationOfDrinkingWaterSanitation,				// Keyword: DWDWWVDWS_ObservationOfDrinkingWaterSanitation
		DWDWWVDWS_WarmWaterReducedToOperativeMinimum,				// Keyword: DWDWWVDWS_WarmWaterReducedToOperativeMinimum
		DWDWWVDWS_ColdWaterLessThan20Degrees,						// Keyword: DWDWWVDWS_ColdWaterLessThan20Degrees
		NUM_DWDWWVDWS
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env2_2_5(){}

	Env2_2_5(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double scoreBonus();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_DWDWWVSC[NUM_DWDWWVSC];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_DWDWWVDWS[NUM_DWDWWVDWS];			// XML:E
	
	IBK::Parameter					m_para[NUM_P];								// XML:E

	Utilities::UsageType			m_usageType;

};

} // namespace DGNB

#endif // Env2_2_5H
