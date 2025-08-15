#include "DGNB_Env2_3_2.h"

namespace DGNB {

double DGNB::Env2_3_2::score(){
	double env2_3_2 = 0;
	double env2_3_2_1DegreeOfSealing = m_para[(P_CurrentValue_env2_3_2ADDSAM_DegreeOfSealing)].get_value();

	if (m_flag_ADDSAM[(ADDSAM_ResultsSubmitted)].isEnabled()) {
		std::vector<double> xVal_2_3_2{50, 80};
		std::vector<double> yVal_2_3_2{20, 0};

		IBK::LinearSpline ls2_3_2_1_1;
		ls2_3_2_1_1.setValues(xVal_2_3_2, yVal_2_3_2);

		// assigning up to 20 points based on interpolation of degree of sealing
		env2_3_2 = ls2_3_2_1_1.value(env2_3_2_1DegreeOfSealing);
	}

	// assigning 10 points for implementation of adjustment measures
	env2_3_2 += (m_flag_ADDSAM[(AD_DegreeOfSealingAndAdjustmentMeasures)1].isEnabled() ? 10 : 0);

	// capping points at 20
	env2_3_2 = std::min<double>(20, env2_3_2);

	/*! Env2_3_2_2 Circular Economy Bonus - Unsealing */
	//assigning 10 bonus points for unsealing > 30% of area
	env2_3_2 += (m_flag_ADCEBU[(AD_CircularEconomyBonusUnsealing)0].isEnabled() ? 10 : 0);

	return env2_3_2;
}

double DGNB::Env2_3_2::scoreBonus(){
	double scoreBonusEnv2_3_2 = 0;

	/*! Env2_3_2_2 Circular Economy Bonus - Unsealing */
	//assigning 10 bonus points for unsealing > 30% of area
	scoreBonusEnv2_3_2 += (m_flag_ADCEBU[(AD_CircularEconomyBonusUnsealing)0].isEnabled() ? 10 : 0);

	return scoreBonusEnv2_3_2;
}   // Env2.3.2



} // namespace DGNB
