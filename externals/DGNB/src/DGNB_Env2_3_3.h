#ifndef DGNB_Env2_3_3H
#define DGNB_Env2_3_3H
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Env2_3_3 Soil quality intensification */
class Env2_3_3 {
	public:
	
	/*! Env2_3_3_1 Soil restoration */
	enum ADSQI_SoilRestoration {															// max +10
		ADSQISR_ExaminationOfSiteAndPreexistingBuildingForContamination,					// Keyword: ADSQISR_ExaminationOfSiteAndPreexistingBuildingForContamination
		ADSQISR_LowContaminationRecyclingAndDisposal,										// Keyword: ADSQISR_LowContaminationRecyclingAndDisposal
		ADSQISR_HighContaminationDisposal,													// Keyword: ADSQISR_HighContaminationDisposal
		NUM_ADSQISR
	};

	/*! Env2_3_3_2 Circular Economy Bonus In-Situ soil restoration and safeguarding */
	enum ADSQI_CircularEconomyBonusInSituSoilRestorationAndProtection {						// max +15
		ADSQICEBISSRS_InSituRestorationChemicalOrBiologicalNoSoilExchange,					// Keyword: ADSQICEBISSRS_InSituRestorationChemicalOrBiologicalNoSoilExchange
		ADSQICEBISSRS_LowDegreeOfTransformationOfSoilAndSafeguardingOfContaminants,			// Keyword: ADSQICEBISSRS_LowDegreeOfTransformationOfSoilAndSafeguardingOfContaminants
		ADSQICEBISSRS_RestorationOfGroundWaterDamages,										// Keyword: ADSQICEBISSRS_RestorationOfGroundWaterDamages
		NUM_ADSQICEBISSRS
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env2_3_3(){}

	Env2_3_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag				m_flag_ADSQISR[NUM_ADSQISR];						// XML:E
	/*! List of flags. */
	IBK::Flag				m_flag_ADSQICEBISSRS[NUM_ADSQICEBISSRS];			// XML:E

	Utilities::UsageType	m_usageType;

};

} // namespace DGNB

#endif // Env2_3_3H
