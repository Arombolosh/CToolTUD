#ifndef DGNB_TechnologyH
#define DGNB_TechnologyH

#include "DGNB_Tec1_3.h"
#include "DGNB_Tec1_4.h"
#include "DGNB_Tec1_6.h"
#include "DGNB_Tec3_1.h"


namespace DGNB{


class Technology
{
public:

	/*! Weighing Factors for Technology */
	enum para_weights {
		/*! Tec1.3 */
		PW_Tec1_3,												// Keyword: PW_Tec1_3		[-]
		/*! Tec1.4 */
		PW_Tec1_4,												// Keyword: PW_Tec1_4		[-]
		/*! Tec1.6 */
		PW_Tec1_6,												// Keyword: PW_Tec1_6		[-]
		/*! Tec3.1 */
		PW_Tec3_1,												// Keyword: PW_Tec3_1		[-]
		NUM_PW
	};

	/*! Weighing Factors for Technology */
	enum para_goals {
		/*! Tec1.3 */
		PG_Tec1_3,												// Keyword: PG_Tec1_3		[-]
		/*! Tec1.4 */
		PG_Tec1_4,												// Keyword: PG_Tec1_4		[-]
		/*! Tec1.6 */
		PG_Tec1_6,												// Keyword: PG_Tec1_6		[-]
		/*! Tec3.1 */
		PG_Tec3_1,												// Keyword: PG_Tec3_1		[-]
		NUM_PG
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Technology(){}

	Technology(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	void setUsageType(const Utilities::UsageType &ut);

	// double score();
	int grading();
	std::vector<bool> minimumRequirementsMet();
	std::vector<bool> platinumRequirementsMet();


	Tec1_3						m_tec1_3;										// XML:E
	Tec1_4						m_tec1_4;										// XML:E
	Tec1_6						m_tec1_6;										// XML:E
	Tec3_1						m_tec3_1;										// XML:E

	IBK::Parameter				m_para_PW[NUM_PW];								// XML:E

	IBK::Parameter				m_para_PG[NUM_PG];								// XML:E

	Utilities::UsageType		m_usageType;

};	// Technology

}	// Namespace
#endif // DGNB_TechnologyH
