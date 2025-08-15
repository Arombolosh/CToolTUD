#ifndef DGNB_Soc1_1H
#define DGNB_Soc1_1H
#include "DGNB_Soc1_1_1.h"
#include "DGNB_Soc1_1_2.h"
#include "DGNB_Soc1_1_3.h"
#include "DGNB_Soc1_1_4.h"
#include "DGNB_Soc1_1_5.h"
#include "DGNB_Soc1_1_6.h"
#include "DGNB_Soc1_1_Alt.h"

namespace DGNB {
	
/*! Thermal Comfort */
class Soc1_1 {
	public:

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_1(){}

	Soc1_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{
		m_soc1_1_1 = Soc1_1_1(ut);
		m_soc1_1_2 = Soc1_1_2(ut);
		m_soc1_1_3 = Soc1_1_3(ut);
	}

	void readReferenceValuesFromXML(const TiXmlElement *element);
	void readInputValuesFromXML(const TiXmlElement *element);

	double score();
	double scoreBonus();


	// *** PUBLIC MEMBER VARIABLES ***

	Soc1_1_1						m_soc1_1_1;									// XML:E
	Soc1_1_2						m_soc1_1_2;									// XML:E
	Soc1_1_3						m_soc1_1_3;									// XML:E
	Soc1_1_4						m_soc1_1_4;									// XML:E
	Soc1_1_5						m_soc1_1_5;									// XML:E
	Soc1_1_6						m_soc1_1_6;									// XML:E
	Soc1_1_Alt						m_soc1_1_alt;								// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // Soc1_1H
