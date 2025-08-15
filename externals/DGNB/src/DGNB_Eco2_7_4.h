#ifndef DGNB_Eco2_7_4H
#define DGNB_Eco2_7_4H

#include "DGNB_Utilities.h"

namespace DGNB {

/*! Eco2.7.4 Digital Twin for Operational Phase */
class Eco2_7_4 {

public:

	/*! Eco2.7.4.1 Creation and Handover of as-built-documentation / building model */
	enum DTOP_CreationAndHandoverOfAsBuiltDocumentationOrBuildingModel {			// Not for HC: max +10
		DTOPCHDBM_CalculationByBGFSmallerThan5000m2Method,							// Keyword: DTOPCHDBM_CalculationByBGFSmallerThan5000m2Method
		DTOPCHDBM_AsBuiltControlImplementedAndDocumented,							// Keyword: DTOPCHDBM_AsBuiltControlImplementedAndDocumented
		DTOPCHDBM_BuildingDocumentationOrModelHasAsBuiltQuality,					// Keyword: DTOPCHDBM_BuildingDocumentationOrModelHasAsBuiltQuality
		DTOPCHDBM_DigitalBuildingRessourcePassIsPartOfDigitalTwinAndAvailable,		// Keyword: DTOPCHDBM_DigitalBuildingRessourcePassIsPartOfDigitalTwinAndAvailable
		NUM_DTOPCHDBM
	};

	/*! Eco2.7.4.2 Circular Economy Bonus Digitalisation of preexisting constructions */
	enum DTOP_CircularEconomyDigitalisationOfPreexistingConstructions {				// Not for HC: max +10
		DTOPCEDPC_DigitalisationConducted,											// Keyword: DTOPCEDPC_DigitalisationConducted
		NUM_DTOPCEDPC
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco2_7_4(){}

	Eco2_7_4(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_DTOPCHDBM[NUM_DTOPCHDBM];			// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_DTOPCEDPC[NUM_DTOPCEDPC];			// XML:E

	Utilities::UsageType			m_usageType;

}; // Eco 2.7.4

} // namespace DGNB

#endif // DGNB_Eco2_7_4H
