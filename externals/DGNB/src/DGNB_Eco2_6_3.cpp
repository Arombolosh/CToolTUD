#include "DGNB_Eco2_6_3.h"

namespace DGNB {
	
double DGNB::Eco2_6_3::score() {
	double scoreEco2_6_3 = 0;
	// assigning 5 pts for Eco2.6.3.1.1
	scoreEco2_6_3 += (m_flag_ASBCSA[(MAFERS_CompensationMeasuresAirQuality)0].isEnabled() ? 5 : 0);
	// assigning 2 pts for Eco2.6.3.1.2
	scoreEco2_6_3 += (m_flag_ASBCSA[(MAFERS_CompensationMeasuresAirQuality)1].isEnabled() ? 2 : 0);
	// assigning 3 pts for Eco2.6.3.1.3
	scoreEco2_6_3 += (m_flag_ASBCSA[(MAFERS_CompensationMeasuresAirQuality)1].isEnabled() ? 3 : 0);

	// assigning 3 pts for Eco2.6.3.2.1
	scoreEco2_6_3 += (m_flag_MAFERSCMN[(MAFERS_CompensationMeasuresNoise)0].isEnabled() ? 2.5 : 0);
	// assigning 3 pts for Eco2.6.3.2.2
	scoreEco2_6_3 += (m_flag_MAFERSCMN[(MAFERS_CompensationMeasuresNoise)1].isEnabled() ? 2.5 : 0);
	// assigning 3 pts for Eco2.6.3.2.3
	scoreEco2_6_3 += (m_flag_MAFERSCMN[(MAFERS_CompensationMeasuresNoise)2].isEnabled() ? 2.5 : 0);
	// assigning 3 pts for Eco2.6.3.2.4
	scoreEco2_6_3 += (m_flag_MAFERSCMN[(MAFERS_CompensationMeasuresNoise)3].isEnabled() ? 2.5 : 0);

	// assigning 3 pts for Eco2.6.3.2.4
	scoreEco2_6_3 += (m_flag_MAFERSRRR[(MAFERS_RadonRiskReduction)0].isEnabled() ? 5 : 0);

	return scoreEco2_6_3;
}

} // namespace DGNB
