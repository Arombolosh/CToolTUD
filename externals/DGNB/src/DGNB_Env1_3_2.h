#ifndef DGNB_Env1_3_2H
#define DGNB_Env1_3_2H
#include "DGNB_Utilities.h"

namespace DGNB {
	
/*! responsible resource management */
class Env1_3_2 {													// max +100
	public:

	/*! Basic parameters. */
	enum para_t {
		/*! NumberOfPartsFromDiffManufacturers */
		P_Env1_3_2_1NumberOfPartsFromDiffManufacturers,										// Keyword: Env1_3_2_1NumberOfPartsFromDiffManufacturers									[-]
		/*! RRMRRWPSR_WeightingCostGroup */
		P_ReferenceValueEnv1_3_2_2RRMRRWPSR_WeightingCostGroup,								// Keyword: ReferenceValueEnv1_3_2_2RRMRRWPSR_WeightingCostGroup							[-]
		/*! RRMRRWPSR_DetailedMethodSumOfMassPercentOfPartsOfQS4 */
		P_CurrentValueEnv1_3_2_2RRMRRWPSR_DetailedMethodSumOfMassPercentOfPartsOfQS4,		// Keyword: CurrentValueEnv1_3_2_2RRMRRWPSR_DetailedMethodSumOfMassPercentOfPartsOfQS4		[-]
		/*! RRMRRWPSR_DetailedMethodSumOfMassPercentOfPartsOfQS2 */
		P_CurrentValueEnv1_3_2_2RRMRRWPSR_DetailedMethodSumOfMassPercentOfPartsOfQS2,		// Keyword: CurrentValueEnv1_3_2_2RRMRRWPSR_DetailedMethodSumOfMassPercentOfPartsOfQS2		[-]
		/*! RRMRRWPSR_SimplifiedMethodSumOfNumberOfPartsOfQS4 */
		P_CurrentValueEnv1_3_2_2RRMRRWPSR_SimplifiedMethodSumOfNumberOfPartsOfQS4,			// Keyword: CurrentValueEnv1_3_2_2RRMRRWPSR_SimplifiedMethodSumOfNumberOfPartsOfQS4			[-]
		/*! RRMRRWPSR_SimplifiedMethodSumOfNumberOfPartsOfQS2 */
		P_CurrentValueEnv1_3_2_2RRMRRWPSR_SimplifiedMethodSumOfNumberOfPartsOfQS2,			// Keyword: CurrentValueEnv1_3_2_2RRMRRWPSR_SimplifiedMethodSumOfNumberOfPartsOfQS2			[-]
		NUM_P
	};
	
	/*! Company's responsibility for resource management */
	//Env1_3_2_1
	enum RRM_CompanyResponsibilityForResourceManagement {			// max+20
		RRMCRRM_ResultSumbitted,									// Keyword: RRMCRRM_ResultSumbitted
		NUM_RRMCRRM
	};

	/*! Usage of responsibly won products and of secondary resources */
	//Env1_3_2_2_1
	enum RRM_UsageOfResponsiblyWonProductsSecondaryResources {		// max +100
		RRMRRWPSR_DetailedMethod,									// Keyword: RRMRRWPSR_DetailedMethod
		RRMRRWPSR_SimplifiedMethod,									// Keyword: RRMRRWPSR_SimplifiedMethod
		NUM_RRMRRWPSR
	};

	/*! Percentage of Wood materials from sustainable forestry */
	enum RRM_PercentageOfWoodMaterialsFromSustainableForestry {		// no pts, just platinum requirement
		RRMPWMSF_PercentageMinimum50,								// Keyword: RRMPWMSF_PercentageMinimum50
		NUM_RRMPWMSF
	};

	/*! Percentage of recycled concrete, earthwork materials and plant substrates */
	//Env1_3_2_2_2
	enum RRM_PRCEWMPS {												// max +5
		RRMPRCEWMPS_Percentage,										// Keyword: RRMPRCEWMPS_Percentage
		NUM_RRMPRCEWMPS
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env1_3_2(){}

	Env1_3_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	bool minimumRequirementsMet();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag				m_flag_RRMCRRM[NUM_RRMCRRM];						// XML:E
	/*! List of flags. */
	IBK::Flag				m_flag_RRMRRWPSR[NUM_RRMRRWPSR];					// XML:E
	/*! List of flags. */
	IBK::Flag				m_flag_RRMPWMSF[NUM_RRMPWMSF];						// XML:E
	/*! List of flags. */
	IBK::Flag				m_flag_RRMPRCEWMPS[NUM_RRMPRCEWMPS];				// XML:E

	IBK::Parameter			m_para[NUM_P];										// XML:E

	Utilities::UsageType	m_usageType;

};

} // namespace DGNB

#endif // Env1_3_2H
