#include "DGNB_Soc1_4_6.h"

namespace DGNB {
	
double DGNB::Soc1_4_6::score() {
	double soc1_4_6 = 0;
	switch (m_usageType) {
		case Utilities::UT_Residential:
			if (m_flag_SEDR[(SED_Residential)2].isEnabled())
				soc1_4_6 += 30;
			else if (m_flag_SEDR[(SED_Residential)1].isEnabled())
				soc1_4_6 += 15;
			else if (m_flag_SEDR[(SED_Residential)0].isEnabled())
				soc1_4_6 += 5;
			break;

		case Utilities::UT_Hotel:
		case Utilities::UT_Healthcare:
			if (m_flag_SEDHHC[(SED_HotelHealthcare)3].isEnabled())
				soc1_4_6 += 20;
			else if (m_flag_SEDHHC[(SED_HotelHealthcare)2].isEnabled())
				soc1_4_6 += 16;
			else if (m_flag_SEDHHC[(SED_HotelHealthcare)1].isEnabled())
				soc1_4_6 += 12;
			else if (m_flag_SEDHHC[(SED_HotelHealthcare)0].isEnabled())
				soc1_4_6 += 8;
			break;

		default:
			soc1_4_6 += 0;
			break;
	}

	return soc1_4_6;
} // Soc1.4.6

} // namespace DGNB
