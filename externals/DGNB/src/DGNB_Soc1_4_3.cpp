#include "DGNB_Soc1_4_3.h"

namespace DGNB {
	
double DGNB::Soc1_4_3::score() {
	double soc1_4_3 = 0;
	switch (m_usageType) {
		case Utilities::UT_ConvenienceStore:
			soc1_4_3 += (m_flag_LOSOCSCBSC[(LOSO_ConvenienceStoreCommercialBuildingShoppingCenter)0].isEnabled() ? 9 : 0);
			soc1_4_3 += (m_flag_LOSOCSCBSC[(LOSO_ConvenienceStoreCommercialBuildingShoppingCenter)4].isEnabled() ? 9 : 0);
			break;

		case Utilities::UT_CommercialBuilding:
		case Utilities::UT_ShoppingCenter:
			soc1_4_3 += (m_flag_LOSOCSCBSC[(LOSO_ConvenienceStoreCommercialBuildingShoppingCenter)0].isEnabled() ? 10 : 0);
			soc1_4_3 += m_para[(P_CurrentValue_soc1_4_3_1aPercentageOfOpenFacade)].get_value() *2;
			soc1_4_3 += (m_flag_LOSOCSCBSC[(LOSO_ConvenienceStoreCommercialBuildingShoppingCenter)2].isEnabled() ? 10 : 0);
			soc1_4_3 += m_para[(P_CurrentValue_soc1_4_3_1aPercentageOfDirectLOSOfShopAreasToOutside)].get_value() /5;
			break;

		case Utilities::UT_Residential:
			if (m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)2].isEnabled())
				soc1_4_3 += 30;
			else if (m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)1].isEnabled() || m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)3].isEnabled())
				soc1_4_3 += 18;
			else if (m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)0].isEnabled())
				soc1_4_3 += 10;
			break;

		case Utilities::UT_Office:
		case Utilities::UT_Education:
		case Utilities::UT_Logistics:
			if (m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)2].isEnabled())
				soc1_4_3 += 20;
			else if (m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)1].isEnabled())
				soc1_4_3 += 15;
			else if (m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)0].isEnabled())
				soc1_4_3 += 8;
			break;

		case Utilities::UT_Hotel:
			if (m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)2].isEnabled())
				soc1_4_3 += 20;
			else if (m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)1].isEnabled() || m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)3].isEnabled())
				soc1_4_3 += 15;
			else if (m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)0].isEnabled())
				soc1_4_3 += 8;
			break;

		case Utilities::UT_Assembly:
			// assembly type 1
			if (m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)4].isEnabled()) {
				if (m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)2].isEnabled())
					soc1_4_3 += 20;
				else if (m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)1].isEnabled())
					soc1_4_3 += 15;
				else if (m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)0].isEnabled())
					soc1_4_3 += 8;
			}
			// assembly type 2
			else if (m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)5].isEnabled()) {
				if (m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)8].isEnabled())
					soc1_4_3 += 20;
				else if (m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)7].isEnabled())
					soc1_4_3 += 15;
				else if (m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)6].isEnabled())
					soc1_4_3 += 8;
			}
			break;
			
		case Utilities::UT_Healthcare:
			if (m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)2].isEnabled())
				soc1_4_3 += 15;
			else if (m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)1].isEnabled() || m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)3].isEnabled())
				soc1_4_3 += 10;
			else if (m_flag_LOSOOEHLARHc[(LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare)0].isEnabled())
				soc1_4_3 += 6;
			break;
			
		default:
			soc1_4_3 += 0;
			break;
	}

	return soc1_4_3;
} // Soc1.4.3

} // namespace DGNB
