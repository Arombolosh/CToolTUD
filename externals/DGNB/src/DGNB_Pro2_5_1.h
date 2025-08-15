#ifndef DGNB_Pro2_5_1H
#define DGNB_Pro2_5_1H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Pro2_5_1
{
public:

	/*! Pro2.5.1 Facility Management Check */
	enum FM_Check {																// max +20
		FMC_ConductionWithRegardToAccessibilityOperationRoutingAndAreaUsage,	// Keyword: FMC_ConductionWithRegardToAccessibilityOperationRoutingAndAreaUsage
		NUM_FMC
	};
	

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_5_1(){}

	Pro2_5_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_FMC[NUM_FMC];						// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro2_5_1H
