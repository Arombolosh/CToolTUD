#include "DGNB_Pro2_3_2.h"

namespace DGNB {
	
double DGNB::Pro2_3_2::score() {
	double pro2_3_2 = 0;

	pro2_3_2 += ((m_flag_TMCP[(TMCP_ContinuationOfAMonitoringConcept)].isEnabled() || m_flag_TMCP[(TMCP_CertifiedAlternativeSolution)].isEnabled()) ? 5 : 0);

	return pro2_3_2;
} // Pro2.3.2

} // namespace DGNB
