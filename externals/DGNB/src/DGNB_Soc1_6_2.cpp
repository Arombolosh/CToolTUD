#include "DGNB_Soc1_6_2.h"

namespace DGNB {
	
double DGNB::Soc1_6_2::score() {
	double soc1_6_2 = 0;

	// assigning points for Soc1.6.2.1 depending on usage Type
	switch (m_usageType) {
		case Utilities::UT_ShoppingCenter:
		case Utilities::UT_CommercialBuilding:
		case Utilities::UT_ConvenienceStore:
			if ((m_flag_AOUAOS[(AOUAOS_AdditionalOffersMultifunctionRoomsCommonRooms)].isEnabled() && m_flag_AOUAOS[(AOUAOS_CSCBSC_LockersChangingRooms)].isEnabled()) || (m_flag_AOUAOS[(AOUAOS_InnovationRoomAlternativeCertification)].isEnabled() && m_para[(P_Soc1_6_2_1AlternativeInnovativeSolutions)].get_value() > 0))
				soc1_6_2 += 10;
			break;

		case Utilities::UT_Residential:
			if ((m_flag_AOUAOS[(AOUAOS_AdditionalOffersMultifunctionRoomsCommonRooms)].isEnabled() && m_flag_AOUAOS[(AOUAOS_Residential_CommonRoomsAvailableToEveryone)].isEnabled() && m_flag_AOUAOS[(AOUAOS_Residential_LaundryAndDryingRoomsFunctionAsCommonRooms_PartialWaivingOfLaundryMachineConnectionsInResidentialUnits)].isEnabled()) || (m_flag_AOUAOS[(AOUAOS_InnovationRoomAlternativeCertification)].isEnabled() && m_para[(P_Soc1_6_2_1AlternativeInnovativeSolutions)].get_value() > 0))
				soc1_6_2 += 10;
			break;

		case Utilities::UT_Healthcare:
			if ((m_flag_AOUAOS[(AOUAOS_AdditionalOffersMultifunctionRoomsCommonRooms)].isEnabled() && m_flag_AOUAOS[(AOUAOS_Hc_AdditionalOffersAvailableToEveryone)].isEnabled()) || (m_flag_AOUAOS[(AOUAOS_InnovationRoomAlternativeCertification)].isEnabled() && m_para[(P_Soc1_6_2_1AlternativeInnovativeSolutions)].get_value() > 0))
				soc1_6_2 += 10;
			break;

		default:
			if (m_flag_AOUAOS[(AOUAOS_AdditionalOffersMultifunctionRoomsCommonRooms)].isEnabled() || (m_flag_AOUAOS[(AOUAOS_InnovationRoomAlternativeCertification)].isEnabled() && m_para[(P_Soc1_6_2_1AlternativeInnovativeSolutions)].get_value() > 0))
				soc1_6_2 += 0;
			break;
	}

	// assigning points for Soc1.6.2.2
	soc1_6_2 += (((m_flag_AOUOI[(AOUOI_Signage)].isEnabled() && m_flag_AOUOI[(AOUOI_InformationDesk)].isEnabled()) || (m_flag_AOUOI[(AOUOI_InnovationRoomAlternativeCertification)].isEnabled() && m_para[(P_Soc1_6_2_2AlternativeInnovativeSolutions)].get_value() > 0)) ? 5 : 0);

	return soc1_6_2;
} // Soc1.6.2

} // namespace DGNB
