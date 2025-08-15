#include "DGNB_Soc1_4_4.h"

namespace DGNB {
	
double DGNB::Soc1_4_4::score() {
	double soc1_4_4 = 0;
	double currentSoc1_4_4_1DaylightGlareProbability = m_para[(P_CurrentValue_soc1_4_4_1DaylightGlareProbability)].get_value();

	switch (m_usageType) {
		case Utilities::UT_Office:
		case Utilities::UT_Education:
			if (m_flag_DGSOEA12Hc[(DGS_OfficeEducationAssembly1And2Healthcare)0].isEnabled()) {
				if (currentSoc1_4_4_1DaylightGlareProbability <= 0.35)
					soc1_4_4 += 20;
				else if (currentSoc1_4_4_1DaylightGlareProbability <= 0.4)
					soc1_4_4 += 15;
				else if (currentSoc1_4_4_1DaylightGlareProbability <= 0.45)
					soc1_4_4 += 10;
			}
			break;

		case Utilities::UT_Assembly:
			// assembly type 1
			if (m_flag_DGSOEA12Hc[(DGS_OfficeEducationAssembly1And2Healthcare)1].isEnabled()) {
				if (m_flag_DGSOEA12Hc[(DGS_OfficeEducationAssembly1And2Healthcare)0].isEnabled()) {
					if (currentSoc1_4_4_1DaylightGlareProbability <= 0.35)
						soc1_4_4 += 20;
					else if (currentSoc1_4_4_1DaylightGlareProbability <= 0.4)
						soc1_4_4 += 15;
					else if (currentSoc1_4_4_1DaylightGlareProbability <= 0.45)
						soc1_4_4 += 10;
				}
			} else
			// assembly type 2
			if (m_flag_DGSOEA12Hc[(DGS_OfficeEducationAssembly1And2Healthcare)2].isEnabled()) {
				if (m_flag_DGSOEA12Hc[(DGS_OfficeEducationAssembly1And2Healthcare)0].isEnabled()) {
					if (currentSoc1_4_4_1DaylightGlareProbability <= 0.35)
						soc1_4_4 += 20;
					else if (currentSoc1_4_4_1DaylightGlareProbability <= 0.4)
						soc1_4_4 += 15;
					else if (currentSoc1_4_4_1DaylightGlareProbability <= 0.45)
						soc1_4_4 += 10;
				} else if (m_flag_DGSOEA12Hc[(DGS_OfficeEducationAssembly1And2Healthcare)3].isEnabled() || m_flag_DGSOEA12Hc[(DGS_OfficeEducationAssembly1And2Healthcare)4].isEnabled())
					soc1_4_4 += 20;
			}
			break;

		case Utilities::UT_Healthcare:
			if (currentSoc1_4_4_1DaylightGlareProbability <= 0.35)
				soc1_4_4 += 10;
			else if (currentSoc1_4_4_1DaylightGlareProbability <= 0.4)
				soc1_4_4 += 8;
			else if (currentSoc1_4_4_1DaylightGlareProbability <= 0.45)
				soc1_4_4 += 6;
			break;

		case Utilities::UT_ConvenienceStore:
				soc1_4_4 += (m_flag_DGSCS[(DGS_ConvenienceStore)0].isEnabled() ? 12 : 0);
			break;

		case Utilities::UT_Logistics:
			if (m_flag_DGSL[(DGS_Logistics)2].isEnabled())
				soc1_4_4 += 20;
			else if (m_flag_DGSL[(DGS_Logistics)1].isEnabled())
				soc1_4_4 += 10;
			else if (m_flag_DGSL[(DGS_Logistics)0].isEnabled())
				soc1_4_4 += 5;
			break;

		case Utilities::UT_Production:
			soc1_4_4 += (m_flag_DGSP[(DGS_Production)0].isEnabled() || m_flag_DGSP[(DGS_Production)1].isEnabled() ? 30 : 0);
			break;

		default:
			soc1_4_4 += 0;
			break;
	}

	return soc1_4_4;
} // Soc1.4.4

} // namespace DGNB
