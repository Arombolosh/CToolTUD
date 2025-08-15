#include "DGNB_Site1_3_6.h"

namespace DGNB {
	
double DGNB::Site1_3_6::scoreBonus() {
	double site1_3_6Bonus = 0;
	
	// assigning points for Site1.3.6.1 Agenda 2030
	site1_3_6Bonus += (m_flag_A2030UPLI[(A2030UPLI_PublicLoadingInfrastructureForMotorisedIndividualTransportWithin350Meters)].isEnabled() ? 5 : 0);

	return site1_3_6Bonus;
} // Site1.3.6

} // namespace DGNB
