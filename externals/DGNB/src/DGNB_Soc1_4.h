#ifndef DGNB_Soc1_4H
#define DGNB_Soc1_4H

#include "DGNB_Soc1_4_1.h"
#include "DGNB_Soc1_4_2.h"
#include "DGNB_Soc1_4_3.h"
#include "DGNB_Soc1_4_4.h"
#include "DGNB_Soc1_4_5.h"
#include "DGNB_Soc1_4_6.h"

namespace DGNB {
	
/*! Visual Comfort */
class Soc1_4 {
	public:

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_4(){}

	Soc1_4(const Utilities::UsageType &ut):
		m_usageType(ut)
	{
		m_soc1_4_1 = Soc1_4_1(ut);
		m_soc1_4_2 = Soc1_4_2(ut);
		m_soc1_4_3 = Soc1_4_3(ut);
		m_soc1_4_4 = Soc1_4_4(ut);
		m_soc1_4_5 = Soc1_4_5(ut);
		m_soc1_4_6 = Soc1_4_6(ut);
	}

	void readReferenceValuesFromXML(const TiXmlElement *element);
	void readInputValuesFromXML(const TiXmlElement *element);

	double score();


	// *** PUBLIC MEMBER VARIABLES ***

	Soc1_4_1						m_soc1_4_1;									// XML:E
	Soc1_4_2						m_soc1_4_2;									// XML:E
	Soc1_4_3						m_soc1_4_3;									// XML:E
	Soc1_4_4						m_soc1_4_4;									// XML:E
	Soc1_4_5						m_soc1_4_5;									// XML:E
	Soc1_4_6						m_soc1_4_6;									// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // Soc1_4H
