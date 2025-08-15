#ifndef DGNB_Site1_3_4H
#define DGNB_Site1_3_4H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Site1.3.4 Foot Traffic */
class Site1_3_4
{
public:

	/*! Site 1.3.4.1 Walkway Network Within 350 Meters of Building Main Entrance*/
	enum FT_WalkwayNetworkWithin350Meters {										// max +5
		FTWN350M_50PercentOrMoreCoverage,										// Keyword: FTWN350M_50PercentOrMoreCoverage
		FTWN350M_80PercentOrMoreCoverage,										// Keyword: FTWN350M_80PercentOrMoreCoverage
		FTWN350M_100PercentCoverage,											// Keyword: FTWN350M_100PercentCoverage
		NUM_FTWN350M
	};

	/*! Site 1.3.4.2 Crossing Options Within 350 Meters of Building Main Entrance */
	enum FT_CrossingOptionsWithin350Meters {									// max +5
		FTCO350M_80PercentOfStreetsAreSafeToCrossAndCrossingsAreSafeToReach,	// Keyword: FTCO350M_80PercentOfStreetsAreSafeToCrossAndCrossingsAreSafeToReach
		FTCO350M_100PercentOfStreetsAreSafeToCrossAndCrossingsAreSafeToReach,	// Keyword: FTCO350M_100PercentOfStreetsAreSafeToCrossAndCrossingsAreSafeToReach
		NUM_FTCO350M
	};

	/*! Site 1.3.4 Signage Systems */
	enum FT_SignageSystems{														// max +5
		FTSS_SignageCoversSurroundingArea,										// Keyword: FTSS_SignageCoversSurroundingArea
		FTSS_SignageAndOrientationPlansCoverSurroundingArea,					// Keyword: FTSS_SignageAndOrientationPlansCoverSurroundingArea
		NUM_FTSS
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Site1_3_4(){}

	Site1_3_4(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_FTWN350M[NUM_FTWN350M];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_FTCO350M[NUM_FTCO350M];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_FTSS[NUM_FTSS];						// XML:E

	Utilities::UsageType			m_usageType;
};

} // namespace DGNB

#endif // DGNB_Site1_3_4H
