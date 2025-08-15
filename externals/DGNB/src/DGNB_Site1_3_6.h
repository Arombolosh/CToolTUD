#ifndef DGNB_Site1_3_6H
#define DGNB_Site1_3_6H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Site1.3.6 Agenda 2030 Bonus */
class Site1_3_6
{
public:

	/*! Site 1.3.6.1 Usage of Preexisting Loading Infrastructure */
	enum A2030_UsageOfPreexistingLoadingInfrastructure {											// max +5
		A2030UPLI_PublicLoadingInfrastructureForMotorisedIndividualTransportWithin350Meters,		// Keyword: A2030UPLI_PublicLoadingInfrastructureForMotorisedIndividualTransportWithin350Meters
		NUM_A2030UPLI
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Site1_3_6(){}

	Site1_3_6(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double scoreBonus();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_A2030UPLI[NUM_A2030UPLI];								// XML:E
	
	Utilities::UsageType			m_usageType;
};

} // namespace DGNB

#endif // DGNB_Site1_3_6H
