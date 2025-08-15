#ifndef DGNB_Pro2_5_3H
#define DGNB_Pro2_5_3H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Pro2_5_3
{
public:

	/*! Pro2.5.3 Facility Manager Guidebook */
	enum FacilityManagerGuidebook {								// max +20
		FMG_CreationAndHandoverToFacilityManager,				// Keyword: FMG_CreationAndHandoverToFacilityManager
		NUM_FMG
	};
	

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_5_3(){}

	Pro2_5_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_FMG[NUM_FMG];		// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro2_5_3H
