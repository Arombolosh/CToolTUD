#ifndef DGNB_Env2_4_6H
#define DGNB_Env2_4_6H
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Env2.4.6 preparative care and monitoring */
class Env2_4_6 {
	public:
	
	/*! Env2.4.6.1 Development and maintenance care contract */
	enum BDOS_PreparativeCareAndMonitoringDevelopmentAndMaintenanceCareContract {	// max +18 (+5, +3, +4, +2, +2, +2)
		BDOSPCMDMCC_ContractSubmitted,								// Keyword: BDOSPCMDMCC_ContractSubmitted
		BDOSPCMDMCC_EcologicalCarePlanSubmitted,					// Keyword: BDOSPCMDMCC_EcologicalCarePlanSubmitted
		BDOSPCMDMCC_NoUseOfTurfMaterials,							// Keyword: BDOSPCMDMCC_NoUseOfTurfMaterials
		BDOSPCMDMCC_NoUseOfHerbicidesOnSite,						// Keyword: BDOSPCMDMCC_NoUseOfHerbicidesOnSite
		BDOSPCMDMCC_NoUseOfBiocidesOnSite,							// Keyword: BDOSPCMDMCC_NoUseOfBiocidesOnSite
		BDOSPCMDMCC_NoUseOfChemicalFertiliserOnSite,				// Keyword: BDOSPCMDMCC_NoUseOfChemicalFertiliserOnSite
		NUM_BDOSPCMDMCC
	};

	/*! Env2.4.6.2 Monitoring and Success Control */
	enum BDOS_PreparativeCareAndMonitoringMonitoringAndSuccessControl {				// max +5
		BDOSPCMMSC_SimpleMonitoringOfNestingAids,					// Keyword: BDOSPCMMSC_SimpleMonitoringOfNestingAids
		BDOSPCMMSC_ExtensiveMonitoring,								// Keyword: BDOSPCMMSC_ExtensiveMonitoring
		NUM_BDOSPCMMSC
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env2_4_6(){}

	Env2_4_6(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_BDOSPCMDMCC[NUM_BDOSPCMDMCC];		// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_BDOSPCMMSC[NUM_BDOSPCMMSC];			// XML:E

	Utilities::UsageType			m_usageType;

};

} // namespace DGNB

#endif // Env2_4_6H
