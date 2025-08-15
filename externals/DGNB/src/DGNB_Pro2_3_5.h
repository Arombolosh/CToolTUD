#ifndef DGNB_Pro2_3_5H
#define DGNB_Pro2_3_5H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Pro2_3_5
{
public:

	/*! Pro2.3.5 Technical Monitoring: Complete Monitoring */
	enum TM_CompleteMonitoring {											// max +70
		TMCM_AssignmentOfACompleteTechnicalMonitoring,						// Keyword: TMCM_AssignmentOfACompleteTechnicalMonitoring
		NUM_TMCM
	};
	

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_3_5(){}

	Pro2_3_5(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_TMCM[NUM_TMCM];				// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro2_3_5H
