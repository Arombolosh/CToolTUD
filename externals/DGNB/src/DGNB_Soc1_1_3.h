#ifndef DGNB_Soc1_1_3H
#define DGNB_Soc1_1_3H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.1.3 Draught */
class Soc1_1_3
{
public:

	/*! Soc 1.1.3.1 Draught - Cooling Period */
	enum D_CoolingPeriod {										// pts depending on usage type
		DCP_ObservationOfDIN_EN_ISO_7730_A_A2_KatB,				// Keyword: DCP_ObservationOfDIN_EN_ISO_7730_A_A2_KatB
		DCP_ShoppingCenterPreventionOfDraught,					// Keyword: DCP_ShoppingCenterPreventionOfDraught
		NUM_DCP
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_1_3(){}

	Soc1_1_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_DCP[NUM_DCP];		// XML:E

	Utilities::UsageType			m_usageType;

};

} // namespace DGNB

#endif // DGNB_Soc1_1_3H
