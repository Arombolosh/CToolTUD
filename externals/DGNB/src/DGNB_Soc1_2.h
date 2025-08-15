#ifndef DGNB_Soc1_2H
#define DGNB_Soc1_2H
#include "DGNB_Soc1_2_1.h"
#include "DGNB_Soc1_2_2.h"

namespace DGNB {
	
/*! Thermal Comfort */
class Soc1_2 {
	public:

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_2(){}

	Soc1_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{
		m_soc1_2_1 = Soc1_2_1(ut);
		m_soc1_2_2 = Soc1_2_2(ut);
	}

	void readReferenceValuesFromXML(const TiXmlElement *element);
	void readInputValuesFromXML(const TiXmlElement *element);

	double score();
	double scoreBonus();


	// *** PUBLIC MEMBER VARIABLES ***

	Soc1_2_1						m_soc1_2_1;									// XML:E
	Soc1_2_2						m_soc1_2_2;									// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // Soc1_1H
