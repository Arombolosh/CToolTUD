#ifndef DGNB_Tec3_1_2H
#define DGNB_Tec3_1_2H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

/*! Tec3.1.2 Infrastructures */
class Tec3_1_2
{
public:

	/*! Tec3.1.2.1 Pedestrian Infrastructure */
	enum I_PedestrianInfrastructure {																									// max +15
		IPI_TransparentSafeAndBarrierFreeRoutingVisibleAndComprehensiveSignage,															// Keyword: IPI_TransparentSafeAndBarrierFreeRoutingVisibleAndComprehensiveSignage
		IPI_DesignatedParkingSpotsForMobilityAidsLikeWalkersOrStrollers,																// Keyword: IPI_DesignatedParkingSpotsForMobilityAidsLikeWalkersOrStrollers
		NUM_IPI
	};

	/*! Tec3.1.2.2 Bicycle Infrastructure */
	enum I_BicycleInfrastructure {																										// max +20
		IBI_AtLeast80PerceptOfBicycleParkingSpotsAreClearlyRelatedToTheBuildingNearTheEntranceAccessibleAndHaveProtectionAgainstTheft,	// Keyword: IBI_AtLeast80PerceptOfBicycleParkingSpotsAreClearlyRelatedToTheBuildingNearTheEntranceAccessibleAndHaveProtectionAgainstTheft
		IBI_Residential100PercentAllOthers80PercentOfParkingSpotsAreEquippedWithWeatherProtection,										// Keyword: IBI_Residential100PercentAllOthers80PercentOfParkingSpotsAreEquippedWithWeatherProtection
		IBI_SufficientNumberOfParkingSpotsForCargoBikesWithTheftProtection,																// Keyword: IBI_SufficientNumberOfParkingSpotsForCargoBikesWithTheftProtection
		NUM_IBI
	};

	/*! Tec3.1.2.3 Motorised Individual Transport */
	enum I_MotorisedIndividualTransport {																								// max +25
		IMIT_ParkingSpacesReducedAccordingToRegulations,																				// Keyword: IMIT_ParkingSpacesReducedAccordingToRegulations
		IMIT_ReducedParkingDemandRedirectedToMobilityHubThatFeaturesFurtherReductionsOfTransportationNeeds,								// Keyword: IMIT_ReducedParkingDemandRedirectedToMobilityHubThatFeaturesFurtherReductionsOfTransportationNeeds
		IMIT_ParkingSpacesOnSiteFulfillOrganisationalAndConstructionalRequirementsForCarsharing,										// Keyword: IMIT_ParkingSpacesOnSiteFulfillOrganisationalAndConstructionalRequirementsForCarsharing
		IMIT_AtLeast80PercentOfParkingSpacesHaveNoDesignatedSpecificOccupant,															// Keyword: IMIT_AtLeast80PercentOfParkingSpacesHaveNoDesignatedSpecificOccupant
		IMIT_Alternative_MobilityConceptForgoesParkingSpacesWithTheExceptionOfDisabledParkingAndCarsharingSpaces,						// Keyword: IMIT_Alternative_MobilityConceptForgoesParkingSpacesWithTheExceptionOfDisabledParkingAndCarsharingSpaces
		NUM_IMIT
	};

	/*! Tec3.1.2.4 Agenda 2030 Bonus Mobility Management Concept */
	enum I_Agenda2030MobilityManagementConcept {																						// max +25
		IA2030MMC_MobilityConceptIncludesMobilityManagementConcept,																		// Keyword: IA2030MMC_MobilityConceptIncludesMobilityManagementConcept
		NUM_IA2030MMC
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Tec3_1_2(){}

	Tec3_1_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_IPI[NUM_IPI];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_IBI[NUM_IBI];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_IMIT[NUM_IMIT];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_IA2030MMC[NUM_IA2030MMC];	// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Tec3_1_2H
