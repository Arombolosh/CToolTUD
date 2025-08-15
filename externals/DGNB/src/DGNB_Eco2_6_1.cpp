#include "DGNB_Eco2_6_1.h"

namespace DGNB {
	
double DGNB::Eco2_6_1::score() {
	double scoreEco2_6_1 = 0;

	scoreEco2_6_1 += (m_flag_BCRMPVPrePH4[(BCRMPV_PrePlanningphase4)0].isEnabled() ? 15 : 0);

	scoreEco2_6_1 += ((m_flag_BCRMPVPostPH4[(BCRMPV_PostPlanningphase4)0].isEnabled() && m_flag_BCRMPVPostPH4[(BCRMPV_PostPlanningphase4)1].isEnabled()) ? 10 : 0);
	scoreEco2_6_1 = std::min<double>(15, scoreEco2_6_1);

	return scoreEco2_6_1;
}

double DGNB::Eco2_6_1::scoreBonus() {
	double scoreEco2_6_1Bonus = 0;

	scoreEco2_6_1Bonus += (m_flag_A2030CBA[(Agenda2030_CostBenefitAnalysis)0].isEnabled() ? 5 : 0);
	return scoreEco2_6_1Bonus;
}

} // namespace DGNB
