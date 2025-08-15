#ifndef DGNB_Eco2_7_2H
#define DGNB_Eco2_7_2H

#include "DGNB_Utilities.h"

namespace DGNB {

/*! Eco2.7.2 Object Documentation for Buildings in Use */
class Eco2_7_2 {

public:

	/*! Eco2.7.2.1 Revision, Operation and Maintenance Plan */
	enum ODBU_RevisionOperationMaintenancePlan {									// max +30/+10
		ODBUROMP_CalculationByBGFSmallerThan5000m2Method,							// Keyword: ODBUROMP_CalculationByBGFSmallerThan5000m2Method
		ODBUROMP_CompleteObjectDocumentationChecklistHandedOverToClient,			// Keyword: ODBUROMP_CompleteObjectDocumentationChecklistHandedOverToClient
		ODBUROMP_AllDataKeptOnFileForFiveYearsAndHandedOverToOperatorCompany,		// Keyword: ODBUROMP_AllDataKeptOnFileForFiveYearsAndHandedOverToOperatorCompany
		NUM_ODBUROMP
	};

	/*! Eco2.7.2.2 Operator-Friendly Building Model */
	enum ODBU_OperatorFriendlyBuildingModel {													// max +0/+10
		ODBUOFBM_CalculationByBGFSmallerThan5000m2Method,										// Keyword: ODBUOFBM_CalculationByBGFSmallerThan5000m2Method
		ODBUOFBM_UpToDateCompleteOperatorFriendlyModelHandedOvertoOperatorCompany,				// Keyword: ODBUOFBM_UpToDateCompleteOperatorFriendlyModelHandedOvertoOperatorCompany
		ODBUOFBM_LifeCycleGreenhouseGasAndEnergyBalanceIncludedOrPreparedForMonitoring,			// Keyword: ODBUOFBM_LifeCycleGreenhouseGasAndEnergyBalanceIncludedOrPreparedForMonitoring
		NUM_ODBUOFBM
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco2_7_2(){}

	Eco2_7_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_ODBUROMP[NUM_ODBUROMP];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_ODBUOFBM[NUM_ODBUOFBM];				// XML:E

	Utilities::UsageType			m_usageType;

}; // Eco 2.7.2

} // namespace DGNB

#endif // DGNB_Eco2_7_2H
