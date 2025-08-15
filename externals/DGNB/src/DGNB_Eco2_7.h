#ifndef DGNB_Eco2_7H
#define DGNB_Eco2_7H

#include "DGNB_Eco2_7_1.h"
#include "DGNB_Eco2_7_2.h"
#include "DGNB_Eco2_7_3.h"
#include "DGNB_Eco2_7_4.h"
#include "DGNB_Eco2_7_5.h"
#include "DGNB_Eco2_7_Alt.h"

namespace DGNB {

/*! Eco2.7 Documentation */
class Eco2_7
{
public:

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco2_7(){}

	Eco2_7(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}



	double score();
	double scoreBonus();


	Eco2_7_1					m_eco2_7_1;										// XML:E
	Eco2_7_2					m_eco2_7_2;										// XML:E
	Eco2_7_3					m_eco2_7_3;										// XML:E
	Eco2_7_4					m_eco2_7_4;										// XML:E
	Eco2_7_5					m_eco2_7_5;										// XML:E
	Eco2_7_Alt					m_eco2_7_alt;									// XML:E

	Utilities::UsageType		m_usageType;

}; // Eco2.7

} // namespace DGNB

#endif // DGNB_Eco2_7H
