#ifndef DGNB_Pro1_6_1H
#define DGNB_Pro1_6_1H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

/*! Pro1.6.1 Creative Examination of Variants or Planning Competition */
class Pro1_6_1
{
public:

	/*! Pro1.6.1.1 Preemptive Examination of Variants or Planning Competition*/
	enum CEV_PreemptiveExaminationOfVariantsOrPlanningCompetition {									// max +10
		CEVPEVPC_PreemptiveExaminationButNoPlanningCompetitionConducted,							// Keyword: CEVPEVPC_PreemptiveExaminationButNoPlanningCompetitionConducted
		NUM_CEVPEVPC
	};
	
	// alternative
	/*! Pro1.6.1.2 ConceptAssignment */
	/*! Pro1.6.1.2.1 ConceptAssignment: Manner and Scope of Method */
	enum CEV_ConceptAssignmentMannerAndScopeOfMethod {												// max +10
		CEVCAMSM_ImplementationOfConceptAssignment,													// Keyword: CEVCAMSM_ImplementationOfConceptAssignment
		CEVCAMSM_ImplementationOfConceptAssignmentWithSpecialConcernForSustainableConstruction,		// Keyword: CEVCAMSM_ImplementationOfConceptAssignmentWithSpecialConcernForSustainableConstruction
		NUM_CEVCAMSM
	};
	
	/*! Pro1.6.1.2.2 ConceptAssignment: Quality Ensurance */
	enum CEV_ConceptAssignmentQualityEnsurance {													// max +20
		CEVCAQE_CompetentDecisionMakingBoard,														// Keyword: CEVCAQE_CompetentDecisionMakingBoard
		CEVCAQE_PostProcedureQualityEnsurance,														// Keyword: CEVCAQE_PostProcedureQualityEnsurance
		NUM_CEVCAQE
	};
	
	// alternative
	/*! Pro1.6.1.3.1 Multiple Assignments */
	/*! Pro1.6.1.3.1 Multiple Assignments: Scope Of Method */
	enum CEV_MultipleAssignmentsScopeOfMethod {														// max +15
		CEVMASM_ImplementationOfMultipleAssignments,												// Keyword: CEVMASM_ImplementationOfMultipleAssignments
		CEVMASM_ImplementationOfMultipleAssignmentsWithSpecialConcernForSustainableConstruction,	// Keyword: CEVMASM_ImplementationOfMultipleAssignmentsWithSpecialConcernForSustainableConstruction
		NUM_CEVMASM
	};
	
	/*! Pro1.6.1.3.2 Multiple Assignments: Quality Ensurance */
	enum CEV_MultipleAssignmentsQualityEnsurance {													// max +10
		CEVMAQE_CompetentDecisionMakingBoardOrSupervisionBySuch,									// Keyword: CEVMAQE_CompetentDecisionMakingBoardOrSupervisionBySuch
		NUM_CEVMAQE
	};
	
	/*! Pro1.6.1.3.3 Multiple Assignments: Implementation Of An Award-Winning Design */
	enum CEV_MultipleAssignmentsImplementationOfAnAwardWinningDesign {								// max +15
		CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH3,			// Keyword: CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH3
		CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH5,			// Keyword: CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH5
		CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH8,			// Keyword: CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH8
		NUM_CEVMAIAWD
	};
	
	/*! Pro1.6.1.4 Planning Competition */
	/*! Pro1.6.1.4.1 Planning Competition: Scope and Quality of Method */
	enum CEV_PlanningCompetitionScopeAndQualityOfMethod {											// max +20
		CEVPCSQM_ImplementationOfPlanningCompetition,												// Keyword: CEVPCSQM_ImplementationOfPlanningCompetition
		CEVPCSQM_ImplementationOfPlanningCompetitionWithSpecialConcernForSustainableConstruction,	// Keyword: CEVPCSQM_ImplementationOfPlanningCompetitionWithSpecialConcernForSustainableConstruction
		NUM_CEVPCSQM
	};
	
	/*! Pro1.6.1.4.2 Planning Competition: Manner of Competition Method */
	enum CEV_PlanningCompetitionMannerOfCompetitionMethod {											// max +20
		CEVPCMCM_CooperativeMethod,																	// Keyword: CEVPCMCM_CooperativeMethod
		CEVPCMCM_OneOrTwoPhases_OpenCompetitionOrClosedCompetitionWithPreliminaryRound,				// Keyword: CEVPCMCM_OneOrTwoPhases_OpenCompetitionOrClosedCompetitionWithPreliminaryRound
		NUM_CEVPCMCM
	};
	
	/*! Pro1.6.1.4.3 Planning Competition: Implementation Of An Award-Winning Design */
	enum CEV_PlanningCompetitionImplementationOfAnAwardWinningDesign {								// max +20
		CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH3,			// Keyword: CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH3
		CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH5,			// Keyword: CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH5
		CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH8,			// Keyword: CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH8
		NUM_CEVPCIAWD
	};
	
	/*! Pro1.6.1.4.3 Planning Competition: Commissioning of Award Winner's Planning Team */
	enum CEV_PlanningCompetitionCommissioningOfAwardWinnersPlanningTeam {							// max +20
		CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH3,					// Keyword: CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH3
		CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH5,					// Keyword: CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH5
		CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH8,					// Keyword: CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH8
		NUM_CEVPCCAWPT
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro1_6_1(){}

	Pro1_6_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_CEVPEVPC[NUM_CEVPEVPC];		// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CEVCAMSM[NUM_CEVCAMSM];		// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CEVCAQE[NUM_CEVCAQE];		// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CEVMASM[NUM_CEVMASM];		// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CEVMAQE[NUM_CEVMAQE];		// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CEVMAIAWD[NUM_CEVMAIAWD];	// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CEVPCSQM[NUM_CEVPCSQM];		// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CEVPCMCM[NUM_CEVPCMCM];		// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CEVPCIAWD[NUM_CEVPCIAWD];	// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CEVPCCAWPT[NUM_CEVPCCAWPT];	// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro1_6_1H
