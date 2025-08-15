#ifndef DGNB_Soc1_6_3H
#define DGNB_Soc1_6_3H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.6.3 family-friendliness, child-friendliness, elderly-friendliness */
class Soc1_6_3
{
public:

	/*! Basic parameters. */
	enum para_t {
		/*! Soc1_6_3_1AlternativeInnovativeSolutions */
		P_Soc1_6_3_1AlternativeInnovativeSolutions,					// Keyword: Soc1_6_3_1AlternativeInnovativeSolutions		[-]
		NUM_P
	};

	/*! Soc1.6.3.1 On Site Offers */
	enum FCEF_OnSiteOffers {										// max +10
		FCEFOSO_Daycare,											// Keyword: FCEFOSO_Daycare
		FCEFOSO_BabyChangeAndSeparateBreastFeedingRooms,			// Keyword: FCEFOSO_BabyChangeAndSeparateBreastFeedingRooms
		FCEFOSO_Playground,											// Keyword: FCEFOSO_Playground
		FCEFOSO_ElderlyCommonRoomsPlayrooms,						// Keyword: FCEFOSO_ElderlyCommonRoomsPlayrooms
		FCEFOSO_FamilyFriendlyParking,								// Keyword: FCEFOSO_FamilyFriendlyParking
		FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithBabyChange,		// Keyword: FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithBabyChange
		FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithCrib,				// Keyword: FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithCrib
		FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithKitchenette,		// Keyword: FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithKitchenette
		FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithDarkeningBlind,	// Keyword: FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithDarkeningBlind
		FCEFOSO_InnovationRoomAlternativeCertification,				// Keyword: FCEFOSO_InnovationRoomAlternativeCertification
		NUM_FCEFOSO
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_6_3(){}

	Soc1_6_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag					m_flag_FCEFOSO[NUM_FCEFOSO];	// XML:E
	
	IBK::Parameter				m_para[NUM_P];					// XML:E

	Utilities::UsageType		m_usageType;

};

} // namespace DGNB

#endif // DGNB_Soc1_6_3
