#ifndef DGNB_Env2_4_5H
#define DGNB_Env2_4_5H
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Env2.4.5 reduction of negative influences */
class Env2_4_5 {
	public:
	
	/*! Env2.4.5.1 illumination concept for protection of species */
	enum BDOS_ReductionOfNegativeInfluencesIlluminationConcept{						// +3 each, +9 max
		BDOSRNIIC_IlluminationConceptForAvoidanceOfLightPollution,					// Keyword: BDOSRNIIC_IlluminationConceptForAvoidanceOfLightPollution
		BDOSRNIIC_HarmlessLightSourceOrientation,									// Keyword: BDOSRNIIC_HarmlessLightSourceOrientation
		BDOSRNIIC_HarmlessLightColourAndLightSourceTemperature,						// Keyword: BDOSRNIIC_HarmlessLightColourAndLightSourceTemperature
		BDOSRNIIC_NoUnwantedBlindingEffects,										// Keyword: BDOSRNIIC_NoUnwantedBlindingEffects
		NUM_BDOSRNIIC
	};

	/*! Env2.4.5.2 reduction of animal traps */
	enum BDOS_ReductionOfNegativeInfluencesAnimalTraps {							// +5
		BDOSRNIAT_EvaluationOfDangersToAnimals,										// Keyword: BDOSRNIAT_EvaluationOfDangersToAnimals
		NUM_BDOSRNIAT
	};

	/*! Env2.4.5.3 construction site planning */
	enum BDOS_ReductionOfNegativeInfluencesConstructionSitePlan {					// +5
		BDOSRNICSP_AccordanceWithEnvironmentProtectionAndBiodiversityInterests,		// Keyword: BDOSRNICSP_AccordanceWithEnvironmentProtectionAndBiodiversityInterests
		NUM_BDOSRNICSP
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env2_4_5(){}

	Env2_4_5(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_BDOSRNIIC[NUM_BDOSRNIIC];			// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_BDOSRNIAT[NUM_BDOSRNIAT];			// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_BDOSRNICSP[NUM_BDOSRNICSP];			// XML:E

	Utilities::UsageType			m_usageType;

};

} // namespace DGNB

#endif // Env2_4_5H
