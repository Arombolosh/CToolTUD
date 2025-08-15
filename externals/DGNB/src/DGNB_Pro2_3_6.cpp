#include "DGNB_Pro2_3_6.h"

namespace DGNB {
	
double DGNB::Pro2_3_6::score() {
	double pro2_3_6 = 0;

	pro2_3_6 += (m_flag_OSUM[(OSUM_StartUpManagementInAdditionToTechnicalManagement)].isEnabled() ? 25 : 0);

	return pro2_3_6;
} // Pro2.3.6

} // namespace DGNB
