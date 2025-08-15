#ifndef DGNB_Pro2_3_4H
#define DGNB_Pro2_3_4H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Pro2_3_4
{
public:

	/*! Pro2.3.4 Technical Monitoring: during the First Operation Phase (LPH 9) */
	enum TM_FirstOperationPhase {											// max +20
		TMFOP_AssignmentOfARegulationMonitoringToOptimiseOperation,			// Keyword: TMFOP_AssignmentOfARegulationMonitoringToOptimiseOperation
		TMFOP_CertifiedAlternativeSolution,									// Keyword: TMFOP_CertifiedAlternativeSolution
		NUM_TMFOP
	};
	

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_3_4(){}

	Pro2_3_4(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_TMFOP[NUM_TMFOP];			// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro2_3_4H
