#ifndef DGNB_Soc1_1_4H
#define DGNB_Soc1_1_4H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.1.4 radiation temperature asymmetry and floor temperature */
class Soc1_1_4
{
public:

	/*! Soc 1.1.4.1 radiation temperature asymmetry and floor temperature - Cooling Period */
	enum RTAFT_CoolingPeriod {									// pts depending on usage type
		RTAFTCP_CeilingMin16Degrees,							// Keyword: RTAFTCP_CeilingMin16Degrees
		RTAFTCP_CeilingMax35Degrees,							// Keyword: RTAFTCP_CeilingMax35Degrees
		RTAFTCP_GlassSurfacesMin18Degrees,						// Keyword: RTAFTCP_GlassSurfacesMin18Degrees
		RTAFTCP_GlassSurfacesMax35Degrees,						// Keyword: RTAFTCP_GlassSurfacesMax35Degrees
		RTAFTCP_FloorMin19Degrees,								// Keyword: RTAFTCP_FloorMin19Degrees
		RTAFTCP_FloorMax29Degrees,								// Keyword: RTAFTCP_FloorMax29Degrees
		RTAFTCP_LogisticAndProductionMeasuresTakenToPreventRTA,	// Keyword: RTAFTCP_LogisticAndProductionMeasuresTakenToPreventRTA
		NUM_RTAFTCP
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_1_4(){}

	Soc1_1_4(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag					m_flag_RTAFTCP[NUM_RTAFTCP];	// XML:E

	Utilities::UsageType		m_usageType;

};

} // namespace DGNB

#endif // DGNB_Soc1_1_4H
