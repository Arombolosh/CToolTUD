#ifndef DGNB_Pro2_5_4H
#define DGNB_Pro2_5_4H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Pro2_5_4
{
public:

	/*! Pro2.5.4 Communication with Users */
	enum CWU_PreparationOfUserFriendlyBuildingOperation {									// max +20
		CWU_CreationAndHandoverTechnicalOperationHandbook,									// Keyword: CWU_CreationAndHandoverTechnicalOperationHandbook
		CWU_PreparationAndHandoverOfQuestionaryOnUserSatisfactionDuringOperationPhase,		// Keyword: CWU_PreparationAndHandoverOfQuestionaryOnUserSatisfactionDuringOperationPhase
		NUM_CWU
	};
	

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_5_4(){}

	Pro2_5_4(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_CWU[NUM_CWU];		// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro2_5_4H
