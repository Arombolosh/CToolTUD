#include "DGNB_Pro2_3_5.h"

namespace DGNB {
	
double DGNB::Pro2_3_5::score() {
	double pro2_3_5 = 0;

	pro2_3_5 += (m_flag_TMCM[(TMCM_AssignmentOfACompleteTechnicalMonitoring)].isEnabled() ? 70 : 0);

	return pro2_3_5;
} // Pro2.3.5

} // namespace DGNB
