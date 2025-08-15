#ifndef DGNB_Site1_4_3H
#define DGNB_Site1_4_3H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Site1.4.3 Building-Associated Infrastructure and Usage Diversity */
class Site1_4_3
{
public:

	/*! Site1.4.3.1 In-House Diversity*/
	enum BAIUD_InHouseDiversity {												// max +10
		BAIUDIHD_Daycare,														// Keyword: BAIUDIHD_Daycare
		BAIUDIHD_SecondaryOrVocationalSchool,									// Keyword: BAIUDIHD_SecondaryOrVocationalSchool
		BAIUDIHD_CinemaTheatreOrGallery,										// Keyword: BAIUDIHD_CinemaTheatreOrGallery
		BAIUDIHD_Bookstore,														// Keyword: BAIUDIHD_Bookstore
		BAIUDIHD_QuarterCenter,													// Keyword: BAIUDIHD_QuarterCenter
		BAIUDIHD_ParishHall,													// Keyword: BAIUDIHD_ParishHall
		BAIUDIHD_YouthCenter,													// Keyword: BAIUDIHD_YouthCenter
		BAIUDIHD_ElderlyCenter,													// Keyword: BAIUDIHD_ElderlyCenter
		BAIUDIHD_FitnessCenter,													// Keyword: BAIUDIHD_FitnessCenter
		BAIUDIHD_FitnessProgramOpenToExternalUsers,								// Keyword: BAIUDIHD_FitnessProgramOpenToExternalUsers
		BAIUDIHD_Playground,													// Keyword: BAIUDIHD_Playground
		BAIUDIHD_GymSportsFieldOrSwimmingPool,									// Keyword: BAIUDIHD_GymSportsFieldOrSwimmingPool
		BAIUDIHD_LocalAmeneties1_ShoppingCenter,								// Keyword: BAIUDIHD_LocalAmeneties1_ShoppingCenter
		BAIUDIHD_LocalAmeneties2_Retailers_BakeryButcherDrugstoreEtc,			// Keyword: BAIUDIHD_LocalAmeneties2_Retailers_BakeryButcherDrugstoreEtc
		BAIUDIHD_LocalAmeneties3_FarmersMarket,									// Keyword: BAIUDIHD_LocalAmeneties3_FarmersMarket
		BAIUDIHD_Gastronomy_RestaurantCafeBakeryEtc,							// Keyword: BAIUDIHD_Gastronomy_RestaurantCafeBakeryEtc
		BAIUDIHD_OtherServices_BankPostOfficeBarberFitnessCenterWellnessCenter,	// Keyword: BAIUDIHD_OtherServices_BankPostOfficeBarberFitnessCenterWellnessCenter
		BAIUDIHD_Healthcare1_GeneralPractitioner,								// Keyword: BAIUDIHD_Healthcare1_GeneralPractitioner
		BAIUDIHD_Healthcare2_MedicalSpecialistPharmacyEtc,						// Keyword: BAIUDIHD_Healthcare2_MedicalSpecialistPharmacyEtc
		NUM_BAIUDIHD
	};

	/*! Site1.4.3.2 Circular Economy Bonus - Offers of Daily Necessities and Exchange Offers */
	enum BAIUD_CircularEconomyOffersOfDailyNecessitiesAndExchange {				// max +10
		BAIUDCEODNE_UnconventionalOffersPresentedToUsersAndExternals,			// Keyword: BAIUDCEODNE_UnconventionalOffersPresentedToUsersAndExternals
		BAIUDCEODNE_ConstructionalImplementationOrPreparationOfOffers,			// Keyword: BAIUDCEODNE_ConstructionalImplementationOrPreparationOfOffers
		NUM_BAIUDCEODNE
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Site1_4_3(){}

	Site1_4_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_BAIUDIHD[NUM_BAIUDIHD];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_BAIUDCEODNE[NUM_BAIUDCEODNE];		// XML:E

	Utilities::UsageType			m_usageType;
};

} // namespace DGNB

#endif // DGNB_Site1_4_3H
