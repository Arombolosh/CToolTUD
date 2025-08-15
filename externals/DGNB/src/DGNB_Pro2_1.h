#ifndef DGNB_Pro2_1H
#define DGNB_Pro2_1H

#include "DGNB_Pro2_1_1.h"
#include "DGNB_Pro2_1_2.h"
#include "DGNB_Pro2_1_3.h"
#include "DGNB_Pro2_1_4.h"
#include "DGNB_Pro2_1_5.h"
#include "DGNB_Pro2_1_6.h"
#include "DGNB_Pro2_1_7.h"
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Pro2.1 Construction Site / Construction Process */
class Pro2_1
{
public:
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_1(){}

	Pro2_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	/*! Calculates the points for process 2.1  */
	double score();
	double scoreBonus();


	Pro2_1_1					m_pro2_1_1;										// XML:E
	Pro2_1_2					m_pro2_1_2;										// XML:E
	Pro2_1_3					m_pro2_1_3;										// XML:E
	Pro2_1_4					m_pro2_1_4;										// XML:E
	Pro2_1_5					m_pro2_1_5;										// XML:E
	Pro2_1_6					m_pro2_1_6;										// XML:E
	Pro2_1_7					m_pro2_1_7;										// XML:E

	Utilities::UsageType		m_usageType;
};

} // namespace DGNB

#endif // DGNB_Pro2_1H
