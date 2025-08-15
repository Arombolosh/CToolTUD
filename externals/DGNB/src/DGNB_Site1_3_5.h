#ifndef DGNB_Site1_3_5H
#define DGNB_Site1_3_5H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Site1.3.5 Accessible Stations */
class Site1_3_5
{
public:

	/*! Site 1.3.5.1 Stations Within 350 Meters of Building Main Entrance*/
	enum AS_Within350Meters {																									// max +5
		ASW350M_80PercentOfWalkwaysBetweenEntranceAndStationFeatureHeightDifferencesSmallerThan3cmAndMarkedBoardingSpots,		// Keyword: ASW350M_80PercentOfWalkwaysBetweenEntranceAndStationFeatureHeightDifferencesSmallerThan3cmAndMarkedBoardingSpots
		ASW350M_100PercentOfWalkwaysBetweenEntranceAndStationFeatureHeightDifferencesSmallerThan3cmAndMarkedBoardingSpots,		// Keyword: ASW350M_100PercentOfWalkwaysBetweenEntranceAndStationFeatureHeightDifferencesSmallerThan3cmAndMarkedBoardingSpots
		NUM_ASW350M
	};

	/*! Site 1.3.5.2 Accessible Development of Routing to Building and Surroundings */
	enum AS_AccessibleDevelopmentOfRoutingToBuildingAndSurroundings {															// max +10
		ASADRBS_TactileGuidingElementsPrivateWalkwayLoweringsAndCrossingsSeparatedFromCycletracksNoSightObstructionOrStairs,	// Keyword: ASADRBS_TactileGuidingElementsPrivateWalkwayLoweringsAndCrossingsSeparatedFromCycletracksNoSightObstructionOrStairs
		NUM_ASADRBS
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Site1_3_5(){}

	Site1_3_5(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_ASW350M[NUM_ASW350M];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_ASADRBS[NUM_ASADRBS];				// XML:E

	Utilities::UsageType			m_usageType;
};

} // namespace DGNB

#endif // DGNB_Site1_3_5H
