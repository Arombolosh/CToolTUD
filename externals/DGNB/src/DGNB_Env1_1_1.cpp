#include "DGNB_Env1_1_1.h"

namespace DGNB {

double DGNB::Env1_1_1::score() {
	double env1_1_1 = 0;
	int esOECounter = 0, esFVCounter = 0, psOECounter = 0, psFVCounter = 0, psEOCounter = 0;

	/*! Env1.1.1.1.1a */
	// we need minimum 2 elements to get 5 points
	for(unsigned int i=0; i<NUM_CO2ESOE; ++i)
		esOECounter += (m_flag_ESOE[(CO2EarlyStage_OperatingEvaluation)i].isEnabled() ? 1 : 0);

	/*! Env1.1.1.1.1b */
	// we need minimum 3 elements to get 5 points
	for(unsigned int i=0; i<NUM_CO2ESFV; ++i)
		esFVCounter += (m_flag_ESFV[(CO2EarlyStage_FurtherVariants)i].isEnabled() ? 1 : 0);

	/*! Env 1.1.1.1.2a */
	// we need minimum 2 elements to get 5 points
	for(unsigned int i=0; i<NUM_CO2PSOE; ++i)
		psOECounter += (m_flag_PSOE[(CO2PlanningStage_OperatingEvaluation)i].isEnabled() ? 1 : 0);

	/*! Env 1.1.1.1.2b */
	// we need minimum 3 elements to get 5 points
	for(unsigned int i=0; i<NUM_CO2PSFV; ++i)
		psFVCounter += (m_flag_PSFV[(CO2PlanningStage_FurtherVariants)i].isEnabled() ? 1 : 0);

	/*! Env 1.1.1.1.2c */
	// needs to be fulfilled fpr 2.5 points
	for(unsigned int i=0; i<NUM_CO2PSEO; ++i)
		psEOCounter += (m_flag_PSEO[(CO2PlanningStage_EmissionOptimization)i].isEnabled() ? 1 : 0);

	// 1.1.1 Lebenszyklus-CO2-Bilanz in frühen Projektphasen:
	if (esOECounter > 1)		  // points for ENV 1.1.1.1.1 a
		env1_1_1 += 5;

	if (esFVCounter > 2)		  // points for ENV 1.1.1.1.1 b
		env1_1_1 += 5;

	// 1.1.2 Lebenszyklus-CO2-Bilanz in Genehmigungs- und Ausführungsplanung:
	if (psOECounter > 1)		  // points for ENV 1.1.1.1.2 a
		env1_1_1 += 5;

	if (psFVCounter > 2)		  // points for ENV 1.1.1.1.2 b
		env1_1_1 += 5;

	if (psEOCounter > 0)		  // points for ENV 1.1.1.1.2 c
		env1_1_1 += 2.5;

	// Capping at 10
	env1_1_1 = std::min<double>(10, env1_1_1);		// capping points for ENV 1.1.1 at 10

	return env1_1_1;
}   // Env1.1.1

double DGNB::Env1_1_1::scoreBonus(){
	double env1_1_1Bonus = 0;

	// Agenda 2030 Bonus
	/*! Env 1.1.1.2.1 */
	// needs to be fulfilled for 5 BONUS points
	env1_1_1Bonus += (m_flag_A2030IPB[(CO2A2030IPB_IntegrationOfPreexistingBuilding)].isEnabled() ? 5 : 0);

	/*! Env 1.1.1.2.2a */
	// needs to be fulfilled for 2.5 BONUS points
	env1_1_1Bonus += (m_flag_A2030MO[(CO2A2030MO_ForEmission)].isEnabled() ? 2.5 : 0);


	return env1_1_1Bonus;
}   // Env1.1.1 Bonus



} // namespace DGNB
