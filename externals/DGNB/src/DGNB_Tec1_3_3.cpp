#include "DGNB_Tec1_3_3.h"

namespace DGNB {
	
double DGNB::Tec1_3_3::score() {
	double tec1_3_3 = 0;
	double currentTec1_3_3AirExchangeRateThroughBuildingEnvelope = m_para[(P_Tec1_3_3AirExchangeRateThroughBuildingEnvelope)].get_value();
	double currentTec1_3_3AirExchangeRateRelativeToEnvelopeSurface = m_para[(P_Tec1_3_3AirExchangeRateRelativeToEnvelopeSurface)].get_value();

	if (m_flag_ABEM[(ABEM_ResultsSubmitted)].isEnabled()) {
		if (m_flag_ABEM[(ABEM_BuildingAirVolumeGreaterThan1500sqm)].isEnabled() == false) {
			if (currentTec1_3_3AirExchangeRateThroughBuildingEnvelope <= 0.6)
				tec1_3_3 += 10;
			else if (currentTec1_3_3AirExchangeRateThroughBuildingEnvelope <= 1.0)
				tec1_3_3 += 5;
			else if (currentTec1_3_3AirExchangeRateThroughBuildingEnvelope <= 1.5)
				tec1_3_3 += 2.5;
		} else if (m_flag_ABEM[(ABEM_BuildingAirVolumeGreaterThan1500sqm)].isEnabled()) {
			if (currentTec1_3_3AirExchangeRateThroughBuildingEnvelope <= 0.6 && currentTec1_3_3AirExchangeRateRelativeToEnvelopeSurface <= 1.8)
				tec1_3_3 += 10;
			else if (currentTec1_3_3AirExchangeRateThroughBuildingEnvelope <= 1.0 && currentTec1_3_3AirExchangeRateRelativeToEnvelopeSurface <= 2.0)
				tec1_3_3 += 5;
			else if (currentTec1_3_3AirExchangeRateThroughBuildingEnvelope <= 1.5 && currentTec1_3_3AirExchangeRateRelativeToEnvelopeSurface <= 2.5)
				tec1_3_3 += 2.5;
		}
	}
	return tec1_3_3;
} // Tec1.3.3

} // namespace DGNB
