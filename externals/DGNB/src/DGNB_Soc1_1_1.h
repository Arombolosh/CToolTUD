#ifndef DGNB_Soc1_1_1H
#define DGNB_Soc1_1_1H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.1.1 operative temperature / room temperature */
class Soc1_1_1
{
public:

	/*! Basic parameters. */
	enum para_t {
		/*! ShoppingCenterRentalAreaCoolingLoad */
		P_CurrentValue_soc1_1_1_ShoppingCenterRentalAreaCoolingLoad,	// Keyword: CurrentValue_soc1_1_1_ShoppingCenterRentalAreaCoolingLoad		[W/m2]
		NUM_P
	};

	/*! Soc 1.1.1 operative temperature (cooling period) */
	enum OTRT_OperativeTemperatureCoolingPeriod {												// pts depending on usage type
		// also for ShoppingCenterRentalArea and Logistic & Production offices:
		OTRTOT_Max5PercentDeviationFromDIN_EN_16798_1_Category3,								// Keyword: OTRTOT_Max5PercentDeviationFromDIN_EN_16798_1_Category3
		// also for ShoppingCenterRentalArea and Logistic & Production offices:
		OTRTOT_Max5PercentDeviationFromDIN_EN_16798_1_Category1and2,							// Keyword: OTRTOT_Max5PercentDeviationFromDIN_EN_16798_1_Category1and2
		OTRTOT_ShoppingCenterRentalAreaCoolingLoadCertification,								// Keyword: OTRTOT_ShoppingCenterRentalAreaCoolingLoadCertification
		OTRTOT_ShoppingCenterMallStreetMax5PercentDeviationFromDIN_EN_16798_1_Category3,		// Keyword: OTRTOT_ShoppingCenterMallStreetMax5PercentDeviationFromDIN_EN_16798_1_Category3
		OTRTOT_ShoppingCenterMallStreetMax5PercentDeviationFromDIN_EN_16798_1_Category1and2,	// Keyword: OTRTOT_ShoppingCenterMallStreetMax5PercentDeviationFromDIN_EN_16798_1_Category1and2
		OTRTOT_LogisticsAndProductionMeasuresTakenAbove26Degrees,								// Keyword: OTRTOT_LogisticsAndProductionMeasuresTakenAbove26Degrees
		OTRTOT_LogisticsAndProductionLimitationTo30Degrees,										// Keyword: OTRTOT_LogisticsAndProductionLimitationTo30Degrees
		NUM_OTRTOT
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_1_1(){}

	Soc1_1_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_OTRTOT[NUM_OTRTOT];			// XML:E
	
	IBK::Parameter					m_para[NUM_P];						// XML:E

	Utilities::UsageType			m_usageType;

};

} // namespace DGNB

#endif // DGNB_Soc1_1_1H
