#ifndef DGNB_Soc1_4_5H
#define DGNB_Soc1_4_5H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.4.5 Artificial Light according to DIN EN 12464 */
class Soc1_4_5
{
public:

	/*! Soc1.4.5.1 Artificial Light - Lighting Concept */
	enum AL_LightingConcept {												// max +5 / +10 depending on usage Type
		ALLC_CreationOfLightingConcept,										// Keyword: ALLC_CreationOfLightingConcept
		NUM_ALLC
	};

	/*! Soc1.4.5.2 Artificial Light - Implementation of planned Concept and Observation of Requirements */
	enum AL_ImplementationOfPlannedConceptAndObservationOfRequirements {	// max +15 / +20 / +30 depending on usage Type
		ALIPCOR_DIN_EN_12464_1_IlluminationRequirementsMet,					// Keyword: ALIPCOR_DIN_EN_12464_1_IlluminationRequirementsMet
		ALIPCOR_AtLeastTwoOptimisationMeasuresTaken,						// Keyword: ALIPCOR_AtLeastTwoOptimisationMeasuresTaken
		ALIPCOR_AdditionalOptimisationMeasuresTaken,						// Keyword: ALIPCOR_AdditionalOptimisationMeasuresTaken
		NUM_ALIPCOR
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_4_5(){}

	Soc1_4_5(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag					m_flag_ALLC[NUM_ALLC];						// XML:E
	/*! List of flags. */
	IBK::Flag					m_flag_ALIPCOR[NUM_ALIPCOR];				// XML:E

	Utilities::UsageType		m_usageType;
	
};

} // namespace DGNB

#endif // DGNB_Soc1_4_5
