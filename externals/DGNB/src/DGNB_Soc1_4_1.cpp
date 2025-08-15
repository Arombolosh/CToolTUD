#include "DGNB_Soc1_4_1.h"

namespace DGNB {

double DGNB::Soc1_4_1::score() {
	double soc1_4_1 = 0;
	double currentSoc1_4_1ET = m_para[(P_CurrentValue_soc1_4_1ET)].get_value();
	double currentSoc1_4_1D = m_para[(P_CurrentValue_soc1_4_1D)].get_value();
	double currentSoc1_4_1LitAreaPercentageOfUsableArea = m_para[(P_CurrentValue_soc1_4_1LitAreaPercentageOfUsableArea)].get_value();

	switch (m_usageType) {
		case Utilities::UT_Office:
		case Utilities::UT_Education:
		case Utilities::UT_Assembly:
			if (m_flag_DSOEARHHcP[(DS_OfficeEducationAssemblyResidentialHotelHealthcareProduction)0].isEnabled()) {
				if (currentSoc1_4_1ET >= 300 || currentSoc1_4_1D >= 2)
					soc1_4_1 += 20;
				else if (currentSoc1_4_1ET >= 200 || currentSoc1_4_1D >= 1.5)
					soc1_4_1 += 14;
				else if (currentSoc1_4_1ET >= 150 || currentSoc1_4_1D >= 1)
					soc1_4_1 += 10;
			}
			break;
			
		case Utilities::UT_Hotel:
			if (m_flag_DSOEARHHcP[(DS_OfficeEducationAssemblyResidentialHotelHealthcareProduction)0].isEnabled() && m_flag_DSOEARHHcP[(DS_OfficeEducationAssemblyResidentialHotelHealthcareProduction)0].isEnabled() == false) {
				if (currentSoc1_4_1ET >= 300 || currentSoc1_4_1D >= 2)
					soc1_4_1 += 40;
				else if (currentSoc1_4_1ET >= 200 || currentSoc1_4_1D >= 1.5)
					soc1_4_1 += 30;
				else if (currentSoc1_4_1ET >= 150 || currentSoc1_4_1D >= 1)
					soc1_4_1 += 20;
			} else if (m_flag_DSOEARHHcP[(DS_OfficeEducationAssemblyResidentialHotelHealthcareProduction)0].isEnabled() && m_flag_DSOEARHHcP[(DS_OfficeEducationAssemblyResidentialHotelHealthcareProduction)0].isEnabled() == false)
				if (currentSoc1_4_1D >= 2)
					soc1_4_1 += 20;
			break;
			
		case Utilities::UT_Healthcare:
			if (m_flag_DSOEARHHcP[(DS_OfficeEducationAssemblyResidentialHotelHealthcareProduction)0].isEnabled()) {
				if (currentSoc1_4_1ET >= 300 || currentSoc1_4_1D >= 2)
					soc1_4_1 += 20;
				else if (currentSoc1_4_1ET >= 200 || currentSoc1_4_1D >= 1.5)
					soc1_4_1 += 15;
				else if (currentSoc1_4_1ET >= 150 || currentSoc1_4_1D >= 1)
					soc1_4_1 += 8;
			}
			break;
			
		case Utilities::UT_Residential:
			if (m_flag_DSOEARHHcP[(DS_OfficeEducationAssemblyResidentialHotelHealthcareProduction)0].isEnabled()) {
				if (currentSoc1_4_1ET >= 300 || currentSoc1_4_1D >= 2)
					soc1_4_1 += 40;
				else if (currentSoc1_4_1ET >= 200 || currentSoc1_4_1D >= 1.5)
					soc1_4_1 += 30;
				else if (currentSoc1_4_1ET >= 150 || currentSoc1_4_1D >= 1)
					soc1_4_1 += 20;
			}
			break;
			
		case Utilities::UT_Production:
			if (m_flag_DSOEARHHcP[(DS_OfficeEducationAssemblyResidentialHotelHealthcareProduction)0].isEnabled()) {
				if (currentSoc1_4_1ET >= 150 || currentSoc1_4_1D >= 1)
					soc1_4_1 += 30;
				else if (currentSoc1_4_1ET >= 100 || currentSoc1_4_1D >= 0.75)
					soc1_4_1 += 20;
				else if (currentSoc1_4_1ET >= 75 || currentSoc1_4_1D >= 0.5)
					soc1_4_1 += 15;
			}
			break;
			
		case Utilities::UT_ConvenienceStore:
			if (m_flag_DSOCSSCCB[(DS_ConvenienceStoreShoppingCenterCommercialBuilding)0].isEnabled()) {
				if (currentSoc1_4_1LitAreaPercentageOfUsableArea >= 50)
					soc1_4_1 += 35;
				else if (currentSoc1_4_1LitAreaPercentageOfUsableArea >= 25)
					soc1_4_1 += 25;
				else if (currentSoc1_4_1LitAreaPercentageOfUsableArea >= 15)
					soc1_4_1 += 15;
			}
			soc1_4_1 += (m_flag_DSOCSSCCB[(DS_ConvenienceStoreShoppingCenterCommercialBuilding)0].isEnabled() ? 15 : 0);
			break;
			
		case Utilities::UT_ShoppingCenter:
			if (m_flag_DSOCSSCCB[(DS_ConvenienceStoreShoppingCenterCommercialBuilding)0].isEnabled()) {
				if (currentSoc1_4_1LitAreaPercentageOfUsableArea >= 50)
					soc1_4_1 += 40;
				else if (currentSoc1_4_1LitAreaPercentageOfUsableArea >= 25)
					soc1_4_1 += 25;
				else if (currentSoc1_4_1LitAreaPercentageOfUsableArea >= 15)
					soc1_4_1 += 10;
			}
			break;
			
		case Utilities::UT_CommercialBuilding:
			if (m_flag_DSOCSSCCB[(DS_ConvenienceStoreShoppingCenterCommercialBuilding)0].isEnabled()) {
				if (currentSoc1_4_1LitAreaPercentageOfUsableArea >= 15)
					soc1_4_1 += 40;
				else if (currentSoc1_4_1LitAreaPercentageOfUsableArea >= 10)
					soc1_4_1 += 25;
				else if (currentSoc1_4_1LitAreaPercentageOfUsableArea >= 5)
					soc1_4_1 += 10;
			}
			break;
			
		default:
			soc1_4_1 += 0;
			break;
	}

	return soc1_4_1;
} // Soc1.4.1

} // namespace DGNB
