#include "DGNB_Env2_2_2.h"

namespace DGNB {

double DGNB::Env2_2_2::score() {
	double env2_2_2 = 0;
	// assigning points with dynamic reference value = X * threshold value and dynamic target value = Y * threshold value depending on usage type
	// TODO DGNB the norm doesn't state that the use of interpolation is permitted but since otherwise there would be no regulation for (threshold > waterUsageIndex > reference value) and (reference value > waterUsageIndex > target value) it seems safe to assume that interpolation was intended
	/*! drinking water demand and waste water management: Water Usage Index */

	double thresholdValueEnv2_2_2_1 = m_para[(P_RefValue_env2_2DWDWWVWUI_DynamicThreshold)].get_value();
	double referenceValue2_2_2_1 = 0, targetValue2_2_2_1 = 0;
	double currentValueEnv2_2_2_1 = m_para[(P_CurrentValue_env2_2WaterUsageIndex)].get_value();
	if (m_flag_DWDWWVWUI[(DWDWWVWUI_ResultsSubmitted)].isEnabled()) {
		switch (m_usageType) {
			case Utilities::UT_Residential:
				referenceValue2_2_2_1 = 0.68 * thresholdValueEnv2_2_2_1;
				targetValue2_2_2_1 = 0.46 * thresholdValueEnv2_2_2_1;
			break;
			default:
				referenceValue2_2_2_1 = 0.66 * thresholdValueEnv2_2_2_1;
				targetValue2_2_2_1 = 0.33 * thresholdValueEnv2_2_2_1;
			break;
		}

	std::vector<double> xVal_2_5_1{targetValue2_2_2_1, referenceValue2_2_2_1, thresholdValueEnv2_2_2_1};
	std::vector<double> yVal_2_5_1{80, 45, 10};

	IBK::LinearSpline ls2_2_2_1;
	ls2_2_2_1.setValues(xVal_2_5_1, yVal_2_5_1);
	double env2_2_2_1WaterUsageIndex = ls2_2_2_1.value((currentValueEnv2_2_2_1));

	env2_2_2 += env2_2_2_1WaterUsageIndex;
	}
	return env2_2_2;
}   // Env2.2.2



} // namespace DGNB
