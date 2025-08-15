#include "DGNB_Tec1_3_5.h"

namespace DGNB {
	
double DGNB::Tec1_3_5::score() {
	double tec1_3_5 = 0;

	tec1_3_5 += (m_flag_QAMQC[(QAMQC_BlowerDoorTest)].isEnabled() ? 10 : 0);
	tec1_3_5 += (m_flag_QAMQC[(QAMQC_BuildingThermographyDuringBuildingPhase)].isEnabled() ? 10 : 0);
	tec1_3_5 += (m_flag_QAMQC[(QAMQC_OtherRelevantMeasurements)].isEnabled() ? 10 : 0);

	tec1_3_5 = std::min<double>(20, tec1_3_5);

	return tec1_3_5;
} // Tec1.3.5

} // namespace DGNB
