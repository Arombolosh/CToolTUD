#include "DGNB_Pro1_4_1.h"

namespace DGNB {

double DGNB::Pro1_4_1::score() {
	double pro1_4_1 = 0;

	if (m_flag_SATOEI[(SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAndTechnicalAspectsOfConstructionProductsIncludedCraftSpecificallyAndSelectivelyOnAServiceItemLevelInOffer)].isEnabled())
		pro1_4_1 += 100;
	else if (m_flag_SATOEI[(SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAspectsOfConstructionProductsIncludedCraftSpecificallyAndSelectivelyOnAServiceItemLevelInOffer)].isEnabled())
		pro1_4_1 += 75;
	else if (m_flag_SATOEI[(SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAspectsOfConstructionProductsIncludedInOffersGeneralPreliminaryRemarks)].isEnabled())
		pro1_4_1 += 50;
	else if (m_flag_SATOEI[(SATOEI_SelectSustainabilityAspectsOfHealthCompatibilityOrEnvironmentCompatibilityOrRelevantTechnicalAspectsIncludedInOffersGeneralPreliminaryRemarks)].isEnabled())
		pro1_4_1 += 10;

	return pro1_4_1;
}

double DGNB::Pro1_4_1::scoreBonus() {
	double pro1_4_1Bonus = 0;

	pro1_4_1Bonus += (m_flag_SATOCERM[(SATOCERM_NoExclusionOfRecycledMaterialsInTenderOffer)].isEnabled() ? 10 : 0);

	return pro1_4_1Bonus;
} // Pro1.4.1

} // namespace DGNB
