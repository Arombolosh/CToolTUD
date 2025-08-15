#ifndef DGNB_Eco1_1_1H
#define DGNB_Eco1_1_1H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Eco1_1_1
{
public:

	/*! Eco1.1.1.1 Life cycle cost calculation during planning: Integration during early stages */
	enum  LCCCP_IntegrationOfLCCCDuringPlanningProcessEarlyStages {	// max +15
		LCCCPIES_Var1SubmissionOfCO2OrClimateCosts,					// Keyword: LCCCPIES_Var1SubmissionOfCO2OrClimateCosts
		LCCCPIES_Var2SubmissionOfEcologicalSuggestions,				// Keyword: LCCCPIES_Var2SubmissionOfEcologicalSuggestions
		NUM_LCCCPIES
	};

	/*! Eco1.1.1.2 Life Cycle cost optimisation during planning support */
	enum LCCCP_IntegrationOfLCCCDuringPlanningProcessLCCostOptimisation {			// max +5
		LCCCPICO_CalculationAndDisclosureOfConstructionAndUtilisationCosts,			// Keyword: LCCCPICO_CalculationAndDisclosureOfConstructionAndUtilisationCosts
		NUM_LCCCPICO
	};

	/*! Eco1.1.1.3 Life Cycle cost optimisation - partial examination */
	enum LCCCP_IntegrationOfLCCCDuringPlanningProcessPartialExamination {			// max +10 (+5 each)
		LCCCPIPE_PartialExaminationsDuringLP2,										// Keyword: LCCCPIPE_PartialExaminationsDuringLP2
		LCCCPIPE_PartialExaminationsDuringLP3,										// Keyword: LCCCPIPE_PartialExaminationsDuringLP3
		LCCCPIPE_PartialExaminationsDuringLP4,										// Keyword: LCCCPIPE_PartialExaminationsDuringLP4
		LCCCPIPE_FundingAdviceSessionByEndOfLP4,									// Keyword: LCCCPIPE_FundingAdviceSessionByEndOfLP4
		LCCCPIPE_SubmissionOfClimateProtectionAgendaDiscussionWithOwner,			// Keyword: LCCCPIPE_SubmissionOfClimateProtectionAgendaDiscussionWithOwner
		NUM_LCCCPIPE
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco1_1_1(){}

	Eco1_1_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag			m_flag_LCCCPIES[NUM_LCCCPIES];				// XML:E
	/*! List of flags. */
	IBK::Flag			m_flag_LCCCPICO[NUM_LCCCPICO];				// XML:E
	/*! List of flags. */
	IBK::Flag			m_flag_LCCCPIPE[NUM_LCCCPIPE];				// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Eco1_1_1H
