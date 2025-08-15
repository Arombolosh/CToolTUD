#include "DGNB_Pro2_3_4.h"

namespace DGNB {
	
double DGNB::Pro2_3_4::score() {
	double pro2_3_4 = 0;

	pro2_3_4 += ((m_flag_TMFOP[(TMFOP_AssignmentOfARegulationMonitoringToOptimiseOperation)].isEnabled() || m_flag_TMFOP[(TMFOP_AssignmentOfARegulationMonitoringToOptimiseOperation)].isEnabled()) ? 20 : 0);

	return pro2_3_4;
} // Pro2.3.4

} // namespace DGNB
