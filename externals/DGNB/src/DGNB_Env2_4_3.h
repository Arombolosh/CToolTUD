#ifndef DGNB_Env2_4_3H
#define DGNB_Env2_4_3H
#include "DGNB_Utilities.h"

namespace DGNB {
	
/*! Env2.4.3 vegetation */
class Env2_4_3 {
	public:

	/*! Basic parameters. */
	enum para_t {
		/*! BDOSVEDLSSS_SelectionIsLocalDiverseAndSuitedToSitePointResult */
		P_CurrentValue_env2_4_3BDOSVEDLSSS_SelectionIsLocalDiverseAndSuitedToSitePointResult,	// Keyword: CurrentValue_env2_4_3BDOSVEDLSSS_SelectionIsLocalDiverseAndSuitedToSitePointResult		[-]
		NUM_P
	};
	
	/*! Env2.4.3.1 no employment of invasive plant species */
	enum BDOS_VegetationNoEmploymentOfInvasivePlantSpecies {									// max +7
		BDOSVNEIPS_NoFurtherEmploymentOfInvasivePlantSpecies,									// Keyword: BDOSVNEIPS_NoFurtherEmploymentOfInvasivePlantSpecies
		BDOSVNEIPS_PlanForControlOfPreexistingInvasiveSpecies,									// Keyword: BDOSVNEIPS_PlanForControlOfPreexistingInvasiveSpecies
		NUM_BDOSVNEIPS
	};

	/*! Env2.4.3.2 Employment of diverse local species suited to site */
	enum BDOS_VegetationEmploymentOfDiverseLocalSpeciesSuitedToSite {							// max +20	(+8, +1-20)
		BDOSVEDLSSS_SelectionBasedOnBiodiversitySupportingConcept,								// Keyword: BDOSVEDLSSS_SelectionBasedOnBiodiversitySupportingConcept
		BDOSVEDLSSS_ResultSubmitted,															// Keyword: BDOSVEDLSSS_ResultSubmitted
		NUM_BDOSVEDLSSS
	};

	/*! Agenda 2030 Bonus Preservation of vegetation with high ecological value */
	enum BDOS_VegetationAgenda2030BonusPreservationOfVegetationWithHighEcologicalValue {		// max +5
		BDOSVA2030PVHEV_PreservationOfSaidVegetationDuringConstructionAndAfter,					// Keyword: BDOSVA2030PVHEV_PreservationOfSaidVegetationDuringConstructionAndAfter
		NUM_BDOSVA2030PVHEV
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env2_4_3(){}

	Env2_4_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_BDOSVNEIPS[NUM_BDOSVNEIPS];							// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_BDOSVEDLSSS[NUM_BDOSVEDLSSS];						// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_BDOSVA2030PVHEV[NUM_BDOSVA2030PVHEV];				// XML:E

	IBK::Parameter					m_para[NUM_P];												// XML:E
	
	Utilities::UsageType			m_usageType;

};

} // namespace DGNB

#endif // Env2_4_3H
