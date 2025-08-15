#ifndef DGNB_Env2_2_1H
#define DGNB_Env2_2_1H
#include "DGNB_Utilities.h"

namespace DGNB {
	
/*! Env2_2_1: concept for water usage */
class Env2_2_1 {													// +10
	public:

	/*! Env2_2_1_1: concept for water usage - superordinate concept */
	enum DWDWWV_SuperordinateConceptForWaterUsage {					// +7
		DWDWWVSCWU_ConceptDevelopedInEarlyPlanningStage,			// Keyword: DWDWWVSCWU_ConceptDevelopedInEarlyPlanningStage
		DWDWWVSCWU_FlowClassesOfSanitaryEquipment,					// Keyword: DWDWWVSCWU_FlowClassesOfSanitaryEquipment
		DWDWWVSCWU_LocalWaterUsageIndex,	/*! WEI+ */				// Keyword: DWDWWVSCWU_LocalWaterUsageIndex
		DWDWWVSCWU_PotentialOfRainAndGrayWaterUsage,				// Keyword: DWDWWVSCWU_PotentialOfRainAndGrayWaterUsage
		DWDWWVSCWU_EfficentWateringOfOutsideAreas,					// Keyword: DWDWWVSCWU_EfficentWateringOfOutsideAreas
		DWDWWVSCWU_EdequatePlanningOfWaterUsageMeteringPoint,		// Keyword: DWDWWVSCWU_EdequatePlanningOfWaterUsageMeteringPoint
		NUM_DWDWWVSCWU

	};

	/*! Env2_2_1_2: concept for water usage - providing updates to superordinate concept */
	enum DWDWWV_UpdatesToSuperordinateConcept {						// +3
		DWDWWVUSC_ConceptUpdatedToPlanningProgress,					// Keyword: DWDWWVUSC_ConceptUpdatedToPlanningProgress
		DWDWWVUSC_ImplementationOfDemonstrablyRelevantAspects,		// Keyword: DWDWWVUSC_ImplementationOfDemonstrablyRelevantAspects
		NUM_DWDWWVUSC
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env2_2_1(){}

	Env2_2_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_DWDWWVSCWU[NUM_DWDWWVSCWU];			// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_DWDWWVUSC[NUM_DWDWWVUSC];			// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // Env2_2_1H
