#ifndef DGNB_Eco2_7_AltH
#define DGNB_Eco2_7_AltH

#include "DGNB_Utilities.h"

namespace DGNB {

/*! Eco2.7 Alternative Certification  */
class Eco2_7_Alt {

public:

	/*! Eco2.7.Alt Innovation: circular digital twin  */
	enum AC_CircularDigitalTwin {									// Alt: +100
		ACCDT_CircularDigitalTwinImplemented,						// Keyword: ACCDT_CircularDigitalTwinImplemented
		NUM_ACCDT
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco2_7_Alt(){}

	Eco2_7_Alt(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_ACCDT[NUM_ACCDT];					// XML:E

	Utilities::UsageType			m_usageType;

}; // Eco 2.7 Alternative Certification

} // namespace DGNB

#endif // DGNB_Eco2_7_AltH
