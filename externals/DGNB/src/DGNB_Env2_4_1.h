#ifndef DGNB_Env2_4_1H
#define DGNB_Env2_4_1H
#include "DGNB_Utilities.h"

namespace DGNB {
	
/*! Env2.4.1 biodiversity strategy */
class Env2_4_1 {
	public:
	
	/*! compilation and execution of biodiversity strategy */
	enum BDOS_CompilationAndExecutionOfBiodiversityStrategy {	// +20 pts
		BDOSCEBDS_ExtensiveAndLongTermStrategy,					// Keyword: BDOSCEBDS_ExtensiveAndLongTermStrategy
		NUM_BDOSCEBDS
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env2_4_1(){}

	Env2_4_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag			m_flag_BDOSCEBDS[NUM_BDOSCEBDS];			// XML:E

	Utilities::UsageType	m_usageType;

};

} // namespace DGNB

#endif // Env2_4_1H
