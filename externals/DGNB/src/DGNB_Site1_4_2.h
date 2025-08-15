#ifndef DGNB_Site1_4_2H
#define DGNB_Site1_4_2H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Site1.4.2 Profit Oriented Economy */
class Site1_4_2
{
public:

	/*! Site1.4.2 Infrastructure of Profit Oriented Economy in Quarter or Surroundings */
	enum POE_InfrastructureInQuarterOrSurroundings {							// max +10
		POEIQS_LocalAmeneties1_ShoppingCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters,								// Keyword: POEIQS_LocalAmeneties1_ShoppingCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters
		POEIQS_LocalAmeneties2_Retailers_BakeryButcherDrugstoreEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters,			// Keyword: POEIQS_LocalAmeneties2_Retailers_BakeryButcherDrugstoreEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters
		POEIQS_LocalAmeneties3_FarmersMarketWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters,									// Keyword: POEIQS_LocalAmeneties3_FarmersMarketWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters
		POEIQS_Gastronomy_RestaurantCafeBakeryEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters,							// Keyword: POEIQS_Gastronomy_RestaurantCafeBakeryEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters
		POEIQS_OtherServices_BankPostOfficeBarberFitnessCenterWellnessCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters,	// Keyword: POEIQS_OtherServices_BankPostOfficeBarberFitnessCenterWellnessCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters
		POEIQS_Healthcare1_GeneralPractitionerWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters,								// Keyword: POEIQS_Healthcare1_GeneralPractitionerWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters
		POEIQS_Healthcare2_MedicalSpecialistPharmacyEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters,						// Keyword: POEIQS_Healthcare2_MedicalSpecialistPharmacyEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters
		NUM_POEIQS
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Site1_4_2(){}

	Site1_4_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_POEIQS[NUM_POEIQS];					// XML:E

	Utilities::UsageType			m_usageType;
};

} // namespace DGNB

#endif // DGNB_Site1_4_2H
