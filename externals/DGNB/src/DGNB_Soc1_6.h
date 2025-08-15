#ifndef DGNB_Soc1_6H
#define DGNB_Soc1_6H

#include "DGNB_Soc1_6_1.h"
#include "DGNB_Soc1_6_2.h"
#include "DGNB_Soc1_6_3.h"
#include "DGNB_Soc1_6_4.h"
#include "DGNB_Soc1_6_5.h"

namespace DGNB {
	
/*! Visual Comfort */
class Soc1_6 {
	public:

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_6(){}

	Soc1_6(const Utilities::UsageType &ut):
		m_usageType(ut)
	{
		m_soc1_6_1 = Soc1_6_1(ut);
		m_soc1_6_2 = Soc1_6_2(ut);
		m_soc1_6_3 = Soc1_6_3(ut);
		m_soc1_6_4 = Soc1_6_4(ut);
		m_soc1_6_5 = Soc1_6_5(ut);
	}

	void readReferenceValuesFromXML(const TiXmlElement *element);
	void readInputValuesFromXML(const TiXmlElement *element);

	double score();
	double scoreBonus();


	// *** PUBLIC MEMBER VARIABLES ***

	Soc1_6_1						m_soc1_6_1;									// XML:E
	Soc1_6_2						m_soc1_6_2;									// XML:E
	Soc1_6_3						m_soc1_6_3;									// XML:E
	Soc1_6_4						m_soc1_6_4;									// XML:E
	Soc1_6_5						m_soc1_6_5;									// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // Soc1_6H
