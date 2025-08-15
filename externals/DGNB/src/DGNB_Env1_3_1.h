#ifndef DGNB_Env1_3_1H
#define DGNB_Env1_3_1H
#include "DGNB_Utilities.h"

namespace DGNB {

/*! responsible usage of resources in planning and execution */
class Env1_3_1 {													// max +20
	public:

	// max +5
	/*! Env1.3.1.1 Supply Chain Diligence */
	enum RURPE_SupplyChainDiligence {
		RURPESCD_DeclarationOfDiligenceGiven,						// Keyword: RURPESCD_DeclarationOfDiligenceGiven
		NUM_RURPESCD
	};

	// max +5
	/*! Env1.3.1.2 responsible usage of resources in planning */
	enum RURPE_ResponsibleUsageOfResourcesInPlanning {
		RURPERURP_RegularIntegrationOfMeasures,						// Keyword: RURPERURP_RegularIntegrationOfMeasures
		NUM_RURPERURP
	};

	// max +10
	/*! Env1.3.1.2 responsible usage of resources in execution and documentation */
	enum RURPE_ResponsibleUsageOfResourcesInExecutionAndDocumentation {
		RURPERURED_PartsCatalogue,									// Keyword: RURPERURED_PartsCatalogue
		NUM_RURPERURED
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env1_3_1(){}

	Env1_3_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_RURPESCD[NUM_RURPESCD];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_RURPERURP[NUM_RURPERURP];			// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_RURPERURED[NUM_RURPERURED];			// XML:E

	Utilities::UsageType			m_usageType;

};

} // namespace DGNB

#endif // Env1_3_1H
