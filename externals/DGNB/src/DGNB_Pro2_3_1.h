#ifndef DGNB_Pro2_3_1H
#define DGNB_Pro2_3_1H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Pro2_3_1
{
public:

	/*! Pro2.3.1 Technical Monitoring: during the Planning Phase (LPH 3-7) */
	enum TM_PlanningPhase {													// max +15
		TMPP_DesignOfAMonitoringConceptIncludingEnergeticMonitoring,		// Keyword: TMPP_DesignOfAMonitoringConceptIncludingEnergeticMonitoring
		TMPP_CertifiedAlternativeSolution,									// Keyword: TMPP_CertifiedAlternativeSolution
		NUM_TMPP
	};
	

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_3_1(){}

	Pro2_3_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_TMPP[NUM_TMPP];				// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro2_3_1H
