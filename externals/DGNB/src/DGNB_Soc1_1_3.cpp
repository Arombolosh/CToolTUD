#include "DGNB_Soc1_1_3.h"

namespace DGNB {
	
double DGNB::Soc1_1_3::score() {
	double soc1_1_3 = 0;

	switch (m_usageType) {
		case Utilities::UT_ShoppingCenter:
			soc1_1_3 += (m_flag_DCP[(D_CoolingPeriod)1].isEnabled() ? 20 : 0);
			break;

		default:
			soc1_1_3 += (m_flag_DCP[(D_CoolingPeriod)0].isEnabled() ? 25 : 0);
			break;
	}

	return soc1_1_3;
} // Soc1.1.3

} // namespace DGNB
