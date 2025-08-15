#ifndef DGNB_Env2_2H
#define DGNB_Env2_2H

#include "DGNB_Env2_2_1.h"
#include "DGNB_Env2_2_2.h"
#include "DGNB_Env2_2_3.h"
#include "DGNB_Env2_2_4.h"
#include "DGNB_Env2_2_5.h"

#include "DGNB_Utilities.h"

namespace DGNB {
	
/*! Env2_2 drinking water demand and waste water volume */
class Env2_2 {
	public:

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env2_2(){}

	Env2_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{
	m_env2_2_1 = Env2_2_1(ut);
	m_env2_2_2 = Env2_2_2(ut);
	m_env2_2_3 = Env2_2_3(ut);
	m_env2_2_4 = Env2_2_4(ut);
	m_env2_2_5 = Env2_2_5(ut);
	}

	//void readXML(const TiXmlElement *element);
	void readReferenceValuesFromXML(const TiXmlElement *element);
	void readInputValuesFromXML(const TiXmlElement *element);

	double score();
	double scoreBonus();

	Env2_2_1						m_env2_2_1;									// XML:E
	Env2_2_2						m_env2_2_2;									// XML:E
	Env2_2_3						m_env2_2_3;									// XML:E
	Env2_2_4						m_env2_2_4;									// XML:E
	Env2_2_5						m_env2_2_5;									// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // Env2_2H
