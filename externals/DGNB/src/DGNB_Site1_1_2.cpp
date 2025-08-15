#include "DGNB_Site1_1_2.h"

namespace DGNB {
	
double DGNB::Site1_1_2::score() {
	double site1_1_2 = 0;
	
	site1_1_2 += (m_flag_ECRSCFPRECC[(ECRSCFPRECC_DeterminedRisksAndVulnerabilitiesOnSiteExclusivelyMinorToOperationUsersAndAssetValue)].isEnabled() ? 10 : 0);

	return site1_1_2;
} // Site1.1.2

} // namespace DGNB
