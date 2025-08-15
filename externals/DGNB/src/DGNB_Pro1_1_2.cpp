#include "DGNB_Pro1_1_2.h"

namespace DGNB {
	
double DGNB::Pro1_1_2::scoreBonus() {
	double pro1_1_2Bonus = 0;

	pro1_1_2Bonus += (m_flag_A2030P[(A2030P_CounselDuringRequirementAnalysis)].isEnabled() ? 7 : 0);
	pro1_1_2Bonus += (m_flag_A2030P[(A2030P_ParticipationDuringRequirementAnalysis)].isEnabled() ? 10 : 0);
	pro1_1_2Bonus += (m_flag_A2030P[(A2030P_CounselDuringConceptionPhase)].isEnabled() ? 7 : 0);
	pro1_1_2Bonus += (m_flag_A2030P[(A2030P_ParticipationDuringConceptionPhase)].isEnabled() ? 10 : 0);
	pro1_1_2Bonus += (m_flag_A2030P[(A2030P_CounselDuringImplementationPhase)].isEnabled() ? 7 : 0);
	pro1_1_2Bonus += (m_flag_A2030P[(A2030P_ParticipationDuringImplementationPhase)].isEnabled() ? 10 : 0);

	pro1_1_2Bonus = std::min<double>(10, pro1_1_2Bonus);

	return pro1_1_2Bonus;
} // Pro1.1.2

} // namespace DGNB
