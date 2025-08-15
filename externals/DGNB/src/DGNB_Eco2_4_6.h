#ifndef DGNB_Eco2_4_6H
#define DGNB_Eco2_4_6H

#include "DGNB_Utilities.h"

namespace DGNB {

/*! Eco2.4.6 Agenda 2030 Bonus Connectivity */
class Eco2_4_6	// max +10
{
public:

	/*! Eco2.4.6.1 Digital Infrastructure */
	enum A2030C_DigitalInfrastructure {								// max +5 bonus
		A2030CDI_QualityOfInternetConnection,						// Keyword: A2030CDI_QualityOfInternetConnection
		NUM_A2030CDI
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco2_4_6(){}

	Eco2_4_6(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double scoreBonus();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag			m_flag_A2030CDI[NUM_A2030CDI];				// XML:E

	Utilities::UsageType			m_usageType;

}; // Eco 2.4.6

} // namespace DGNB

#endif // DGNB_Eco2_4_6H
