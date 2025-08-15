#ifndef DGNB_Eco2_6H
#define DGNB_Eco2_6H

#include "DGNB_Eco2_6_1.h"
#include "DGNB_Eco2_6_2.h"
#include "DGNB_Eco2_6_3.h"

namespace DGNB {

/*! Eco2.6 Climate Resilience */
class Eco2_6
{
public:
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco2_6(){}

	Eco2_6(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}



	double score();
	double scoreBonus();

	Eco2_6_1					m_eco2_6_1;										// XML:E
	Eco2_6_2					m_eco2_6_2;										// XML:E
	Eco2_6_3					m_eco2_6_3;										// XML:E

	Utilities::UsageType		m_usageType;

}; // Eco2.6

} // namespace DGNB

#endif // DGNB_Eco2_6H
