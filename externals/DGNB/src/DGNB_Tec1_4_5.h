#ifndef DGNB_Tec1_4_5H
#define DGNB_Tec1_4_5H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Tec1_4_5
{
public:

	/*! Tec1.4.5.1 Use of Renewable Energy Sources and Energy Production: Energy Sources */
	enum  URE_EnergySources {													// max +10
		UREES_PortionOfEnergyFromRenewableSourcesAtLeast85Percent,				// Keyword: UREES_PortionOfEnergyFromRenewableSourcesAtLeast85Percent
		UREES_PortionOfEnergyFromRenewableSourcesAtLeast95Percent,				// Keyword: UREES_PortionOfEnergyFromRenewableSourcesAtLeast95Percent
		NUM_UREES
	};

	/*! Tec1.4.5.1 Use of Renewable Energy Sources and Energy Production: Production On Site */
	enum  URE_Production {														// max +10
		UREP_AtLeast60PercentOfSuitableRoofAreaUsedForSolarEnergyProduction,	// Keyword: UREP_AtLeast60PercentOfSuitableRoofAreaUsedForSolarEnergyProduction
		UREP_AtLeast60PercentOfSuitableParkingAreaUsedForSolarEnergyProduction,	// Keyword: UREP_AtLeast60PercentOfSuitableParkingAreaUsedForSolarEnergyProduction
		UREP_Residential_MinimumPowerOf0_06kWPeakPerSQMOfPlot,					// Keyword: UREP_Residential_MinimumPowerOf0_06kWPeakPerSQMOfPlot
		UREP_AtLeast80PercentOfSuitableRoofAreaUsedForSolarEnergyProduction,	// Keyword: UREP_AtLeast80PercentOfSuitableRoofAreaUsedForSolarEnergyProduction
		UREP_AtLeast80PercentOfSuitableParkingAreaUsedForSolarEnergyProduction,	// Keyword: UREP_AtLeast80PercentOfSuitableParkingAreaUsedForSolarEnergyProduction
		UREP_Residential_MinimumPowerOf0_08kWPeakPerSQMOfPlot,					// Keyword: UREP_Residential_MinimumPowerOf0_08kWPeakPerSQMOfPlot
		NUM_UREP
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Tec1_4_5(){}

	Tec1_4_5(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	bool platinumRequirementsMet();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_UREES[NUM_UREES];		// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_UREP[NUM_UREP];			// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Tec1_4_5H
