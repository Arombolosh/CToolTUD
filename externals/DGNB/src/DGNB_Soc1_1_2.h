#ifndef DGNB_Soc1_1_2H
#define DGNB_Soc1_1_2H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.1.2 relative humidity (quantitative) */
class Soc1_1_2
{
public:

	/*! Soc 1.1.2.1 relative humidity (heating period) */
	enum RH_RelativeHumidityHeatingPeriod {							// pts depending on usage type
		RHHP_RelativeHumidityHigherThan30Percent,					// Keyword: RHHP_RelativeHumidityHigherThan30Percent
		RHHP_HotelRelativeHumidityLowerThan70Percent,				// Keyword: RHHP_HotelRelativeHumidityLowerThan70Percent
		RHHP_ConditionMetFor95PercentOfTime,						// Keyword: RHHP_ConditionMetFor95PercentOfTime
		NUM_RHHP
	};
	
	/*! Soc 1.1.2.2 relative humidity (cooling period) */
	enum RH_RelativeHumidityCoolingPeriod {							// pts depending on usage type
		RHCP_MaxHumidity12GramPerKilogram,							// Keyword: RHCP_MaxHumidity12GramPerKilogram
		NUM_RHCP
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_1_2(){}

	Soc1_1_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_RHHP[NUM_RHHP];			// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_RHCP[NUM_RHCP];			// XML:E

	Utilities::UsageType			m_usageType;

};

} // namespace DGNB

#endif // DGNB_Soc1_1_2H
