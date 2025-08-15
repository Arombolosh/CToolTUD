#include "DGNB_Pro2_3_3.h"

namespace DGNB {
	
double DGNB::Pro2_3_3::score() {
	double pro2_3_3 = 0;

	pro2_3_3 += ((m_flag_TO[(TO_TrialOperationConductedPriorToApprovalAndHandover)].isEnabled() || m_flag_TO[(TO_CertifiedAlternativeSolution)].isEnabled()) ? 20 : 0);

	return pro2_3_3;
} // Pro2.3.3

} // namespace DGNB
