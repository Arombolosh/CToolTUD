#include "DGNB_Site1_4_2.h"

namespace DGNB {
	
double DGNB::Site1_4_2::score() {
	double site1_4_2 = 0;
	
	// assigning points for Site1.4.2.1
	site1_4_2 += (m_flag_POEIQS[(POEIQS_LocalAmeneties1_ShoppingCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters)].isEnabled() ? 15 : 0);
	site1_4_2 += (m_flag_POEIQS[(POEIQS_LocalAmeneties2_Retailers_BakeryButcherDrugstoreEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters)].isEnabled() ? 5 : 0);
	site1_4_2 += (m_flag_POEIQS[(POEIQS_LocalAmeneties3_FarmersMarketWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters)].isEnabled() ? 5 : 0);
	site1_4_2 += (m_flag_POEIQS[(POEIQS_Gastronomy_RestaurantCafeBakeryEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters)].isEnabled() ? 5 : 0);
	site1_4_2 += (m_flag_POEIQS[(POEIQS_OtherServices_BankPostOfficeBarberFitnessCenterWellnessCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters)].isEnabled() ? 5 : 0);
	site1_4_2 += (m_flag_POEIQS[(POEIQS_Healthcare1_GeneralPractitionerWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters)].isEnabled() ? 10 : 0);
	site1_4_2 += (m_flag_POEIQS[(POEIQS_Healthcare2_MedicalSpecialistPharmacyEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters)].isEnabled() ? 5 : 0);

	// capping points at 35
	site1_4_2 = std::min<double>(35, site1_4_2);

	return site1_4_2;
} // Site1.4.2

} // namespace DGNB
