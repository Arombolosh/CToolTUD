#ifndef DGNB_Eco2_7_1H
#define DGNB_Eco2_7_1H

#include "DGNB_Utilities.h"

namespace DGNB {

/*! Eco2.7.1 Documentation of constructed building */
class Eco2_7_1 {

public:

	/*! Eco2.7.1.1 Current Planning Data */
	enum DCB_CurrentPlanningData {									// max +45/+27
		DCBCPD_CalculationByBGFSmallerThan5000m2Method,				// Keyword: DCBCPD_CalculationByBGFSmallerThan5000m2Method
		DCBCPD_ModelMatchesBuildingAndWasHandedOverToClient,		// Keyword: DCBCPD_ModelMatchesBuildingAndWasHandedOverToClient
		DCBCPD_RelevantCertificationsAndCalculationsMatchBuilding,	// Keyword: DCBCPD_RelevantCertificationsAndCalculationsMatchBuilding
		NUM_DCBCPD
	};

	/*! Eco2.7.1.2 Complete Sustainablity Building Documentation */
	enum DCB_CompleteSustainabilityBuildingDocumentation {							// max +20/+15
		DCBCSBD_CalculationByBGFSmallerThan5000m2Method,							// Keyword: DCBCSBD_CalculationByBGFSmallerThan5000m2Method
		DCBCSBD_PartsCatalogueIncludesEcologicalBalanceData,						// Keyword: DCBCSBD_PartsCatalogueIncludesEcologicalBalanceData
		DCBCSBD_PartsCatalogueIncludesEcologicalProductInformation,					// Keyword: DCBCSBD_PartsCatalogueIncludesEcologicalProductInformation
		DCBCSBD_PartsCatalogueIncludesCircularPropertiesMatchingBuilding,			// Keyword: DCBCSBD_PartsCatalogueIncludesCircularPropertiesMatchingBuilding
		DCBCSBD_PartsCatalogueHandedOverToClient,									// Keyword: DCBCSBD_PartsCatalogueHandedOverToClient
		NUM_DCBCSBD
	};

	/*! Eco2.7.1.3 Circular Economy Bonus Data Basis for "urban mines" */
	enum DCB_CircularEconomyDataBasisForUrbanMines {								// max +5
		DCBCEDBUM_BuildingRessourcePassIsPartOfSuperordinateDataBaseForUrbanMines,	// Keyword: DCBCEDBUM_BuildingRessourcePassIsPartOfSuperordinateDataBaseForUrbanMines
		NUM_DCBCEDBUM
	};

	/*! Eco2.7.1.1 Agenda 2030 Bonus Digital Footprint */
	enum DCB_Agenda2030DigitalFootprint {							// max +5
		DCBA2030DF_DigitalFootprintHeavilyReduced,					// Keyword: DCBA2030DF_DigitalFootprintHeavilyReduced
		NUM_DCBA2030DF
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco2_7_1(){}

	Eco2_7_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_DCBCPD[NUM_DCBCPD];					// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_DCBCSBD[NUM_DCBCSBD];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_DCBCEBDBUM[NUM_DCBCEDBUM];			// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_DCBA2030DF[NUM_DCBA2030DF];			// XML:E

	Utilities::UsageType			m_usageType;

}; // Eco 2.7.1

} // namespace DGNB

#endif // DGNB_Eco2_7_1H
