#ifndef DGNB_Site1_4H
#define DGNB_Site1_4H
#include "DGNB_Site1_4_1.h"
#include "DGNB_Site1_4_2.h"
#include "DGNB_Site1_4_3.h"

namespace DGNB {
	
/*! Proximity to usage-relevant objects and facilities */
class Site1_4 {
	public:

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Site1_4(){}

	Site1_4(const Utilities::UsageType &ut):
		m_usageType(ut)
	{
		m_site1_4_1 = Site1_4_1(ut);
		m_site1_4_2 = Site1_4_2(ut);
		m_site1_4_3 = Site1_4_3(ut);
	}

	/*! Calculates the points for site 1.4  */
	double score();
	double scoreBonus();


	// *** PUBLIC MEMBER VARIABLES ***

	Site1_4_1						m_site1_4_1;									// XML:E
	Site1_4_2						m_site1_4_2;									// XML:E
	Site1_4_3						m_site1_4_3;									// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // Site1_4H
