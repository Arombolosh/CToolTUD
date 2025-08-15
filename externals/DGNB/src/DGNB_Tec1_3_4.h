#ifndef DGNB_Tec1_3_4H
#define DGNB_Tec1_3_4H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Tec1_3_4
{
public:

	/*! Basic parameters. */
	enum para_t {
		/*! UntercuttingOfLegalRequirements */
		P_Tec1_3_4UntercuttingOfLegalRequirements,													// Keyword: Tec1_3_4UntercuttingOfLegalRequirements		[---] // ToDo Einheit % SO oder anders?
		NUM_P
	};

	/*! Tec1.3.4 Heat Insulation during Summer: Verification and Variations */
	enum  HIS_VerificationAndVariations {															// max +10
		HISVV_ExaminationOfDifferentVariations,														// Keyword: HISVV_ExaminationOfDifferentVariations
		HISVV_ExaminationOfNonCommonRooms,															// Keyword: HISVV_ExaminationOfNonCommonRooms
		HISVV_ExaminationOfBuildingWithLocalClimateDataAndImplementationOfResultsDuringPlanning,	// Keyword: HISVV_ExaminationOfBuildingWithLocalClimateDataAndImplementationOfResultsDuringPlanning
		HISVV_UndercuttingLegalMinimumRequirementsByAtLeast20PercentResultsSubmitted,				// Keyword: HISVV_UndercuttingLegalMinimumRequirementsByAtLeast20PercentResultsSubmitted
		NUM_HISVV
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Tec1_3_4(){}

	Tec1_3_4(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_HISVV[NUM_HISVV];										// XML:E
	
	IBK::Parameter					m_para[NUM_P];													// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Tec1_3_4H
