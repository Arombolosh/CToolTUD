#ifndef DGNB_Env2_4H
#define DGNB_Env2_4H

#include "DGNB_Env2_4_1.h"
#include "DGNB_Env2_4_2.h"
#include "DGNB_Env2_4_3.h"
#include "DGNB_Env2_4_4.h"
#include "DGNB_Env2_4_5.h"
#include "DGNB_Env2_4_6.h"
#include "DGNB_Env2_4_Alt.h"

#include "DGNB_Utilities.h"

namespace DGNB {
	
/*! Env2.4 biodiversity on site */
class Env2_4 {
	public:

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env2_4(){}

	Env2_4(const Utilities::UsageType &ut):
		m_usageType(ut)
	{
	m_env2_4_1 = Env2_4_1(ut);
	m_env2_4_2 = Env2_4_2(ut);
	m_env2_4_3 = Env2_4_3(ut);
	m_env2_4_4 = Env2_4_4(ut);
	m_env2_4_5 = Env2_4_5(ut);
	m_env2_4_6 = Env2_4_6(ut);
	m_env2_4_alt = Env2_4_Alt(ut);
	}

	//void readXML(const TiXmlElement *element);
	void readInputValuesFromXML(const TiXmlElement *element);

	double score();
	double scoreBonus();


	Env2_4_1					m_env2_4_1;					// XML:E
	Env2_4_2					m_env2_4_2;					// XML:E
	Env2_4_3					m_env2_4_3;					// XML:E
	Env2_4_4					m_env2_4_4;					// XML:E
	Env2_4_5					m_env2_4_5;					// XML:E
	Env2_4_6					m_env2_4_6;					// XML:E
	Env2_4_Alt					m_env2_4_alt;				// XML:E
	
	Utilities::UsageType		m_usageType;


};

} // namespace DGNB

#endif // Env2_4H
