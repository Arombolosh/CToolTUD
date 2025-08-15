#include "DGNB_Pro1_6_1.h"

namespace DGNB {
	
double DGNB::Pro1_6_1::score() {
	double pro1_6_1 = 0;

	// assigning points for pro1.6.1.4 planning competition
	if (m_flag_CEVPCSQM[(CEVPCSQM_ImplementationOfPlanningCompetition)].isEnabled()) {
		pro1_6_1 += 15;
		// assigning another 5 pts if requirement "With Special Concern For Sustainable Construction" is fulfilled
		pro1_6_1 += (m_flag_CEVPCSQM[(CEVPCSQM_ImplementationOfPlanningCompetitionWithSpecialConcernForSustainableConstruction)].isEnabled() ? 5 : 0);

		// assigning points for pro1.6.1.4.2
		if (m_flag_CEVPCMCM[(CEVPCMCM_OneOrTwoPhases_OpenCompetitionOrClosedCompetitionWithPreliminaryRound)].isEnabled())
			pro1_6_1 += 35;
		else if (m_flag_CEVPCMCM[(CEVPCMCM_CooperativeMethod)].isEnabled())
			pro1_6_1 += 15;

		// assigning points for pro1.6.1.4.4
		if (m_flag_CEVPCIAWD[(CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH8)].isEnabled())
			pro1_6_1 += 20;
		else if (m_flag_CEVPCIAWD[(CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH5)].isEnabled())
			pro1_6_1 += 15;
		else if (m_flag_CEVPCIAWD[(CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH3)].isEnabled())
			pro1_6_1 += 10;

		// assigning points for pro1.6.1.4.4
		if (m_flag_CEVPCCAWPT[(CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH8)].isEnabled())
			pro1_6_1 += 10;
		else if (m_flag_CEVPCCAWPT[(CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH5)].isEnabled())
			pro1_6_1 += 7.5;
		else if (m_flag_CEVPCCAWPT[(CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH3)].isEnabled())
			pro1_6_1 += 5;
	} else
	// assigning points for pro1.6.1.3 Multiple Assignments
	if (m_flag_CEVMASM[(CEVMASM_ImplementationOfMultipleAssignments)].isEnabled()) {
		pro1_6_1 += 10;
		// assigning another 5 pts if requirement "With Special Concern For Sustainable Construction" is fulfilled
		pro1_6_1 += (m_flag_CEVMASM[(CEVMASM_ImplementationOfMultipleAssignmentsWithSpecialConcernForSustainableConstruction)].isEnabled() ? 5 : 0);

		// assigning points for pro1.6.1.3.2
		pro1_6_1 += (m_flag_CEVMAQE[(CEVMAQE_CompetentDecisionMakingBoardOrSupervisionBySuch)].isEnabled() ? 10 : 0);

		// assigning points for pro1.6.1.3.3
		if (m_flag_CEVMAIAWD[(CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH8)].isEnabled())
			pro1_6_1 += 15;
		else if (m_flag_CEVMAIAWD[(CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH5)].isEnabled())
			pro1_6_1 += 10;
		else if (m_flag_CEVMAIAWD[(CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH3)].isEnabled())
			pro1_6_1 += 5;
	} else
	// assigning points for pro1.6.1.2 Concept Assignment
	if (m_flag_CEVCAMSM[(CEVCAMSM_ImplementationOfConceptAssignment)].isEnabled()) {
		pro1_6_1 += 5;
		// assigning another 5 pts if requirement "With Special Concern For Sustainable Construction" is fulfilled
		pro1_6_1 += (m_flag_CEVCAMSM[(CEVCAMSM_ImplementationOfConceptAssignmentWithSpecialConcernForSustainableConstruction)].isEnabled() ? 5 : 0);

		// assigning points for pro1.6.1.3.2
		pro1_6_1 += (m_flag_CEVCAQE[(CEVCAQE_CompetentDecisionMakingBoard)].isEnabled() ? 10 : 0);
		pro1_6_1 += (m_flag_CEVCAQE[(CEVCAQE_PostProcedureQualityEnsurance)].isEnabled() ? 10 : 0);
	} else
	// assigning points for pro1.6.1.1 Preemptive Examination of Variants
	if (m_flag_CEVCAMSM[(CEVCAMSM_ImplementationOfConceptAssignment)].isEnabled()) {
		pro1_6_1 += 10;
	}



	return pro1_6_1;
} // Pro1.6.1

} // namespace DGNB
