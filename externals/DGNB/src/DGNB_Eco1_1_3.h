#ifndef DGNB_Eco1_1_3H
#define DGNB_Eco1_1_3H

#include "DGNB_Utilities.h"

namespace DGNB {
/*! Eco1.1.3 building-related life cycle costs */
class Eco1_1_3	// max +10
{
public:

	/*! Basic parameters. */
	enum para_t {

		// alles in EUR/m2
		/*! netLCCPerBuildingTypeUpperValue */
		P_ReferenceValue_eco1_1_3netLCCPerBuildingTypeUpperValue,						// Keyword: ReferenceValue_eco1_1_3netLCCPerBuildingTypeUpperValue							[-]
		/*! netLCCPerBuildingTypeIntermediateValue */
		P_ReferenceValue_eco1_1_3netLCCPerBuildingTypeIntermediateValue,				// Keyword: ReferenceValue_eco1_1_3netLCCPerBuildingTypeIntermediateValue					[-]
		/*! netLCCPerBuildingTypeLowerValue */
		P_ReferenceValue_eco1_1_3netLCCPerBuildingTypeLowerValue,						// Keyword: ReferenceValue_eco1_1_3netLCCPerBuildingTypeLowerValue							[-]
		/*! BRLCCC_NetLifeCycleCosts */
		P_CurrentValue_eco1_1_3BRLCCC_NetLifeCycleCosts,								// Keyword: CurrentValue_eco1_1_3BRLCCC_NetLifeCycleCosts									[-]
		/*! BRLCCC_CSAnnualEnergyConsumptionPerMeterRefrigeratedDC */
		P_CurrentValue_eco1_1_3BRLCCC_CSAnnualEnergyConsumptionPerMeterRefrigeratedDC,	// Keyword: CurrentValue_eco1_1_3BRLCCC_CSAnnualEnergyConsumptionPerMeterRefrigeratedDC		[-]
		/*! BRLCCC_HealthCareTypeII */
		P_ReferenceValue_eco1_1_3BRLCCC_HealthCareTypeII,								// Keyword: ReferenceValue_eco1_1_3BRLCCC_HealthCareTypeII									[-]
		NUM_P
	};


	/*! Eco1.1.3.1 calculation of building-related life cycle costs */
	enum BRLCC_Calculation {										// max +80
		BRLCCC_NetLifeCycleCostsResultsSubmitted,					// Keyword: BRLCCC_NetLifeCycleCostsResultsSubmitted
		// convenience stores only:
		BRLCCC_DisplayCaseFlag,										// Keyword: BRLCCC_DisplayCaseFlag
		// health care type II buildings only (hospitals and university hospitals:
		BRLCCC_HealthCareTypeIIFlag,								// Keyword: BRLCCC_HealthCareTypeIIFlag
		NUM_BRLCCC
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco1_1_3(){}

	Eco1_1_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag			m_flag_BRLCCC[NUM_BRLCCC];					// XML:E

	IBK::Parameter					m_para[NUM_P];					// XML:E

	Utilities::UsageType			m_usageType;

};

} // namespace DGNB

#endif // DGNB_Eco1_1_3H
