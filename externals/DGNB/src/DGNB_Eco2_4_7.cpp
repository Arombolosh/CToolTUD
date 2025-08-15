#include "DGNB_Eco2_4_7.h"

namespace DGNB {
	
double DGNB::Eco2_4_7::scoreBonus() {
	double scoreEco2_4_7Bonus = 0;

	scoreEco2_4_7Bonus += (m_flag_A2030E[(A2030E_Concept)].isEnabled() ? 5 : 0);
	scoreEco2_4_7Bonus += (m_flag_A2030IA[(A2030IA_AddressEffect)].isEnabled() ? 5 : 0);

	return scoreEco2_4_7Bonus;
}

} // namespace DGNB
