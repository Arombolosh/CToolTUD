#include "DGNB_Pro2_3_7.h"

namespace DGNB {
	
double DGNB::Pro2_3_7::score() {
	double pro2_3_7 = 0;

	pro2_3_7 += (m_flag_BP[(BP_AssignmentOfContinuousImprovementProcessAfterHandover)].isEnabled() ? 15 : 0);

	return pro2_3_7;
} // Pro2.3.7

} // namespace DGNB
