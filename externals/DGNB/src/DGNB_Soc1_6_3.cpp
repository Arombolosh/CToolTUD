#include "DGNB_Soc1_6_3.h"

namespace DGNB {
	
double DGNB::Soc1_6_3::score() {
	double soc1_6_3 = 0;
	int fcefosoCounter = 0, fcefosoHotelCounter = 0;

	for (unsigned int i = 0; i<(NUM_FCEFOSO-4); ++i)
		fcefosoCounter += (m_flag_FCEFOSO[(FCEF_OnSiteOffers)i].isEnabled() ? 1 : 0);

	fcefosoCounter += (m_flag_FCEFOSO[(FCEF_OnSiteOffers)9].isEnabled() ? m_para[(P_Soc1_6_3_1AlternativeInnovativeSolutions)].get_value() : 0);

	switch (m_usageType) {

		case Utilities::UT_Hotel:
			for (unsigned int j = (NUM_FCEFOSO-4); j < (NUM_FCEFOSO-1); ++j)
				fcefosoCounter += (m_flag_FCEFOSO[(FCEF_OnSiteOffers)j].isEnabled() ? 1 : 0);
			soc1_6_3 += 5*fcefosoCounter;
			soc1_6_3 += ((fcefosoHotelCounter > 2) ? 5 : 0);
			soc1_6_3 = std::min<double>(20, soc1_6_3);
			break;

		default:
			soc1_6_3 += 5*fcefosoCounter;
			soc1_6_3 = std::min<double>(20, soc1_6_3);
			break;
	}

	return soc1_6_3;
} // Soc1.6.3

} // namespace DGNB
