#include "DGNB_Eco2_6_2.h"

namespace DGNB {
	
double DGNB::Eco2_6_2::score() {
	double scoreEco2_6_2 = 0, scoreEco2_6_2_2_2 = 0;
	// assigning 10 pts for Eco2.6.2.1.1
	scoreEco2_6_2 += (m_flag_ACCQEM[(ACC_QuantitativeEvaluationOfMeasures)0].isEnabled() ? 10 : 0);
	// assigning 10 pts for Eco2.6.2.1.2
	scoreEco2_6_2 += (m_flag_ACCQEM[(ACC_QuantitativeEvaluationOfMeasures)1].isEnabled()? 10 : 0);
	// assigning 10 pts for Eco2.6.2.1.3
	scoreEco2_6_2 += (m_flag_ACCQEM[(ACC_QuantitativeEvaluationOfMeasures)2].isEnabled() ? 5 : 0);
	// assigning 10 pts for Eco2.6.2.1.4
	scoreEco2_6_2 += (m_flag_ACCQEM[(ACC_QuantitativeEvaluationOfMeasures)3].isEnabled() ? 5 : 0);

	// assigning 10 pts for Eco2.6.2.2.1
	scoreEco2_6_2 += (m_flag_ACCQIAM[(ACC_QualityOfImplementedAdaptationMeasures)0].isEnabled() ? 5 : 0);

	// assigning 10 pts for Eco2.6.2.2.2
	scoreEco2_6_2_2_2 += (m_flag_ACCQIAM[(ACC_QualityOfImplementedAdaptationMeasures)1].isEnabled() ? 5 : 0);
	// assigning 10 pts for Eco2.6.2.2.2
	scoreEco2_6_2_2_2 += (m_flag_ACCQIAM[(ACC_QualityOfImplementedAdaptationMeasures)2].isEnabled() ? 3 : 0);
	// capping Eco2.6.2.2.2 at 5 pts
	scoreEco2_6_2 += std::min<double>(5, scoreEco2_6_2_2_2);

	// assigning 10 pts for Eco2.6.2.2.3
	scoreEco2_6_2 += (m_flag_ACCQIAM[(ACC_QualityOfImplementedAdaptationMeasures)3].isEnabled() ? 5 : 0);

	// assigning 15 pts for Eco2.6.2.3
	scoreEco2_6_2 += ((m_flag_ACCGRED[(ACC_GeneralResilienceToElementalDamages)0].isEnabled() && m_flag_ACCGRED[(ACC_GeneralResilienceToElementalDamages)0].isEnabled())? 15 : 0);


	return scoreEco2_6_2;
}

double DGNB::Eco2_6_2::scoreBonus() {
	double scoreEco2_6_2Bonus = 0;
	// assigning 5 pts for Eco2.6.2.4
	scoreEco2_6_2Bonus += ((m_flag_ACCA2030HL[(ACC_Agenda2030HeadLoad)0].isEnabled() && m_flag_ACCA2030HL[(ACC_Agenda2030HeadLoad)1].isEnabled()) ? 5 : 0);

	return scoreEco2_6_2Bonus;
}

bool DGNB::Eco2_6_2::minimumRequirementsMet() {
	bool eco2_6_2minimumRequirementsMet = false;
	int minReqMetCounter = 0;
	minReqMetCounter += (m_flag_ACCGRED[(Eco2_6_2::ACCGRED_EssentialMeasuresTaken)].isEnabled() ? 1 : 0);
	minReqMetCounter += (m_flag_ACCGRED[(Eco2_6_2::ACCGRED_GeneralResilienceExists)].isEnabled() ? 1 : 0);

	eco2_6_2minimumRequirementsMet = (minReqMetCounter == 2 ? true : false);

	return eco2_6_2minimumRequirementsMet;
}

bool DGNB::Eco2_6_2::platinumRequirementsMet() {
	bool eco2_6_2PlatinumRequirementsMet = false;

	eco2_6_2PlatinumRequirementsMet = (m_flag_ACCQEM[(ACCQEM_MeasuresImproveResilienceAndInlcudeReductionOfAllHighRiskFactors)].isEnabled()? true : false);

	return eco2_6_2PlatinumRequirementsMet;
}

} // namespace DGNB
