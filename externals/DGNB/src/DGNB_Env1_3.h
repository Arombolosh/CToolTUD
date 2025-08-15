#ifndef DGNB_Env1_3H
#define DGNB_Env1_3H

#include "DGNB_Env1_3_1.h"
#include "DGNB_Env1_3_2.h"


#include "DGNB_Utilities.h"

namespace DGNB {
	
/*! responsible winning of resources */
class Env1_3 {
	public:

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE
	
	Env1_3(){}

	Env1_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{
	m_env1_3_1 = Env1_3_1(ut);
	m_env1_3_2 = Env1_3_2(ut);
	}

	//void readXML(const TiXmlElement *element);
	void readReferenceValuesFromXML(const TiXmlElement *element);
	void readInputValuesFromXML(const TiXmlElement *element);

	double score();


	Env1_3_1						m_env1_3_1;									// XML:E
	Env1_3_2						m_env1_3_2;									// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // Env1_3H
