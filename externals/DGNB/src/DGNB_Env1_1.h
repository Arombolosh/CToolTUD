#ifndef DGNB_Env1_1H
#define DGNB_Env1_1H
#include "DGNB_Env1_1_1.h"
#include "DGNB_Env1_1_2.h"
#include "DGNB_Env1_1_3.h"

namespace DGNB {
	
/*! Optimisation of CO2 balance during planning */
class Env1_1 {
	public:

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env1_1(){}

	Env1_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{
		m_env1_1_1 = Env1_1_1(ut);
		m_env1_1_2 = Env1_1_2(ut);
		m_env1_1_3 = Env1_1_3(ut);
	}

	/*!
	void readReferenceValuesFromXML(const TiXmlElement *element);
	void readInputValuesFromXML(const TiXmlElement *element);
	*/

	double score();
	double scoreBonus();


	// *** PUBLIC MEMBER VARIABLES ***

	Env1_1_1						m_env1_1_1;									// XML:E
	Env1_1_2						m_env1_1_2;									// XML:E
	Env1_1_3						m_env1_1_3;									// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // Env1_1H
