#include "DGNB_Pro2_5_3.h"

namespace DGNB {
	
double DGNB::Pro2_5_3::score() {
	double pro2_5_3 = 0;

	pro2_5_3 += (m_flag_FMG[(FMG_CreationAndHandoverToFacilityManager)].isEnabled() ? 20 : 0);

	return pro2_5_3;
} // Pro2.5.3

} // namespace DGNB
