#ifndef DGNB_Pro2_5_6H
#define DGNB_Pro2_5_6H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Pro2_5_6
{
public:

	/*! Pro2.5.6 Operation Cost Prognosis: Extended Prognosis */
	enum OCP_Extended {															// max +10
		OCPE_CreationOfExtendedOperationCostPrognosis,							// Keyword: OCPE_CreationOfExtendedOperationCostPrognosis
		NUM_OCPE
	};
	

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_5_6(){}

	Pro2_5_6(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_OCPE[NUM_OCPE];						// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro2_5_6H
