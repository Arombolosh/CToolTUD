#ifndef DGNB_EnvironmentH
#define DGNB_EnvironmentH

#include "DGNB_Env1_1.h"
#include "DGNB_Env1_2.h"
#include "DGNB_Env1_3.h"
#include "DGNB_Env2_2.h"
#include "DGNB_Env2_3.h"
#include "DGNB_Env2_4.h"

namespace DGNB {

class Environment
{
public:

	/*! Weighing Factors for Environment */
	enum para_weights {
		/*! Env1.1 */
		PW_Env1_1,												// Keyword: PW_Env1_1		[-]
		/*! Env1.2 */
		PW_Env1_2,												// Keyword: PW_Env1_2		[-]
		/*! Env1.3 */
		PW_Env1_3,												// Keyword: PW_Env1_3		[-]
		/*! Env2.2 */
		PW_Env2_2,												// Keyword: PW_Env2_2		[-]
		/*! Env2.3 */
		PW_Env2_3,												// Keyword: PW_Env2_3		[-]
		/*! Env2,4 */
		PW_Env2_4,												// Keyword: PW_Env2_4		[-]
		NUM_PW
	};

	/*! Point Goals for Environment */
	enum para_goals {
		/*! Env1.1 */
		PG_Env1_1,												// Keyword: PG_Env1_1		[-]
		/*! Env1.2 */
		PG_Env1_2,												// Keyword: PG_Env1_2		[-]
		/*! Env1.3 */
		PG_Env1_3,												// Keyword: PG_Env1_3		[-]
		/*! Env2.2 */
		PG_Env2_2,												// Keyword: PG_Env2_2		[-]
		/*! Env2.3 */
		PG_Env2_3,												// Keyword: PG_Env2_3		[-]
		/*! Env2,4 */
		PG_Env2_4,												// Keyword: PG_Env2_4		[-]
		NUM_PG
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Environment(){}

	Environment(const Utilities::UsageType &ut):
		m_usageType(ut)
	{
		// m_env1_1 = Env1_1(ut);
		// m_env1_2 = Env1_2(ut);
		// m_env1_3 = Env1_3(ut);
		// m_env2_2 = Env2_2(ut);
		// m_env2_3 = Env2_3(ut);
		// m_env2_4 = Env2_4(ut);
	}

	void setUsageType(const Utilities::UsageType &ut);
	void readReferenceValuesFromXML(const TiXmlElement *element);
	void readInputValuesFromXML(const TiXmlElement *element);

	std::vector<double> score();


	int grading(const double & envTotal);
	std::vector<bool> minimumRequirementsMet();
	std::vector<bool> platinumRequirementsMet();
	//bool readReferenceValues(const IBK::Path &filename);
	//void readCurrentData();		// das kommt später vom UI



	Env1_1							m_env1_1;					// XML:E
	Env1_2							m_env1_2;					// XML:E
	Env1_3							m_env1_3;					// XML:E
	Env2_2							m_env2_2;					// XML:E
	Env2_3							m_env2_3;					// XML:E
	Env2_4							m_env2_4;					// XML:E

	IBK::Parameter					m_para_PW[NUM_PW];			// XML:E

	IBK::Parameter					m_para_PG[NUM_PG];			// XML:E

	Utilities::UsageType			m_usageType;

};

} // namespace DGNB

#endif // DGNB_EnvironmentH
