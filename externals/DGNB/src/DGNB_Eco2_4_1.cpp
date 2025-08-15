#include "DGNB_Eco2_4_1.h"

namespace DGNB {
	
double DGNB::Eco2_4_1::score() {
	double scoreEco2_4_1 = 0;
	int asbcsaCounter = 0, asbhcbcsCounter = 0;

	// any usageType but healthcare
	if (m_usageType != Utilities::UT_Healthcare) {
		for (unsigned int i = 0; i < NUM_ASBCSA; ++i)
			asbcsaCounter += (m_flag_ASBCSA[(ASBC_SiteAnalysis)i].isEnabled() ? 1 : 0);

		// assigning +10 pts for Eco2.4.1.1
		if (asbcsaCounter > 2)
				scoreEco2_4_1 += 10;

		// assigning individual pts for Eco2.4.1.2
		scoreEco2_4_1 += (m_flag_ASBCBCS[(ASBC_BuildingConceptAndSynergies)0].isEnabled() ? 5 : 0);
		scoreEco2_4_1 += (m_flag_ASBCBCS[(ASBC_BuildingConceptAndSynergies)1].isEnabled() ? 10 : 0);
	}

	// only usageType healthcare
	if (m_usageType == Utilities::UT_Healthcare) {
		// assigning +15 pts for Eco2.4.1.2b.1
		scoreEco2_4_1 += (m_flag_ASBCHCBCS[(ASBC_HealthcareBuildingConceptAndSynergies)0].isEnabled() ? 15 : 0);
		for (unsigned int i = 1; i < (NUM_ASBCHCBCS -1); ++i)
			asbhcbcsCounter += (m_flag_ASBCHCBCS[(ASBC_HealthcareBuildingConceptAndSynergies)i].isEnabled() ? 1 : 0);
		// assigning +10 pts for Eco2.4.1.2b.2
		if (asbhcbcsCounter > 4)
				scoreEco2_4_1 += 10;
		// assigning +10 pts for Eco2.4.1.2b.3
		scoreEco2_4_1 += (m_flag_ASBCHCBCS[(ASBC_HealthcareBuildingConceptAndSynergies)6].isEnabled() ? 10 : 0);
	}
	return scoreEco2_4_1;
}

} // namespace DGNB
