#ifndef DGNB_Soc1_4_4H
#define DGNB_Soc1_4_4H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.4.4 No Daylight Glare */
class Soc1_4_4
{
public:

	/*! Basic parameters. */
	enum para_t {
		/*! DaylightGlareProbability */
		P_CurrentValue_soc1_4_4_1DaylightGlareProbability,					// Keyword: CurrentValue_soc1_4_4_1DaylightGlareProbability		[---]	// ToDo Einheit % SO oder anders?
		NUM_P
	};

	/*! Soc1.4.4.1a Daylight Glare Shields - Office Education Assembly 1 & 2 Healthcare */
	enum DGS_OfficeEducationAssembly1And2Healthcare {						// max +10 / +20 depending on usage Type
		DGSOEA12Hc_DGPResultsSubmitted,										// Keyword: DGSOEA12Hc_DGPResultsSubmitted
		DGSOEA12Hc_AssemblyType1,											// Keyword: DGSOEA12Hc_AssemblyType1
		DGSOEA12Hc_AssemblyType2,											// Keyword: DGSOEA12Hc_AssemblyType2
		DGSOEA12Hc_A2_CombinationOfLightDivertingSystemsAndGlareShields,	// Keyword: DGSOEA12Hc_A2_CombinationOfLightDivertingSystemsAndGlareShields
		DGSOEA12Hc_A2_UseOfHighNorthLightDiffusionCeilingLights,			// Keyword: DGSOEA12Hc_A2_UseOfHighNorthLightDiffusionCeilingLights
		NUM_DGSOEA12Hc
	};

	/*! Soc1.4.4.1b Daylight Glare Shields - ConvenienceStore */
	enum DGS_ConvenienceStore {												// max +12
		DGSCS_ObservationOfASRA3_4Chapter4_2,								// Keyword: DGSCS_ObservationOfASRA3_4Chapter4_2
		NUM_DGSCS
	};

	/*! Soc1.4.4.1c Daylight Glare Shields - Logistics */
	enum DGS_Logistics {													// max +20
		DGSL_UncertifiedGlareShieldSystem,									// Keyword: DGSL_UncertifiedGlareShieldSystem
		DGSL_Class2GlareShieldSystem,										// Keyword: DGSL_Class2GlareShieldSystem
		DGSL_Class3OrHigherGlareShieldSystem,								// Keyword: DGSL_Class3OrHigherGlareShieldSystem
		NUM_DGSL
	};
	

	/*! Soc1.4.4.1d Daylight Glare Shields - Production */
	enum DGS_Production {													// max +30
		DGSP_CombinationOfLightDivertingSystemsAndGlareShields,				// Keyword: DGSP_CombinationOfLightDivertingSystemsAndGlareShields
		DGSP_UseOfHighNorthLightDiffusionCeilingLights,						// Keyword: DGSP_UseOfHighNorthLightDiffusionCeilingLights
		NUM_DGSP
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_4_4(){}

	Soc1_4_4(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag					m_flag_DGSOEA12Hc[NUM_DGSOEA12Hc];					// XML:E
	/*! List of flags. */
	IBK::Flag					m_flag_DGSCS[NUM_DGSCS];							// XML:E
	/*! List of flags. */
	IBK::Flag					m_flag_DGSL[NUM_DGSL];								// XML:E
	/*! List of flags. */
	IBK::Flag					m_flag_DGSP[NUM_DGSP];								// XML:E

	IBK::Parameter				m_para[NUM_P];										// XML:E
	
	Utilities::UsageType		m_usageType;

};

} // namespace DGNB

#endif // DGNB_Soc1_4_4
