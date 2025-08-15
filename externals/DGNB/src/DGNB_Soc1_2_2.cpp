#include "DGNB_Soc1_2_2.h"

namespace DGNB {
	
double DGNB::Soc1_2_2::score() {
	double soc1_2_2 = 0;
	double currentSoc1_2_2_1_aPercentageOfMechanicalAeration = m_para[(P_CurrentValue_soc1_2_2_1_a_PercentageOfMechanicalAeration)].get_value();
	double currentSoc1_2_2_1_aZonalSreamingSimulationResult = m_para[(P_CurrentValue_soc1_2_2_1_a_ZonalStreamingSimulationResult)].get_value();

	if (m_flag_IHACFOEHAH[(IHACFOEHAH_RatioSubmitted)].isEnabled()) {
		switch (m_usageType) {
			case Utilities::UT_Office:
			case Utilities::UT_Education:
			case Utilities::UT_Hotel:
			case Utilities::UT_Assembly:
			case Utilities::UT_Healthcare: {
				if (m_flag_IHACFOEHAH[(IHACFOEHAH_ZonalStreamingSimulation)].isEnabled() == false) {
					if (m_flag_IHACFOEHAH[(IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat1)].isEnabled())
						soc1_2_2 += currentSoc1_2_2_1_aPercentageOfMechanicalAeration * 50;
					else if (m_flag_IHACFOEHAH[(IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat2)].isEnabled())
						soc1_2_2 += currentSoc1_2_2_1_aPercentageOfMechanicalAeration * 40;
					else if (m_flag_IHACFOEHAH[(IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat3)].isEnabled())
						soc1_2_2 += currentSoc1_2_2_1_aPercentageOfMechanicalAeration * 0;

					if (m_flag_IHACFOEHAH[(IHACFOEHAH_ManualObservationOfASR3_6AndSensorMonitoring)].isEnabled())
						soc1_2_2 += (100 - currentSoc1_2_2_1_aPercentageOfMechanicalAeration) * 50;
					else if (m_flag_IHACFOEHAH[(IHACFOEHAH_ManualObservationOfASR3_6)].isEnabled())
						soc1_2_2 += (100 - currentSoc1_2_2_1_aPercentageOfMechanicalAeration) * 25;
					else if (m_flag_IHACFOEHAH[(IHACFOEHAH_ManualNoCertification)].isEnabled())
						soc1_2_2 += (100 - currentSoc1_2_2_1_aPercentageOfMechanicalAeration) * 0;
				} else {
					if (m_flag_IHACFOEHAH[(IHACFOEHAH_ZonalDIN_EN_16798_1_Kat1and2)].isEnabled() && currentSoc1_2_2_1_aZonalSreamingSimulationResult <= 550)
						soc1_2_2 += 50;
					else if (m_flag_IHACFOEHAH[(IHACFOEHAH_ZonalDIN_EN_16798_1_Kat3)].isEnabled() || currentSoc1_2_2_1_aZonalSreamingSimulationResult <= 800)
						soc1_2_2 += 25;
					else if (m_flag_IHACFOEHAH[(IHACFOEHAH_ZonalDIN_EN_16798_1_Kat4)].isEnabled() || currentSoc1_2_2_1_aZonalSreamingSimulationResult > 800)
						soc1_2_2 += 0;
				}
			} break;

			case Utilities::UT_Residential: {
				if (m_flag_IHACFR[(IHACFR_AerationMeasuresAccordingToLevelsNL)].isEnabled())
					soc1_2_2 += 50;
				else if (m_flag_IHACFR[(IHACFR_AerationMeasuresAccordingToLevelsRL)].isEnabled())
					 soc1_2_2 += 35;
				else if (m_flag_IHACFR[(IHACFR_AerationMeasuresAccordingToLevelsFL)].isEnabled())
					soc1_2_2 += 15;
			} break;

			case Utilities::UT_Logistics:
			case Utilities::UT_Production: {
				if (m_flag_IHACFLP[(IHACFLP_AerationExceedsMinimumRateByAtLeast20Percent)].isEnabled())
					soc1_2_2 += 50;
				else if (m_flag_IHACFLP[(IHACFLP_NeedbasedAeration)].isEnabled())
					soc1_2_2 += 40;
				else if (m_flag_IHACFLP[(IHACFLP_ObservationOfASR3_6)].isEnabled())
					soc1_2_2 += 25;
				else if (m_flag_IHACFLP[(IHACFLP_NoCertification)].isEnabled())
					soc1_2_2 += 0;
			} break;

			case Utilities::UT_ShoppingCenter: {
				// shops
				if (m_flag_IHACFSCCBCS[(IHACFSCCBCS_DIN_EN_16798_1_Kat1and2_CBCSandSCShops)].isEnabled())
					soc1_2_2 += 50;
				else if (m_flag_IHACFSCCBCS[(IHACFSCCBCS_DIN_EN_16798_1_Kat3_CBCSandSCShops)].isEnabled())
					soc1_2_2 += 25;
				else if (m_flag_IHACFSCCBCS[(IHACFSCCBCS_DIN_EN_16798_1_Kat4_CBCSandSCShops)].isEnabled())
					soc1_2_2 += 0;
				// mall
				if (m_flag_IHACFSCCBCS[(IHACFSCCBCS_DIN_EN_16798_1_Kat1and2_SCMalls)].isEnabled())
					soc1_2_2 += 20;
				else if (m_flag_IHACFSCCBCS[(IHACFSCCBCS_DIN_EN_16798_1_Kat3_SCMalls)].isEnabled())
					soc1_2_2 += 10;
				else if (m_flag_IHACFSCCBCS[(IHACFSCCBCS_DIN_EN_16798_1_Kat4_SCMalls)].isEnabled())
					soc1_2_2 += 0;
			} break;

			case Utilities::UT_ConvenienceStore: {
				if (m_flag_IHACFSCCBCS[(IHACFSCCBCS_DIN_EN_16798_1_Kat1and2_CBCSandSCShops)].isEnabled())
					soc1_2_2 += 70;
				else if (m_flag_IHACFSCCBCS[(IHACFSCCBCS_DIN_EN_16798_1_Kat3_CBCSandSCShops)].isEnabled())
					soc1_2_2 += 30;
				else if (m_flag_IHACFSCCBCS[(IHACFSCCBCS_DIN_EN_16798_1_Kat4_CBCSandSCShops)].isEnabled())
					soc1_2_2 += 0;
			} break;

			case Utilities::UT_CommercialBuilding: {
				if (m_flag_IHACFSCCBCS[(IHACFSCCBCS_DIN_EN_16798_1_Kat1and2_CBCSandSCShops)].isEnabled())
					soc1_2_2 += 70;
				else if (m_flag_IHACFSCCBCS[(IHACFSCCBCS_DIN_EN_16798_1_Kat3_CBCSandSCShops)].isEnabled())
					soc1_2_2 += 35;
				else if (m_flag_IHACFSCCBCS[(IHACFSCCBCS_DIN_EN_16798_1_Kat4_CBCSandSCShops)].isEnabled())
					soc1_2_2 += 0;
			} break;

			default:
				soc1_2_2 += 0;
				break;
		}
	}

	return soc1_2_2;
} // Soc1.2.1
} // namespace DGNB
