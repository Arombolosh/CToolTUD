#include "DGNB_Soc1_3_2.h"

namespace DGNB {
	
double DGNB::Soc1_3_2::score() {
	double soc1_3_2 = 0;
	switch (m_usageType) {
		case Utilities::UT_Office:
		case Utilities::UT_Education:			
		case Utilities::UT_Hotel:
		case Utilities::UT_Assembly:
		case Utilities::UT_Healthcare:
			soc1_3_2 += (m_flag_PAACRAC[(PAAC_RoomAcousticConcepts)0].isEnabled() ? 10 : 0);
			break;
			
		default:
			soc1_3_2 += 0;
			break;
	}

	return soc1_3_2;
} // Soc1.3.2

} // namespace DGNB
