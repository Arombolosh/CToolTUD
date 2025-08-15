#ifndef DGNB_Env2_2_4H
#define DGNB_Env2_2_4H
#include "DGNB_Utilities.h"

namespace DGNB {
	
/*! Env 2.2.4 Integration into quarters' infrastructure */
class Env2_2_4 {
	public:
	
	/*! Env 2.2.4.1 Degree of Integration */
	enum DWDWWV_DegreeOfIntegrationIntoQuartersInfrastructure {		// max +4
		DWDWWVDIQI_DegreeOfIntegrationIntoPreexistingInfrastructureAndUseOfSeparationReductionEtc,		// Keyword: DWDWWVDIQI_DegreeOfIntegrationIntoPreexistingInfrastructureAndUseOfSeparationReductionEtc
		NUM_DWDWWVDIQI
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env2_2_4(){}

	Env2_2_4(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();



	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag				m_flag_DWDWWVDIQI[NUM_DWDWWVDIQI];					// XML:E

	Utilities::UsageType	m_usageType;

};

} // namespace DGNB

#endif // Env2_2_4H
