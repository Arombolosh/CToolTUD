#include "DGNB_Eco1_1_3.h"

namespace DGNB {
	
double DGNB::Eco1_1_3::score() {
	double eco1_1_3 = 0;

	double netLCC = m_para[(P_CurrentValue_eco1_1_3BRLCCC_NetLifeCycleCosts)].get_value();

	// TODO DGNB:
	// convenience stores without refrigerated display cases can or can not reach 80 pts?
	// residential buildings can reach 80 pts and the 50 pts cap is probably a typo?
	if (m_flag_BRLCCC[(BRLCCC_NetLifeCycleCostsResultsSubmitted)].isEnabled()) {
		switch (m_usageType) {
			case Utilities::UT_ConvenienceStore: // convenience stores
				if (m_flag_BRLCCC[(BRLCCC_DisplayCaseFlag)].isEnabled()) {
					if (m_para[(P_CurrentValue_eco1_1_3BRLCCC_CSAnnualEnergyConsumptionPerMeterRefrigeratedDC)].get_value() < 1200)
						eco1_1_3 += 10;
					else if (m_para[(P_CurrentValue_eco1_1_3BRLCCC_CSAnnualEnergyConsumptionPerMeterRefrigeratedDC)].get_value() < 3000)
						eco1_1_3 += 1;
					if (netLCC <= m_para[(P_ReferenceValue_eco1_1_3netLCCPerBuildingTypeLowerValue)].get_value())
						eco1_1_3 += 70;	 // probably mistake in catalogue as there are only 70 points available for this category
					else if (netLCC <= m_para[(P_ReferenceValue_eco1_1_3netLCCPerBuildingTypeIntermediateValue)].get_value())
						eco1_1_3 += 40;	 // possible follow-up mistake but no change will be made here
					else if (netLCC <= m_para[(P_ReferenceValue_eco1_1_3netLCCPerBuildingTypeUpperValue)].get_value())
						eco1_1_3 += 10;
				}
				else {
					if (netLCC <= m_para[(P_ReferenceValue_eco1_1_3netLCCPerBuildingTypeLowerValue)].get_value())
						eco1_1_3 += 80;	 // will be assigning 80 max points here despite catalogue saying 10-70, as the max 80 pts could not possibly be reached by a convenience store without refrigerated display cases otherwise
					else if (netLCC <= m_para[(P_ReferenceValue_eco1_1_3netLCCPerBuildingTypeIntermediateValue)].get_value())
						eco1_1_3 += 40;
					else if (netLCC <= m_para[(P_ReferenceValue_eco1_1_3netLCCPerBuildingTypeUpperValue)].get_value())
						eco1_1_3 += 10;
				}
			break;

			case Utilities::UT_Healthcare:
				if (m_flag_BRLCCC[(BRLCCC_HealthCareTypeIIFlag)].isEnabled() == false) { // health care type I buildings only
					if (netLCC <= m_para[(P_ReferenceValue_eco1_1_3netLCCPerBuildingTypeLowerValue)].get_value())
						eco1_1_3 += 80;
					else if (netLCC <= m_para[(P_ReferenceValue_eco1_1_3netLCCPerBuildingTypeIntermediateValue)].get_value())
						eco1_1_3 += 40;
					else if (netLCC <= m_para[(P_ReferenceValue_eco1_1_3netLCCPerBuildingTypeUpperValue)].get_value())
						eco1_1_3 += 10;
				} else {	// health care type II buildings only (hospitals and university hospitals
					if (netLCC <= m_para[(P_ReferenceValue_eco1_1_3netLCCPerBuildingTypeLowerValue)].get_value() * m_para[(P_ReferenceValue_eco1_1_3BRLCCC_HealthCareTypeII)].get_value())
						eco1_1_3 += 80;
					else if (netLCC <= m_para[(P_ReferenceValue_eco1_1_3netLCCPerBuildingTypeIntermediateValue)].get_value() * m_para[(P_ReferenceValue_eco1_1_3BRLCCC_HealthCareTypeII)].get_value())
						eco1_1_3 += 40;
					else if (netLCC <= m_para[(P_ReferenceValue_eco1_1_3netLCCPerBuildingTypeUpperValue)].get_value() * m_para[(P_ReferenceValue_eco1_1_3BRLCCC_HealthCareTypeII)].get_value())
						eco1_1_3 += 10;
				}
			break;

			default: // offices, education, residential, hotel, shopping center, commercial building, assembly
				if (netLCC <= m_para[(P_ReferenceValue_eco1_1_3netLCCPerBuildingTypeLowerValue)].get_value()) {
					eco1_1_3 += 80;
				} else if (netLCC <= m_para[(P_ReferenceValue_eco1_1_3netLCCPerBuildingTypeIntermediateValue)].get_value()) {
					eco1_1_3 += 40;
				} else if (netLCC <= m_para[(P_ReferenceValue_eco1_1_3netLCCPerBuildingTypeUpperValue)].get_value()){
					eco1_1_3 += 10;
				}
			break;
		}
	}
	return eco1_1_3;

} // Eco1.1.3

} // namespace DGNB
