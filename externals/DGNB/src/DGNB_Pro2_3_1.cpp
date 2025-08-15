#include "DGNB_Pro2_3_1.h"

namespace DGNB {
	
double DGNB::Pro2_3_1::score() {
	double pro2_3_1 = 0;

	pro2_3_1 += ((m_flag_TMPP[(TMPP_DesignOfAMonitoringConceptIncludingEnergeticMonitoring)].isEnabled() || m_flag_TMPP[(TMPP_CertifiedAlternativeSolution)].isEnabled()) ? 15 : 0);

	return pro2_3_1;
} // Pro2.3.1

} // namespace DGNB
