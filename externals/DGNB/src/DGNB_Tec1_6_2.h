#ifndef DGNB_Tec1_6_2H
#define DGNB_Tec1_6_2H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

/*! Circular Construction - Concept Phase */
class Tec1_6_2
{
public:

	/*! Tec1.6 Circular Construction: Project included Demolition */
	enum CC_ProjectIncludesDemolition {														// impact on scoring of several indicators
		CCPID162_DemolitionOrPartialDemolition,												// Keyword: CCPID162_DemolitionOrPartialDemolition
		NUM_CCPID162
	};

	/*! Tec1.6.2.1 Goal and Focus Definition */
	enum CCCP_GoalAndFocusDefinition {														// max +5/+1
		CCCPGFD_PlanningWithCircularGoal,													// Keyword: CCCPGFD_PlanningWithCircularGoal
		CCCPGFD_Alt_PlanIncludesPreexistingRecyclableMaterials,								// Keyword: CCCPGFD_Alt_PlanIncludesPreexistingRecyclableMaterials
		NUM_CCCPGFD
	};

	/*! Tec1.6.2.2 Project Related Circular Design Concepts */
	/*! Tec1.6.2.2.1 - Early Phase */
	enum CCCP_ProjectRelatedCircularDesignConceptsEarlyPhase {								// max +5/+2
		CCCPPRCDCEP_CreationAndEvaluationOfVariantsOfAtLeast4Topics,						// Keyword: CCCPPRCDCEP_CreationAndEvaluationOfVariantsOfAtLeast4Topics
		CCCPPRCDCEP_Alt_UseOfToolsForCreationOfCircularityOptimisationBalancesAndIndices,	// Keyword: CCCPPRCDCEP_Alt_UseOfToolsForCreationOfCircularityOptimisationBalancesAndIndices
		NUM_CCCPPRCDCEP
	};
	
	/*! Tec1.6.2.2.1 - Approval and Execution Phase */
	enum CCCP_ProjectRelatedCircularDesignConceptsApprovalAndExecutionPhase {				// max +5/+2
		CCCPPRCDCAEP_CreationAndEvaluationOfVariantsOfAtLeast4Topics,						// Keyword: CCCPPRCDCAEP_CreationAndEvaluationOfVariantsOfAtLeast4Topics
		CCCPPRCDCAEP_Alt_UseOfToolsForCreationOfCircularityOptimisationBalancesAndIndices,	// Keyword: CCCPPRCDCAEP_Alt_UseOfToolsForCreationOfCircularityOptimisationBalancesAndIndices
		CCCPPRCDCAEP_Alt_GenerationOfABuildingResourcePass,									// Keyword: CCCPPRCDCAEP_Alt_GenerationOfABuildingResourcePass
		CCCPPRCDCAEP_ParallelEvaluationOfClimateInfluenceAndCosts,							// Keyword: CCCPPRCDCAEP_ParallelEvaluationOfClimateInfluenceAndCosts
		NUM_CCCPPRCDCAEP
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Tec1_6_2(){}

	Tec1_6_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_CCPID162[NUM_CCPID162];			// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CCCPGFD[NUM_CCCPGFD];			// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CCCPPRCDCEP[NUM_CCCPPRCDCEP];	// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CCCPPRCDCAEP[NUM_CCCPPRCDCAEP];	// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Tec1_6_2H
