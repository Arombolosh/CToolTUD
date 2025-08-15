#ifndef DGNB_Pro1_1H
#define DGNB_Pro1_1H

#include "DGNB_Pro1_1_1.h"
#include "DGNB_Pro1_1_2.h"
#include "DGNB_Pro1_1_3.h"
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Pro1.1 Quality of Project Preparation */
class Pro1_1
{
public:
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro1_1(){}

	Pro1_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	/*! Calculates the points for process 1.1.  */
	double score();
	double scoreBonus();


	Pro1_1_1					m_pro1_1_1;										// XML:E
	Pro1_1_2					m_pro1_1_2;										// XML:E
	Pro1_1_3					m_pro1_1_3;										// XML:E

	Utilities::UsageType		m_usageType;
};

} // namespace DGNB

#endif // DGNB_Pro1_1H
