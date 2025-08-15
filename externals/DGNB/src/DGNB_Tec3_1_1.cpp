#include "DGNB_Tec3_1_1.h"

namespace DGNB {
	
double DGNB::Tec3_1_1::score() {
	double tec3_1_1 = 0;
	
	tec3_1_1 += (m_flag_MIMC[(MIMC_ConceptIncludesGoalsForSustainableMobility)].isEnabled() ? 5 : 0);
	tec3_1_1 += (m_flag_MIMC[(MIMC_ConceptIncludesFutureTrafficDemands)].isEnabled() ? 5 : 0);
	
	return tec3_1_1;
} // Tec3.1.1

} // namespace DGNB
