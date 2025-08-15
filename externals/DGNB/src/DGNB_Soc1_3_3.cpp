#include "DGNB_Soc1_3_3.h"

namespace DGNB {
	
double DGNB::Soc1_3_3::score() {
	double soc1_3_3 = 0;
	switch (m_usageType) {
		case Utilities::UT_Office:
			soc1_3_3 += (m_flag_RAHHcAEO[(RAHHcAEO_ObservationOfDIN_18041ForRoomTypesAAndB)].isEnabled() ? 20 : 0);
			soc1_3_3 += (m_flag_RAHHcAEO[(RAHHcAEO_ObservationOfDIN_18041ForInclusiveUse)].isEnabled() ? 10 : 0);
			soc1_3_3 += (m_flag_RAHHcAEO[(RAHHcAEO_ObservationOfVDI_2569ClassA)].isEnabled() ? 10 : 0);
			soc1_3_3 += (m_flag_RAHHcAEO[(RAHHcAEO_ObservationOfVDI_2569ClassB)].isEnabled() ? 10 : 0);
			break;		
		
		case Utilities::UT_Education:	
			soc1_3_3 += (m_flag_RAHHcAEO[(RAHHcAEO_ObservationOfDIN_18041ForRoomTypesAAndB)].isEnabled() ? 35 : 0);
			soc1_3_3 += (m_flag_RAHHcAEO[(RAHHcAEO_ObservationOfDIN_18041ForInclusiveUse)].isEnabled() ? 15 : 0);
			soc1_3_3 += (m_flag_RAHHcAEO[(RAHHcAEO_ObservationOfVDI_2569ClassA)].isEnabled() ? 5 : 0);
			soc1_3_3 += (m_flag_RAHHcAEO[(RAHHcAEO_ObservationOfVDI_2569ClassB)].isEnabled() ? 5 : 0);
			break;
			
		case Utilities::UT_Hotel:
		case Utilities::UT_Assembly:
		case Utilities::UT_Healthcare:
			soc1_3_3 += (m_flag_RAHHcAEO[(RAHHcAEO_ObservationOfDIN_18041ForRoomTypesAAndB)].isEnabled() ? 30 : 0);
			soc1_3_3 += (m_flag_RAHHcAEO[(RAHHcAEO_ObservationOfDIN_18041ForInclusiveUse)].isEnabled() ? 10 : 0);
			soc1_3_3 += (m_flag_RAHHcAEO[(RAHHcAEO_ObservationOfVDI_2569ClassA)].isEnabled() ? 5 : 0);
			soc1_3_3 += (m_flag_RAHHcAEO[(RAHHcAEO_ObservationOfVDI_2569ClassB)].isEnabled() ? 5 : 0);
			break;
			
		case Utilities::UT_Residential:
			soc1_3_3 += (m_flag_RAR[(RAR_RoomAcousticMeasuresTakenForSharedHallwaysAndStairways)].isEnabled() ? 10 : 0);
			soc1_3_3 += (m_flag_RAR[(RAR_RoomAcousticMeasuresTakenForSharedGroupMealAndLectureRooms)].isEnabled() ? 10 : 0);
			break;
			
		default:
			soc1_3_3 += 0;
			break;
	}

	return soc1_3_3;
} // Soc1.3.3

} // namespace DGNB
