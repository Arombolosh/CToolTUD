#ifndef DGNB_Eco2_4H
#define DGNB_Eco2_4H

#include "DGNB_Eco2_4_1.h"
#include "DGNB_Eco2_4_2.h"
#include "DGNB_Eco2_4_3.h"
#include "DGNB_Eco2_4_4.h"
#include "DGNB_Eco2_4_5.h"
#include "DGNB_Eco2_4_6.h"
#include "DGNB_Eco2_4_7.h"
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Eco2_4 Value retention and adabtability */
class Eco2_4
{
public:
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco2_4(){}

	Eco2_4(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}



	double score();
	double scoreBonus();

	Eco2_4_1		m_eco2_4_1;										// XML:E
	Eco2_4_2		m_eco2_4_2;										// XML:E
	Eco2_4_3		m_eco2_4_3;										// XML:E
	Eco2_4_4		m_eco2_4_4;										// XML:E
	Eco2_4_5		m_eco2_4_5;										// XML:E
	Eco2_4_6		m_eco2_4_6;										// XML:E
	Eco2_4_7		m_eco2_4_7;										// XML:E

	Utilities::UsageType		m_usageType;

}; // Eco2.4

} // namespace DGNB

#endif // DGNB_Eco2_4H
