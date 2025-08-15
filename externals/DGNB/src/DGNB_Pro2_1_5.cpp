#include "DGNB_Pro2_1_5.h"

namespace DGNB {
	
double DGNB::Pro2_1_5::score() {
	double pro2_1_5 = 00;
	int cisiCounter = 0;

	pro2_1_5 += (m_flag_CESI[(CESI_NotificationOfNearbyResidentsOnProjectAndSite)].isEnabled() ? 5 : 0);
	pro2_1_5 += (m_flag_CECR[(CECR_DetailsOnHowResidentsAreInformedOnAndIncludedInProjectAsideFromSignage)].isEnabled() ? 5 : 0);

	for (unsigned int i = 0; i < NUM_CISI; ++i)
		cisiCounter += (m_flag_CISI[(C_InternalSharingOfInformation)i].isEnabled() ? 1 : 0);

	if (cisiCounter > 4)
		pro2_1_5 += 5;

	return pro2_1_5;
} // Pro2.1.5

} // namespace DGNB
