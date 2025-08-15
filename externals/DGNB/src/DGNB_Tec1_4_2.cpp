#include "DGNB_Tec1_4_2.h"

namespace DGNB {
	
double DGNB::Tec1_4_2::score() {
	double tec1_4_2 = 0;

	if (m_flag_AAOTIREW[(AAOTIREW_AverageTemperatureOf35DegreesOrLess)].isEnabled() || m_flag_AAOTIREW[(AAOTIREW_NoHeatingSystemInBuilding)].isEnabled() || m_flag_AAOTIREW[(AAOTIREW_100PercentOfWarmthDemandCoveredByRegenerativeEnergy)].isEnabled())
		tec1_4_2 += 7.5;
	else if (m_flag_AAOTIREW[(AAOTIREW_AverageTemperatureBetween35and50Degrees)].isEnabled())
		tec1_4_2 += 4;
	else if (m_flag_AAOTIREW[(AAOTIREW_AverageTemperatureOf50DegreesOrMore)].isEnabled())
		tec1_4_2 += 1;
	
	if (m_flag_AAOTIREC[(AAOTIREC_AverageTemperatureOf19DegreesOrMore)].isEnabled() || m_flag_AAOTIREC[(AAOTIREC_NoCoolingSystemInBuilding)].isEnabled() || m_flag_AAOTIREC[(AAOTIREC_100PercentOfCoolingDemandCoveredByRegenerativeEnergy)].isEnabled())
		tec1_4_2 += 7.5;
	else if (m_flag_AAOTIREC[(AAOTIREC_AverageTemperatureBetween14and19Degrees)].isEnabled())
		tec1_4_2 += 4;
	else if (m_flag_AAOTIREC[(AAOTIREC_AverageTemperatureOf14DegreesOrLess)].isEnabled())
		tec1_4_2 += 1;

	return tec1_4_2;
} // Tec1.4.2

} // namespace DGNB
