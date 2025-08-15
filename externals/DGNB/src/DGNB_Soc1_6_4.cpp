#include "DGNB_Soc1_6_4.h"

namespace DGNB {
	
double DGNB::Soc1_6_4::score() {
	double soc1_6_4 = 0;
	int qsiiaCounter = 0;

	for (unsigned int i = 0; i<(NUM_QSIAA-1); ++i)
		qsiiaCounter += (m_flag_QSIAA[(QS_InnerAllotmentAreas)i].isEnabled() ? 1 : 0);

	qsiiaCounter += (m_flag_QSIAA[(QS_InnerAllotmentAreas)4].isEnabled() ? m_para[(P_Soc1_6_4_1AlternativeInnovativeSolutions)].get_value() : 0);

	if (qsiiaCounter >= 5)
		soc1_6_4 += 20;
	else if (qsiiaCounter == 4)
		soc1_6_4 += 15;
	else if (qsiiaCounter == 3)
		soc1_6_4 += 10;

	return soc1_6_4;
} // Soc1.6.4

} // namespace DGNB
