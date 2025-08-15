#ifndef DGNB_Env2_4_2H
#define DGNB_Env2_4_2H
#include "DGNB_Utilities.h"

namespace DGNB {
	
/*! Env2.4.2 biotope */
class Env2_4_2 {
	public:

	/*! Basic parameters. */
	enum para_t {
		/*! BDOSBBSA_PercentageOfBiodiversitySupportingOutdoorArea */
		P_CurrentValue_env2_4_2BDOSBBSA_PercentageOfBiodiversitySupportingOutdoorArea,	// Keyword: CurrentValue_env2_4_2BDOSBBSA_PercentageOfBiodiversitySupportingOutdoorArea		[---]	// ToDo Einheit % SO oder anders?
		/*! BDOSBGR_PercentageOfGreenRoof */
		P_CurrentValue_env2_4_2BDOSBGR_PercentageOfGreenRoof,							// Keyword: CurrentValue_env2_4_2BDOSBGR_PercentageOfGreenRoof								[---]	// ToDo Einheit % SO oder anders?
		/*! BDOSBAFA2030VB_BFFOfSite */
		P_CurrentValue_env2_4_2BDOSBAFA2030VB_BFFOfSite,								// Keyword: CurrentValue_env2_4_2BDOSBAFA2030VB_BFFOfSite									[-]
		NUM_P
	};

	/*! Env2.4.2.1 biodiversity-supporting area */
	enum BDOS_BiotopeBiotopeSupportingArea {						// max +40
		/*! 40% = 15 pts, 100 % = 20 pts, interpolation possible
			so, still 15 pts if less than 40% are supportive or just none at all? Feeling inclined to assign none at all. */
		BDOSBBSA_ResultsSubmitted,									// Keyword: BDOSBBSA_ResultsSubmitted
		NUM_BDOSBBSA
	};

	/*! Env2.4.2.2 green roof */
	enum BDOS_BiotopeGreenRoof {									// max +7: +5 for 50%, +7 for 70% interpolation possible
		BDOSBGR_ResultsSubmitted,									// Keyword: BDOSBGR_ResultsSubmitted
		NUM_BDOSBGR
	};

	// including Env2.4.2.4 in 2.4.2.3 because the latter results from an overfulfillment of the latter
	/*! Env2.4.2.3 biotope area factor BFF & Env2.4.2.4 Agenda 2030 Bonus - vegetated building */
	enum BDOS_BiotopeAreaFactorAndAgenda2030VegetatedBuilding {		// max +20 and +5 for Agenda 2030
		BDOSBAFA2030VB_ResultsSubmitted,							// Keyword: BDOSBAFA2030VB_ResultsSubmitted
		NUM_BDOSBAFA2030VB
	};

	/*! Env2.4.2.5 Diversity of structures as biotope for flora and fauna */
	enum BDOS_DiversityOfStructures {												// max +7 (+5, +2)
		BDOSDS_StructureTypesEmbeddedInBiodiversitySupportingConcept,				// Keyword:BDOSDS_StructureTypesEmbeddedInBiodiversitySupportingConcept
		BDOSDS_TwoBiotopeStructureTypesAvailable,									// Keyword:BDOSDS_TwoBiotopeStructureTypesAvailable
		NUM_BDOSDS
	};

	/*! Env2.4.2.6 Agenda 2030 Bonus - Fertile Soil */
	enum BDOS_Agenda2030BonusFertileSoil {															// max +5
		BDOSA2030FS_EmploymentOfSOTAMethodsForImprovementOfSoilQualityAndCultivationOfHumus,		// Keyword: BDOSA2030FS_EmploymentOfSOTAMethodsForImprovementOfSoilQualityAndCultivationOfHumus
		NUM_BDOSA2030FS
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env2_4_2(){}

	Env2_4_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_BDOSBBSA[NUM_BDOSBBSA];									// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_BDOSBGR[NUM_BDOSBGR];									// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_BDOSBAFA2030VB[NUM_BDOSBAFA2030VB];						// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_BDOSDS[NUM_BDOSDS];										// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_BDOSA2030FS[NUM_BDOSA2030FS];							// XML:E
	
	IBK::Parameter					m_para[NUM_P];													// XML:E

	Utilities::UsageType			m_usageType;

};

} // namespace DGNB

#endif // Env2_4_2H
