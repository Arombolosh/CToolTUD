#ifndef DGNB_Site1_1H
#define DGNB_Site1_1H
#include "DGNB_Site1_1_1.h"
#include "DGNB_Site1_1_2.h"
#include "DGNB_Site1_1_3.h"

namespace DGNB {
	
/*! Micro Site */
class Site1_1 {
	public:

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Site1_1(){}

	Site1_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{
		m_site1_1_1 = Site1_1_1(ut);
		m_site1_1_2 = Site1_1_2(ut);
		m_site1_1_3 = Site1_1_3(ut);
	}

	/*! Calculates the points for site 1.1  */
	double score();
	double scoreBonus();


	// *** PUBLIC MEMBER VARIABLES ***

	Site1_1_1						m_site1_1_1;									// XML:E
	Site1_1_2						m_site1_1_2;									// XML:E
	Site1_1_3						m_site1_1_3;									// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // Site1_1H
