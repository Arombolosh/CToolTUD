#include "DGNB_Eco2_4_4.h"

namespace DGNB {
	
double DGNB::Eco2_4_4::score() {
	double scoreEco2_4_4 = 0, scoreEco2_4_4_2 = 0;
	double currentEco2_4_4RatioOfUsableSpaceToGroundSpace = m_para[(P_CurrentValue_eco2_4_4RatioOfUsableSpaceToGroundSpace)].get_value();
	double currentEco2_4_4RatioOfUsableSpaceToGroundSpaceLower = m_para[(P_ReferenceValueeco2_4_4RatioOfUsableSpaceToGroundSpace_lower)].get_value();
	double currentEco2_4_4RatioOfUsableSpaceToGroundSpaceUpper = m_para[(P_ReferenceValueeco2_4_4RatioOfUsableSpaceToGroundSpace_upper)].get_value();

	switch (m_usageType) {
		case Utilities::UT_Logistics:
		case Utilities::UT_Production:
			if (m_flag_SERUSGS[(SERUSGS_LogisticsAndProductionCostOptimisation)].isEnabled() && m_flag_SERUSGS[(SERUSGS_LogisticsAndProductionEnvironmentalOptimisation)].isEnabled() && m_flag_SERUSGS[(SERUSGS_LogisticsAndProductionSocialOptimisation)].isEnabled())
				scoreEco2_4_4 += 10;
			else if ((m_flag_SERUSGS[(SERUSGS_LogisticsAndProductionCostOptimisation)].isEnabled() && (m_flag_SERUSGS[(SERUSGS_LogisticsAndProductionEnvironmentalOptimisation)].isEnabled() != m_flag_SERUSGS[(SERUSGS_LogisticsAndProductionSocialOptimisation)].isEnabled())))
				scoreEco2_4_4 += 7.5;
			else if (m_flag_SERUSGS[(SERUSGS_LogisticsAndProductionCostOptimisation)].isEnabled())
				scoreEco2_4_4 += 1;
			break;
		default:
			if (m_flag_SERUSGS[(SERUSGS_ResultsSubmitted)].isEnabled() && (currentEco2_4_4RatioOfUsableSpaceToGroundSpace >= currentEco2_4_4RatioOfUsableSpaceToGroundSpaceLower)) {

				std::vector<double> xVal_2_4_4{currentEco2_4_4RatioOfUsableSpaceToGroundSpaceLower, currentEco2_4_4RatioOfUsableSpaceToGroundSpaceUpper};
				std::vector<double> yVal_2_4_4{1, 10};

				IBK::LinearSpline ls_2_4_4;
				ls_2_4_4.setValues(xVal_2_4_4, yVal_2_4_4);
				double eco_2_4_2_1InterpolatedBalance = ls_2_4_4.value(currentEco2_4_4RatioOfUsableSpaceToGroundSpace);
				scoreEco2_4_4 += eco_2_4_2_1InterpolatedBalance;
				}
	}
	scoreEco2_4_4_2 += (m_flag_SEMUS[(SEMUS_ConceptIncludesMultipleUseOfRelevantPortionOfSpace)].isEnabled() ? 5 : 0);
	scoreEco2_4_4_2 += (m_flag_SEMUS[(SEMUS_UseIncludesMultipleUseOfRelevantPortionOfSpace)].isEnabled() ? 10 : 0);

	// capping pts for Eco2.4.4.2 at 10
	scoreEco2_4_4 += std::min<double>(10, scoreEco2_4_4_2);

	return scoreEco2_4_4;
}

double DGNB::Eco2_4_4::scoreBonus() {
	double scoreEco2_4_4Bonus = 0;

	scoreEco2_4_4Bonus += (m_flag_SEA2030S[(SEA2030S_SubmissionAndImplementationOfSufficiencyStrategy)].isEnabled() ? 5 : 0);

	return scoreEco2_4_4Bonus;
}

} // namespace DGNB
