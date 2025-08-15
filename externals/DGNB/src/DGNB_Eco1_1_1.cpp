#include "DGNB_Eco1_1_1.h"

namespace DGNB {
	
double DGNB::Eco1_1_1::score() {
	double eco1_1_1 = 0;
	int lccoPartialEvaluationCounter = 0;
	// assigning 7.5 pts each for variant 1 and 2 during Eco1.1.1.1.1
	for (unsigned int i = 0; i < NUM_LCCCPIES; ++i)
		eco1_1_1 += (m_flag_LCCCPIES[(LCCCP_IntegrationOfLCCCDuringPlanningProcessEarlyStages)i].isEnabled() ? 7.5 : 0);

	// assigning 5 pts for life cycle cost optimisation during planning support
	eco1_1_1 += (m_flag_LCCCPICO[(LCCCPICO_CalculationAndDisclosureOfConstructionAndUtilisationCosts)].isEnabled() ? 5 : 0);

	// assigning up to 10 pts for partial examination
	for (unsigned int i = 0; i < NUM_LCCCPIPE; ++i)
		lccoPartialEvaluationCounter +=  (m_flag_LCCCPIPE[(LCCCP_IntegrationOfLCCCDuringPlanningProcessPartialExamination)i].isEnabled() ? 1 : 0);

	lccoPartialEvaluationCounter = std::min<int>(2, lccoPartialEvaluationCounter);
	eco1_1_1 += 5 * lccoPartialEvaluationCounter;

	return eco1_1_1;
} // Eco1.1.1

} // namespace DGNB
