#ifndef DGNB_EconomyH
#define DGNB_EconomyH

#include "DGNB_Eco1_1.h"
#include "DGNB_Eco2_4.h"
#include "DGNB_Eco2_6.h"
#include "DGNB_Eco2_7.h"


namespace DGNB{


class Economy
{
public:

	/*! Weighing Factors for Economy */
	enum para_weights {
		/*! Eco1.1 */
		PW_Eco1_1,												// Keyword: PW_Eco1_1		[-]
		/*! Eco2.4 */
		PW_Eco2_4,												// Keyword: PW_Eco2_4		[-]
		/*! Eco2.6 */
		PW_Eco2_6,												// Keyword: PW_Eco2_6		[-]
		/*! Eco2.7 */
		PW_Eco2_7,												// Keyword: PW_Eco2_7		[-]
		NUM_PW
	};

	/*! Point Goals for Economy */
	enum para_goals {
		/*! Eco1.1 */
		PG_Eco1_1,												// Keyword: PG_Eco1_1		[-]
		/*! Eco2.4 */
		PG_Eco2_4,												// Keyword: PG_Eco2_4		[-]
		/*! Eco2.6 */
		PG_Eco2_6,												// Keyword: PG_Eco2_6		[-]
		/*! Eco2.7 */
		PG_Eco2_7,												// Keyword: PG_Eco2_7		[-]
		NUM_PG
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Economy(){}

	Economy(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	void setUsageType(const Utilities::UsageType &ut);
	void readReferenceValuesFromXML(const TiXmlElement *element);
	void readInputValuesFromXML(const TiXmlElement *element);

	// double score();
	int grading(const double & ecoTotal);
	std::vector<bool> minimumRequirementsMet();
	std::vector<bool> platinumRequirementsMet();


	Eco1_1						m_eco1_1;										// XML:E
	Eco2_4						m_eco2_4;										// XML:E
	Eco2_6						m_eco2_6;										// XML:E
	Eco2_7						m_eco2_7;										// XML:E

	IBK::Parameter				m_para_PW[NUM_PW];								// XML:E

	IBK::Parameter				m_para_PG[NUM_PG];								// XML:E

	Utilities::UsageType		m_usageType;

}; // Economy

} // Namespace
#endif // DGNB_EconomyH
