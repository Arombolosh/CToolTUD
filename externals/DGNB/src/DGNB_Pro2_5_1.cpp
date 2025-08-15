#include "DGNB_Pro2_5_1.h"

namespace DGNB {
	
double DGNB::Pro2_5_1::score() {
	double pro2_5_1 = 0;

	pro2_5_1 += (m_flag_FMC[(FMC_ConductionWithRegardToAccessibilityOperationRoutingAndAreaUsage)].isEnabled() ? 20 : 0);

	return pro2_5_1;
} // Pro2.5.1

} // namespace DGNB
