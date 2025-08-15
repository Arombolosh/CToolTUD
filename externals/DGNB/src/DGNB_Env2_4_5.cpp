#include "DGNB_Env2_4_5.h"

namespace DGNB {

double DGNB::Env2_4_5::score() {
	double env2_4_5 = 0;
	int bdosRNIICCounter = 0;

	for (unsigned int i = 0; i < NUM_BDOSRNIIC; ++i)
		bdosRNIICCounter += (m_flag_BDOSRNIIC[(BDOS_ReductionOfNegativeInfluencesIlluminationConcept)i].isEnabled() ? 1 : 0);

	// summing up points
	// Env2.4.5.1
	env2_4_5 += std::min<double>(9, bdosRNIICCounter*3);

	// Env2.4.5.2
	env2_4_5 += (m_flag_BDOSRNIIC[(BDOS_ReductionOfNegativeInfluencesAnimalTraps)0].isEnabled() ? 5 : 0);

	// Env2.4.5.3
	env2_4_5 += (m_flag_BDOSRNIIC[(BDOS_ReductionOfNegativeInfluencesConstructionSitePlan)0].isEnabled() ? 5 : 0);

	return env2_4_5;
}



} // namespace DGNB
