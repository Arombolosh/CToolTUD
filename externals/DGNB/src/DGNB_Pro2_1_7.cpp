#include "DGNB_Pro2_1_7.h"

namespace DGNB {
	
double DGNB::Pro2_1_7::score() {
	double pro2_1_7 = 0;

	pro2_1_7 += (m_flag_MP[(MP_CreationAndImplementationOfAnAerationProgrammSuitedToConstructionSituationGuaranteeingSufficientDryingOutOfSite)].isEnabled() ? 5 : 0);

	return pro2_1_7;
} // Pro2.1.7

} // namespace DGNB
