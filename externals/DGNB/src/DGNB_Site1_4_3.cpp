#include "DGNB_Site1_4_3.h"

namespace DGNB {

double DGNB::Site1_4_3::score() {
	double site1_4_3 = 0;


	// assigning points for Site1.4.3.1.a
	site1_4_3 += (m_flag_BAIUDIHD[(BAIUDIHD_Daycare)].isEnabled() ? 10 : 0);
	site1_4_3 += (m_flag_BAIUDIHD[(BAIUDIHD_SecondaryOrVocationalSchool)].isEnabled() ? 5 : 0);
	site1_4_3 += (m_flag_BAIUDIHD[(BAIUDIHD_CinemaTheatreOrGallery)].isEnabled() ? 5 : 0);
	site1_4_3 += (m_flag_BAIUDIHD[(BAIUDIHD_Bookstore)].isEnabled() ? 5 : 0);
	site1_4_3 += (m_flag_BAIUDIHD[(BAIUDIHD_QuarterCenter)].isEnabled() ? 5 : 0);
	site1_4_3 += (m_flag_BAIUDIHD[(BAIUDIHD_ParishHall)].isEnabled() ? 5 : 0);
	site1_4_3 += (m_flag_BAIUDIHD[(BAIUDIHD_YouthCenter)].isEnabled() ? 5 : 0);
	site1_4_3 += (m_flag_BAIUDIHD[(BAIUDIHD_ElderlyCenter)].isEnabled() ? 5 : 0);
	site1_4_3 += ((m_flag_BAIUDIHD[(BAIUDIHD_FitnessCenter)].isEnabled() || m_flag_BAIUDIHD[(BAIUDIHD_FitnessProgramOpenToExternalUsers)].isEnabled()) ? 5 : 0);
	site1_4_3 += (m_flag_BAIUDIHD[(BAIUDIHD_Playground)].isEnabled() ? 10 : 0);
	site1_4_3 += (m_flag_BAIUDIHD[(BAIUDIHD_GymSportsFieldOrSwimmingPool)].isEnabled() ? 5 : 0);
	// assigning points for Site1.4.3.1.b
	site1_4_3 += (m_flag_BAIUDIHD[(BAIUDIHD_LocalAmeneties1_ShoppingCenter)].isEnabled() ? 15 : 0);
	site1_4_3 += (m_flag_BAIUDIHD[(BAIUDIHD_LocalAmeneties2_Retailers_BakeryButcherDrugstoreEtc)].isEnabled() ? 5 : 0);
	site1_4_3 += (m_flag_BAIUDIHD[(BAIUDIHD_LocalAmeneties3_FarmersMarket)].isEnabled() ? 5 : 0);
	site1_4_3 += (m_flag_BAIUDIHD[(BAIUDIHD_Gastronomy_RestaurantCafeBakeryEtc)].isEnabled() ? 5 : 0);
	site1_4_3 += (m_flag_BAIUDIHD[(BAIUDIHD_OtherServices_BankPostOfficeBarberFitnessCenterWellnessCenter)].isEnabled() ? 5 : 0);
	site1_4_3 += (m_flag_BAIUDIHD[(BAIUDIHD_Healthcare1_GeneralPractitioner)].isEnabled() ? 10 : 0);
	site1_4_3 += (m_flag_BAIUDIHD[(BAIUDIHD_Healthcare2_MedicalSpecialistPharmacyEtc)].isEnabled() ? 5 : 0);

	// capping points at 30
	site1_4_3 = std::min<double>(30, site1_4_3);

	return site1_4_3;
}

double DGNB::Site1_4_3::scoreBonus() {
	double site1_4_3Bonus = 0;

	site1_4_3Bonus += ((m_flag_BAIUDCEODNE[BAIUDCEODNE_UnconventionalOffersPresentedToUsersAndExternals].isEnabled() && m_flag_BAIUDCEODNE[(BAIUDCEODNE_ConstructionalImplementationOrPreparationOfOffers)].isEnabled()) ? 10 : 0);

	return site1_4_3Bonus;
} // Site1.4.3

} // namespace DGNB
