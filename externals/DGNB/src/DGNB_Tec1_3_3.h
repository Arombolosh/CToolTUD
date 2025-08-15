#ifndef DGNB_Tec1_3_3H
#define DGNB_Tec1_3_3H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Tec1_3_3
{
public:

	/*! Basic parameters. */
	enum para_t {
		/*! AirExchangeRateThroughBuildingEnvelope */
		P_Tec1_3_3AirExchangeRateThroughBuildingEnvelope,		// Keyword: Tec1_3_3AirExchangeRateThroughBuildingEnvelope			[1/h]
		/*! PercentageOfDirectLOSOfShopAreasToOutside */
		P_Tec1_3_3AirExchangeRateRelativeToEnvelopeSurface,		// Keyword: Tec1_3_3AirExchangeRateRelativeToEnvelopeSurface		[-]		// ToDo Einheit [m3/(hm2)]
		NUM_P
	};

	/*! Tec1.3.3.1 Airtightness Of Building Envelope: Measuring Air Tightness */
	enum  ABE_Measuring {										// max +10
		ABEM_BuildingAirVolumeGreaterThan1500sqm,				// Keyword: ABEM_BuildingAirVolumeGreaterThan1500sqm
		ABEM_BuildingAirVolumeLessThan1500sqm,					// Keyword: ABEM_BuildingAirVolumeLessThan1500sqm
		ABEM_ResultsSubmitted,									// Keyword: ABEM_ResultsSubmitted
		NUM_ABEM
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Tec1_3_3(){}

	Tec1_3_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_ABEM[NUM_ABEM];		// XML:E
	
	IBK::Parameter					m_para[NUM_P];				// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Tec1_3_3H
