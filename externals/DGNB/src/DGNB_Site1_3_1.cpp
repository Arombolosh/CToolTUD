#include "DGNB_Site1_3_1.h"

namespace DGNB {
	
double DGNB::Site1_3_1::score() {
	double site1_3_1 = 0;
	
	site1_3_1 += (m_flag_MITS[(MITS_ConnectionToBundesstrasseA_Road)].isEnabled() ? 5 : 0);
	site1_3_1 += (m_flag_MITS[(MITS_ConnectionToFreeway)].isEnabled() ? 5 : 0);
	site1_3_1 += (m_flag_MITS[(MITS_ConnectionToMainStreet)].isEnabled() ? 5 : 0);

	site1_3_1 += (m_flag_MITRB[(MITRB_BuildingParkingSpacesAreIntegratedIntoSuperordinateParkingConceptOfParkingAreasUsedMostlyByUserGroupsOfSeveralBuildingsInTheQuarter)].isEnabled() ? 10 : 0);

	return site1_3_1;
} // Site1.3.1

} // namespace DGNB
