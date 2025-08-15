#ifndef DGNB_Env2_3H
#define DGNB_Env2_3H

#include "DGNB_Env2_3_1.h"
#include "DGNB_Env2_3_2.h"
#include "DGNB_Env2_3_3.h"

#include "DGNB_Utilities.h"

namespace DGNB {
	
/*! Env2_3 area demand */
class Env2_3 {
	public:

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env2_3(){}

	Env2_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{
	m_env2_3_1 = Env2_3_1(ut);
	m_env2_3_2 = Env2_3_2(ut);
	m_env2_3_3 = Env2_3_3(ut);
	}

	void readInputValuesFromXML(const TiXmlElement *element);

	double score();
	double scoreBonus();

	//void readXML(const TiXmlElement *element);



	Env2_3_1						m_env2_3_1;									// XML:E
	Env2_3_2						m_env2_3_2;									// XML:E
	Env2_3_3						m_env2_3_3;									// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // Env2_3H
