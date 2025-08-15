#ifndef DGNB_Eco2_4_4H
#define DGNB_Eco2_4_4H

#include "DGNB_Utilities.h"

namespace DGNB {
/*! Eco2.4.4 Space Efficiency */
class Eco2_4_4	// max +10
{
public:
	/*! Basic parameters. */
	enum para_t {
		/*! RatioOfUsableSpaceToGroundSpace */
		P_CurrentValue_eco2_4_4RatioOfUsableSpaceToGroundSpace,			// Keyword: CurrentValue_eco2_4_4RatioOfUsableSpaceToGroundSpace		[-]
		/*! RatioOfUsableSpaceToGroundSpace_lower */
		P_ReferenceValueeco2_4_4RatioOfUsableSpaceToGroundSpace_lower,	// Keyword: ReferenceValueeco2_4_4RatioOfUsableSpaceToGroundSpace_lower		[-]
		/*! RatioOfUsableSpaceToGroundSpace_upper */
		P_ReferenceValueeco2_4_4RatioOfUsableSpaceToGroundSpace_upper,	// Keyword: ReferenceValueeco2_4_4RatioOfUsableSpaceToGroundSpace_upper		[-]
		NUM_P
	};

	/*! Eco2.4.4.1 Space Efficiency */
	enum SE_RatioOfUsableSpaceToGroundSpace {						// max +10
		SERUSGS_ResultsSubmitted,									// Keyword: SERUSGS_ResultsSubmitted
		SERUSGS_LogisticsAndProductionCostOptimisation,				// Keyword: SERUSGS_LogisticsAndProductionCostOptimisation
		SERUSGS_LogisticsAndProductionEnvironmentalOptimisation,	// Keyword: SERUSGS_LogisticsAndProductionEnvironmentalOptimisation
		SERUSGS_LogisticsAndProductionSocialOptimisation,			// Keyword: SERUSGS_LogisticsAndProductionSocialOptimisation
		NUM_SERUSGS
	};

	/*! Eco2.4.4.2 Multiple Use of Space */
	enum SE_MultipleUseOfSpace {									// max +10
		SEMUS_ConceptIncludesMultipleUseOfRelevantPortionOfSpace,	// Keyword: SEMUS_ConceptIncludesMultipleUseOfRelevantPortionOfSpace
		SEMUS_UseIncludesMultipleUseOfRelevantPortionOfSpace,		// Keyword: SEMUS_UseIncludesMultipleUseOfRelevantPortionOfSpace
		NUM_SEMUS
	};

	/*! Eco2.4.4.3 Agenda 2030 Bonus Sufficiency */
	enum SE_Agenda2030BonusSufficiency {
		SEA2030S_SubmissionAndImplementationOfSufficiencyStrategy,	// Keyword: SEA2030S_SubmissionAndImplementationOfSufficiencyStrategy
		NUM_SEA2030S
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco2_4_4(){}

	Eco2_4_4(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag			m_flag_SERUSGS[NUM_SERUSGS];					// XML:E
	/*! List of flags. */
	IBK::Flag			m_flag_SEMUS[NUM_SEMUS];						// XML:E
	/*! List of flags. */
	IBK::Flag			m_flag_SEA2030S[NUM_SEA2030S];					// XML:E

	IBK::Parameter					m_para[NUM_P];					// XML:E

	Utilities::UsageType			m_usageType;

}; // Eco 2.4.4

} // namespace DGNB

#endif // DGNB_Eco2_4_4H
