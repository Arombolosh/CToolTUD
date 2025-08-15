#ifndef DGNB_Tec1_6_1H
#define DGNB_Tec1_6_1H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

/*! Site and Stock Analysis and preceding (partial) demolition */
class Tec1_6_1
{
public:

	/*! Tec1.6 Circular Construction: Project included Demolition */
	enum CC_ProjectIncludesDemolition {													// impact on scoring of several indicators
		CCPID161_DemolitionOrPartialDemolition,											// Keyword: CCPID161_DemolitionOrPartialDemolition
		NUM_CCPID161
	};

	/*! Tec1.6.1.1 Stock and Site Analysis */
	enum SSAPPD_Analysis {																// max +10
		SSAPPDA_CircularConstructionPotentialsOfSiteAndRegionResourcesHasBeenAnalysed,	// Keyword: SSAPPDA_CircularConstructionPotentialsOfSiteAndRegionResourcesHasBeenAnalysed
		NUM_SSAPPDA
	};

	/*! Tec1.6.1.2 CE Bonus - Stock Preservation or Use */
	enum SSAPPD_CircularEconomyBonusStockPreservationOrUse {							// +10 if any are true
		SSAPPDCEBSPU_StockPreserved,													// Keyword: SSAPPDCEBSPU_StockPreserved
		SSAPPDCEBSPU_StockExpanded,														// Keyword: SSAPPDCEBSPU_StockExpanded
		SSAPPDCEBSPU_StockElementsPutToUse,												// Keyword: SSAPPDCEBSPU_StockElementsPutToUse
		NUM_SSAPPDCEBSPU
	};

	/*! Tec1.6.1.3 Variable Indicator: Demolition */
	/*! Tec1.6.1.3.1 Variable Indicator: Demolition - Justification */
	enum SSAPPD_DemolitionJustification {												// max +5 for Demolition Projects only
		SSAPPDDJ_JustificationProvided,													// Keyword: SSAPPDDJ_JustificationProvided
		SSAPPDDJ_InventoryOfPartsMaterialFlowBalanceStockAnalysisTaken,					// Keyword: SSAPPDDJ_InventoryOfPartsMaterialFlowBalanceStockAnalysisTaken
		NUM_SSAPPDDJ
	};

	/*! Tec1.6.1.3.2 Variable Indicator: Demolition - Execution */
	enum SSAPPD_DemolitionExecution {													// max +10 for Demolition Projects only
		SSAPPDDE_ProactiveSearchForBuyersOrAcceptorsOfPartsAndProductsDuringDemolition,	// Keyword: SSAPPDDE_ProactiveSearchForBuyersOrAcceptorsOfPartsAndProductsDuringDemolition
		SSAPPDDE_InventoryTakenForMassesAndTransportDistances,							// Keyword: SSAPPDDE_InventoryTakenForMassesAndTransportDistances
		SSAPPDDE_MeasuresTakenToOptimiseReuseAndDisposal,								// Keyword: SSAPPDDE_MeasuresTakenToOptimiseReuseAndDisposal
		SSAPPDDE_RecommendedOrOtherSuitableMeasuresAgainstHazardousMaterialsTaken,		// Keyword: SSAPPDDE_RecommendedOrOtherSuitableMeasuresAgainstHazardousMaterialsTaken
		NUM_SSAPPDDE
	};

	/*! Tec1.6.1.3.3 Variable Indicator: Demolition - Alternative Certification */
	enum SSAPPD_DemolitionAlternativeCertification {									// alternative max +15 for Demolition Projects only
		SSAPPDDAC_DGNBDemolitionCertificationFollowed,									// Keyword: SSAPPDDAC_DGNBDemolitionCertificationFollowed
		NUM_SSAPPDDAC
	};

	/*! Tec1.6.1.3.4 CE Bonus - Reuse On Site */
	enum SSAPPD_CircularEconomyBonusReuseOnSite {										// +2.5 Bonus pts for Demolition Projects only
		SSAPPDCERS_MaterialsOrElementsLeftFromDemolitionReusedInProject,				// Keyword: SSAPPDCERS_MaterialsOrElementsLeftFromDemolitionReusedInProject
		NUM_SSAPPDCERS
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Tec1_6_1(){}

	Tec1_6_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();
	bool platinumRequirementsMet();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_CCPID161[NUM_CCPID161];			// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_SSAPPDA[NUM_SSAPPDA];			// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_SSAPPDCEBSPU[NUM_SSAPPDCEBSPU];	// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_SSAPPDDJ[NUM_SSAPPDDJ];			// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_SSAPPDDE[NUM_SSAPPDDE];			// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_SSAPPDDAC[NUM_SSAPPDDAC];		// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_SSAPPDCERS[NUM_SSAPPDCERS];		// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Tec1_6_1H
