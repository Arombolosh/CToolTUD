#ifndef DGNB_Pro1_1_2H
#define DGNB_Pro1_1_2H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

/*! Pro1.1.2 Agenda 2030 Participation */
class Pro1_1_2
{
public:

	/*! Pro1.1.2 Agenda 2030 Participation */
	enum A2030_Participation {											// max +20
		A2030P_CounselDuringRequirementAnalysis,						// Keyword: A2030P_CounselDuringRequirementAnalysis
		A2030P_ParticipationDuringRequirementAnalysis,					// Keyword: A2030P_ParticipationDuringRequirementAnalysis
		A2030P_CounselDuringConceptionPhase,							// Keyword: A2030P_CounselDuringConceptionPhase
		A2030P_ParticipationDuringConceptionPhase,						// Keyword: A2030P_ParticipationDuringConceptionPhase
		A2030P_CounselDuringImplementationPhase,						// Keyword: A2030P_CounselDuringImplementationPhase
		A2030P_ParticipationDuringImplementationPhase,					// Keyword: A2030P_ParticipationDuringImplementationPhase
		NUM_A2030P
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro1_1_2(){}

	Pro1_1_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double scoreBonus();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_A2030P[NUM_A2030P];			// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro1_1_2H
