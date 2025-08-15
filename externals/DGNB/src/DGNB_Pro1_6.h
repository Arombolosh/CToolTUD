#ifndef DGNB_Pro1_6H
#define DGNB_Pro1_6H

#include "DGNB_Pro1_6_1.h"
#include "DGNB_Pro1_6_2.h"
#include "DGNB_Pro1_6_3.h"
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Pro1.6 Methods of city-constructional and creative concepts */
class Pro1_6
{
public:
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro1_6(){}

	Pro1_6(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	/*! Calculates the points for process 1.6 */
	double score();


	Pro1_6_1					m_pro1_6_1;										// XML:E
	Pro1_6_2					m_pro1_6_2;										// XML:E
	Pro1_6_3					m_pro1_6_3;										// XML:E

	Utilities::UsageType		m_usageType;
};

} // namespace DGNB

#endif // DGNB_Pro1_6H
