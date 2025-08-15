#ifndef DGNB_Tec1_4_3H
#define DGNB_Tec1_4_3H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Tec1_4_3
{
public:

	/*! Tec1.4.3.1 Accessibility of Building Services: Systems Engineering and Creation */
	enum  ABS_SystemsEngineeringAndCreation {												// max +10
		ABSSEC_GenerallyGoodAccessibilityOfAllSystemComponentsForReplacementAndRetrofitting,// Keyword: ABSSEC_GenerallyGoodAccessibilityOfAllSystemComponentsForReplacementAndRetrofitting
		ABSSEC_SufficientNumberAndSizeOfOpeningsDoorsAndHallways,							// Keyword: ABSSEC_SufficientNumberAndSizeOfOpeningsDoorsAndHallways
		ABSSEC_TransportAndReplacementOfComponentsPossibleWithoutConstructionalMeasures,	// Keyword: ABSSEC_TransportAndReplacementOfComponentsPossibleWithoutConstructionalMeasures
		NUM_ABSSEC
	};

	/*! Tec1.4.3.2 Accessibility of Building Services: Ducts, Traces, Allocation */
	enum  ABS_DuctsTracesAllocation {														// max +10
		ABSDTA_VerticalDuctsAndTracesOfAllSubsectionsAccessible,							// Keyword: ABSDTA_VerticalDuctsAndTracesOfAllSubsectionsAccessible
		ABSDTA_PossibilityOfRetrofittingWithoutMajorDisturbanceToBuildingOperation,			// Keyword: ABSDTA_PossibilityOfRetrofittingWithoutMajorDisturbanceToBuildingOperation
		NUM_ABSDTA
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Tec1_4_3(){}

	Tec1_4_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_ABSSEC[NUM_ABSSEC];		// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_ABSDTA[NUM_ABSDTA];		// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Tec1_4_3H
