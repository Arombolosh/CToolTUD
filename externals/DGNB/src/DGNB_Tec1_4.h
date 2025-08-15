#ifndef DGNB_Tec1_4H
#define DGNB_Tec1_4H

#include "DGNB_Tec1_4_1.h"
#include "DGNB_Tec1_4_2.h"
#include "DGNB_Tec1_4_3.h"
#include "DGNB_Tec1_4_4.h"
#include "DGNB_Tec1_4_5.h"
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Tec1.4 Use and Integration of Building Technology */
class Tec1_4
{
public:
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Tec1_4(){}

	Tec1_4(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	/*! Calculates the points for tec1.4  */
	double score();
	double scoreBonus();


	Tec1_4_1					m_tec1_4_1;										// XML:E
	Tec1_4_2					m_tec1_4_2;										// XML:E
	Tec1_4_3					m_tec1_4_3;										// XML:E
	Tec1_4_4					m_tec1_4_4;										// XML:E
	Tec1_4_5					m_tec1_4_5;										// XML:E

	Utilities::UsageType		m_usageType;
};

} // namespace DGNB

#endif // DGNB_Tec1_4H
