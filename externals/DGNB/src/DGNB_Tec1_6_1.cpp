#include "DGNB_Tec1_6_1.h"

namespace DGNB {
	
double DGNB::Tec1_6_1::score() {
	double tec1_6_1 = 0;
	
	// Assigning pts for no (partial) demolition
	if (m_flag_CCPID161[(CCPID161_DemolitionOrPartialDemolition)].isEnabled() == false) {
		tec1_6_1 +=(m_flag_SSAPPDA[(SSAPPDA_CircularConstructionPotentialsOfSiteAndRegionResourcesHasBeenAnalysed)].isEnabled() ? 5 : 0);
	} else
	// Assigning pts for (partial) demolition
	if (m_flag_CCPID161[(CCPID161_DemolitionOrPartialDemolition)].isEnabled()) {
		tec1_6_1 +=(m_flag_SSAPPDA[(SSAPPDA_CircularConstructionPotentialsOfSiteAndRegionResourcesHasBeenAnalysed)].isEnabled() ? 5 : 0);
		
		if (m_flag_SSAPPDDAC[(SSAPPDDAC_DGNBDemolitionCertificationFollowed)].isEnabled()) {
			tec1_6_1 += 15;
		} else
		if (m_flag_SSAPPDDAC[(SSAPPDDAC_DGNBDemolitionCertificationFollowed)].isEnabled() == false) {
			tec1_6_1 +=((m_flag_SSAPPDDJ[(SSAPPDDJ_JustificationProvided)].isEnabled() && m_flag_SSAPPDDJ[(SSAPPDDJ_InventoryOfPartsMaterialFlowBalanceStockAnalysisTaken)].isEnabled()) ? 5 : 0);
			tec1_6_1 +=((m_flag_SSAPPDDE[(SSAPPDDE_ProactiveSearchForBuyersOrAcceptorsOfPartsAndProductsDuringDemolition)].isEnabled() && m_flag_SSAPPDDE[(SSAPPDDE_InventoryTakenForMassesAndTransportDistances)].isEnabled() && m_flag_SSAPPDDE[(SSAPPDDE_MeasuresTakenToOptimiseReuseAndDisposal)].isEnabled() && m_flag_SSAPPDDE[(SSAPPDDE_RecommendedOrOtherSuitableMeasuresAgainstHazardousMaterialsTaken)].isEnabled()) ? 10 : 0);
		}
	}


	return tec1_6_1;
}

double DGNB::Tec1_6_1::scoreBonus() {
	double tec1_6_1Bonus = 0;
	
	// Assigning bonus pts for Tec1.6.1.2
	tec1_6_1Bonus +=((m_flag_SSAPPDCEBSPU[(SSAPPDCEBSPU_StockPreserved)].isEnabled() || m_flag_SSAPPDCEBSPU[(SSAPPDCEBSPU_StockExpanded)].isEnabled() || m_flag_SSAPPDCEBSPU[(SSAPPDCEBSPU_StockElementsPutToUse)].isEnabled()) ? 10 : 0);
	
	// Assigning bonus pts for Tec1.6.1.3.4 for (partial) demolition
	if (m_flag_CCPID161[(CCPID161_DemolitionOrPartialDemolition)].isEnabled())
		tec1_6_1Bonus +=(m_flag_SSAPPDCERS[(SSAPPDCERS_MaterialsOrElementsLeftFromDemolitionReusedInProject)].isEnabled() ? 2.5 : 0);
	
	return tec1_6_1Bonus;
}

bool DGNB::Tec1_6_1::platinumRequirementsMet() {
	bool platReqMet = false;
	int platReqMetCounter = 0;

	platReqMetCounter += (m_flag_SSAPPDDJ[(DGNB::Tec1_6_1::SSAPPDDJ_JustificationProvided)].isEnabled() ? 1 : 0);

	platReqMet = (platReqMetCounter == 1 ? true : false);

	return platReqMet;
} // Tec1.6.1

} // namespace DGNB
