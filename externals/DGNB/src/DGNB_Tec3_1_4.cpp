#include "DGNB_Tec3_1_4.h"

namespace DGNB {
	
double DGNB::Tec3_1_4::score() {
	double tec3_1_4 = 0;
	
	if (m_flag_IAFSBTEB[(RSMS_Alt_BuildingAndOccupantsArePartOfAQuarterMobilityConceptIncludingOrganisationAndSupportOfSharingsystems)].isEnabled())
		tec3_1_4 += 10;
	else if (m_flag_IAFSBTEB[(RSMS_ResultsSubmitted)].isEnabled())
		tec3_1_4 += std::min<double>(2, m_para[P_Tec3_1_4NumberOfIndividualNonOverlappingMobilitySharingOffers].get_value()) * 5;
	
	return tec3_1_4;
} // Tec3.1.4

} // namespace DGNB
