#ifndef DGNB_Pro1_1_1H
#define DGNB_Pro1_1_1H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

/*! Pro1.1.1 Requirement Planning */
class Pro1_1_1
{
public:

	/*! Pro1.1.1.1 Basis */
	enum RP_Basis {																			// max +20
		RPB_ImplementationOfDeclarationSustainabilityArchitecture,							// Keyword: RPB_ImplementationOfDeclarationSustainabilityArchitecture
		RPB_ComplianceWithEuropeanSustainableReportFrameworkLevels,							// Keyword: RPB_ComplianceWithEuropeanSustainableReportFrameworkLevels
		NUM_RPB
	};

	/*! Pro1.1.1.2 Requirement Planning */
	enum RP_RP{																				// max +50
		RPRP_PlanFollowsChecklist1OrAnnexe1A,												// Keyword: RPRP_PlanFollowsChecklist1OrAnnexe1A
		RPRP_PlanFollowsChecklist12OrAnnexe1B,												// Keyword: RPRP_PlanFollowsChecklist12OrAnnexe1B
		RPRP_PlanFollowsChecklist123OrAnnexe1C,												// Keyword: RPRP_PlanFollowsChecklist123OrAnnexe1C
		NUM_RPRP
	};

	/*! Pro1.1.1.3 Agenda 2030 Bonus Feasibility Survey */
	enum RP_Agenda2030FeasibilitySurvey{													// max +5
		RPA2030FS_FeasibilitySurveyConductedAllowingForImplementationOfSustainableConcepts,	// Keyword: RPA2030FS_FeasibilitySurveyConductedAllowingForImplementationOfSustainableConcepts
		NUM_RPA2030FS
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro1_1_1(){}

	Pro1_1_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_RPB[NUM_RPB];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_RPRP[NUM_RPRP];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_RPA2030FS[NUM_RPA2030FS];	// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro1_1_1H
