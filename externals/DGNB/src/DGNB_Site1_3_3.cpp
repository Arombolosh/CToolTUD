#include "DGNB_Site1_3_3.h"

namespace DGNB {
	
double DGNB::Site1_3_3::score() {
	double site1_3_3 = 0;

	// assigning points for Site1.3.3.1
	if (m_flag_BTCT500M[(BTCT500M_NoMixWithMotorTrafficOrSharedSpaceOrCycleTracks)].isEnabled())
		site1_3_3 += 5;
	else if (m_flag_BTCT500M[(BTCT500M_PartialMixWithMotorTraffic)].isEnabled())
		site1_3_3 += 2.5;

	// assigning points for Site1.3.3.2
	if (m_flag_BTC[(BTC_ContinuousInterregionalConnectionMoreThan10KM)].isEnabled())
		site1_3_3 += 5;
	else if (m_flag_BTC[(BTC_ContinuousRegionalConnection)].isEnabled())
		site1_3_3 += 2.5;

	// assigning points for Site1.3.3.3
	site1_3_3 += (m_flag_BTRB[(BTRB_RoutingOnSiteAllowsRidingUpToBuildingOrBicycleRacks)].isEnabled() ? 5 : 0);

	

	return site1_3_3;
} // Site1.3.3

} // namespace DGNB
