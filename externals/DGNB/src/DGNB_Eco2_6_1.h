#ifndef DGNB_Eco2_6_1H
#define DGNB_Eco2_6_1H

#include "DGNB_Utilities.h"

namespace DGNB {

/*! Eco2.6.1 Building Concept for Risk Management and Presentation of Vulnerability */
class Eco2_6_1 {

public:

	/*! Eco2.6.1.1  */
	enum BCRMPV_PrePlanningphase4 {									// max +15
		BCRMPVPrePH4_ConceptSubmitted,								// Keyword: BCRMPVPrePH4_ConceptSubmitted
		NUM_BCRMPVPrePH4
	};

	/*! Eco2.6.1.2  */
	enum BCRMPV_PostPlanningphase4 {								// max +10
		BCRMPVPostPH4_ConceptSubmitted,								// Keyword: BCRMPVPostPH4_ConceptSubmitted
		BCRMPVPostPH4_ProofOfNoNegativeConcequences,				// Keyword: BCRMPVPostPH4_ProofOfNoNegativeConcequences
		NUM_BCRMPVPostPH4
	};

	/*! Eco2.6.1.3  */
	enum Agenda2030_CostBenefitAnalysis {							// max +5
		A2030CBA_Evaluation,										// Keyword: A2030CBA_Evaluation
		NUM_A2030CBA
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco2_6_1(){}

	Eco2_6_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_BCRMPVPrePH4[NUM_BCRMPVPrePH4];		// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_BCRMPVPostPH4[NUM_BCRMPVPostPH4];	// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_A2030CBA[NUM_A2030CBA];				// XML:E

	Utilities::UsageType			m_usageType;

}; // Eco 2.6.1

} // namespace DGNB

#endif // DGNB_Eco2_6_1H
