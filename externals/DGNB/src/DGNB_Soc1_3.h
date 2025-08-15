#ifndef DGNB_Soc1_3H
#define DGNB_Soc1_3H
#include "DGNB_Soc1_3_1.h"
#include "DGNB_Soc1_3_2.h"
#include "DGNB_Soc1_3_3.h"

namespace DGNB {
	
/*! Soundproofing and Acoustic Comfort */
class Soc1_3 {
	public:

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_3(){}

	Soc1_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{
		m_soc1_3_1 = Soc1_3_1(ut);
		m_soc1_3_2 = Soc1_3_2(ut);
		m_soc1_3_3 = Soc1_3_3(ut);
	}

	void readReferenceValuesFromXML(const TiXmlElement *element);
	void readInputValuesFromXML(const TiXmlElement *element);

	double score();
	double scoreBonus();


	// *** PUBLIC MEMBER VARIABLES ***

	Soc1_3_1						m_soc1_3_1;									// XML:E
	Soc1_3_2						m_soc1_3_2;									// XML:E
	Soc1_3_3						m_soc1_3_3;									// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // Soc1_3H
