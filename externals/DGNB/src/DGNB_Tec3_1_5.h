#ifndef DGNB_Tec3_1_5H
#define DGNB_Tec3_1_5H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

/*! Tec3.1.5 Occupation Comfort */
class Tec3_1_5
{
public:

	/*! Tec3.1.5 Occupation Comfort in the Building and for Groups of Occupants */
	enum OC_InTheBuildingAndForGroupsOfOccupants {								// max +20
		OCBGO_SufficientAvailabilityOfShowers,									// Keyword: OCBGO_SufficientAvailabilityOfShowers
		OCBGO_SufficientAvailabilityOfChangingRoomsAndDryingRoomsForBikeWear,	// Keyword: OCBGO_SufficientAvailabilityOfChangingRoomsAndDryingRoomsForBikeWear
		OCBGO_SufficientAvailabilityOfMaintenanceFacilitiesForBikes,			// Keyword: OCBGO_SufficientAvailabilityOfMaintenanceFacilitiesForBikes
		OCBGO_Residential_ParkingSpacesForBikeTrailers,							// Keyword: OCBGO_Residential_ParkingSpacesForBikeTrailers
		NUM_OCBGO
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Tec3_1_5(){}

	Tec3_1_5(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_OCBGO[NUM_OCBGO];			// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Tec3_1_5H
