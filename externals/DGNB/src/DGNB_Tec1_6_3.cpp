#include "DGNB_Tec1_6_3.h"

namespace DGNB {
	
double DGNB::Tec1_6_3::score() {
	double tec1_6_3 = 0;
	
	// Assigning pts for no (partial) demolition (no difference in scoring method but separated in catalogue)
	if (m_flag_CCPID163[(CCPID163_DemolitionOrPartialDemolition)].isEnabled() == false) {
		if (m_flag_CCEDDCBPBP[(CCEDDCBPBP_CompleteBuildingPass)].isEnabled())
			tec1_6_3 += 50;
		else if (m_flag_CCEDDCBPBP[(CCEDDCBPBP_ReducedBuildingPass)].isEnabled())
			tec1_6_3 += 35;
		
		
		if (m_flag_CCEDERCPBL[(CCEDERCPBL_HighGoalQuotaReachedForAtLeast2Properties)].isEnabled())
			tec1_6_3 += 15;
		else if (m_flag_CCEDERCPBL[(CCEDERCPBL_ModerateGoalQuotaReachedForAllProperties)].isEnabled())
			tec1_6_3 += 10;
		
		if (m_flag_CCEDUCPCEL[(CCEDUCPCEL_UseOfProductsOfQS4)].isEnabled())
			tec1_6_3 += 25;
		else if (m_flag_CCEDUCPCEL[(CCEDUCPCEL_UseOfProductsOfQS3)].isEnabled() || m_flag_CCEDUCPCEL[(CCEDUCPCEL_RequirementsOfSimplifiedMethodFulfilled)].isEnabled())
			tec1_6_3 += 20;
		else if (m_flag_CCEDUCPCEL[(CCEDUCPCEL_UseOfProductsOfQS2)].isEnabled())
			tec1_6_3 += 15;
		else if (m_flag_CCEDUCPCEL[(CCEDUCPCEL_UseOfProductsOfQS1)].isEnabled())
			tec1_6_3 += 10;

		if (m_flag_CCEDRRDI[(CCEDRRDI_InstructionsIncludeReuseRebuildingAndDemolition)].isEnabled())
			tec1_6_3 += 5;
		else if (m_flag_CCEDRRDI[(CCEDRRDI_InstructionsIncludeRebuildingAndDemolition)].isEnabled())
			tec1_6_3 += 3;
	}
	else // this is exactly the same, doubling it here in case there will be future changes that include another differentiation
	{
		if (m_flag_CCEDDCBPBP[(CCEDDCBPBP_CompleteBuildingPass)].isEnabled())
			tec1_6_3 += 50;
		else if (m_flag_CCEDDCBPBP[(CCEDDCBPBP_ReducedBuildingPass)].isEnabled())
			tec1_6_3 += 35;
		
		
		if (m_flag_CCEDERCPBL[(CCEDERCPBL_HighGoalQuotaReachedForAtLeast2Properties)].isEnabled())
			tec1_6_3 += 15;
		else if (m_flag_CCEDERCPBL[(CCEDERCPBL_ModerateGoalQuotaReachedForAllProperties)].isEnabled())
			tec1_6_3 += 10;
		
		if (m_flag_CCEDUCPCEL[(CCEDUCPCEL_UseOfProductsOfQS4)].isEnabled())
			tec1_6_3 += 25;
		else if (m_flag_CCEDUCPCEL[(CCEDUCPCEL_UseOfProductsOfQS3)].isEnabled() || m_flag_CCEDUCPCEL[(CCEDUCPCEL_RequirementsOfSimplifiedMethodFulfilled)].isEnabled())
			tec1_6_3 += 20;
		else if (m_flag_CCEDUCPCEL[(CCEDUCPCEL_UseOfProductsOfQS2)].isEnabled())
			tec1_6_3 += 15;
		else if (m_flag_CCEDUCPCEL[(CCEDUCPCEL_UseOfProductsOfQS1)].isEnabled())
			tec1_6_3 += 10;

		if (m_flag_CCEDRRDI[(CCEDRRDI_InstructionsIncludeReuseRebuildingAndDemolition)].isEnabled())
			tec1_6_3 += 5;
		else if (m_flag_CCEDRRDI[(CCEDRRDI_InstructionsIncludeRebuildingAndDemolition)].isEnabled())
			tec1_6_3 += 3;
	}

	return tec1_6_3;
}
	
double DGNB::Tec1_6_3::scoreBonus() {
	double tec1_6_3Bonus = 0;
	
	// assigning up to 22.5 bonus pts for Tec1.6.3.2.3
	tec1_6_3Bonus += (m_flag_CCEDCERMACAMMCI[(CCEDCERMACAMMCI_UseOfRecycledMaterials)].isEnabled() ? 10 : 0);
	if (m_flag_CCEDCERMACAMMCI[(CCEDCERMACAMMCI_NumberOfConstructionsUsingMaterialAppropriateConstructionsResultsSubmitted)].isEnabled())
		tec1_6_3Bonus += std::min<double>(5, m_para[(P_CCEDCERMACAMMCI_NumberOfConstructionsUsingMaterialAppropriateConstructions)].get_value());
	if (m_flag_CCEDCERMACAMMCI[(CCEDCERMACAMMCI_NumberOfConstructionsAvoidingMaterialMixingOrLayeringResultsSubmitted)].isEnabled())
		tec1_6_3Bonus += std::min<double>(5, m_para[(P_CCEDCERMACAMMCI_NumberOfConstructionsAvoidingMaterialMixingOrLayering)].get_value());
	tec1_6_3Bonus += (m_flag_CCEDCERMACAMMCI[(CCEDCERMACAMMCI_CircularAspectsImplementedInConstructiveIntegrations)].isEnabled() ? 2.5 : 0);
	
	// assigning up to 25 Bonus pts for Tec1.6.3.4
	tec1_6_3Bonus += (m_flag_CCEDCECBACE[(CCEDCECBACE_MoreThan90PercentOfPartsOriginateFromCircularEconomy)].isEnabled() ? 5 : 0);
	tec1_6_3Bonus += (m_flag_CCEDCECBACE[(CCEDCECBACE_MoreThan90PercentOfBuildingMassSuitedForReuseInCircularEconomy)].isEnabled() ? 5 : 0);
	tec1_6_3Bonus += (m_flag_CCEDCECBACE[(CCEDCECBACE_AggregatedCircularyIndexEvaluationDocumentedInBuildingPassAndRatedGoodOrAbove)].isEnabled() ? 10 : 0);

	return tec1_6_3Bonus;
}

bool DGNB::Tec1_6_3::minimumRequirementsMet() {
	bool minReqMet = false;
	int minReqMetCounter = 0;

	minReqMetCounter += (m_flag_CCEDRRDI[(DGNB::Tec1_6_3::CCEDRRDI_InstructionsIncludeReuseRebuildingAndDemolition)].isEnabled() || m_flag_CCEDRRDI[(DGNB::Tec1_6_3::CCEDRRDI_InstructionsIncludeRebuildingAndDemolition)].isEnabled() ? 1 : 0);

	minReqMet = (minReqMetCounter == 1 ? true : false);

	return minReqMet;
}

bool DGNB::Tec1_6_3::platinumRequirementsMet() {
	bool platReqMet = false;
	int platReqMetCounter = 0;

	platReqMetCounter += (m_flag_CCEDRRDI[(DGNB::Tec1_6_3::CCEDRRDI_InstructionsIncludeReuseRebuildingAndDemolition)].isEnabled() || m_flag_CCEDRRDI[(DGNB::Tec1_6_3::CCEDRRDI_InstructionsIncludeRebuildingAndDemolition)].isEnabled() ? 1 : 0);
	platReqMetCounter += (score() >= 20 ? 1 : 0);

	platReqMet = (platReqMetCounter == 2 ? true : false);

	return platReqMet;
} // Tec1.6.3
} // namespace DGNB
