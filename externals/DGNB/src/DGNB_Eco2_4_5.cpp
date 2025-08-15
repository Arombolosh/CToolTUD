#include "DGNB_Eco2_4_5.h"

namespace DGNB {
	
double DGNB::Eco2_4_5::score() {
	double scoreEco2_4_5 = 0;

	scoreEco2_4_5 += (m_flag_RAAEF[(RAAEF_RiskAnalysisDuringEarlyPlanningPhases)].isEnabled() ? 5 : 0);
	scoreEco2_4_5 += ((m_flag_RABCT[(RABCT_AspirationsForVerification)].isEnabled() && m_flag_RABCT[(RABCT_ImplementationOfStandards)].isEnabled()) ? 10 : 0);

	scoreEco2_4_5 = std::min<double>(10, scoreEco2_4_5);

	return scoreEco2_4_5;
}

} // namespace DGNB
