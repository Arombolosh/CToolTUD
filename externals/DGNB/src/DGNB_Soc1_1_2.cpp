#include "DGNB_Soc1_1_2.h"

namespace DGNB {
	
double DGNB::Soc1_1_2::score() {
	double soc1_1_2 = 0;
	bool airTemperatureNotTooDry = false;

	switch (m_usageType) {
		case Utilities::UT_Hotel:
			airTemperatureNotTooDry = (m_flag_RHHP[(RH_RelativeHumidityHeatingPeriod)1].isEnabled() ? true : false);
			break;

		default:
			airTemperatureNotTooDry = (m_flag_RHHP[(RH_RelativeHumidityHeatingPeriod)0].isEnabled() ? true : false);
			break;
	}

	soc1_1_2 += ((airTemperatureNotTooDry && m_flag_RHHP[(RH_RelativeHumidityHeatingPeriod)1].isEnabled()) ? 5 : 0);


	soc1_1_2 += (m_flag_RHCP[(RH_RelativeHumidityCoolingPeriod)0].isEnabled() ? 5 : 0);

	return soc1_1_2;
} // Soc1.1.2

} // namespace DGNB
