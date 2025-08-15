#ifndef DGNB_Tec1_3H
#define DGNB_Tec1_3H

#include "DGNB_Tec1_3_1.h"
#include "DGNB_Tec1_3_2.h"
#include "DGNB_Tec1_3_3.h"
#include "DGNB_Tec1_3_4.h"
#include "DGNB_Tec1_3_5.h"
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Tec1.3 Quality of the Building Envelope */
class Tec1_3
{
public:
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Tec1_3(){}

	Tec1_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	/*! Calculates the points for technology 1.3  */
	double score();


	Tec1_3_1					m_tec1_3_1;										// XML:E
	Tec1_3_2					m_tec1_3_2;										// XML:E
	Tec1_3_3					m_tec1_3_3;										// XML:E
	Tec1_3_4					m_tec1_3_4;										// XML:E
	Tec1_3_5					m_tec1_3_5;										// XML:E

	Utilities::UsageType		m_usageType;
};

} // namespace DGNB

#endif // DGNB_Tec1_3H
