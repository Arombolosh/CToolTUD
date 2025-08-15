#ifndef DGNB_Tec1_6_3H
#define DGNB_Tec1_6_3H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

/*! Circular Construction - Execution and Documentation */
class Tec1_6_3
{
public:

	/*! Basic parameters. */
	enum para_t {
		/*! number of constructions using material-appropriate constructions */
		P_CCEDCERMACAMMCI_NumberOfConstructionsUsingMaterialAppropriateConstructions,				// Keyword: CCEDCERMACAMMCI_NumberOfConstructionsUsingMaterialAppropriateConstructions		[-]
		/*! number of constructions avoiding material-mixing or layering */
		P_CCEDCERMACAMMCI_NumberOfConstructionsAvoidingMaterialMixingOrLayering,					// Keyword: CCEDCERMACAMMCI_NumberOfConstructionsAvoidingMaterialMixingOrLayering			[-]
		NUM_P
	};

	/*! Tec1.6 Circular Construction: Project included Demolition */
	enum CC_ProjectIncludesDemolition {																// impact on scoring of several indicators
		CCPID163_DemolitionOrPartialDemolition,														// Keyword: CCPID163_DemolitionOrPartialDemolition
		NUM_CCPID163
	};

	/*! Tec1.6.3.1 Description Of Circular Building Properties: Building Pass */
	enum CCED_DescriptionOfCircularBuildingPropertiesBuildingPass {									// max +50
		CCEDDCBPBP_ReducedBuildingPass,																// Keyword: CCEDDCBPBP_ReducedBuildingPass
		CCEDDCBPBP_CompleteBuildingPass,															// Keyword: CCEDDCBPBP_CompleteBuildingPass
		NUM_CCEDDCBPBP
	};

	/*! Tec1.6.3.2.1 Evaluation of Realised Circular Properties on Building Level */
	enum CCED_EvaluationOfRealisedCircularPropertiesOnBuildingLevel {								// max +15
		CCEDERCPBL_ModerateGoalQuotaReachedForAllProperties,										// Keyword: CCEDERCPBL_ModerateGoalQuotaReachedForAllProperties
		CCEDERCPBL_HighGoalQuotaReachedForAtLeast2Properties,										// Keyword: CCEDERCPBL_HighGoalQuotaReachedForAtLeast2Properties
		NUM_CCEDERCPBL
	};

	/*! Tec1.6.3.2.2 Use of Circular Products on Construction Element Level */
	enum CCED_UseOfCircularProductsOnConstructionElementLevel {										// max +25
		CCEDUCPCEL_UseOfProductsOfQS4,																// Keyword: CCEDUCPCEL_UseOfProductsOfQS4
		CCEDUCPCEL_UseOfProductsOfQS3,																// Keyword: CCEDUCPCEL_UseOfProductsOfQS3
		CCEDUCPCEL_UseOfProductsOfQS2,																// Keyword: CCEDUCPCEL_UseOfProductsOfQS2
		CCEDUCPCEL_UseOfProductsOfQS1,																// Keyword: CCEDUCPCEL_UseOfProductsOfQS1
		CCEDUCPCEL_RequirementsOfSimplifiedMethodFulfilled,											// Keyword: CCEDUCPCEL_RequirementsOfSimplifiedMethodFulfilled
		NUM_CCEDUCPCEL
	};

	/*! Tec1.6.3.2.3 Circular Economy Bonus - Recycling, material-appropriate Construction, Avoidance Of Material-Mixing, Constructive Integrations  */
	enum CCED_CircularEconomyBonusRecyclingMaterialAppropriateConstructionAvoidanceOfMaterialMixingConstructiveIntegrations {		// max +25
		CCEDCERMACAMMCI_UseOfRecycledMaterials,														// Keyword: CCEDCERMACAMMCI_UseOfRecycledMaterials
		CCEDCERMACAMMCI_NumberOfConstructionsUsingMaterialAppropriateConstructionsResultsSubmitted,	// Keyword: CCEDCERMACAMMCI_NumberOfConstructionsUsingMaterialAppropriateConstructionsResultsSubmitted
		CCEDCERMACAMMCI_NumberOfConstructionsAvoidingMaterialMixingOrLayeringResultsSubmitted,		// Keyword: CCEDCERMACAMMCI_NumberOfConstructionsAvoidingMaterialMixingOrLayeringResultsSubmitted
		CCEDCERMACAMMCI_CircularAspectsImplementedInConstructiveIntegrations,						// Keyword: CCEDCERMACAMMCI_CircularAspectsImplementedInConstructiveIntegrations
		NUM_CCEDCERMACAMMCI
	};

	/*! Tec1.6.3.3 Reuse Rebuilding and Demolition Instructions */
	enum CCED_ReuseRebuildingAndDemolitionInstructions {											// max +5
		CCEDRRDI_InstructionsIncludeReuseRebuildingAndDemolition,									// Keyword: CCEDRRDI_InstructionsIncludeReuseRebuildingAndDemolition
		CCEDRRDI_InstructionsIncludeRebuildingAndDemolition,										// Keyword: CCEDRRDI_InstructionsIncludeRebuildingAndDemolition
		NUM_CCEDRRDI
	};

	/*! Tec1.6.3.4 Circular Economy Bonus - Circular Building and Aggregated Circularity Evaluation */
	enum CCED_CircularEconomyBonusCircularBuildingAndAggregatedCircularityEvaluation {				// max +20
		CCEDCECBACE_MoreThan90PercentOfPartsOriginateFromCircularEconomy,							// Keyword: CCEDCECBACE_MoreThan90PercentOfPartsOriginateFromCircularEconomy
		CCEDCECBACE_MoreThan90PercentOfBuildingMassSuitedForReuseInCircularEconomy,					// Keyword: CCEDCECBACE_MoreThan90PercentOfBuildingMassSuitedForReuseInCircularEconomy
		CCEDCECBACE_AggregatedCircularyIndexEvaluationDocumentedInBuildingPassAndRatedGoodOrAbove,	// Keyword: CCEDCECBACE_AggregatedCircularyIndexEvaluationDocumentedInBuildingPassAndRatedGoodOrAbove
		NUM_CCEDCECBACE
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Tec1_6_3(){}

	Tec1_6_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();
	bool minimumRequirementsMet();
	bool platinumRequirementsMet();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_CCPID163[NUM_CCPID163];						// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CCEDDCBPBP[NUM_CCEDDCBPBP];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CCEDERCPBL[NUM_CCEDERCPBL];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CCEDUCPCEL[NUM_CCEDUCPCEL];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CCEDCERMACAMMCI[NUM_CCEDCERMACAMMCI];	// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CCEDRRDI[NUM_CCEDRRDI];					// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CCEDCECBACE[NUM_CCEDCECBACE];			// XML:E
	
	IBK::Parameter					m_para[NUM_P];									// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Tec1_6_3H
