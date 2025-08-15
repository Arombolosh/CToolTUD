#ifndef DGNB_Env2_2_3H
#define DGNB_Env2_2_3H
#include "DGNB_Utilities.h"

namespace DGNB {
	
/*! Env2.2.3 Outside areas */
class Env2_2_3 {
	public:
	
	/*! Irrigation and Retention */
	enum DWDWWV_IrrigatioAndRetention {								// max +6 (+2, +4)
		DWDWWVIR_NoPlannedIrrigationWithDrinkingWater,				// Keyword: DWDWWVIR_NoPlannedIrrigationWithDrinkingWater
		DWDWWVIR_OutsideAreasIncludeRainwaterIrrigationSetup,		// Keyword: DWDWWVIR_OutsideAreasIncludeRainwaterIrrigationSetup
		NUM_DWDWWVIR
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env2_2_3(){}

	Env2_2_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag				m_flag_DWDWWVIR[NUM_DWDWWVIR];						// XML:E

	Utilities::UsageType	m_usageType;

};

} // namespace DGNB

#endif // Env2_2_3H
