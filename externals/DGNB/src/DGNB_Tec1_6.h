#ifndef DGNB_Tec1_6H
#define DGNB_Tec1_6H

#include "DGNB_Tec1_6_1.h"
#include "DGNB_Tec1_6_2.h"
#include "DGNB_Tec1_6_3.h"
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Tec1.6 Circular Construction */
class Tec1_6
{
public:
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Tec1_6(){}

	Tec1_6(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	/*! Calculates the points for tec1.1.  */
	double score();
	double scoreBonus();


	Tec1_6_1					m_tec1_6_1;										// XML:E
	Tec1_6_2					m_tec1_6_2;										// XML:E
	Tec1_6_3					m_tec1_6_3;										// XML:E

	Utilities::UsageType		m_usageType;
};

} // namespace DGNB

#endif // DGNB_Tec1_6H
