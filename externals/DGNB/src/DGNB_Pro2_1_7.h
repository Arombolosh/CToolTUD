#ifndef DGNB_Pro2_1_7H
#define DGNB_Pro2_1_7H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Pro2_1_7
{
public:

	/*! Pro2.1.7 Mold: Prevention */
	enum M_Prevention {																											// max +5
		MP_CreationAndImplementationOfAnAerationProgrammSuitedToConstructionSituationGuaranteeingSufficientDryingOutOfSite,		// Keyword: MP_CreationAndImplementationOfAnAerationProgrammSuitedToConstructionSituationGuaranteeingSufficientDryingOutOfSite
		NUM_MP
	};
	

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_1_7(){}

	Pro2_1_7(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_MP[NUM_MP];				// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro2_1_7H
