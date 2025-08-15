#ifndef DGNB_Tec3_1_3H
#define DGNB_Tec3_1_3H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

/*! Tec3.1.3 Infrastructure for alternative Fuel Sources */
class Tec3_1_3
{
public:

	/*! Basic parameters. */
	enum para_t {
		/*! IAFSBTEB_NumberOfRequiredBicycleParkingSpots */
		P_Tec3_1_3_1IAFSBTEB_NumberOfRequiredBicycleParkingSpots,															// Keyword: Tec3_1_3_1IAFSBTEB_NumberOfRequiredBicycleParkingSpots															[-]
		/*! IAFSBTEB_NumberOfBicycleParkingSpotsEquippedWithLoadingDock */
		P_Tec3_1_3_1IAFSBTEB_NumberOfBicycleParkingSpotsEquippedWithLoadingDock,											// Keyword: Tec3_1_3_1IAFSBTEB_NumberOfBicycleParkingSpotsEquippedWithLoadingDock											[-]
		/*! IAFSMIT_PercentageOfParkingsSpotsOfPermanentelyDesignatedOccupantsOrResidentsEquippedWithLoadingDock */
		P_Tec3_1_3_2IAFSMIT_PercentageOfParkingsSpotsOfPermanentelyDesignatedOccupantsOrResidentsEquippedWithLoadingDock,	// Keyword: Tec3_1_3_2IAFSMIT_PercentageOfParkingsSpotsOfPermanentelyDesignatedOccupantsOrResidentsEquippedWithLoadingDock	[---]		// ToDo Einheit % SO oder anders?
		/*! IAFSMIT_PercentageOfOtherParkingsSpotsEquippedWithLoadingDock */
		P_Tec3_1_3_2IAFSMIT_PercentageOfOtherParkingsSpotsEquippedWithLoadingDock,											// Keyword: Tec3_1_3_2IAFSMIT_PercentageOfOtherParkingsSpotsEquippedWithLoadingDock											[---]		// ToDo Einheit % SO oder anders?
		/*! IAFSMIT_TotalNumberOfParkingsSpotsEquippedWithLoadingDock */
		P_Tec3_1_3_2IAFSMIT_TotalNumberOfParkingsSpotsEquippedWithLoadingDock,												// Keyword: Tec3_1_3_2IAFSMIT_TotalNumberOfParkingsSpotsEquippedWithLoadingDock												[-]
		/*! IAFSMIT_PercentageOfOtherParkingsSpotsPreparedToBeEquippedWithLoadingDock */
		P_Tec3_1_3_2IAFSMIT_PercentageOfOtherParkingsSpotsPreparedToBeEquippedWithLoadingDock,								// Keyword: Tec3_1_3_2IAFSMIT_PercentageOfOtherParkingsSpotsPreparedToBeEquippedWithLoadingDock								[---]		// ToDo Einheit % SO oder anders?
		NUM_P
	};

	/*! Tec3.1.3.1 Bicycle Traffic and Electric Bicycles */
	enum IAFS_BicycleTrafficAndElectricBicycles {																			// max +10
		IAFSBTEB_ResultsSubmitted,																							// Keyword: IAFSBTEB_ResultsSubmitted
		NUM_IAFSBTEB
	};

	/*! Tec3.1.3.2 MotorisedIndividualTransport */
	enum IAFS_MotorisedIndividualTransport {																				// max +10
		IAFSMIT_ResultsSubmitted,																							// Keyword: IAFSMIT_ResultsSubmitted
		NUM_IAFSMIT
	};

	/*! Tec3.1.2.3 Integration of Loading or Tank Stations */
	enum IAFS_IntegrationOfLoadingOrTankStations {																			// max +5
		IAFSILTS_IntegrationIntoBuildingEnergyManagement,																	// Keyword: IAFSILTS_IntegrationIntoBuildingEnergyManagement
		IAFSILTS_IntegrationIntoLoadingManagementNetwork,																	// Keyword: IAFSILTS_IntegrationIntoLoadingManagementNetwork
		NUM_IAFSILTS
	};

	/*! Tec3.1.2.4 Agenda 2030 Bonus Climate Protection Goals */
	enum IAFS_Agenda2030ClimateProtectionGoals {																			// max +10
		IAFSA2030CPG_VehicleToGrid_SetupForBidirectionalLoadingAndUnloadingOfElectricVehicles,								// Keyword: IAFSA2030CPG_VehicleToGrid_SetupForBidirectionalLoadingAndUnloadingOfElectricVehicles
		NUM_IAFSA2030CPG
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Tec3_1_3(){}

	Tec3_1_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_IAFSBTEB[NUM_IAFSBTEB];			// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_IAFSMIT[NUM_IAFSMIT];			// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_IAFSILTS[NUM_IAFSILTS];			// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_IAFSA2030CPG[NUM_IAFSA2030CPG];	// XML:E
	
	IBK::Parameter					m_para[NUM_P];							// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Tec3_1_3H
