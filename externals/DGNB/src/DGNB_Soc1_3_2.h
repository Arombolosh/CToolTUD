#ifndef DGNB_Soc1_3_2H
#define DGNB_Soc1_3_2H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.3.2 Building Acoustics - Observation of DIN 4109 and VDI 2569 */
class Soc1_3_2
{
public:

	/*! Soc1.3.2 Planning-Accompanying Acoustic Concept (only Office, Education, Hotel, Healthcare, Assembly) */
	enum PAAC_RoomAcousticConcepts {												// max +10
		PAACRAC_CreationOfPlanningAccompanyingRoomAcousticConcept,					// Keyword: PAACRAC_CreationOfPlanningAccompanyingRoomAcousticConcept
		NUM_PAACRAC
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_3_2(){}

	Soc1_3_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag					m_flag_PAACRAC[NUM_PAACRAC];						// XML:E

	Utilities::UsageType		m_usageType;

};

} // namespace DGNB

#endif // DGNB_Soc1_3_2
