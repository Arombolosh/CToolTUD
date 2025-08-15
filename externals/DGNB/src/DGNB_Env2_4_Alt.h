#ifndef DGNB_Env2_4_AltH
#define DGNB_Env2_4_AltH
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Env2.4 Innovation: Alternative Certification */
class Env2_4_Alt {
	public:
	
	enum BDOS_AlternativeCertification {							// alternative 100 pts
		BDOSAC_AlternativeCertificationSubmitted,					// Keyword: BDOSAC_AlternativeCertificationSubmitted
		NUM_BDOSAC
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env2_4_Alt(){}

	Env2_4_Alt(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_BDOSAC[NUM_BDOSAC];		// XML:E

	Utilities::UsageType			m_usageType;

};

} // namespace DGNB

#endif // Env2_4_AltH
