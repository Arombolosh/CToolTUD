#include "DGNB_Eco2_7_2.h"

namespace DGNB {
	
double DGNB::Eco2_7_2::score() {
	double scoreEco2_7_2 = 0;


	// assigning up to +30/+10 pts for Eco2.7.2.1 depending on selection
	if (m_flag_ODBUROMP[(ODBU_RevisionOperationMaintenancePlan)0].isEnabled()) {
		scoreEco2_7_2 += (m_flag_ODBUROMP[(ODBU_RevisionOperationMaintenancePlan)1].isEnabled() ? 20 : 0);
		scoreEco2_7_2 += (m_flag_ODBUROMP[(ODBU_RevisionOperationMaintenancePlan)2].isEnabled() ? 10 : 0);
	} else {
		scoreEco2_7_2 += (m_flag_ODBUROMP[(ODBU_RevisionOperationMaintenancePlan)1].isEnabled() ? 5 : 0);
		scoreEco2_7_2 += (m_flag_ODBUROMP[(ODBU_RevisionOperationMaintenancePlan)2].isEnabled() ? 5 : 0);
	}

	// assigning up to +0/+10 pts for Eco2.7.2.2 depending on selection
	if (m_flag_ODBUOFBM[(ODBU_OperatorFriendlyBuildingModel)0].isEnabled() == false) {
		scoreEco2_7_2 += (m_flag_ODBUOFBM[(ODBU_OperatorFriendlyBuildingModel)1].isEnabled() ? 5 : 0);
		scoreEco2_7_2 += (m_flag_ODBUOFBM[(ODBU_OperatorFriendlyBuildingModel)2].isEnabled() ? 5 : 0);
	}

	return scoreEco2_7_2;
}

} // namespace DGNB
