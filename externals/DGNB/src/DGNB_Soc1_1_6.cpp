#include "DGNB_Soc1_1_6.h"

namespace DGNB {
	
double DGNB::Soc1_1_6::score() {
	double soc1_1_6 = 0;
	int uiCounter = 0;
	for (unsigned int i = 0; i < NUM_UI; ++i)
		uiCounter += (m_flag_UI[(UI_UserInfluence)i].isEnabled() ? 1 : 0);

	soc1_1_6 += std::min<double>(15, (5 * uiCounter));

	return soc1_1_6;
} // Soc1.1.6

} // namespace DGNB
