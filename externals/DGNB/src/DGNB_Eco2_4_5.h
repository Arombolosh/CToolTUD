#ifndef DGNB_Eco2_4_5H
#define DGNB_Eco2_4_5H

#include "DGNB_Utilities.h"

namespace DGNB {

/*! Eco2.4.5 Risk Analysis */
class Eco2_4_5	// max +10
{
public:

	/*! Eco2.4.5 Risk Analysis according to European Report Framework */
	enum RA_RiskAnalysisAccordingToEuropeanFramework {				// max +5
		RAAEF_RiskAnalysisDuringEarlyPlanningPhases,				// Keyword: RAAEF_RiskAnalysisDuringEarlyPlanningPhases
		NUM_RAAEF
	};

	/*! Eco2.4.5.2 Building conform to taxonomy */
	enum RA_BuildingConformToTaxonomy {								// max +10
		RABCT_AspirationsForVerification,							// Keyword: RABCT_AspirationsForVerification
		RABCT_ImplementationOfStandards,							// Keyword: RABCT_ImplementationOfStandards
		NUM_RABCT
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco2_4_5(){}

	Eco2_4_5(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag			m_flag_RAAEF[NUM_RAAEF];					// XML:E
	/*! List of flags. */
	IBK::Flag			m_flag_RABCT[NUM_RABCT];					// XML:E

	Utilities::UsageType			m_usageType;

}; // Eco 2.4.5

} // namespace DGNB

#endif // DGNB_Eco2_4_5H
