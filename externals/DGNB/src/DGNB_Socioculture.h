#ifndef DGNB_SocioculturalFunctionalH
#define DGNB_SocioculturalFunctionalH

#include "DGNB_Soc1_1.h"
#include "DGNB_Soc1_2.h"
#include "DGNB_Soc1_3.h"
#include "DGNB_Soc1_4.h"
#include "DGNB_Soc1_6.h"
#include "DGNB_Soc2_1.h"


namespace DGNB{


class Socioculture
{
public:

	/*! Weighing Factors for Socioculture */
	enum para_weights {
		/*! Soc1.1 */
		PW_Soc1_1,												// Keyword: PW_Soc1_1		[-]
		/*! Soc1.2 */
		PW_Soc1_2,												// Keyword: PW_Soc1_2		[-]
		/*! Soc1.3 */
		PW_Soc1_3,												// Keyword: PW_Soc1_3		[-]
		/*! Soc1.4 */
		PW_Soc1_4,												// Keyword: PW_Soc1_4		[-]
		/*! Soc1.6 */
		PW_Soc1_6,												// Keyword: PW_Soc1_6		[-]
		/*! Soc2.1 */
		PW_Soc2_1,												// Keyword: PW_Soc2_1		[-]
		NUM_PW
	};

	/*! Weighing Factors for Socioculture */
	enum para_goals {
		/*! Soc1.1 */
		PG_Soc1_1,												// Keyword: PG_Soc1_1		[-]
		/*! Soc1.2 */
		PG_Soc1_2,												// Keyword: PG_Soc1_2		[-]
		/*! Soc1.3 */
		PG_Soc1_3,												// Keyword: PG_Soc1_3		[-]
		/*! Soc1.4 */
		PG_Soc1_4,												// Keyword: PG_Soc1_4		[-]
		/*! Soc1.6 */
		PG_Soc1_6,												// Keyword: PG_Soc1_6		[-]
		/*! Soc2.1 */
		PG_Soc2_1,												// Keyword: PG_Soc2_1		[-]
		NUM_PG
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Socioculture(){}

	Socioculture(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	void setUsageType(const Utilities::UsageType &ut);
	void readReferenceValuesFromXML(const TiXmlElement *element);
	void readInputValuesFromXML(const TiXmlElement *element);

	// double score();
	int grading(const double & socTotal);
	std::vector<bool> minimumRequirementsMet();
	std::vector<bool> platinumRequirementsMet();


	Soc1_1						m_soc1_1;										// XML:E
	Soc1_2						m_soc1_2;										// XML:E
	Soc1_3						m_soc1_3;										// XML:E
	Soc1_4						m_soc1_4;										// XML:E
	Soc1_6						m_soc1_6;										// XML:E
	Soc2_1						m_soc2_1;										// XML:E

	IBK::Parameter				m_para_PW[NUM_PW];								// XML:E

	IBK::Parameter				m_para_PG[NUM_PG];								// XML:E

	Utilities::UsageType		m_usageType;

}; // SocioculturalFunctional

} // Namespace
#endif // DGNB_SocioculturalFunctionalH
