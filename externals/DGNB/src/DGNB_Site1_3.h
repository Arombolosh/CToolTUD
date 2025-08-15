#ifndef DGNB_Site1_3H
#define DGNB_Site1_3H
#include "DGNB_Site1_3_1.h"
#include "DGNB_Site1_3_2.h"
#include "DGNB_Site1_3_3.h"
#include "DGNB_Site1_3_4.h"
#include "DGNB_Site1_3_5.h"
#include "DGNB_Site1_3_6.h"

namespace DGNB {
	
/*! Transport Connection */
class Site1_3 {
	public:

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Site1_3(){}

	Site1_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{
		m_site1_3_1 = Site1_3_1(ut);
		m_site1_3_2 = Site1_3_2(ut);
		m_site1_3_3 = Site1_3_3(ut);
		m_site1_3_4 = Site1_3_4(ut);
		m_site1_3_5 = Site1_3_5(ut);
		m_site1_3_6 = Site1_3_6(ut);
	}

	/*! Calculates the points for site 1.3  */
	double score();
	double scoreBonus();


	// *** PUBLIC MEMBER VARIABLES ***

	Site1_3_1						m_site1_3_1;									// XML:E
	Site1_3_2						m_site1_3_2;									// XML:E
	Site1_3_3						m_site1_3_3;									// XML:E
	Site1_3_4						m_site1_3_4;									// XML:E
	Site1_3_5						m_site1_3_5;									// XML:E
	Site1_3_6						m_site1_3_6;									// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // Site1_3H
