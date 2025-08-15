#ifndef DGNB_Tec1_4_2H
#define DGNB_Tec1_4_2H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Tec1_4_2
{
public:

	/*! Tec1.4.2.1 Adaptability of Allocation of Operation Temperatures for Implementation of Regenerative Energy: Warmth */
	enum  AAOTIRE_Warmth {												// max +10
		AAOTIREW_AverageTemperatureOf50DegreesOrMore,					// Keyword: AAOTIREW_AverageTemperatureOf50DegreesOrMore
		AAOTIREW_AverageTemperatureBetween35and50Degrees,				// Keyword: AAOTIREW_AverageTemperatureBetween35and50Degrees
		AAOTIREW_AverageTemperatureOf35DegreesOrLess,					// Keyword: AAOTIREW_AverageTemperatureOf35DegreesOrLess
		AAOTIREW_NoHeatingSystemInBuilding,								// Keyword: AAOTIREW_NoHeatingSystemInBuilding
		AAOTIREW_100PercentOfWarmthDemandCoveredByRegenerativeEnergy,	// Keyword: AAOTIREW_100PercentOfWarmthDemandCoveredByRegenerativeEnergy
		NUM_AAOTIREW
	};

	/*! Tec1.4.2.2 Adaptability of Allocation of Operation Temperatures for Implementation of Regenerative Energy: Cooling */
	enum  AAOTIRE_Cooling {												// max +10
		AAOTIREC_AverageTemperatureOf14DegreesOrLess,					// Keyword: AAOTIREC_AverageTemperatureOf14DegreesOrLess
		AAOTIREC_AverageTemperatureBetween14and19Degrees,				// Keyword: AAOTIREC_AverageTemperatureBetween14and19Degrees
		AAOTIREC_AverageTemperatureOf19DegreesOrMore,					// Keyword: AAOTIREC_AverageTemperatureOf19DegreesOrMore
		AAOTIREC_NoCoolingSystemInBuilding,								// Keyword: AAOTIREC_NoCoolingSystemInBuilding
		AAOTIREC_100PercentOfCoolingDemandCoveredByRegenerativeEnergy,	// Keyword: AAOTIREC_100PercentOfCoolingDemandCoveredByRegenerativeEnergy
		NUM_AAOTIREC
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Tec1_4_2(){}

	Tec1_4_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_AAOTIREW[NUM_AAOTIREW];	// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_AAOTIREC[NUM_AAOTIREC];	// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Tec1_4_2H
