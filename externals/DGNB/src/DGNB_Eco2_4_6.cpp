#include "DGNB_Eco2_4_6.h"

namespace DGNB {
	
double DGNB::Eco2_4_6::scoreBonus() {
	double scoreEco2_4_6Bonus = 0;

	scoreEco2_4_6Bonus += (m_flag_A2030CDI[(A2030CDI_QualityOfInternetConnection)].isEnabled() ? 5 : 0);

	return scoreEco2_4_6Bonus;
}

} // namespace DGNB
