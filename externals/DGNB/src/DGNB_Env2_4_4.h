#ifndef DGNB_Env2_4_4H
#define DGNB_Env2_4_4H
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Env2.4.4 Relation to Surroundings */
class Env2_4_4 {
	public:
	
	/*! Env2.4.4.1 measures taken for biotope interconnectivity */
	enum BDOS_RelationToSurroundingsBiotopeInterconnectivity{					// +7
		BDOSRSBI_ConceptDeveloped,												// Keyword: BDOSRSBI_ConceptDeveloped
		NUM_BDOSRSBI
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env2_4_4(){}

	Env2_4_4(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_BDOSRSBI[NUM_BDOSRSBI];				// XML:E

	Utilities::UsageType			m_usageType;

};

} // namespace DGNB

#endif // Env2_4_4H
