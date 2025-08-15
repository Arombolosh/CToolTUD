#ifndef DGNB_Pro2_3_6H
#define DGNB_Pro2_3_6H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Pro2_3_6
{
public:

	/*! Pro2.3.6 Operation Start-Up Management */
	enum OperationStartUpManagement {										// max +25
		OSUM_StartUpManagementInAdditionToTechnicalManagement,				// Keyword: OSUM_StartUpManagementInAdditionToTechnicalManagement
		NUM_OSUM
	};
	

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_3_6(){}

	Pro2_3_6(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_OSUM[NUM_OSUM];				// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro2_3_6H
