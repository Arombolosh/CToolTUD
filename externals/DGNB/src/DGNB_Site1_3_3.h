#ifndef DGNB_Site1_3_3H
#define DGNB_Site1_3_3H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Site1.3.3 Bicycle Traffic */
class Site1_3_3
{
public:

	/*! Site 1.3.3.1 Cycle Track within 500 Meters */
	enum BT_CycleTrackWithin500Meters {									// max +5
		BTCT500M_PartialMixWithMotorTraffic,							// Keyword: BTCT500M_PartialMixWithMotorTraffic
		BTCT500M_NoMixWithMotorTrafficOrSharedSpaceOrCycleTracks,		// Keyword: BTCT500M_NoMixWithMotorTrafficOrSharedSpaceOrCycleTracks
		NUM_BTCT500M
	};

	/*! Site 1.3.3.2 Connection */
	enum BT_Connection {												// max +5
		BTC_ContinuousRegionalConnection,								// Keyword: BTC_ContinuousRegionalConnection
		BTC_ContinuousInterregionalConnectionMoreThan10KM,				// Keyword: BTC_ContinuousInterregionalConnectionMoreThan10KM
		NUM_BTC
	};

	/*! Site 1.3.3.3 Relation to Building */
	enum BT_RelationToBuilding{											// max +5
		BTRB_RoutingOnSiteAllowsRidingUpToBuildingOrBicycleRacks,		// Keyword: BTRB_RoutingOnSiteAllowsRidingUpToBuildingOrBicycleRacks
		NUM_BTRB
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Site1_3_3(){}

	Site1_3_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_BTCT500M[NUM_BTCT500M];		// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_BTC[NUM_BTC];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_BTRB[NUM_BTRB];				// XML:E

	Utilities::UsageType			m_usageType;
};

} // namespace DGNB

#endif // DGNB_Site1_3_3H
