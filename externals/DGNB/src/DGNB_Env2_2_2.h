#ifndef DGNB_Env2_2_2H
#define DGNB_Env2_2_2H
#include "DGNB_Utilities.h"

namespace DGNB {
	
/*! Env2_2_2 drinking water demand and waste water management */
class Env2_2_2 {													// +80
	public:

	/*! Basic parameters. */
	enum para_t {
		/*! Env2_2WaterUsageIndex */
		P_CurrentValue_env2_2WaterUsageIndex,						// Keyword: CurrentValue_env2_2WaterUsageIndex				[-]		// ToDo Einheit m3/a
		/*! Env2_2DWDWWVWUI_DynamicThreshold */
		P_RefValue_env2_2DWDWWVWUI_DynamicThreshold,				// Keyword: RefValue_env2_2DWDWWVWUI_DynamicThreshold		[-]		// ToDo Einheit m3/a
		NUM_P
	};
	
	/*! Water Usage Index */
	// W(KM) // so, this a sum of ~20 different things, user will have to look it up anyway, calculating that by hand and just inputting final value is likely faster in the end
	enum DWDWWV_WaterUsageIndex {									// +80
		DWDWWVWUI_ResultsSubmitted,									// Keyword: DWDWWVWUI_ResultsSubmitted
		NUM_DWDWWVWUI
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env2_2_2(){}

	Env2_2_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag				m_flag_DWDWWVWUI[NUM_DWDWWVWUI];					// XML:E
	
	IBK::Parameter			m_para[NUM_P];										// XML:E

	Utilities::UsageType	m_usageType;

};

} // namespace DGNB

#endif // Env2_2_2H
