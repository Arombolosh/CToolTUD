#include "DGNB_Soc1_4_5.h"

namespace DGNB {
	
double DGNB::Soc1_4_5::score() {
	double soc1_4_5 = 0;
	switch (m_usageType) {
		case Utilities::UT_Residential:
			soc1_4_5 += 0;
			break;

		case Utilities::UT_Logistics:
			soc1_4_5 += (m_flag_ALLC[(AL_LightingConcept)0].isEnabled() ? 10 : 0);
			soc1_4_5 += (m_flag_ALIPCOR[(AL_ImplementationOfPlannedConceptAndObservationOfRequirements)0].isEnabled() ? 5 : 0);
			soc1_4_5 += (m_flag_ALIPCOR[(AL_ImplementationOfPlannedConceptAndObservationOfRequirements)1].isEnabled() ? 10 : 0);
			soc1_4_5 += (m_flag_ALIPCOR[(AL_ImplementationOfPlannedConceptAndObservationOfRequirements)2].isEnabled() ? 5 : 0);
			break;

		case Utilities::UT_Production:
			soc1_4_5 += (m_flag_ALLC[(AL_LightingConcept)0].isEnabled() ? 10 : 0);
			soc1_4_5 += (m_flag_ALIPCOR[(AL_ImplementationOfPlannedConceptAndObservationOfRequirements)0].isEnabled() ? 10 : 0);
			soc1_4_5 += (m_flag_ALIPCOR[(AL_ImplementationOfPlannedConceptAndObservationOfRequirements)1].isEnabled() ? 15 : 0);
			soc1_4_5 += (m_flag_ALIPCOR[(AL_ImplementationOfPlannedConceptAndObservationOfRequirements)2].isEnabled() ? 5 : 0);
			break;
			
		default:
			soc1_4_5 += (m_flag_ALLC[(AL_LightingConcept)0].isEnabled() ? 5 : 0);
			soc1_4_5 += (m_flag_ALIPCOR[(AL_ImplementationOfPlannedConceptAndObservationOfRequirements)0].isEnabled() ? 5 : 0);
			soc1_4_5 += (m_flag_ALIPCOR[(AL_ImplementationOfPlannedConceptAndObservationOfRequirements)1].isEnabled() ? 5 : 0);
			soc1_4_5 += (m_flag_ALIPCOR[(AL_ImplementationOfPlannedConceptAndObservationOfRequirements)2].isEnabled() ? 5 : 0);
			break;
	}

	return soc1_4_5;
} // Soc1.4.5

} // namespace DGNB
