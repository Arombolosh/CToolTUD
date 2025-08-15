#include "DGNB_Soc1_1_1.h"

namespace DGNB {
	
double DGNB::Soc1_1_1::score() {
	double soc1_1_1 = 0, soc1_1_1_SC1 = 0, soc1_1_1_SC2 = 0, soc1_1_1_LP1 = 0, soc1_1_1_LP2 = 0;
	switch (m_usageType) {
		case Utilities::UT_ShoppingCenter:
			soc1_1_1_SC1 += (m_flag_OTRTOT[(OTRT_OperativeTemperatureCoolingPeriod)3].isEnabled() ? 10 : 0);
			soc1_1_1_SC1 += (m_flag_OTRTOT[(OTRT_OperativeTemperatureCoolingPeriod)4].isEnabled() ? 20 : 0);
			soc1_1_1_SC1 = std::min<double>(20, soc1_1_1_SC1);
			// TODO DGNB: Assuming we are allowed to interpolate points
			if (m_flag_OTRTOT[(OTRT_OperativeTemperatureCoolingPeriod)2].isEnabled()) {
				soc1_1_1_SC2 += 10 + 10 * ((m_para[(P_CurrentValue_soc1_1_1_ShoppingCenterRentalAreaCoolingLoad-40)].get_value())/20);
			} else {
				soc1_1_1_SC2 += (m_flag_OTRTOT[(OTRT_OperativeTemperatureCoolingPeriod)0].isEnabled() ? 10 : 0);
				soc1_1_1_SC2 += (m_flag_OTRTOT[(OTRT_OperativeTemperatureCoolingPeriod)1].isEnabled() ? 20 : 0);
				soc1_1_1_SC2 = std::min<double>(20, soc1_1_1_SC2);
			}
			soc1_1_1 += soc1_1_1_SC1 + soc1_1_1_SC2;
			break;

		case Utilities::UT_Logistics:
		case Utilities::UT_Production:
			soc1_1_1_LP1 += (m_flag_OTRTOT[(OTRT_OperativeTemperatureCoolingPeriod)0].isEnabled() ? 10 : 0);
			soc1_1_1_LP1 += (m_flag_OTRTOT[(OTRT_OperativeTemperatureCoolingPeriod)1].isEnabled() ? 15 : 0);
			soc1_1_1_LP1 = std::min<double>(20, soc1_1_1_LP1);
			soc1_1_1_LP2 += (m_flag_OTRTOT[(OTRT_OperativeTemperatureCoolingPeriod)5].isEnabled() ? 10 : 0);
			soc1_1_1_LP2 += (m_flag_OTRTOT[(OTRT_OperativeTemperatureCoolingPeriod)6].isEnabled() ? 15 : 0);
			soc1_1_1_LP2 = std::min<double>(20, soc1_1_1_LP2);
			soc1_1_1 += soc1_1_1_LP1 + soc1_1_1_LP2;
			break;

		default:
			soc1_1_1 += (m_flag_OTRTOT[(OTRT_OperativeTemperatureCoolingPeriod)0].isEnabled() ? 15 : 0);
			soc1_1_1 += (m_flag_OTRTOT[(OTRT_OperativeTemperatureCoolingPeriod)1].isEnabled() ? 35 : 0);
			soc1_1_1 = std::min<double>(35, soc1_1_1);
			break;
	}

	return soc1_1_1;
} // Soc1.1.1

} // namespace DGNB
