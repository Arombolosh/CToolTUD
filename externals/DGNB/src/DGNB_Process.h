#ifndef DGNB_ProcessH
#define DGNB_ProcessH

#include "DGNB_Pro1_1.h"
#include "DGNB_Pro1_4.h"
#include "DGNB_Pro1_6.h"
#include "DGNB_Pro2_1.h"
#include "DGNB_Pro2_3.h"
#include "DGNB_Pro2_5.h"


namespace DGNB{


class Process
{
public:

	/*! Weighing Factors for Process */
	enum para_weights {
		/*! Pro1.1 */
		PW_Pro1_1,												// Keyword: PW_Pro1_1		[-]
		/*! Pro1.4 */
		PW_Pro1_4,												// Keyword: PW_Pro1_4		[-]
		/*! Pro1.6 */
		PW_Pro1_6,												// Keyword: PW_Pro1_6		[-]
		/*! Pro2.1 */
		PW_Pro2_1,												// Keyword: PW_Pro2_1		[-]
		/*! Pro2.3 */
		PW_Pro2_3,												// Keyword: PW_Pro2_3		[-]
		/*! Pro2.5 */
		PW_Pro2_5,												// Keyword: PW_Pro2_5		[-]
		NUM_PW
	};

	/*! Point Goals for Process */
	enum para_goals {
		/*! Pro1.1 */
		PG_Pro1_1,												// Keyword: PG_Pro1_1		[-]
		/*! Pro1.4 */
		PG_Pro1_4,												// Keyword: PG_Pro1_4		[-]
		/*! Pro1.6 */
		PG_Pro1_6,												// Keyword: PG_Pro1_6		[-]
		/*! Pro2.1 */
		PG_Pro2_1,												// Keyword: PG_Pro2_1		[-]
		/*! Pro2.3 */
		PG_Pro2_3,												// Keyword: PG_Pro2_3		[-]
		/*! Pro2.5 */
		PG_Pro2_5,												// Keyword: PG_Pro2_5		[-]
		NUM_PG
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Process(){}

	Process(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	void setUsageType(const Utilities::UsageType &ut);
	void readReferenceValuesFromXML(const TiXmlElement *element);
	void readInputValuesFromXML(const TiXmlElement *element);

	// double score();
	int grading();
	std::vector<bool> minimumRequirementsMet();
	std::vector<bool> platinumRequirementsMet();


	Pro1_1						m_pro1_1;										// XML:E
	Pro1_4						m_pro1_4;										// XML:E
	Pro1_6						m_pro1_6;										// XML:E
	Pro2_1						m_pro2_1;										// XML:E
	Pro2_3						m_pro2_3;										// XML:E
	Pro2_5						m_pro2_5;										// XML:E

	IBK::Parameter				m_para_PW[NUM_PW];								// XML:E

	IBK::Parameter				m_para_PG[NUM_PG];								// XML:E

	Utilities::UsageType		m_usageType;

}; // Process

} // Namespace
#endif // DGNB_ProcessH
