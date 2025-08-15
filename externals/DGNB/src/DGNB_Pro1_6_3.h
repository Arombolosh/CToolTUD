#ifndef DGNB_Pro1_6_3H
#define DGNB_Pro1_6_3H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

/*! Honoring with Architecture Award */
class Pro1_6_3
{
public:

	/*! Pro1.6.3 Recognition */
	enum HAA_Recognition {														// max +15
		HAAR_RecognitionOfGoodConstructionalCulturalQuality,					// Keyword: HAAR_RecognitionOfGoodConstructionalCulturalQuality
		HAAR_RecognitionOfFinishedProjectWithArchitectureAwardDGNBDiamond,		// Keyword: HAAR_RecognitionOfFinishedProjectWithArchitectureAwardDGNBDiamond
		NUM_HAAR
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro1_6_3(){}

	Pro1_6_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_HAAR[NUM_HAAR];			// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro1_6_3H
