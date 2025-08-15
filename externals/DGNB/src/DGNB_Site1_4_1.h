#ifndef DGNB_Site1_4_1H
#define DGNB_Site1_4_1H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Site1.4.1 Social Infrastructure */
class Site1_4_1
{
public:

	/*! Site1.4.1.1 Within Quarter/Surroundings */
	enum SI_WithinQuarterOrSurroundings {																	// max +10
		SIQS_DaycareWithin5MinutesOnFootOrByPublicTransportAndWithin350Meters,								// Keyword: SIQS_DaycareWithin5MinutesOnFootOrByPublicTransportAndWithin350Meters
		SIQS_SecondaryOrVocationalSchoolWithin15MinutesOnFootOrByPublicTransportAndWithin1300Meters,		// Keyword: SIQS_SecondaryOrVocationalSchoolWithin15MinutesOnFootOrByPublicTransportAndWithin1300Meters
		SIQS_CinemaTheatreOrGalleryWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters,				// Keyword: SIQS_CinemaTheatreOrGalleryWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters
		SIQS_BookstoreWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters,							// Keyword: SIQS_BookstoreWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters
		SIQS_QuarterCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters,						// Keyword: SIQS_QuarterCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters
		SIQS_ParishHallWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters,							// Keyword: SIQS_ParishHallWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters
		SIQS_YouthCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters,							// Keyword: SIQS_YouthCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters
		SIQS_ElderlyCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters,						// Keyword: SIQS_ElderlyCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters
		SIQS_FitnessCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters,						// Keyword: SIQS_FitnessCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters
		SIQS_PubliclyAccessibleFitnessProgramInTheBuildingAndOpenToExternalUsers,							// Keyword: SIQS_PubliclyAccessibleFitnessProgramInTheBuildingAndOpenToExternalUsers
		SIQS_PlaygroundWithin5MinutesOnFootOrByPublicTransportAndWithin350Meters,							// Keyword: SIQS_PlaygroundWithin5MinutesOnFootOrByPublicTransportAndWithin350Meters
		SIQS_GymSportsFieldOrSwimmingPoolWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters,		// Keyword: SIQS_GymSportsFieldOrSwimmingPoolWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters
		NUM_SIQS
	};

	/*! Site1.4.1.2 Options To Use Indoor and Outdoor Building Spaces */
	enum SI_OptionsToUseIndoorAndOutdoorBuildingSpaces {													// max +10
		SIOUIOBS_ThirdPartiesHaveTheOptionToRentBuildingSpacesTemporarily,									// Keyword: SIOUIOBS_ThirdPartiesHaveTheOptionToRentBuildingSpacesTemporarily
		SIOUIOBS_SC_NeccessaryRoutingAccessibleOutsideOfBusinessHours,										// Keyword: SIOUIOBS_SC_NeccessaryRoutingAccessibleOutsideOfBusinessHours
		SIOUIOBS_OutdoorBuildingSpacesAccessibleToPublicAtAllTimes,											// Keyword: SIOUIOBS_OutdoorBuildingSpacesAccessibleToPublicAtAllTimes
		NUM_SIOUIOBS
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Site1_4_1(){}

	Site1_4_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_SIQS[NUM_SIQS];													// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_SIOUIOBS[NUM_SIOUIOBS];											// XML:E

	Utilities::UsageType			m_usageType;
};

} // namespace DGNB

#endif // DGNB_Site1_4_1H
