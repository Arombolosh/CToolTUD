#ifndef DGNB_Eco1_1_2H
#define DGNB_Eco1_1_2H

#include "DGNB_Utilities.h"

namespace DGNB {
/*! Eco1.1.2 Examplary energetic and climate balance during operation */

class Eco1_1_2	// max +10
{
public:
	/*! Basic parameters. */
	enum para_t {
		/*! EECBOCEBR_NumberOfCircularEconomySolutionsForReuse */
		P_CurrentValue_eco1_1_2EECBOCEBR_NumberOfCircularEconomySolutionsForReuse,	// Keyword: CurrentValue_eco1_1_2EECBOCEBR_NumberOfCircularEconomySolutionsForReuse		[-]
		NUM_P
	};
	
	/*! Eco1.1.2.1 new building up to GEG § 103 innovation clause */
	enum EECBO_BuildingEnergyBill {													// max +10
		EECBOBEB_BuildingUpToInnovationClauseStandards,								// Keyword: EECBOBEB_BuildingUpToInnovationClauseStandards
		EECBOBEB_AltBuildingReceivedKFWFundingForEnergyEfficiencyClassAOrBetter,	// Keyword: EECBOBEB_AltBuildingReceivedKFWFundingForEnergyEfficiencyClassAOrBetter
		NUM_EECBOBEB
	};

	/*! Eco1.1.2.2. Circular Economy Bonus */
	enum EECBO_CircularEconomyBonusReuse {							// max +10
		EECBOCEBR_CircularEconomySolutionsForReuseSubmitted,		// Keyword: EECBOCEBR_CircularEconomySolutionsForReuseSubmitted
		EECBOCEBR_LCCModelIncludesEndOfLifeCosts,					// Keyword: EECBOCEBR_LCCModelIncludesEndOfLifeCosts
		EECBOCEBR_DocumentationOfRawMaterialValue,					// Keyword: EECBOCEBR_DocumentationOfRawMaterialValue
		NUM_EECBOCEBR
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco1_1_2(){}

	Eco1_1_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}



	double score();
	double scoreBonus();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag			m_flag_EECBOBEB[NUM_EECBOBEB];				// XML:E
	/*! List of flags. */
	IBK::Flag			m_flag_EECBOCEBR[NUM_EECBOCEBR];			// XML:E

	Utilities::UsageType			m_usageType;

	IBK::Parameter					m_para[NUM_P];					// XML:E
	/*!
	double				m_currentValue_eco1_1_2EECBOCEBR_NumberOfCircularEconomySolutionsForReuse;			// Keyword: currentValue_eco1_1_2EECBOCEBR_NumberOfCircularEconomySolutionsForReuse
	*/
};

} // namespace DGNB

#endif // DGNB_Eco1_1_2H
