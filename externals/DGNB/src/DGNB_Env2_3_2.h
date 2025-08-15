#ifndef DGNB_Env2_3_2H
#define DGNB_Env2_3_2H
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Env2_3_2 degree of sealing and adjustment measures */
class Env2_3_2 {
	public:

	/*! Basic parameters. */
	enum para_t {
		/*! Env2_3_2ADDSAM_DegreeOfSealing*/
		P_CurrentValue_env2_3_2ADDSAM_DegreeOfSealing,					// Keyword: CurrentValue_env2_3_2ADDSAM_DegreeOfSealing		[---]	// ToDo Einheit % SO oder anders?
		NUM_P
	};
	
	/*! Env2_3_2_1 degree of sealing and adjustment measures */
	enum AD_DegreeOfSealingAndAdjustmentMeasures {					// max +20
		ADDSAM_ResultsSubmitted,									// Keyword: ADDSAM_ResultsSubmitted
		ADDSAM_ImplementationOfAdjustmentMeasures,					// Keyword: ADDSAM_ImplementationOfAdjustmentMeasures
		NUM_ADDSAM
	};

	/*! Env2_3_2_2 Circular Economy Bonus - Unsealing */
	enum AD_CircularEconomyBonusUnsealing {							// max +10
		ADCEBU_30PercentOfAreaUnsealedPreConstruction,				// Keyword: ADCEBU_30PercentOfAreaUnsealedPreConstruction
		NUM_ADCEBU
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env2_3_2(){}

	Env2_3_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag				m_flag_ADDSAM[NUM_ADDSAM];							// XML:E
	/*! List of flags. */
	IBK::Flag				m_flag_ADCEBU[NUM_ADCEBU];							// XML:E
	
	IBK::Parameter			m_para[NUM_P];										// XML:E

	Utilities::UsageType	m_usageType;

};

} // namespace DGNB

#endif // Env2_3_2H
