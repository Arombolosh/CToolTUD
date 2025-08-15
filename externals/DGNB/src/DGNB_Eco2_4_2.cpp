#include "DGNB_Eco2_4_2.h"

namespace DGNB {
	
double DGNB::Eco2_4_2::score() {
	double scoreEco2_4_2 = 0;
	int atpuspaifCounter = 0;
	// assigning 7.5 pts for Eco2.4.2.1
	scoreEco2_4_2 += (m_flag_ATPUSPR[(ATPUSPR_SameUsageType)].isEnabled() ? 7.5 : 0);
	// assigning 7.5 pts for Eco2.4.2.2
	scoreEco2_4_2 += (m_flag_ATPUSPR[(ATPUSPR_DifferentUsageType)].isEnabled() ? 7.5 : 0);

	for (unsigned int i = 0; i < (NUM_ATPUSPAIF); ++i)
		atpuspaifCounter += (m_flag_ATPUSPAIF[(ATPUS_ProofOfAdaptabilityOfIndividualFactors)i].isEnabled() ? 1 : 0);
	// only 20 pts possible for Eco2.4.2.3
	atpuspaifCounter = std::min<int>(4, atpuspaifCounter);
	// assigning up to 20 pts for Eco2.4.2.3
	scoreEco2_4_2 += atpuspaifCounter * 5;

	return scoreEco2_4_2;
}

} // namespace DGNB
