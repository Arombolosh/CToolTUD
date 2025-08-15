#include "DGNB_Soc1_6_1.h"

namespace DGNB {
	
double DGNB::Soc1_6_1::score() {
	double soc1_6_1 = 0;
	int soc1_6_1NumberOfInnovativeCommunicationConstellations = m_para[(P_AlternativeInnovativeCommunicationConstellations)].get_value();

	if (m_flag_CSOCZMU[(CSO_CommunicationZoneMainUsage)2].isEnabled()) {
		soc1_6_1 += 7.5 * soc1_6_1NumberOfInnovativeCommunicationConstellations;
	} else {
		soc1_6_1 += (m_flag_CSOCZMU[(CSO_CommunicationZoneMainUsage)0].isEnabled() ? 7.5 : 0);
		soc1_6_1 += (m_flag_CSOCZMU[(CSO_CommunicationZoneMainUsage)1].isEnabled() ? 7.5 : 0);
	}
	soc1_6_1 = std::min<double>(15, soc1_6_1);

	return soc1_6_1;
} // Soc1.6.1

} // namespace DGNB
