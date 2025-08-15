#include "DGNB_Env1_1_2.h"

namespace DGNB {

double DGNB::Env1_1_2::score() {
	double env1_1_2 = 0;
	int lcCO2DiscCounter = 0;
	double ref1_1_2_2_1 = m_para[(P_RefEnv1_1_2_2_1)].get_value();
	double ref1_1_2_5_1 = m_para[(P_RefEnv1_1_2_5_1)].get_value();
	double current1_1_2_2_1 = m_para[(P_CurrentValueEnv1_1_2_2_1)].get_value();
	double current1_1_2_5_1 = m_para[(P_CurrentValueEnv1_1_2_5_1)].get_value();

	// ENV1.1.2.1.1
	/*! ENV1.1.2.1.1 Disclosure of Life Cycle Balances for CO2 and non-renewable primary energy */
	for(unsigned int i=0; i<NUM_LCCO2DISC; ++i)
		lcCO2DiscCounter += (m_flag_LCCO2DISC[(LCCO2_DisclosureOfLifeCycleBalances)i].isEnabled() ? 1 : 0);

	/*! 2.1.1 Disclosure of Life Cycle Balances for CO2 and non-renewable primary energy */
	if (lcCO2DiscCounter == 2)			 // +5 points for ENV 1.1 2.1.1 a
		env1_1_2 += 5;

	// ENV1.1.2.2.1
	/*! ENV1.1.2.2.1 Life cycle balance framework: evaluation of life cycle CO2 balance of the finished building */
	if (m_flag_LCCO2IER[(LCCO2IER_ResultsSubmitted)].isEnabled()) {
		// referenceValue1_1_2_2_1
		std::vector<double> xVal_2_2_1{ 0.5 * ref1_1_2_2_1, 0.75 * ref1_1_2_2_1, ref1_1_2_2_1, 2.25 * ref1_1_2_2_1};
		std::vector<double> yVal_2_2_1{ 70, 60, 50, 0};
		IBK::LinearSpline ls_2_2_1;
		ls_2_2_1.setValues(xVal_2_2_1, yVal_2_2_1);

		double env1_1_2_2_1InterpolatedBalance = ls_2_2_1.value( current1_1_2_2_1 );

		/*! ENV1.1.2.2.1 Life cycle balance framework: evaluation of life cycle CO2 balance of the finished building */
		env1_1_2 += env1_1_2_2_1InterpolatedBalance;		// points for ENV1.1 2.2.1 interpolated based on relation of evaluation result and reference value
	}

	// ENV1.1.2.4.1
	/*! ENV1.1 2.4.1 balance framework operation: climate protection agenda and net neutral greenhouse gas operation */
	if (m_flag_LCCO2BFO[LCCO2BFO_NetGreenhouseHeutrallyClimateNeutrallyOperatedBuilding].isEnabled())
		env1_1_2 += 15;
	else if (m_flag_LCCO2BFO[LCCO2BFO_AmbitiousClimateProtectionAgenda].isEnabled())
		env1_1_2 += 10;
	else if (m_flag_LCCO2BFO[LCCO2BFO_ClimateProtectionAgendaClimateNeutralOperation].isEnabled())
		env1_1_2 += 5;

	// ENV1.1.2.5.1
	/*! ENV1.1 2.5.1 balance framework structure: CO2 reduced structure -> CO2 reduced construction phase */
	if (m_flag_LCCO2BFSCO2RCP[(LCCO2BFSCO2RCP_ResultsSubmitted)].isEnabled()) {
		std::vector<double> xVal_2_5_1{0.5*ref1_1_2_5_1, 0.75*ref1_1_2_5_1, ref1_1_2_5_1, 2.25*ref1_1_2_5_1};	   // -> multiplicators for reference value likely missing in DGNB file
		std::vector<double> yVal_2_5_1{ 20, 10, 5, 0};

		IBK::LinearSpline ls_2_5_1;
		ls_2_5_1.setValues(xVal_2_5_1, yVal_2_5_1);
		double env1_1_2_5_1InterpolatedBalance = ls_2_5_1.value((current1_1_2_5_1));

		/*! ENV1.1.2.5.1 balance framework structure: CO2 reduced structure -> CO2 reduced construction phase */
		env1_1_2 += env1_1_2_5_1InterpolatedBalance;
	}
	// Capping at 100
	env1_1_2 = std::min<double>(100, env1_1_2);   // capping points for ENV 1.1.2 at 100

	return env1_1_2;
}   // Env1.1.2

double DGNB::Env1_1_2::scoreBonus() {
	double env1_1_2Bonus = 0;

	/*! Agenda2030 Bonus */
	// ENV1.1 2.3 Agenda 2030
	/*! ENV1.1 2.3 Agenda 2030 Disclosure of Life Cycle Balances for CO2 and non-renewable primary energy */
	/*! ENV1.1 2.3.1 all necessary data provided in ENV1.1 2.2.1 */

	/*! ENV1.1.2.3.1 */
	if (m_flag_LCCO2IER[(LCCO2IER_ResultsSubmitted)].isEnabled())
		// +5 bonus points of Results of life cycle balance <= reference value, ENV1.1 2.3.1
		env1_1_2Bonus += (m_para[P_CurrentValueEnv1_1_2_2_1].get_value() <= 0.5 * m_para[P_RefEnv1_1_2_2_1].get_value() ? 5 : 0);

	/*! ENV1.1 2.3.2 Life cycle climate protection agenda - climate neutral building*/
	env1_1_2Bonus += (m_flag_LCCO2A2030LCCPA[(LCCO2A2030LCCPA_AgendaSubmitted)].isEnabled() ? 10 : 0);

	/*! ENV1.1 2.3.3 climate protection through sufficiency*/
	env1_1_2Bonus += (m_flag_LCCO2A2030CPTS[(LCCO2A2030CPTS_AgendaSubmitted)].isEnabled() ? 5 : 0);

	/*! ENV1.1.2.5.2 Agenda 2030 Bonus */
	if (m_flag_LCCO2BFSCO2RCP[(LCCO2BFSCO2RCP_ResultsSubmitted)].isEnabled())
		env1_1_2Bonus += ((m_para[P_CurrentValueEnv1_1_2_5_1].get_value() <= 0.5* m_para[P_RefEnv1_1_2_5_1].get_value()) ? 2.5 : 0); // +5 bonus points of Results of life cycle balance <= reference value, ENV1.1 2.3.1


	return env1_1_2Bonus;

}   // Env1.1.2 Agenda 2030 Bonus

bool DGNB::Env1_1_2::minimumRequirementsMet() {
	bool env1_1_2MinimumRequirementsMet = false;
	int minReqMetCounter = 0;

	minReqMetCounter += (m_flag_LCCO2DISC[(LCCO2Disc_GreenHouseGasBalance)].isEnabled() ? 1 : 0);
	minReqMetCounter += (m_flag_LCCO2DISC[(LCCO2Disc_NonRenewablePrimaryEnergyBalance)].isEnabled() ? 1 : 0);
	minReqMetCounter += (m_flag_LCCO2DISC[(LCCO2BFO_ClimateProtectionAgendaClimateNeutralOperation)].isEnabled() ? 1 : 0 );

	env1_1_2MinimumRequirementsMet = (minReqMetCounter == 3 ? true : false);

	return env1_1_2MinimumRequirementsMet;
}

bool DGNB::Env1_1_2::platinumRequirementsMet() {
	bool env1_1_2PlatinumRequirementsMet = false;

	env1_1_2PlatinumRequirementsMet = (m_flag_LCCO2DISC[(LCCO2BFO_AmbitiousClimateProtectionAgenda)].isEnabled() ? true : false);

	return env1_1_2PlatinumRequirementsMet;
}

} // namespace DGNB
