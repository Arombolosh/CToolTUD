#ifndef DGNB_Tec1_3_1H
#define DGNB_Tec1_3_1H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Tec1_3_1
{
public:

	/*! Tec1.3.1 Potential Analysis of the Building Envelope: Potential Of Front Elements (Walls and Windows) */
	enum PABE_PotentialOfFrontElements {													// max +30
		PABEPFE_PotentialOfSolarEnergy,														// Keyword: PABEPFE_PotentialOfSolarEnergy
		PABEPFE_PotentialOfGreening,														// Keyword: PABEPFE_PotentialOfGreening
		PABEPFE_AnalysisOfDifferentVariationsFocusedOnSustainabilityThroughoutLifeCycle,	// Keyword: PABEPFE_AnalysisOfDifferentVariationsFocusedOnSustainabilityThroughoutLifeCycle
		PABEPFE_UseOfSustainableResourcesForInsulationAndCladding,							// Keyword: PABEPFE_UseOfSustainableResourcesForInsulationAndCladding
		PABEPFE_PossibilityOfNondestructiveReplacementOfParts, 								// Keyword: PABEPFE_PossibilityOfNondestructiveReplacementOfParts
		PABEPFE_AnalysisOfDifferentVariationsFocusedOnHeatLossOverBuildingEnvelope,			// Keyword: PABEPFE_AnalysisOfDifferentVariationsFocusedOnHeatLossOverBuildingEnvelope
		NUM_PABEPFE
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Tec1_3_1(){}

	Tec1_3_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_PABEPFE[NUM_PABEPFE];	// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Tec1_3_1H
