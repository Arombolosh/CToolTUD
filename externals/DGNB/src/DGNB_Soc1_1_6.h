#ifndef DGNB_Soc1_1_6H
#define DGNB_Soc1_1_6H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.1.6 User Influence */
class Soc1_1_6
{
public:

	/*! Soc 1.1.6.1 User Influence */
	enum UI_UserInfluence {										// max +15, +5 each
		UI_PossibilityOfReuse,									// Keyword: UI_PossibilityOfReuse
		UI_RoomAirCycleIndividuallyManipulable, 				// Keyword: UI_RoomAirCycleIndividuallyManipulable
		UI_RoomTemperatureIndividuallyManipulable,				// Keyword: UI_RoomTemperatureIndividuallyManipulable
		UI_SurveyOnUserSatisfactionAndEnergyEfficiency,			// Keyword: UI_SurveyOnUserSatisfactionAndEnergyEfficiency
		NUM_UI
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_1_6(){}

	Soc1_1_6(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag					m_flag_UI[NUM_UI];				// XML:E

	Utilities::UsageType		m_usageType;

};

} // namespace DGNB

#endif // DGNB_Soc1_1_6H
