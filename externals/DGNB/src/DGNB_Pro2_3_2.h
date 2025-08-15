#ifndef DGNB_Pro2_3_2H
#define DGNB_Pro2_3_2H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Pro2_3_2
{
public:

	/*! Pro2.3.2 Technical Monitoring: during the Construction Phase (LPH 8) */
	enum TM_ConstructionPhase {												// max +5
		TMCP_ContinuationOfAMonitoringConcept,								// Keyword: TMCP_ContinuationOfAMonitoringConcept
		TMCP_CertifiedAlternativeSolution,									// Keyword: TMCP_CertifiedAlternativeSolution
		NUM_TMCP
	};
	

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_3_2(){}

	Pro2_3_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_TMCP[NUM_TMCP];				// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro2_3_2H
