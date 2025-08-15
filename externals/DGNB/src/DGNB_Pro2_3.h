#ifndef DGNB_Pro2_3H
#define DGNB_Pro2_3H

#include "DGNB_Pro2_3_1.h"
#include "DGNB_Pro2_3_2.h"
#include "DGNB_Pro2_3_3.h"
#include "DGNB_Pro2_3_4.h"
#include "DGNB_Pro2_3_5.h"
#include "DGNB_Pro2_3_6.h"
#include "DGNB_Pro2_3_7.h"
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Pro2.1 Construction Site / Construction Process */
class Pro2_3
{
public:
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_3(){}

	Pro2_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	/*! Calculates the points for process 2.3  */
	double score();


	Pro2_3_1					m_pro2_3_1;										// XML:E
	Pro2_3_2					m_pro2_3_2;										// XML:E
	Pro2_3_3					m_pro2_3_3;										// XML:E
	Pro2_3_4					m_pro2_3_4;										// XML:E
	Pro2_3_5					m_pro2_3_5;										// XML:E
	Pro2_3_6					m_pro2_3_6;										// XML:E
	Pro2_3_7					m_pro2_3_7;										// XML:E

	Utilities::UsageType		m_usageType;
};

} // namespace DGNB

#endif // DGNB_Pro2_3H
