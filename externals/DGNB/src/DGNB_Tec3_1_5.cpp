#include "DGNB_Tec3_1_5.h"

namespace DGNB {
	
double DGNB::Tec3_1_5::score() {
	double tec3_1_5 = 0;
	
	tec3_1_5 +=(m_flag_OCBGO[(OCBGO_SufficientAvailabilityOfShowers)].isEnabled() ? 5 : 0);
	tec3_1_5 +=(m_flag_OCBGO[(OCBGO_SufficientAvailabilityOfChangingRoomsAndDryingRoomsForBikeWear)].isEnabled() ? 5 : 0);
	tec3_1_5 +=(m_flag_OCBGO[(OCBGO_SufficientAvailabilityOfMaintenanceFacilitiesForBikes)].isEnabled() ? 5 : 0);
	tec3_1_5 +=(m_flag_OCBGO[(OCBGO_Residential_ParkingSpacesForBikeTrailers)].isEnabled() ? 5 : 0);
	
	tec3_1_5 = std::min<double>(15, tec3_1_5);
	
	return tec3_1_5;
} // Tec3.1.5

} // namespace DGNB
