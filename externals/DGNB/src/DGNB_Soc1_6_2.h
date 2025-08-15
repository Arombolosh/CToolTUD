#ifndef DGNB_Soc1_6_2H
#define DGNB_Soc1_6_2H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.6.2 Additional Offers for Users */
class Soc1_6_2
{
public:

	/*! Basic parameters. */
	enum para_t {
		/*! Soc1_6_2_1AlternativeInnovativeSolutions */
		P_Soc1_6_2_1AlternativeInnovativeSolutions,						// Keyword: Soc1_6_2_1AlternativeInnovativeSolutions		[-]
		/*! Soc1_6_2_1AlternativeInnovativeSolutions */
		P_Soc1_6_2_2AlternativeInnovativeSolutions,						// Keyword: Soc1_6_2_2AlternativeInnovativeSolutions		[-]
		NUM_P
	};

	/*! Soc1.6.2.1 Additional Offers and Services */
	enum AOU_AdditionalOffersAndServices {						// max +10
		AOUAOS_AdditionalOffersMultifunctionRoomsCommonRooms,																						// Keyword: AOUAOS_AdditionalOffersMultifunctionRoomsCommonRooms
		AOUAOS_CSCBSC_LockersChangingRooms,																											// Keyword: AOUAOS_CSCBSC_LockersChangingRooms
		AOUAOS_Residential_CommonRoomsAvailableToEveryone,																							// Keyword: AOUAOS_Residential_CommonRoomsAvailableToEveryone
		AOUAOS_Residential_LaundryAndDryingRoomsFunctionAsCommonRooms_PartialWaivingOfLaundryMachineConnectionsInResidentialUnits,					// Keyword: AOUAOS_Residential_LaundryAndDryingRoomsFunctionAsCommonRooms_PartialWaivingOfLaundryMachineConnectionsInResidentialUnits
		AOUAOS_Hc_AdditionalOffersAvailableToEveryone,																								// Keyword: AOUAOS_Hc_AdditionalOffersAvailableToEveryone
		AOUAOS_InnovationRoomAlternativeCertification,																								// Keyword: AOUAOS_InnovationRoomAlternativeCertification
		NUM_AOUAOS
	};

	/*! Soc1.6.2.2 Orientation/Information */
	enum AOU_OrientationInformation {						// max +5
		AOUOI_Signage,										// Keyword: AOUOI_Signage
		AOUOI_InformationDesk,								// Keyword: AOUOI_InformationDesk
		AOUOI_InnovationRoomAlternativeCertification,		// Keyword: AOUOI_InnovationRoomAlternativeCertification
		NUM_AOUOI
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_6_2(){}

	Soc1_6_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag					m_flag_AOUAOS[NUM_AOUAOS];	// XML:E
	/*! List of flags. */
	IBK::Flag					m_flag_AOUOI[NUM_AOUOI];	// XML:E
	
	IBK::Parameter				m_para[NUM_P];				// XML:E

	Utilities::UsageType		m_usageType;

};

} // namespace DGNB

#endif // DGNB_Soc1_6_2
