#ifndef DGNB_Pro2_3_3H
#define DGNB_Pro2_3_3H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Pro2_3_3
{
public:

	/*! Pro2.3.3 Trial Operation */
	enum TrialOperation {													// max +20
		TO_TrialOperationConductedPriorToApprovalAndHandover,				// Keyword: TO_TrialOperationConductedPriorToApprovalAndHandover
		TO_CertifiedAlternativeSolution,									// Keyword: TO_CertifiedAlternativeSolution
		NUM_TO
	};
	

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_3_3(){}

	Pro2_3_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_TO[NUM_TO];					// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro2_3_3H
