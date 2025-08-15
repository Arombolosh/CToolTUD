#include "DGNB_Pro1_1_1.h"

namespace DGNB {

double DGNB::Pro1_1_1::score() {
	double pro1_1_1 = 0;

	// assigning 20 pts if either is true
	pro1_1_1 += ((m_flag_RPB[(RPB_ImplementationOfDeclarationSustainabilityArchitecture)].isEnabled() || m_flag_RPB[(RPB_ImplementationOfDeclarationSustainabilityArchitecture)].isEnabled()) ? 20 : 0);

	if (m_flag_RPRP[(RPRP_PlanFollowsChecklist123OrAnnexe1C)].isEnabled())
		pro1_1_1 += 50;
	else if (m_flag_RPRP[(RPRP_PlanFollowsChecklist12OrAnnexe1B)].isEnabled())
		pro1_1_1 += 40;
	else if (m_flag_RPRP[(RPRP_PlanFollowsChecklist1OrAnnexe1A)].isEnabled())
		pro1_1_1 += 20;

	return pro1_1_1;
}

double DGNB::Pro1_1_1::scoreBonus() {
	double pro1_1_1Bonus = 0;

	// assigning 20 pts if either is true
	pro1_1_1Bonus += (m_flag_RPA2030FS[(RPA2030FS_FeasibilitySurveyConductedAllowingForImplementationOfSustainableConcepts)].isEnabled() ? 5 : 0);

	return pro1_1_1Bonus;
} // Pro1.1.1

} // namespace DGNB
