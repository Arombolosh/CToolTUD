#include "DGNB_Site1_3_2.h"

namespace DGNB {
	
double DGNB::Site1_3_2::score() {
	double site1_3_2 = 0;

	// assigning points for Site1.3.2.1
	site1_3_2 += (m_flag_PTS[(PTS_DistancedWithin350Meters)].isEnabled() ? 5 : 0);

	// assigning points for Site1.3.2.2
	if (m_flag_PTDTSHD[(PTDTSHD_NoMoreThan10Minutes)].isEnabled())
		site1_3_2 += 5;
	else if (m_flag_PTDTSHD[(PTDTSHD_NoMoreThan15Minutes)].isEnabled())
		site1_3_2 += 2.5;
	else if (m_flag_PTDTSHD[(PTDTSHD_NoMoreThan20Minutes)].isEnabled())
		site1_3_2 += 1;

	// assigning points for Site1.3.2.3
	if (m_flag_PTI[(PTI_NoMoreThan5Minutes)].isEnabled())
		site1_3_2 += 5;
	else if (m_flag_PTI[(PTI_NoMoreThan10Minutes)].isEnabled())
		site1_3_2 += 2.5;
	else if (m_flag_PTI[(PTI_NoMoreThan15Minutes)].isEnabled())
		site1_3_2 += 1;

	// assigning points for Site1.3.2.4
	site1_3_2 += (m_flag_PTRB[(PTRB_BuildingBulletinBoardOrSimilarFeaturesNearbyStationSchedulesOrDigitalDisplay)].isEnabled() ? 5 : 0);
	site1_3_2 += ((m_flag_PTRB[(PTRB_BuildingBulletinBoardOrSimilarFeaturesPlanOfSurroundingsWithStationsAndDistances)].isEnabled() || m_flag_PTRB[(PTRB_BuildingFeaturesSignageToStations)].isEnabled())? 5 : 0);

	return site1_3_2;
} // Site1.3.2

} // namespace DGNB
