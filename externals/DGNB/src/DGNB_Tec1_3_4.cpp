#include "DGNB_Tec1_3_4.h"

namespace DGNB {
	
double DGNB::Tec1_3_4::score() {
	double tec1_3_4 = 0;

	tec1_3_4 += (m_flag_HISVV[(HISVV_ExaminationOfDifferentVariations)].isEnabled() ? 5 : 0);
	tec1_3_4 += (m_flag_HISVV[(HISVV_ExaminationOfNonCommonRooms)].isEnabled() ? 5 : 0);
	tec1_3_4 += (m_flag_HISVV[(HISVV_ExaminationOfBuildingWithLocalClimateDataAndImplementationOfResultsDuringPlanning)].isEnabled() ? 10 : 0);
	if (m_flag_HISVV[(HISVV_UndercuttingLegalMinimumRequirementsByAtLeast20PercentResultsSubmitted)].isEnabled()){
		if (m_para[(P_Tec1_3_4UntercuttingOfLegalRequirements)].get_value() >= 20)
			tec1_3_4 += (m_para[(P_Tec1_3_4UntercuttingOfLegalRequirements)].get_value() -20) /80 * 10;
	}

	tec1_3_4 = std::min<double>(20, tec1_3_4);

	return tec1_3_4;
} // Tec1.3.4

} // namespace DGNB
