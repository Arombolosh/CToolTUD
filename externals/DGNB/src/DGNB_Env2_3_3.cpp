#include "DGNB_Env2_3_3.h"

namespace DGNB {

double DGNB::Env2_3_3::score(){
	double env2_3_3 = 0;

	/*! Env2_3_3_1 Soil restoration */
	if (m_flag_ADSQISR[(ADSQISR_HighContaminationDisposal)].isEnabled())
		env2_3_3 += 10;
	else if (m_flag_ADSQISR[(ADSQISR_LowContaminationRecyclingAndDisposal)].isEnabled())
		env2_3_3 += 5;
	else if (m_flag_ADSQISR[(ADSQISR_ExaminationOfSiteAndPreexistingBuildingForContamination)].isEnabled())
		env2_3_3 += 2;

	return env2_3_3;
} // Env2.3.3


double DGNB::Env2_3_3::scoreBonus(){
	double env2_3_3Bonus = 0;
	int adSQICEBISSRSCounter = 0;

	/*! Env2_3_3_2 Circular Economy Bonus In-Situ soil restoration and safeguarding */
	for(unsigned int i=0; i < NUM_ADSQICEBISSRS; ++i)
		adSQICEBISSRSCounter += (m_flag_ADSQICEBISSRS[(ADSQI_CircularEconomyBonusInSituSoilRestorationAndProtection)i].isEnabled() ? 1 : 0);

	env2_3_3Bonus += 5 * adSQICEBISSRSCounter;	 //assigning +5 bonus pts for every flag triggered for Circular Economy Bonus - In-Situ soil restoration and safeguarding

	return env2_3_3Bonus;
} // Env2.3.3 Bonus



} // namespace DGNB
