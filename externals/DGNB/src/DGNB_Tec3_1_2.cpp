#include "DGNB_Tec3_1_2.h"

namespace DGNB {
	
double DGNB::Tec3_1_2::score() {
	double tec3_1_2 = 0, tec3_1_2_3 = 0;
	
	tec3_1_2 += (m_flag_IPI[(IPI_TransparentSafeAndBarrierFreeRoutingVisibleAndComprehensiveSignage)].isEnabled() ? 7.5 : 0);
	tec3_1_2 += (m_flag_IPI[(IPI_DesignatedParkingSpotsForMobilityAidsLikeWalkersOrStrollers)].isEnabled() ? 7.5 : 0);
	
	tec3_1_2 += (m_flag_IBI[(IBI_AtLeast80PerceptOfBicycleParkingSpotsAreClearlyRelatedToTheBuildingNearTheEntranceAccessibleAndHaveProtectionAgainstTheft)].isEnabled() ? 7.5 : 0);
	tec3_1_2 += (m_flag_IBI[(IBI_Residential100PercentAllOthers80PercentOfParkingSpotsAreEquippedWithWeatherProtection)].isEnabled() ? 7.5 : 0);
	tec3_1_2 += (m_flag_IBI[(IBI_SufficientNumberOfParkingSpotsForCargoBikesWithTheftProtection)].isEnabled() ? 5 : 0);
	
	if (m_flag_IMIT[(IMIT_Alternative_MobilityConceptForgoesParkingSpacesWithTheExceptionOfDisabledParkingAndCarsharingSpaces)].isEnabled()) {
		tec3_1_2 += 25;
	} else {
		tec3_1_2_3 += (m_flag_IMIT[(IMIT_ParkingSpacesReducedAccordingToRegulations)].isEnabled() ? 15 : 0);
		tec3_1_2_3 += (m_flag_IMIT[(IMIT_ReducedParkingDemandRedirectedToMobilityHubThatFeaturesFurtherReductionsOfTransportationNeeds)].isEnabled() ? 5 : 0);
		tec3_1_2_3 += (m_flag_IMIT[(IMIT_ParkingSpacesOnSiteFulfillOrganisationalAndConstructionalRequirementsForCarsharing)].isEnabled() ? 5 : 0);
		tec3_1_2_3 += (m_flag_IMIT[(IMIT_AtLeast80PercentOfParkingSpacesHaveNoDesignatedSpecificOccupant)].isEnabled() ? 5 : 0);
		
		tec3_1_2 += std::min<double>(25, tec3_1_2_3);
	}
	
	return tec3_1_2;
} 	

double DGNB::Tec3_1_2::scoreBonus() {
	double tec3_1_2Bonus = 0;
	
	tec3_1_2Bonus += (m_flag_IA2030MMC[(IA2030MMC_MobilityConceptIncludesMobilityManagementConcept)].isEnabled() ? 5 : 0);
	return tec3_1_2Bonus;
	
} // Tec3.1.2

} // namespace DGNB
