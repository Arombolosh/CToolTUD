#include "DGNB_Tec1_4_4.h"

namespace DGNB {
	
double DGNB::Tec1_4_4::score() {
	double tec1_4_4 = 0, tec1_4_4_2 = 0;

	if (m_flag_ISSU[(ISSU_OpenAndStandardizedProtocolsInExistingNetworks)].isEnabled())
		tec1_4_4 += 5;
	else if (m_flag_ISSU[(ISSU_PlanningAndImplementationAccordingToDIN_EN_ISO_16484_1)].isEnabled())
		tec1_4_4 += 0;
	
	
	for (unsigned int i = 0; i < NUM_ISIFSS; ++i)
		tec1_4_4_2 += (m_flag_ISIFSS[(IS_IntegratedFunctionsInSuperordinateSystems)i].isEnabled() ? 2 : 0);
	
	tec1_4_4_2 = std::min<double>(10, tec1_4_4_2);
	
	tec1_4_4 += tec1_4_4_2;
	
	return tec1_4_4;
}

double DGNB::Tec1_4_4::scoreBonus() {
	double tec1_4_4Bonus = 0;
	int	ispitsmqdsCounter = 0;
	
	for (unsigned int i = 0; i < NUM_ISPITSMQDS; ++i)
		ispitsmqdsCounter += (m_flag_ISPITSMQDS[(IS_PlanningOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings)i].isEnabled() ? 1 : 0);
	
	//assigning 5 bonus pts for Tec1.4.4.3.1
	tec1_4_4Bonus += ((ispitsmqdsCounter > 2) ? 5 : 0);
	//assigning 5 bonus pts for Tec1.4.4.3.2
	tec1_4_4Bonus +=  (m_flag_ISIITSMQDS[(ISIITSMQDS_ImplementationWithTheGoalOfSynergisticUseInRelationToQuarterAndDirectSurroundings)].isEnabled() ? 5 : 0);
	//assigning 10 bonus pts for Tec1.4.4.4.1
	tec1_4_4Bonus +=  ((m_flag_ISIEIQDSQS[(ISIEIQDSQS_BuildingUsesEnergyFromNearbyQuartersOrDirectSurroundingsToFulfillEnergyDemand)].isEnabled() || m_flag_ISIEIQDSQS[(ISIEIQDSQS_BuildingUsesEnergyFromNearbyQuartersOrDirectSurroundingsToFulfillEnergyDemand)].isEnabled()) ? 10 : 0);
	//assigning 10 bonus pts for Tec1.4.4.4.1
	tec1_4_4Bonus +=  ((m_flag_ISIITSMQNES[(ISIITSMQNES_BuildingProvidesRelevantStorageCapacity)].isEnabled() || m_flag_ISIITSMQNES[(ISIITSMQNES_BuildingUsesExistingIntegratedEnergyAndLoadManagement)].isEnabled()) ? 10 : 0);
	
	
	
	return tec1_4_4Bonus;
} // Tec1.4.4

} // namespace DGNB
