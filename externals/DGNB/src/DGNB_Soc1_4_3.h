#ifndef DGNB_Soc1_4_3H
#define DGNB_Soc1_4_3H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.4.3 Line of Sight to Outside */
class Soc1_4_3
{
public:

	/*! Basic parameters. */
	enum para_t {
		/*! PercentageOfOpenFacade */
		P_CurrentValue_soc1_4_3_1aPercentageOfOpenFacade,									// Keyword: CurrentValue_soc1_4_3_1aPercentageOfOpenFacade							[---]	// ToDo Einheit % SO oder anders?
		/*! PercentageOfDirectLOSOfShopAreasToOutside */
		P_CurrentValue_soc1_4_3_1aPercentageOfDirectLOSOfShopAreasToOutside,				// Keyword: CurrentValue_soc1_4_3_1aPercentageOfDirectLOSOfShopAreasToOutside		[---]	// ToDo Einheit % SO oder anders?
		NUM_P
	};

	/*! Soc1.4.3.1a Line Of Sight to Outside: ConvenienceStore CommercialBuilding ShoppingCenter */
	enum LOSO_ConvenienceStoreCommercialBuildingShoppingCenter {							// max +18 / +40 depending on usage Type
		LOSOCSCBSC_QSMedium_DirectOutsideLOSForAllOfficesAnd80PercentOfBreakAndSocialRooms,	// Keyword: LOSOCSCBSC_QSMedium_DirectOutsideLOSForAllOfficesAnd80PercentOfBreakAndSocialRooms
		LOSOCSCBSC_QSLow_CBSC_PercentageOfOpenFacadeResultsSubmitted,						// Keyword: LOSOCSCBSC_QSLow_CBSC_PercentageOfOpenFacadeResultsSubmitted
		LOSOCSCBSC_QSMediumC_BSC_ShopsHaveOutsideLOS,										// Keyword: LOSOCSCBSC_QSMediumC_BSC_ShopsHaveOutsideLOS
		LOSOCSCBSC_QSLOW_CBSC_PercentageOfDirectLOSOfShopAreasToOutsideResultsSubmitted,	// Keyword: LOSOCSCBSC_QSLOW_CBSC_PercentageOfDirectLOSOfShopAreasToOutsideResultsSubmitted
		LOSOCSCBSC_QSLOW_CashierAreasOutsideLOS,											// Keyword: LOSOCSCBSC_QSLOW_CashierAreasOutsideLOS
		NUM_LOSOCSCBSC
	};

	/*! Soc1.4.3.1b Line Of Sight to Outside: Office Education Hotel Logistics Assembly Residential Healthcare */
	enum LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare {					// max +15 / +20 / +30 depending on usage Type
		LOSOOEHLARHc_QSLow_OutsideAreasIntervisibility,										// Keyword: LOSOOEHLARHc_QSLow_OutsideAreasIntervisibility
		LOSOOEHLARHc_QSMedium_WorkplaceResidentialAreaHotelRoomCommonRoomIntervisibility,	// Keyword: LOSOOEHLARHc_QSMedium_WorkplaceResidentialAreaHotelRoomCommonRoomIntervisibility
		LOSOOEHLARHc_QShigh_WorkplaceResidentialAreaHotelRoomCommonRoomIntervisibility,		// Keyword: LOSOOEHLARHc_QShigh_WorkplaceResidentialAreaHotelRoomCommonRoomIntervisibility
		LOSOOEHLARHc_RHHc_AlternativeRequirementsMet,										// Keyword: LOSOOEHLARHc_RHHc_AlternativeRequirementsMet
		LOSOOEHLARHc_AssemblyType1,															// Keyword: LOSOOEHLARHc_AssemblyType1
		LOSOOEHLARHc_AssemblyType2,															// Keyword: LOSOOEHLARHc_AssemblyType2
		LOSOOEHLARHc_AnyDaylightInCommonAreas,												// Keyword: LOSOOEHLARHc_AnyDaylightInCommonAreas
		LOSOOEHLARHc_QSLow_OutsideAreaIntervisibility,										// Keyword: LOSOOEHLARHc_QSLow_OutsideAreaIntervisibility
		LOSOOEHLARHc_QSLow_OutsideAreaDirectIntervisibility,								// Keyword: LOSOOEHLARHc_QSLow_OutsideAreaDirectIntervisibility
		NUM_LOSOOEHLARHc
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_4_3(){}

	Soc1_4_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag					m_flag_LOSOCSCBSC[NUM_LOSOCSCBSC];										// XML:E
	/*! List of flags. */
	IBK::Flag					m_flag_LOSOOEHLARHc[NUM_LOSOOEHLARHc];									// XML:E
	
	IBK::Parameter				m_para[NUM_P];															// XML:E

	Utilities::UsageType		m_usageType;
	
};

} // namespace DGNB

#endif // DGNB_Soc1_4_3
