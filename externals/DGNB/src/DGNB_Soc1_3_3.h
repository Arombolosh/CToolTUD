#ifndef DGNB_Soc1_3_3H
#define DGNB_Soc1_3_3H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.3.3 Room Acoustics - Observation of DIN 18041 and VDI 2569 */
class Soc1_3_3
{
public:

	/*! Soc1.3.3a Room Acoustics - Hotel, Healthcare, Assembly, Education, Office */
	enum RA_HotelHealthcareAssemblyEducationOffice {						// max +50 / +60 depending on usage Type
		RAHHcAEO_ObservationOfDIN_18041ForRoomTypesAAndB,					// Keyword: RAHHcAEO_ObservationOfDIN_18041ForRoomTypesAAndB
		RAHHcAEO_ObservationOfDIN_18041ForInclusiveUse,						// Keyword: RAHHcAEO_ObservationOfDIN_18041ForInclusiveUse
		RAHHcAEO_ObservationOfVDI_2569ClassA,								// Keyword: RAHHcAEO_ObservationOfVDI_2569ClassA
		RAHHcAEO_ObservationOfVDI_2569ClassB,								// Keyword: RAHHcAEO_ObservationOfVDI_2569ClassB
		RAHHcAEO_MeasuresTakenAndVerified,									// Keyword: RAHHcAEO_MeasuresTakenAndVerified
		NUM_RAHHcAEO
	};

	/*! Soc1.3.3b Room Acoustics - Residential */
	enum RA_Residential {													// max +20
		RAR_RoomAcousticMeasuresTakenForSharedHallwaysAndStairways,			// Keyword: RAR_RoomAcousticMeasuresTakenForSharedHallwaysAndStairways
		RAR_RoomAcousticMeasuresTakenForSharedGroupMealAndLectureRooms,		// Keyword: RAR_RoomAcousticMeasuresTakenForSharedGroupMealAndLectureRooms
		NUM_RAR
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_3_3(){}

	Soc1_3_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag					m_flag_RAHHcAEO[NUM_RAHHcAEO];				// XML:E
	/*! List of flags. */
	IBK::Flag					m_flag_RAR[NUM_RAR];						// XML:E

	Utilities::UsageType		m_usageType;

};

} // namespace DGNB

#endif // DGNB_Soc1_3_3
