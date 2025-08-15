#include "DGNB_Site1_3_5.h"

namespace DGNB {
	
double DGNB::Site1_3_5::score() {
	double site1_3_5 = 0;

	// assigning points for Site1.3.5.1
	if (m_flag_ASW350M[(ASW350M_100PercentOfWalkwaysBetweenEntranceAndStationFeatureHeightDifferencesSmallerThan3cmAndMarkedBoardingSpots)].isEnabled())
		site1_3_5 += 10;
	else if (m_flag_ASW350M[(ASW350M_80PercentOfWalkwaysBetweenEntranceAndStationFeatureHeightDifferencesSmallerThan3cmAndMarkedBoardingSpots)].isEnabled())
		site1_3_5 += 5;
	
	// assigning points for Site1.3.5.2
	site1_3_5 += (m_flag_ASADRBS[(ASADRBS_TactileGuidingElementsPrivateWalkwayLoweringsAndCrossingsSeparatedFromCycletracksNoSightObstructionOrStairs)].isEnabled() ? 10 : 0);

	return site1_3_5;
} // Site1.3.5

} // namespace DGNB
