#ifndef DGNB_Tec3_1_1H
#define DGNB_Tec3_1_1H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

/*! Tec3.1.1 Mobility Infrastructure */
class Tec3_1_1
{
public:

	/*! Tec3.1 Mobility Concept */
	enum MI_MobilityConcept {											// impact on scoring of several indicators
		MIMC_ConceptIncludesGoalsForSustainableMobility,				// Keyword: MIMC_ConceptIncludesGoalsForSustainableMobility
		MIMC_ConceptIncludesFutureTrafficDemands,						// Keyword: MIMC_ConceptIncludesFutureTrafficDemands
		NUM_MIMC
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Tec3_1_1(){}

	Tec3_1_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_MIMC[NUM_MIMC];				// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Tec3_1_1H
