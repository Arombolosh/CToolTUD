#ifndef DGNB_Eco2_6_3H
#define DGNB_Eco2_6_3H

#include "DGNB_Utilities.h"

namespace DGNB {

/*! Eco2.6.3 Measures against further environmental risks on site */
class Eco2_6_3 {

public:

	/*! Eco2.6.3.1 Compensation Measures Air Quality */
	enum MAFERS_CompensationMeasuresAirQuality {					// max +10
		MAFERSCMAQ_PositiveInfluenceOnImmissionInVicinity,			// Keyword: MAFERSCMAQ_PositiveInfluenceOnImmissionInVicinity
		MAFERSCMAQ_RiskAnalysisConducted,							// Keyword: MAFERSCMAQ_RiskAnalysisConducted
		MAFERSCMAQ_RiskAnalysisProtectionMeasuresImplemented,		// Keyword: MAFERSCMAQ_RiskAnalysisProtectionMeasuresImplemented
		NUM_ASBCSA
	};

	/*! Eco2.6.3.2 Compensation Measures Noise */
	enum MAFERS_CompensationMeasuresNoise {											// max +10
		MAFERSCMN_NoiseProtectionConstruction,										// Keyword: MAFERSCMN_NoiseProtectionConstruction
		MAFERSCMN_InclusionOfNoiseProtectionGroundPlans,							// Keyword: MAFERSCMN_InclusionOfNoiseProtectionGroundPlans
		MAFERSCMN_SurveyReportForBuildingAndSurroundingsOnOptimisationmeasures,		// Keyword: MAFERSCMN_SurveyReportForBuildingAndSurroundingsOnOptimisationmeasures
		MAFERSCMN_OptimisationmeasuresImplemented							,		// Keyword: MAFERSCMN_OptimisationmeasuresImplemented
		NUM_MAFERSCMN
	};

	/*! Eco2.6.3.2 Compensation Measures Noise */
	enum MAFERS_RadonRiskReduction {								// max +5
		MAFERSRRR_RadonAccessPreventedOrHeavilyHindered,			// Keyword: MAFERSRRR_RadonAccessPreventedOrHeavilyHindered
		NUM_MAFERSRRR
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco2_6_3(){}

	Eco2_6_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag			m_flag_ASBCSA[NUM_ASBCSA];					// XML:E
	/*! List of flags. */
	IBK::Flag			m_flag_MAFERSCMN[NUM_MAFERSCMN];			// XML:E
	/*! List of flags. */
	IBK::Flag			m_flag_MAFERSRRR[NUM_MAFERSRRR];			// XML:E

	Utilities::UsageType			m_usageType;

}; // Eco 2.6.3

} // namespace DGNB

#endif // DGNB_Eco2_6_3H
