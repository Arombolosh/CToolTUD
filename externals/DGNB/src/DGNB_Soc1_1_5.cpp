#include "DGNB_Soc1_1_5.h"

namespace DGNB {
	
double DGNB::Soc1_1_5::scoreBonus() {
	double soc1_1_5 = 0;

	soc1_1_5 += ((m_flag_A2030CARTC[(A2030CA_ResilientThermalComfort)0].isEnabled() && m_flag_A2030CARTC[(A2030CA_ResilientThermalComfort)1].isEnabled()) ? 5 : 0);

	return soc1_1_5;
} // Soc1.1.5

} // namespace DGNB
