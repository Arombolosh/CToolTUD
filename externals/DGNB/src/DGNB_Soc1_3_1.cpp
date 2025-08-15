#include "DGNB_Soc1_3_1.h"

namespace DGNB {
	
double DGNB::Soc1_3_1::score() {
	double soc1_3_1 = 0;
	switch (m_usageType) {
		case Utilities::UT_Office:
			soc1_3_1 += (m_flag_ORSRO[(ORSR_Office)0].isEnabled() ? 10 : 0);
			soc1_3_1 += (m_flag_BAMOEHAHcR[(BAM_OfficeEducationHotelAssemblyHealthcareResidential)0].isEnabled() ? 30 : 0);
			break;
			
		case Utilities::UT_Hotel:
		case Utilities::UT_Assembly:
		case Utilities::UT_Healthcare:
			soc1_3_1 += (m_flag_ORSRHcHA[(ORSR_HealthcareHotelAssembly)0].isEnabled() ? 10 : 0);
			soc1_3_1 += (m_flag_BAMOEHAHcR[(BAM_OfficeEducationHotelAssemblyHealthcareResidential)0].isEnabled() ? 30 : 0);
			break;

		case Utilities::UT_Residential:
			if (m_flag_ORSRR[(ORSR_Residential)0].isEnabled()) {
				soc1_3_1 += 30;
				soc1_3_1 += (m_flag_ORSRR[(ORSR_Residential)1].isEnabled() ? 10 : 0);
			}
			soc1_3_1 += (m_flag_BAMOEHAHcR[(BAM_OfficeEducationHotelAssemblyHealthcareResidential)0].isEnabled() ? 50 : 0);
			break;
			
		case Utilities::UT_Education:
			soc1_3_1 += (m_flag_BAMOEHAHcR[(BAM_OfficeEducationHotelAssemblyHealthcareResidential)0].isEnabled() ? 30 : 0);
			break;

		default:
			soc1_3_1 += 0;
			break;
	}

	return soc1_3_1;
} // Soc1.3.1

} // namespace DGNB
