#ifndef DGNB_Tec1_4_4H
#define DGNB_Tec1_4_4H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Tec1_4_4
{
public:

	/*! Tec1.4.4.1 Integrated Systems: State and Upgradability */
	enum IS_StateAndUpgradability {				// max +10
		ISSU_PlanningAndImplementationAccordingToDIN_EN_ISO_16484_1,	// Keyword: ISSU_PlanningAndImplementationAccordingToDIN_EN_ISO_16484_1
		ISSU_OpenAndStandardizedProtocolsInExistingNetworks,			// Keyword: ISSU_OpenAndStandardizedProtocolsInExistingNetworks
		NUM_ISSU
	};

	/*! Tec1.4.4.2 Integrated Systems: Integrated Functions in Superordinate Systems */
	enum IS_IntegratedFunctionsInSuperordinateSystems {					// max +10
		ISIFSS_Sunblind,												// Keyword: ISIFSS_Sunblind
		ISIFSS_Lighting,												// Keyword: ISIFSS_Lighting
		ISIFSS_Heating,													// Keyword: ISIFSS_Heating
		ISIFSS_Aeration,												// Keyword: ISIFSS_Aeration
		ISIFSS_Cooling,													// Keyword: ISIFSS_Cooling
		ISIFSS_EnergyManagement,										// Keyword: ISIFSS_EnergyManagement
		ISIFSS_PresenceDetection,										// Keyword: ISIFSS_PresenceDetection
		ISIFSS_Lifts,													// Keyword: ISIFSS_Lifts
		NUM_ISIFSS
	};

	/*! Tec1.4.4.3 Integrated Systems: Integration of technical Systems and Media into quarters and direct surroundings */
	/*! Tec1.4.4.3.1 Circular Economy Bonus: Planning of Integration */
	enum IS_PlanningOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings {																					// max +5
		ISPITSMQDS_AnalysisOfExistingEnergyPotentialAndPossibleNetworkingWithExistingSurroundingEnergyInfrastructure,															// Keyword: ISPITSMQDS_AnalysisOfExistingEnergyPotentialAndPossibleNetworkingWithExistingSurroundingEnergyInfrastructure
		ISPITSMQDS_CreationOfQuarterRelatedEnergyBalancesForHeatingCoolingAndElectricityEcologicalComparisonOfTheEmissionsOfAtLeast3PeripheralAndOrCentralHeatSupplyVariants,	// Keyword: ISPITSMQDS_CreationOfQuarterRelatedEnergyBalancesForHeatingCoolingAndElectricityEcologicalComparisonOfTheEmissionsOfAtLeast3PeripheralAndOrCentralHeatSupplyVariants
		ISPITSMQDS_EconomicalAssessmentOfInvestmentsAndOperatingCostsForAtLeast3SupplyVariants,																					// Keyword: ISPITSMQDS_EconomicalAssessmentOfInvestmentsAndOperatingCostsForAtLeast3SupplyVariants
		ISPITSMQDS_AnalysisOfAppropriationOfRegenerativelyProducedEnergyForQuarterAndSurroudingsUnterInclusionOfPossibleConsumers,												// Keyword: ISPITSMQDS_AnalysisOfAppropriationOfRegenerativelyProducedEnergyForQuarterAndSurroudingsUnterInclusionOfPossibleConsumers
		NUM_ISPITSMQDS
	};
	
	/*! Tec1.4.4.3.1 Circular Economy Bonus: Implementation */
	enum IS_ImplementationOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings {																			// max +5
		ISIITSMQDS_ImplementationWithTheGoalOfSynergisticUseInRelationToQuarterAndDirectSurroundings,																			// Keyword: ISIITSMQDS_ImplementationWithTheGoalOfSynergisticUseInRelationToQuarterAndDirectSurroundings
		NUM_ISIITSMQDS
	};

	/*! Tec1.4.4.4 Integrated Systems: Integration of Energy Infrastructure into quarters and direct surroundings */
	/*! Tec1.4.4.4.1 Circular Economy Bonus: Quarter Solution */
	enum IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsQuarterSolution {																					// max +10
		ISIEIQDSQS_BuildingUsesEnergyFromNearbyQuartersOrDirectSurroundingsToFulfillEnergyDemand,																				// Keyword: ISIEIQDSQS_BuildingUsesEnergyFromNearbyQuartersOrDirectSurroundingsToFulfillEnergyDemand
		ISIEIQDSQS_BuildingProvidesGeneratedRegenerativeEnergyToNearbyQuartersAndDirectSurroundings,																			// Keyword: ISIEIQDSQS_BuildingProvidesGeneratedRegenerativeEnergyToNearbyQuartersAndDirectSurroundings
		NUM_ISIEIQDSQS
	};
	
	/*! Tec1.4.4.4.2 Circular Economy Bonus: Networkable Energy System */
	enum IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsNetworkableEnergySystem {																			// max +10
		ISIITSMQNES_BuildingProvidesRelevantStorageCapacity,																													// Keyword: ISIITSMQNES_BuildingProvidesRelevantStorageCapacity
		ISIITSMQNES_BuildingUsesExistingIntegratedEnergyAndLoadManagement,																										// Keyword: ISIITSMQNES_BuildingUsesExistingIntegratedEnergyAndLoadManagement
		NUM_ISIITSMQNES
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Tec1_4_4(){}

	Tec1_4_4(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_ISSU[NUM_ISSU];					// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_ISIFSS[NUM_ISIFSS];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_ISPITSMQDS[NUM_ISPITSMQDS];		// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_ISIITSMQDS[NUM_ISIITSMQDS];		// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_ISIEIQDSQS[NUM_ISIEIQDSQS];		// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_ISIITSMQNES[NUM_ISIITSMQNES];	// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Tec1_4_4H
