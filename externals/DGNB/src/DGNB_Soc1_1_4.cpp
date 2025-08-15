#include "DGNB_Soc1_1_4.h"

namespace DGNB {
	
double DGNB::Soc1_1_4::score() {
	double soc1_1_4 = 0;
	int rtaftcpCounter = 0;

	for (unsigned int i = 0; i < NUM_RTAFTCP; ++i)
		rtaftcpCounter += (m_flag_RTAFTCP[(RTAFT_CoolingPeriod)i].isEnabled() ? 1 : 0);
	if (rtaftcpCounter == 6)
		soc1_1_4 += 15;

	if (m_usageType == Utilities::UT_Logistics || m_usageType == Utilities::UT_Production)
		soc1_1_4 += (m_flag_RTAFTCP[(RTAFT_CoolingPeriod)6].isEnabled() ? 5 : 0);

	return soc1_1_4;
} // Soc1.1.4

} // namespace DGNB
