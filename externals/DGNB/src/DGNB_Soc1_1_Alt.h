#ifndef DGNB_Soc1_1_AltH
#define DGNB_Soc1_1_AltH

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.1.Alt Alternative Certification */
class Soc1_1_Alt
{
public:

	/*! Soc1.1.Alt Alternative Certification */
	enum AC_Innovation {										// alternative +85 pts
		AC_AlternativeCertificationForIndicators1to4,			// Keyword: AC_AlternativeCertificationForIndicators1to4
		NUM_AC
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_1_Alt(){}

	Soc1_1_Alt(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag					m_flag_AC[NUM_AC];				// XML:E

	Utilities::UsageType		m_usageType;

};

} // namespace DGNB

#endif // DGNB_Soc1_1_AltH
