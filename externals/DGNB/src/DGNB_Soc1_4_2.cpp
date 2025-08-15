#include "DGNB_Soc1_4_2.h"

namespace DGNB {
	
double DGNB::Soc1_4_2::score() {
	double soc1_4_2 = 0;
	double currentSoc1_4_2UsageLighting = m_para[(P_CurrentValue_soc1_4_2UsageLighting)].get_value();
	double currentSoc1_4_2TranslucentCeilingLightPortion = m_para[(P_CurrentValue_soc1_4_2TranslucentCeilingLightPortion)].get_value();

	switch (m_usageType) {
		case Utilities::UT_Office:
		case Utilities::UT_Education:
			if (m_flag_ARULOEALHc[(ARUL_OfficeEducationAssemblyLogisticsHealthcare)0].isEnabled()) {
				if (currentSoc1_4_2UsageLighting >= 75)
					soc1_4_2 += 20;
				else if (currentSoc1_4_2UsageLighting >= 60)
					soc1_4_2 += 12;
				else if (currentSoc1_4_2UsageLighting >= 45)
					soc1_4_2 += 8;
			}
			break;

		case Utilities::UT_Assembly:
			// assembly type 1
			if (m_flag_ARULOEALHc[(ARUL_OfficeEducationAssemblyLogisticsHealthcare)2].isEnabled()) {
				if (m_flag_ARULOEALHc[(ARUL_OfficeEducationAssemblyLogisticsHealthcare)0].isEnabled()) {
					if (currentSoc1_4_2UsageLighting >= 75)
						soc1_4_2 += 20;
					else if (currentSoc1_4_2UsageLighting >= 60)
						soc1_4_2 += 12;
					else if (currentSoc1_4_2UsageLighting >= 45)
						soc1_4_2 += 8;
				}
			} else
			// assembly type 2
			if (m_flag_ARULOEALHc[(ARUL_OfficeEducationAssemblyLogisticsHealthcare)3].isEnabled()) {
				if (m_flag_ARULOEALHc[(ARUL_OfficeEducationAssemblyLogisticsHealthcare)1].isEnabled()) {
					if (currentSoc1_4_2TranslucentCeilingLightPortion >= 4)
						soc1_4_2 += 20;
					else if (currentSoc1_4_2TranslucentCeilingLightPortion >= 2)
						soc1_4_2 += 15;
					else if (currentSoc1_4_2TranslucentCeilingLightPortion >= 0.5)
						soc1_4_2 += 8;
				}
			}
			break;
			
		case Utilities::UT_Healthcare:
			if (m_flag_ARULOEALHc[(ARUL_OfficeEducationAssemblyLogisticsHealthcare)0].isEnabled()) {
				if (currentSoc1_4_2UsageLighting >= 75)
					soc1_4_2 += 15;
				else if (currentSoc1_4_2UsageLighting >= 60)
					soc1_4_2 += 10;
				else if (currentSoc1_4_2UsageLighting >= 45)
					soc1_4_2 += 6;
			}
			break;
			
		case Utilities::UT_Logistics:
			if (m_flag_ARULOEALHc[(ARUL_OfficeEducationAssemblyLogisticsHealthcare)0].isEnabled()) {
				if (currentSoc1_4_2UsageLighting >= 75)
					soc1_4_2 += 15;
				else if (currentSoc1_4_2UsageLighting >= 60)
					soc1_4_2 += 10;
				else if (currentSoc1_4_2UsageLighting >= 45)
					soc1_4_2 += 6;
			}
			if (m_flag_ARULOEALHc[(ARUL_OfficeEducationAssemblyLogisticsHealthcare)3].isEnabled()) {
				if (m_flag_ARULOEALHc[(ARUL_OfficeEducationAssemblyLogisticsHealthcare)1].isEnabled()) {
					if (currentSoc1_4_2TranslucentCeilingLightPortion >= 4)
						soc1_4_2 += 15;
					else if (currentSoc1_4_2TranslucentCeilingLightPortion >= 2)
						soc1_4_2 += 9;
					else if (currentSoc1_4_2TranslucentCeilingLightPortion >= 0.5)
						soc1_4_2 += 6;
				}
			}
			break;
			
		default:
			soc1_4_2 += 0;
			break;
	}

	return soc1_4_2;
} // Soc1.4.2

} // namespace DGNB
