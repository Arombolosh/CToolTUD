#include "DGNB_Pro2_5_6.h"

namespace DGNB {
	
double DGNB::Pro2_5_6::score() {
	double pro2_5_6 = 0;

	pro2_5_6 += (m_flag_OCPE[(OCPE_CreationOfExtendedOperationCostPrognosis)].isEnabled() ? 10 : 0);

	return pro2_5_6;
} // Pro2.5.6

} // namespace DGNB
