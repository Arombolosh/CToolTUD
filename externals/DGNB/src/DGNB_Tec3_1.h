#ifndef DGNB_Tec3_1H
#define DGNB_Tec3_1H

#include "DGNB_Tec3_1_1.h"
#include "DGNB_Tec3_1_2.h"
#include "DGNB_Tec3_1_3.h"
#include "DGNB_Tec3_1_4.h"
#include "DGNB_Tec3_1_5.h"
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Tec1.6 Circular Construction */
class Tec3_1
{
public:
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Tec3_1(){}

	Tec3_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	/*! Calculates the points for tec3.1.  */
	double score();
	double scoreBonus();


	Tec3_1_1					m_tec3_1_1;										// XML:E
	Tec3_1_2					m_tec3_1_2;										// XML:E
	Tec3_1_3					m_tec3_1_3;										// XML:E
	Tec3_1_4					m_tec3_1_4;										// XML:E
	Tec3_1_5					m_tec3_1_5;										// XML:E

	Utilities::UsageType		m_usageType;
};

} // namespace DGNB

#endif // DGNB_Tec3_1H
