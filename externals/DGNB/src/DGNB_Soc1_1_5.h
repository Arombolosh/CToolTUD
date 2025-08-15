#ifndef DGNB_Soc1_1_5H
#define DGNB_Soc1_1_5H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.1.5 Agenda 2030 Bonus climate adaptation */
class Soc1_1_5
{
public:

	/*! Soc 1.1.5.1 resilient thermal comfort */
	enum A2030CA_ResilientThermalComfort {												// pts depending on usage type
		A2030CARTC_ExceedanceFrequencyEvaluatedBasedOnPrognosticationsDWDTRYFuture,		// Keyword: A2030CARTC_ExceedanceFrequencyEvaluatedBasedOnPrognosticationsDWDTRYFuture
		A2030CARTC_ResultsHaveBeenIncludedInPlanningProcess,							// Keyword: A2030CARTC_ResultsHaveBeenIncludedInPlanningProcess
		NUM_A2030CARTC
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_1_5(){}

	Soc1_1_5(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double scoreBonus();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag					m_flag_A2030CARTC[NUM_A2030CARTC];		// XML:E

	Utilities::UsageType		m_usageType;

};

} // namespace DGNB

#endif // DGNB_Soc1_1_5H
