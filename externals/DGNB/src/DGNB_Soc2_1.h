#ifndef DGNB_Soc2_1H
#define DGNB_Soc2_1H

#include "DGNB_Soc2_1_1.h"

namespace DGNB {
	
/*! Accessibility */
class Soc2_1 {
	public:

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc2_1(){}

	Soc2_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{
		m_soc2_1_1 = Soc2_1_1(ut);
	}

	void readReferenceValuesFromXML(const TiXmlElement *element);
	void readInputValuesFromXML(const TiXmlElement *element);

	double score();


	// *** PUBLIC MEMBER VARIABLES ***

	Soc2_1_1						m_soc2_1_1;									// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // Soc2_1H
