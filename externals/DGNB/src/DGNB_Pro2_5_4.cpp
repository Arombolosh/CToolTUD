#include "DGNB_Pro2_5_4.h"

namespace DGNB {
	
double DGNB::Pro2_5_4::score() {
	double pro2_5_4 = 0;

	pro2_5_4 += (m_flag_CWU[(CWU_CreationAndHandoverTechnicalOperationHandbook)].isEnabled() ? 10 : 0);
	pro2_5_4 += (m_flag_CWU[(CWU_PreparationAndHandoverOfQuestionaryOnUserSatisfactionDuringOperationPhase)].isEnabled() ? 10 : 0);

	return pro2_5_4;
} // Pro2.5.4

} // namespace DGNB
