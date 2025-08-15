#ifndef DGNB_Soc1_4_6H
#define DGNB_Soc1_4_6H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.4.6 Sunlight Exposure according to DIN EN 17037 */
class Soc1_4_6
{
public:

	/*! Soc1.4.6.1a Sunlight Exposure Duration - Residential */
	enum SED_Residential {												// max +5 / +10 depending on usage Type
		SEDR_1_5HoursExposureOfAtLeastOneRoomOfResidentialUnit,			// Keyword: SEDR_1_5HoursExposureOfAtLeastOneRoomOfResidentialUnit
		SEDR_2HoursExposureOfAtLeastOneRoomOfResidentialUnit,			// Keyword: SEDR_2HoursExposureOfAtLeastOneRoomOfResidentialUnit
		SEDR_3HoursExposureOfAtLeastOneRoomOfResidentialUnit,			// Keyword: SEDR_3HoursExposureOfAtLeastOneRoomOfResidentialUnit
		NUM_SEDR
	};

	/*! Soc1.4.6.1b Sunlight Exposure Duration - Hotel Healthcare */
	enum SED_HotelHealthcare {																	// max +5 / +10 depending on usage Type
		SEDHHC_1_5HoursExposureIn100PercentOfUnitsOrRooms,										// Keyword: SEDHHC_1_5HoursExposureIn100PercentOfUnitsOrRooms
		SEDHHC_2HoursExposureIn50PercentOfUnitsOrRooms,											// Keyword: SEDHHC_2HoursExposureIn50PercentOfUnitsOrRooms
		SEDHHC_2HoursExposureIn60PercentOfUnitsOrRoomsAnd1_5HoursExposureInRemaining40Percent,	// Keyword: SEDHHC_2HoursExposureIn60PercentOfUnitsOrRoomsAnd1_5HoursExposureInRemaining40Percent
		SEDHHC_3HoursExposureIn60PercentOfUnitsOrRoomsAnd1_5HoursExposureInRemaining40Percent,	// Keyword: SEDHHC_3HoursExposureIn60PercentOfUnitsOrRoomsAnd1_5HoursExposureInRemaining40Percent
		NUM_SEDHHC
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_4_6(){}

	Soc1_4_6(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag					m_flag_SEDR[NUM_SEDR];						// XML:E
	/*! List of flags. */
	IBK::Flag					m_flag_SEDHHC[NUM_SEDHHC];					// XML:E

	Utilities::UsageType		m_usageType;
	
};

} // namespace DGNB

#endif // DGNB_Soc1_4_6
