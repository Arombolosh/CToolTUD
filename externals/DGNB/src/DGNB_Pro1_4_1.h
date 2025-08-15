#ifndef DGNB_Pro1_4_1H
#define DGNB_Pro1_4_1H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

/*! Pro1.4.1 Sustainability Aspects in Tender Offers */
class Pro1_4_1
{
public:

	/*! Pro1.4.1.1 Extent of Integration */
	enum SATO_ExtentOfIntegration {										// max +100
		SATOEI_SelectSustainabilityAspectsOfHealthCompatibilityOrEnvironmentCompatibilityOrRelevantTechnicalAspectsIncludedInOffersGeneralPreliminaryRemarks,							// Keyword: SATOEI_SelectSustainabilityAspectsOfHealthCompatibilityOrEnvironmentCompatibilityOrRelevantTechnicalAspectsIncludedInOffersGeneralPreliminaryRemarks
		SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAspectsOfConstructionProductsIncludedInOffersGeneralPreliminaryRemarks,										// Keyword: SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAspectsOfConstructionProductsIncludedInOffersGeneralPreliminaryRemarks
		SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAspectsOfConstructionProductsIncludedCraftSpecificallyAndSelectivelyOnAServiceItemLevelInOffer,				// Keyword: SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAspectsOfConstructionProductsIncludedCraftSpecificallyAndSelectivelyOnAServiceItemLevelInOffer
		SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAndTechnicalAspectsOfConstructionProductsIncludedCraftSpecificallyAndSelectivelyOnAServiceItemLevelInOffer,	// Keyword: SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAndTechnicalAspectsOfConstructionProductsIncludedCraftSpecificallyAndSelectivelyOnAServiceItemLevelInOffer
		NUM_SATOEI
	};


	/*! Pro1.4.1.2 Circular Economy Bonus - Recycled Materials*/
	enum SATO_CircularEconomyRecycledMaterials {				// max +10
		SATOCERM_NoExclusionOfRecycledMaterialsInTenderOffer,	// Keyword: SATOCERM_NoExclusionOfRecycledMaterialsInTenderOffer
		NUM_SATOCERM
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro1_4_1(){}

	Pro1_4_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_SATOEI[NUM_SATOEI];			// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_SATOCERM[NUM_SATOCERM];		// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro1_4_1H
