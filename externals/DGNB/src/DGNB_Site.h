#ifndef DGNB_SiteH
#define DGNB_SiteH

#include "DGNB_Site1_1.h"
#include "DGNB_Site1_3.h"
#include "DGNB_Site1_4.h"


namespace DGNB{


class Site
{
public:

	/*! Weighing Factors for Site */
	enum para_weights {
		/*! Site1.1 */
		PW_Site1_1,												// Keyword: PW_Site1_1		[-]
		/*! Site1.3 */
		PW_Site1_3,												// Keyword: PW_Site1_3		[-]
		/*! Site1.4 */
		PW_Site1_4,												// Keyword: PW_Site1_4		[-]
		NUM_PW
	};

	/*! Point Goals for Site */
	enum para_goals {
		/*! Site1.1 */
		PG_Site1_1,												// Keyword: PG_Site1_1		[-]
		/*! Site1.3 */
		PG_Site1_3,												// Keyword: PG_Site1_3		[-]
		/*! Site1.4 */
		PG_Site1_4,												// Keyword: PG_Site1_4		[-]
		NUM_PG
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Site(){}

	Site(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	void setUsageType(const Utilities::UsageType &ut);

	// double score();
	int grading();
	std::vector<bool> minimumRequirementsMet();
	std::vector<bool> platinumRequirementsMet();


	Site1_1						m_site1_1;										// XML:E
	Site1_3						m_site1_3;										// XML:E
	Site1_4						m_site1_4;										// XML:E

	IBK::Parameter				m_para_PW[NUM_PW];								// XML:E

	IBK::Parameter				m_para_PG[NUM_PG];								// XML:E

	Utilities::UsageType		m_usageType;

}; // Site

} // Namespace
#endif // DGNB_SiteH
