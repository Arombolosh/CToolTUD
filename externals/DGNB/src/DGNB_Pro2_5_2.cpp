#include "DGNB_Pro2_5_2.h"

namespace DGNB {
	
double DGNB::Pro2_5_2::score() {
	double pro2_5_2 = 0;

	pro2_5_2 += (m_flag_MIOSI[(MIOSI_CreationOfInstructionsAndHandoverToHiredServiceCompaniesOrConductors)].isEnabled() ? 10 : 0);
	pro2_5_2 += ((m_flag_MIOSI[(MIOSI_CreationOfMaintenanceAndUpkeepPlansForHighCareElementsOfCostGroups300And400)].isEnabled() && m_flag_MIOSI[(MIOSI_IncorporationOfGuidelinesForSustainableBuildingOperation)].isEnabled()) ? 10 : 0);

	return pro2_5_2;
} // Pro2.5.2

} // namespace DGNB
