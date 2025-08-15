#ifndef DGNB_Eco2_7_5H
#define DGNB_Eco2_7_5H

#include "DGNB_Utilities.h"

namespace DGNB {

/*! Eco2.7.5 Documentation of Circularity */
class Eco2_7_5 {

public:

	/*! Eco2.7.5.1  */
	enum DC_InformationOnBuildingRemovability {									// +5
		DCIBR_CompleteDocumentationOnRemovabilityHandedOverToClient,			// Keyword: DCIBR_CompleteDocumentationOnRemovabilityHandedOverToClient
		NUM_DCIBR
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco2_7_5(){}

	Eco2_7_5(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_DCIBR[NUM_DCIBR];					// XML:E

	Utilities::UsageType			m_usageType;

}; // Eco 2.7.5

} // namespace DGNB

#endif // DGNB_Eco2_7_5H
