#ifndef DGNB_Site1_1_2H
#define DGNB_Site1_1_2H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Site1.1.2 Evaluation Of Climate Risks On Site */
class Site1_1_2
{
public:

	/*! Site 1.1.2 Evaluation of Current and Future Physical Risks from Environment and Climate Change */
	enum ECRS_CurrentAndFuturePhysicalRisksDueToEnvironmentAndClimateChange {								// max +10
		ECRSCFPRECC_DeterminedRisksAndVulnerabilitiesOnSiteExclusivelyMinorToOperationUsersAndAssetValue,	// Keyword: ECRSCFPRECC_DeterminedRisksAndVulnerabilitiesOnSiteExclusivelyMinorToOperationUsersAndAssetValue
		NUM_ECRSCFPRECC
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Site1_1_2(){}

	Site1_1_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_ECRSCFPRECC[NUM_ECRSCFPRECC];									// XML:E

	Utilities::UsageType			m_usageType;
};

} // namespace DGNB

#endif // DGNB_Site1_1_2H
