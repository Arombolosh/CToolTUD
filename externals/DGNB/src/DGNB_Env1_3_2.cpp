#include "DGNB_Env1_3_2.h"

namespace DGNB {

double DGNB::Env1_3_2::score() {
	double env1_3_2 = 0; // max 100
	double env1_3_2_1 = 0;
	double env1_3_2_2 = 0;

	double refEnv1_3_2_2WeightingCG = m_para[(P_ReferenceValueEnv1_3_2_2RRMRRWPSR_WeightingCostGroup)].get_value();
	double currentEnv1_3_2_2DMMassPercentOfPartsQS4 = m_para[(P_CurrentValueEnv1_3_2_2RRMRRWPSR_DetailedMethodSumOfMassPercentOfPartsOfQS4)].get_value()/100;
	double currentEnv1_3_2_2DMMassPercentOfPartsQS2 = m_para[(P_CurrentValueEnv1_3_2_2RRMRRWPSR_DetailedMethodSumOfMassPercentOfPartsOfQS2)].get_value()/100;
	double currentEnv1_3_2_2SMNumberOfPartsQS4 = m_para[(P_CurrentValueEnv1_3_2_2RRMRRWPSR_SimplifiedMethodSumOfNumberOfPartsOfQS4)].get_value();
	double currentEnv1_3_2_2SMNumberOfPartsQS2 = m_para[(P_CurrentValueEnv1_3_2_2RRMRRWPSR_SimplifiedMethodSumOfNumberOfPartsOfQS2)].get_value();

	// assigning +2 points per product made by a different manufacturer
	env1_3_2_1 = 2 * m_para[P_Env1_3_2_1NumberOfPartsFromDiffManufacturers].get_value();
	// capping points at 20
	env1_3_2_1 = std::min<double>(20,env1_3_2_1);

	//calculating points for env1_3_2_2_1
	// TODO DGNB Zählt die Mindestanforderung wirklich nur für den einzelnen Indikator, nicht für die gesamte Zertifizierung?
	if (minimumRequirementsMet()){
		if (m_flag_RRMCRRM[(RRMRRWPSR_DetailedMethod)].isEnabled()) {
			env1_3_2_2 = refEnv1_3_2_2WeightingCG * (100 * currentEnv1_3_2_2DMMassPercentOfPartsQS4 + 60 * currentEnv1_3_2_2DMMassPercentOfPartsQS2);
			// capping points at 100
			env1_3_2_2 = std::min<double>(100,env1_3_2_2);
		}
		else if (m_flag_RRMCRRM[(RRMRRWPSR_SimplifiedMethod)].isEnabled()) {
			env1_3_2_2 = refEnv1_3_2_2WeightingCG * (0.2 * 100 * currentEnv1_3_2_2SMNumberOfPartsQS4 + 0.2 * 0.6 * 100 * currentEnv1_3_2_2SMNumberOfPartsQS2);
			// capping points at 70
			env1_3_2_2 = std::min<double>(70,env1_3_2_2);
		}
	}

	//calculating points for env1_3_2_2_2
	if (RRMPRCEWMPS_Percentage >= 50)
		env1_3_2_2 += 5;
	else if (RRMPRCEWMPS_Percentage >= 40)
		env1_3_2_2 += 4;
	else if (RRMPRCEWMPS_Percentage >= 30)
		env1_3_2_2 += 3;

	env1_3_2 = env1_3_2_1 + env1_3_2_2;
	// summing up and capping points for env1_3_2
	env1_3_2 = std::min<double>(100, env1_3_2);
	return env1_3_2;
}

bool DGNB::Env1_3_2::minimumRequirementsMet() {
	bool env1_3_2_2RequirementsMet = false;
	env1_3_2_2RequirementsMet = (m_flag_RRMCRRM[(RRMPWMSF_PercentageMinimum50)].isEnabled() ? true : false);

	return env1_3_2_2RequirementsMet;
}

} // namespace DGNB
