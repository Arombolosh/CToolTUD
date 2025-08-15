#ifndef DGNB_Pro2_5H
#define DGNB_Pro2_5H

#include "DGNB_Pro2_5_1.h"
#include "DGNB_Pro2_5_2.h"
#include "DGNB_Pro2_5_3.h"
#include "DGNB_Pro2_5_4.h"
#include "DGNB_Pro2_5_5.h"
#include "DGNB_Pro2_5_6.h"
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Pro2.5 Preparation of Sustainable Use */
class Pro2_5
{
public:
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_5(){}

	Pro2_5(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	/*! Calculates the points for process 2.5  */
	double score();
	double scoreBonus();


	Pro2_5_1					m_pro2_5_1;										// XML:E
	Pro2_5_2					m_pro2_5_2;										// XML:E
	Pro2_5_3					m_pro2_5_3;										// XML:E
	Pro2_5_4					m_pro2_5_4;										// XML:E
	Pro2_5_5					m_pro2_5_5;										// XML:E
	Pro2_5_6					m_pro2_5_6;										// XML:E

	Utilities::UsageType		m_usageType;
};

} // namespace DGNB

#endif // DGNB_Pro2_5H
