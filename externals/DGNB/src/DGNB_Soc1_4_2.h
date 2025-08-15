#ifndef DGNB_Soc1_4_2H
#define DGNB_Soc1_4_2H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.4.2 Daylight Availability permanent work places */
class Soc1_4_2
{
public:

	/*! Basic parameters. */
	enum para_t {
		/*! Soc1_4_2UsageLighting*/
		P_CurrentValue_soc1_4_2UsageLighting,						// Keyword: CurrentValue_soc1_4_2UsageLighting						[---]		// ToDo Einheit % SO oder anders?
		/*! Soc1_4_2TranslucentCeilingLightPortion */
		P_CurrentValue_soc1_4_2TranslucentCeilingLightPortion,		// Keyword: CurrentValue_soc1_4_2TranslucentCeilingLightPortion		[---]		// ToDo Einheit % SO oder anders?
		NUM_P
	};

	/*! Soc1.4.2.1 Annual Relative Usage Lighting According to DIN 5034 */
	enum ARUL_OfficeEducationAssemblyLogisticsHealthcare {			// max +15 / +20 depending on usage Type
		ARULOEALHc_UsageLightingResultsSubmitted,					// Keyword: ARULOEALHc_UsageLightingResultsSubmitted
		ARULOEALHc_TranslucentCeilingLightPortionResultsSubmitted,	// Keyword: ARULOEALHc_TranslucentCeilingLightPortionResultsSubmitted
		ARULOEALHc_AssemblyAreaType1,								// Keyword: ARULOEALHc_AssemblyAreaType1
		ARULOEALHc_AssemblyAreaType2,								// Keyword: ARULOEALHc_AssemblyAreaType2
		NUM_ARULOEALHc
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_4_2(){}

	Soc1_4_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag					m_flag_ARULOEALHc[NUM_ARULOEALHc];						// XML:E
	
	IBK::Parameter				m_para[NUM_P];											// XML:E

	Utilities::UsageType		m_usageType;
	
};

} // namespace DGNB

#endif // DGNB_Soc1_4_2
