#ifndef DGNB_Pro1_4H
#define DGNB_Pro1_4H

#include "DGNB_Pro1_4_1.h"
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Pro1.4 Ensuring Sustainability Aspects in Offer and Assignment */
class Pro1_4
{
public:
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro1_4(){}

	Pro1_4(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	/*! Calculates the points for process1.4  */
	double score();
	double scoreBonus();


	Pro1_4_1					m_pro1_4_1;										// XML:E

	Utilities::UsageType		m_usageType;
};

} // namespace DGNB

#endif // DGNB_Pro1_4H
