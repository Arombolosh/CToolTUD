#include "DGNB_Eco2_7_5.h"

namespace DGNB {
	
double DGNB::Eco2_7_5::score() {
	double scoreEco2_7_5 = 0;


	// assigning up to +5 pts for Eco2.7.4.2
	scoreEco2_7_5 += (m_flag_DCIBR[(DC_InformationOnBuildingRemovability)0].isEnabled() ? 10 : 0);

	return scoreEco2_7_5;
}

} // namespace DGNB
