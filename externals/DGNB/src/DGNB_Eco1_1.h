#ifndef DGNB_Eco1_1H
#define DGNB_Eco1_1H

#include "DGNB_Eco1_1_1.h"
#include "DGNB_Eco1_1_2.h"
#include "DGNB_Eco1_1_3.h"
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Eco1.1 Building-related life cycle costs */
class Eco1_1
{
public:
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco1_1(){}

	Eco1_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	/*! Calculates the points for economy 1.1.  */
	double score();
	double scoreBonus();


	Eco1_1_1					m_eco1_1_1;										// XML:E
	Eco1_1_2					m_eco1_1_2;										// XML:E
	Eco1_1_3					m_eco1_1_3;										// XML:E

	Utilities::UsageType		m_usageType;
};

} // namespace DGNB

#endif // DGNB_Eco1_1H
