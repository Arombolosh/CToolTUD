#ifndef DGNB_Site1_3_2H
#define DGNB_Site1_3_2H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Site1.3.2 Public Transport */
class Site1_3_2
{
public:

	/*! Site 1.3.2.1 Stations */
	enum PT_Stations {																			// max +10
		PTS_DistancedWithin350Meters,															// Keyword: PTS_DistancedWithin350Meters
		NUM_PTS
	};

	/*! Site 1.3.2.2 Distance to next Train Station with at least Hourly Departures */
	enum PT_DistanceToNextTrainStationWithAtLeastHourlyDepartures {								// max +10
		PTDTSHD_NoMoreThan20Minutes,															// Keyword: PTDTSHD_NoMoreThan20Minutes
		PTDTSHD_NoMoreThan15Minutes,															// Keyword: PTDTSHD_NoMoreThan15Minutes
		PTDTSHD_NoMoreThan10Minutes,															// Keyword: PTDTSHD_NoMoreThan10Minutes
		NUM_PTDTSHD
	};

	/*! Site 1.3.2.3 Intervals Of Public Transport at 1 or more of the stations in 2.1 and 2.2 */
	enum PT_Intervals {																			// max +10
		PTI_NoMoreThan15Minutes,																// Keyword: PTI_NoMoreThan15Minutes
		PTI_NoMoreThan10Minutes,																// Keyword: PTI_NoMoreThan10Minutes
		PTI_NoMoreThan5Minutes,																	// Keyword: PTI_NoMoreThan5Minutes
		NUM_PTI
	};

	/*! Site 1.3.2.4 Relation to Building */
	enum PT_RelationToBuilding{																	// max +10
		PTRB_BuildingBulletinBoardOrSimilarFeaturesNearbyStationSchedulesOrDigitalDisplay,		// Keyword: PTRB_BuildingBulletinBoardOrSimilarFeaturesNearbyStationSchedulesOrDigitalDisplay
		PTRB_BuildingBulletinBoardOrSimilarFeaturesPlanOfSurroundingsWithStationsAndDistances,	// Keyword: PTRB_BuildingBulletinBoardOrSimilarFeaturesPlanOfSurroundingsWithStationsAndDistances
		PTRB_BuildingFeaturesSignageToStations,													// Keyword: PTRB_BuildingFeaturesSignageToStations
		NUM_PTRB
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Site1_3_2(){}

	Site1_3_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_PTS[NUM_PTS];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_PTDTSHD[NUM_PTDTSHD];		// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_PTI[NUM_PTI];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_PTRB[NUM_PTRB];				// XML:E

	Utilities::UsageType			m_usageType;
};

} // namespace DGNB

#endif // DGNB_Site1_3_2H
