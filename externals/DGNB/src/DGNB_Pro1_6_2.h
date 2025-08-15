#ifndef DGNB_Pro1_6_2H
#define DGNB_Pro1_6_2H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

/*! Recommendations */
class Pro1_6_2
{
public:

	/*! Pro1.6.2 Recommendation of independent Design Board(s) */
	enum R_RecommendationByIndependentDesignBoards {											// max +15
		RIDB_ProjectPresentationInFrontOfDesignBoardOfCommuneAndArchitecturalAssociation,		// Keyword: RIDB_ProjectPresentationInFrontOfDesignBoardOfCommuneAndArchitecturalAssociation
		RIDB_ImplementationOfDesignBoardsRecommendations,										// Keyword: RIDB_ImplementationOfDesignBoardsRecommendations
		NUM_RIDB
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro1_6_2(){}

	Pro1_6_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_RIDB[NUM_RIDB];			// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro1_6_2H
