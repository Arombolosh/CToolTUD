#include "DGNB_Soc1_2_1.h"

namespace DGNB {
	
double DGNB::Soc1_2_1::score() {
	double soc1_2_1 = 0;
	double currentSoc1_2_Formaldehyde = m_para[(P_CurrentValue_soc1_2_Formaldehyde)].get_value() * 1e9;
	double currentSoc1_2_TVOC = m_para[(P_CurrentValue_soc1_2_TVOC)].get_value()* 1e9;
	double currentSoc1_2_FormaldehydeRP = m_para[(P_CurrentValue_soc1_2_FormaldehydeRenterPromise)].get_value()* 1e9;
	double currentSoc1_2_TVOCRP = m_para[(P_CurrentValue_soc1_2_TVOCRenterPromise)].get_value()* 1e9;

	if (m_flag_IHTVOCM[(IHTVOCM_TVOCResultsSubmitted)].isEnabled() && m_flag_IHTVOCM[(IHTVOCM_FormaldehydeResultsSubmitted)].isEnabled()) {
		switch (m_usageType) {
			case Utilities::UT_Office:
			case Utilities::UT_Education:
			case Utilities::UT_Hotel:
			case Utilities::UT_Assembly:
			case Utilities::UT_Healthcare:
				if (m_flag_IHTVOCM[(IHTVOCM_AlternativeCertification)].isEnabled() == false) {
					if (currentSoc1_2_TVOC > 3000 || currentSoc1_2_Formaldehyde > 100)
							soc1_2_1 += 0;
					else if (currentSoc1_2_TVOC > 1000 || currentSoc1_2_Formaldehyde > 60)
						soc1_2_1 += 10;
					else if (currentSoc1_2_TVOC > 500 || currentSoc1_2_Formaldehyde > 30)
						soc1_2_1 += 25;
					else soc1_2_1 += 50;
				} else {
					if (currentSoc1_2_TVOC > 3000 || currentSoc1_2_Formaldehyde > 100)
						soc1_2_1 += 0;
					else if (currentSoc1_2_TVOC > 300 || currentSoc1_2_Formaldehyde > 30)
						soc1_2_1 += 5;
					else soc1_2_1 += 25;
				}
				break;

			case Utilities::UT_Residential:
				// for degree of Rent Extension >= 80%
				if (m_flag_IHTVOCM[(IHTVOCM_ResidentialDegreeOfRentExtensionHigherThan80Percent)].isEnabled()) {
					if (m_flag_IHTVOCM[(IHTVOCM_AlternativeCertification)].isEnabled() == false) {
						if (currentSoc1_2_TVOC > 3000 || currentSoc1_2_Formaldehyde > 100)
							soc1_2_1 += 0;
						else if (currentSoc1_2_TVOC > 1000 || currentSoc1_2_Formaldehyde > 60)
							soc1_2_1 += 10;
						else if (currentSoc1_2_TVOC > 500 || currentSoc1_2_Formaldehyde > 30)
							soc1_2_1 += 25;
						else
							soc1_2_1 += 50;
					} else {
						if (currentSoc1_2_TVOC > 3000 || currentSoc1_2_Formaldehyde > 100)
							soc1_2_1 += 0;
						else if (currentSoc1_2_TVOC > 300 || currentSoc1_2_Formaldehyde > 30)
							soc1_2_1 += 5;
						else
							soc1_2_1 += 15;
					}
				}
				else {
					if (m_flag_IHTVOCM[(IHTVOCM_AlternativeCertification)].isEnabled() == false) {
						if (currentSoc1_2_TVOC > 3000 || currentSoc1_2_Formaldehyde > 100)
							soc1_2_1 += 0;
						else if (currentSoc1_2_TVOC > 1000 || currentSoc1_2_Formaldehyde > 60)
							soc1_2_1 += 5;
						else if (currentSoc1_2_TVOC > 500 || currentSoc1_2_Formaldehyde > 30)
							soc1_2_1 += 10;
						else
							soc1_2_1 += 30;
					} else {
						if (currentSoc1_2_TVOC > 3000 || currentSoc1_2_Formaldehyde > 100)
							soc1_2_1 += 0;
						else if (currentSoc1_2_TVOC > 300 || currentSoc1_2_Formaldehyde > 30)
							soc1_2_1 += 5;
						else
							soc1_2_1 += 10;
					}
					if (currentSoc1_2_TVOCRP > 3000 || currentSoc1_2_FormaldehydeRP > 100)
						soc1_2_1 += 0;
					else if (currentSoc1_2_TVOCRP > 1000 || currentSoc1_2_FormaldehydeRP > 60)
						soc1_2_1 += 5;
					else if (currentSoc1_2_TVOCRP > 500 || currentSoc1_2_FormaldehydeRP > 30)
						soc1_2_1 += 10;
					else
						soc1_2_1 += 15;
				}
				break;

			case Utilities::UT_Logistics:
			case Utilities::UT_Production:
				if (currentSoc1_2_TVOC > 3000 || currentSoc1_2_Formaldehyde > 100)
						soc1_2_1 += 0;
				else if (currentSoc1_2_TVOC > 1000 || currentSoc1_2_Formaldehyde > 60)
					soc1_2_1 += 5;
				else if (currentSoc1_2_TVOC > 500 || currentSoc1_2_Formaldehyde > 30)
					soc1_2_1 += 7.5;
				else soc1_2_1 += 10;
				if (m_flag_IHTVOCM[(IHTVOCM_LP_DeclarationAndVerificationOfProductsForAllInteriorSurfaces)].isEnabled())
					soc1_2_1 += 40;
				else if (m_flag_IHTVOCM[(IHTVOCM_LP_DeclarationAndVerificationOfProductsForFloors)].isEnabled())
					soc1_2_1 += 25;
				break;

			case Utilities::UT_ConvenienceStore:		// TODO DGNB this might get a different calculation method in a later version. So far none has been given in the catalogue
			case Utilities::UT_ShoppingCenter:
			case Utilities::UT_CommercialBuilding:
				if (m_flag_IHTVOCSCCBCS[(IHTVOCSCCBCS_OnlyLowEmissionMaterialsUsed)].isEnabled())
					soc1_2_1 += 15;
				if (m_flag_IHTVOCSCCBCS[(IHTVOCSCCBCS_RentersHoldUpEnv1_2QS3In80PercentOfSpaces)].isEnabled())
					soc1_2_1 += 15;
				else if (m_flag_IHTVOCSCCBCS[(IHTVOCSCCBCS_RentersHoldUpEnv1_2QS3In50PercentOfSpaces)].isEnabled())
					soc1_2_1 += 10;
				break;

			default:
				soc1_2_1 += 0;
				break;
		}
	}
	// assigning +5 points for woodwork
	if (m_flag_IHTVOCWWB[(IHTVOC_WoodworkBonus)0].isEnabled())
		soc1_2_1 += ((m_flag_IHTVOCWWB[(IHTVOC_WoodworkBonus)1].isEnabled() && m_flag_IHTVOCWWB[(IHTVOC_WoodworkBonus)2].isEnabled()) ? 5 : 0);

	return soc1_2_1;
} // Soc1.2.1

double DGNB::Soc1_2_1::scoreBonus() {
	double soc1_2_1Bonus = 0;

	soc1_2_1Bonus += (m_flag_IHTVOCA2030IATMRHC[(IHTVOC_Agenda2030InteriorAirToxicMatterReductionHealthAndComfort)0].isEnabled() ? 2.5 : 0);
	soc1_2_1Bonus += (m_flag_IHTVOCA2030IATMRHC[(IHTVOC_Agenda2030InteriorAirToxicMatterReductionHealthAndComfort)1].isEnabled() ? 2.5 : 0);

	return soc1_2_1Bonus;
}

bool DGNB::Soc1_2_1::minimumRequirementsMet() {
	bool minReqMet = false;

	if (m_flag_IHTVOCM[(IHTVOCM_TVOCResultsSubmitted)].isEnabled() && m_flag_IHTVOCM[(IHTVOCM_FormaldehydeResultsSubmitted)].isEnabled())
		minReqMet = true;

	return minReqMet;
}

bool DGNB::Soc1_2_1::platinumRequirementsMet() {
	bool platReqMet = false;
	int platReqMetCounter = 0;

	double currentSoc1_2_TVOC = m_para[(P_CurrentValue_soc1_2_TVOC)].get_value() * 1e9;
	double currentSoc1_2_Formaldehyde = m_para[(P_CurrentValue_soc1_2_Formaldehyde)].get_value() * 1e9;

	if (m_flag_IHTVOCM[(IHTVOCM_TVOCResultsSubmitted)].isEnabled() && m_flag_IHTVOCM[(IHTVOCM_FormaldehydeResultsSubmitted)].isEnabled()) {
		platReqMetCounter += (currentSoc1_2_TVOC < 1000 ? 1 : 0);
		platReqMetCounter += (currentSoc1_2_Formaldehyde < 60 ? 1 : 0);
	}
	platReqMet = (platReqMetCounter == 2 ? true : false);

	return platReqMet;
}
} // namespace DGNB
