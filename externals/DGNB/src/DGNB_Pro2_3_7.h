#ifndef DGNB_Pro2_3_7H
#define DGNB_Pro2_3_7H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Pro2_3_7
{
public:

	/*! Pro2.3.7 Building Performance */
	enum BuildingPerformance {												// max +15
		BP_AssignmentOfContinuousImprovementProcessAfterHandover,			// Keyword: BP_AssignmentOfContinuousImprovementProcessAfterHandover
		NUM_BP
	};
	

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_3_7(){}

	Pro2_3_7(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_BP[NUM_BP];					// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro2_3_7H
