#ifndef DGNB_Env1_2H
#define DGNB_Env1_2H
#include "DGNB_Env1_2_1.h"

#include "DGNB_Utilities.h"

namespace DGNB {
	
/*! risks to local environment */
class Env1_2 {
	public:

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env1_2(){}

	Env1_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{
		m_env1_2_1 = Env1_2_1(ut);
	}

	void readInputValuesFromXML(const TiXmlElement *element);

	double score();
	double scoreBonus();

	Env1_2_1						m_env1_2_1;									// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // Env1_2H
