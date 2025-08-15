#include "DGNB_Tec1_6_2.h"

namespace DGNB {
	
double DGNB::Tec1_6_2::score() {
	double tec1_6_2 = 0;
	
	// Assigning pts for no (partial) demolition
	if (m_flag_CCPID162[(CCPID162_DemolitionOrPartialDemolition)].isEnabled() == false) {
		// assigning 5 pts for non demolition Tec1.6.2.1
		tec1_6_2 += ((m_flag_CCCPGFD[(CCCPGFD_PlanningWithCircularGoal)].isEnabled() || m_flag_CCCPGFD[(CCCPGFD_Alt_PlanIncludesPreexistingRecyclableMaterials)].isEnabled()) ? 5 : 0);
		// assigning 5 pts for non demolition Tec1.6.2.2.1
		tec1_6_2 += ((m_flag_CCCPPRCDCEP[(CCCPPRCDCEP_CreationAndEvaluationOfVariantsOfAtLeast4Topics)].isEnabled() || m_flag_CCCPPRCDCEP[(CCCPPRCDCEP_Alt_UseOfToolsForCreationOfCircularityOptimisationBalancesAndIndices)].isEnabled()) ? 5 : 0);
		// assigning 5 pts for non demolition Tec1.6.2.2.2
		tec1_6_2 += (((m_flag_CCCPPRCDCAEP[(CCCPPRCDCAEP_CreationAndEvaluationOfVariantsOfAtLeast4Topics)].isEnabled() || (m_flag_CCCPPRCDCAEP[(CCCPPRCDCAEP_Alt_UseOfToolsForCreationOfCircularityOptimisationBalancesAndIndices)].isEnabled() && m_flag_CCCPPRCDCAEP[(CCCPPRCDCAEP_Alt_GenerationOfABuildingResourcePass)].isEnabled())) && m_flag_CCCPPRCDCAEP[(CCCPPRCDCAEP_ParallelEvaluationOfClimateInfluenceAndCosts)].isEnabled()) ? 5 : 0);
	}
	else {
		// assigning 2 pts for demolition Tec1.6.2.1
		tec1_6_2 += ((m_flag_CCCPGFD[(CCCPGFD_PlanningWithCircularGoal)].isEnabled() || m_flag_CCCPGFD[(CCCPGFD_Alt_PlanIncludesPreexistingRecyclableMaterials)].isEnabled()) ? 1 : 0);
		// assigning 2 pts for demolition Tec1.6.2.2.1
		tec1_6_2 += ((m_flag_CCCPPRCDCEP[(CCCPPRCDCEP_CreationAndEvaluationOfVariantsOfAtLeast4Topics)].isEnabled() || m_flag_CCCPPRCDCEP[(CCCPPRCDCEP_Alt_UseOfToolsForCreationOfCircularityOptimisationBalancesAndIndices)].isEnabled()) ? 2 : 0);
		// assigning 2 pts for demolition Tec1.6.2.2.2
		tec1_6_2 += (((m_flag_CCCPPRCDCAEP[(CCCPPRCDCAEP_CreationAndEvaluationOfVariantsOfAtLeast4Topics)].isEnabled() || (m_flag_CCCPPRCDCAEP[(CCCPPRCDCAEP_Alt_UseOfToolsForCreationOfCircularityOptimisationBalancesAndIndices)].isEnabled() && m_flag_CCCPPRCDCAEP[(CCCPPRCDCAEP_Alt_GenerationOfABuildingResourcePass)].isEnabled())) && m_flag_CCCPPRCDCAEP[(CCCPPRCDCAEP_ParallelEvaluationOfClimateInfluenceAndCosts)].isEnabled()) ? 2 : 0);
	}

	return tec1_6_2;
} // Tec1.6.2

} // namespace DGNB
