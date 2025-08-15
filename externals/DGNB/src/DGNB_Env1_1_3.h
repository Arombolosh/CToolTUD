#ifndef Env1_1_3H
#define DGNB_Env1_1_3H
#include "DGNB_Utilities.h"

namespace DGNB {
	
/*! comparative values of additional ecological balance indicators */
class Env1_1_3 {								// max +20 pts
	public:

	/*! Basic parameters. */
	enum para_t {
		/*! RefEnv1_1_3_1_1 */
		P_RefEnv1_1_3_1_1,					// Keyword: RefEnv1_1_3_1_1					[-]		// ToDo Einheit kWh/m2a	[kWh pro m² und Jahr]
		/*! CurrentValueEnv1_1_3_1_1 */
		P_CurrentValueEnv1_1_3_1_1,			// Keyword: CurrentValueEnv1_1_3_1_1		[-]		// ToDo Einheit kWh/m2a	[kWh pro m² und Jahr]
		/*! RefEnv1_1_3_1_2POCP */
		P_RefEnv1_1_3_1_2POCP,				// Keyword: RefEnv1_1_3_1_2POCP				[-]		// ToDo Einheit C2H4e/m2a	[troposphärisches Ozon pro m² und Jahr]
		/*! CurrentValueEnv1_1_3_1_2POCP */
		P_CurrentValueEnv1_1_3_1_2POCP,		// Keyword: CurrentValueEnv1_1_3_1_2POCP	[-]		// ToDo Einheit C2H4e/m2a	[troposphärisches Ozon pro m² und Jahr]
		/*! RefEnv1_1_3_1_2AP */
		P_RefEnv1_1_3_1_2AP,				// Keyword: RefEnv1_1_3_1_2AP				[-]		// ToDo Einheit SO2e/m2a	[Versauerungspotenzial Boden&Wasser pro m² und Jahr]
		/*! CurrentValueEnv1_1_3_1_2AP */
		P_CurrentValueEnv1_1_3_1_2AP,		// Keyword: CurrentValueEnv1_1_3_1_2AP		[-]		// ToDo Einheit SO2e/m2a	[Versauerungspotenzial Boden&Wasser pro m² und Jahr]
		/*! RefEnv1_1_3_1_2EP */
		P_RefEnv1_1_3_1_2EP,				// Keyword: RefEnv1_1_3_1_2EP				[-]		// ToDo Einheit PO43/m2a	[Eutrophierungspotenzial pro m² und Jahr]
		/*! CurrentValueEnv1_1_3_1_2EP */
		P_CurrentValueEnv1_1_3_1_2EP,		// Keyword: CurrentValueEnv1_1_3_1_2EP		[-]		// ToDo Einheit PO43/m2a	[Eutrophierungspotenzial pro m² und Jahr]
		// Anm. FW ist im Katalog nur als bewertbar erwähnt, jedoch nicht in der Tabelle aufgeführt
		/*! RefEnv1_1_3_1_2FW */
		P_RefEnv1_1_3_1_2FW,				// Keyword: RefEnv1_1_3_1_2FW				[-]		// ToDo Einheit m3/m2a	[m3 Frischwasser pro m² und Jahr]
		/*! CurrentValueEnv1_1_3_1_2FW */
		P_CurrentValueEnv1_1_3_1_2FW,		// Keyword: CurrentValueEnv1_1_3_1_2FW		[-]		// ToDo Einheit m3/m2a	[m3 Frischwasser pro m² und Jahr]
		NUM_P
	};
	
	/*! evaluation of additional ecological indicators */
	/*! results of life cycle primary energy balance (non-renewable) fall below target value, reference value, threshold value */
	// ENV1.1.3.1.1
	enum CVAEI_LifeCyclePrimaryEnergyBalance{
		CVAEILCPEB_ResultsSubmitted,								// Keyword: CVAEILCPEB_ResultsSubmitted
		NUM_CVAEILCPEB
	};

	/*! weighted results of additional environmental indicators fall below target value, reference value, threshold value */
	// ENV1.1.3.1.2
	enum CVAEI_WeightedResultsOfAdditionalEnvironmentalIndicators{
		CVAEIWRAEI_ResultsSubmitted,								// Keyword: CVAEIWRAEI_ResultsSubmitted
		NUM_CVAEIWRAEI
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env1_1_3(){}

	Env1_1_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	/*! Current points of this single criteria. */
	/*! early stage: operating evaluation */
	double score();
	double scoreBonus();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_CVAEILCPEB[NUM_CVAEILCPEB];			// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CVAEIWRAEI[NUM_CVAEIWRAEI];			// XML:E

	IBK::Parameter					m_para[NUM_P];								// XML:E

	Utilities::UsageType			m_usageType;

};

} // namespace DGNB

#endif // Env1_1_3H
