#include "DGNB_Tec1_4_5.h"

namespace DGNB {
	
double DGNB::Tec1_4_5::score() {
	double tec1_4_5 = 0;

	if (m_flag_UREES[(UREES_PortionOfEnergyFromRenewableSourcesAtLeast95Percent)].isEnabled())
		tec1_4_5 += 10;
	else if (m_flag_UREES[(UREES_PortionOfEnergyFromRenewableSourcesAtLeast85Percent)].isEnabled())
		tec1_4_5 += 5;
	
	switch (m_usageType) {
		case Utilities::UT_Residential:
			if (m_flag_UREP[(UREP_Residential_MinimumPowerOf0_08kWPeakPerSQMOfPlot)].isEnabled() || (m_flag_UREP[(UREP_AtLeast80PercentOfSuitableRoofAreaUsedForSolarEnergyProduction)].isEnabled() && m_flag_UREP[(UREP_AtLeast80PercentOfSuitableParkingAreaUsedForSolarEnergyProduction)].isEnabled()))
				tec1_4_5 += 10;
			else if (m_flag_UREP[(UREP_Residential_MinimumPowerOf0_06kWPeakPerSQMOfPlot)].isEnabled() || (m_flag_UREP[(UREP_AtLeast60PercentOfSuitableRoofAreaUsedForSolarEnergyProduction)].isEnabled() && m_flag_UREP[(UREP_AtLeast60PercentOfSuitableParkingAreaUsedForSolarEnergyProduction)].isEnabled()))
				tec1_4_5 += 5;
			break;
		default:
			if (m_flag_UREP[(UREP_AtLeast80PercentOfSuitableRoofAreaUsedForSolarEnergyProduction)].isEnabled() && m_flag_UREP[(UREP_AtLeast80PercentOfSuitableParkingAreaUsedForSolarEnergyProduction)].isEnabled())
				tec1_4_5 += 10;
			else if (m_flag_UREP[(UREP_AtLeast60PercentOfSuitableRoofAreaUsedForSolarEnergyProduction)].isEnabled() && m_flag_UREP[(UREP_AtLeast60PercentOfSuitableParkingAreaUsedForSolarEnergyProduction)].isEnabled())
				tec1_4_5 += 5;
		break;
	}

	return tec1_4_5;
}

bool DGNB::Tec1_4_5::platinumRequirementsMet() {
	bool platReqMet = false;

	platReqMet = (m_flag_UREP[(UREP_AtLeast60PercentOfSuitableRoofAreaUsedForSolarEnergyProduction)].isEnabled() || m_flag_UREP[(UREP_AtLeast80PercentOfSuitableRoofAreaUsedForSolarEnergyProduction)].isEnabled() ? true : false);

	return platReqMet;
} // Tec1.4.5

} // namespace DGNB
