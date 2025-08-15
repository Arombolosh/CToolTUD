#include "DGNB_Site1_4_1.h"

namespace DGNB {
	
double DGNB::Site1_4_1::score() {
	double site1_4_1 = 0;
	
	// assigning points for Site1.4.1.1
	site1_4_1 += (m_flag_SIQS[(SIQS_DaycareWithin5MinutesOnFootOrByPublicTransportAndWithin350Meters)].isEnabled() ? 10 : 0);
	site1_4_1 += (m_flag_SIQS[(SIQS_SecondaryOrVocationalSchoolWithin15MinutesOnFootOrByPublicTransportAndWithin1300Meters)].isEnabled() ? 5 : 0);
	site1_4_1 += (m_flag_SIQS[(SIQS_CinemaTheatreOrGalleryWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters)].isEnabled() ? 5 : 0);
	site1_4_1 += (m_flag_SIQS[(SIQS_BookstoreWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters)].isEnabled() ? 5 : 0);
	site1_4_1 += (m_flag_SIQS[(SIQS_QuarterCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters)].isEnabled() ? 5 : 0);
	site1_4_1 += (m_flag_SIQS[(SIQS_ParishHallWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters)].isEnabled() ? 5 : 0);
	site1_4_1 += (m_flag_SIQS[(SIQS_YouthCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters)].isEnabled() ? 5 : 0);
	site1_4_1 += (m_flag_SIQS[(SIQS_ElderlyCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters)].isEnabled() ? 5 : 0);
	site1_4_1 += ((m_flag_SIQS[(SIQS_FitnessCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters)].isEnabled() || m_flag_SIQS[(SIQS_PubliclyAccessibleFitnessProgramInTheBuildingAndOpenToExternalUsers)].isEnabled()) ? 5 : 0);
	site1_4_1 += (m_flag_SIQS[(SIQS_PlaygroundWithin5MinutesOnFootOrByPublicTransportAndWithin350Meters)].isEnabled() ? 10 : 0);
	site1_4_1 += (m_flag_SIQS[(SIQS_GymSportsFieldOrSwimmingPoolWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters)].isEnabled() ? 5 : 0);

	// capping points at 35
	site1_4_1 = std::min<double>(35, site1_4_1);

	// assigning points for Site1.4.1.2
	switch(m_usageType) {
		case Utilities::UT_ShoppingCenter:
			site1_4_1 += ((m_flag_SIOUIOBS[(SIOUIOBS_ThirdPartiesHaveTheOptionToRentBuildingSpacesTemporarily)].isEnabled() && m_flag_SIOUIOBS[(SIOUIOBS_SC_NeccessaryRoutingAccessibleOutsideOfBusinessHours)].isEnabled()) ? 10 : 0);
			break;
		default:
			site1_4_1 += (m_flag_SIOUIOBS[(SIOUIOBS_ThirdPartiesHaveTheOptionToRentBuildingSpacesTemporarily)].isEnabled() ? 10 : 0);
			break;
	}
	site1_4_1 += (m_flag_SIOUIOBS[(SIOUIOBS_OutdoorBuildingSpacesAccessibleToPublicAtAllTimes)].isEnabled() ? 10 : 0);

	// capping points at 35 again because 1.1 and 1.2 combined may only receive 35 points
	site1_4_1 = std::min<double>(35, site1_4_1);

	return site1_4_1;
} // Site1.3.6

} // namespace DGNB
