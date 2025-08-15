#include "DGNB_Tec3_1_3.h"

namespace DGNB {
	
double DGNB::Tec3_1_3::score() {
	double tec3_1_3 = 0;
	double percOfBikeParkingSpotsWithLoadingDocks = 0;
	
	// assigning points for Tec3.1.3.1 with respect to usage type - catalogue differentiates between usage types but not between their point assignments
	if (m_flag_IAFSBTEB[(IAFSBTEB_ResultsSubmitted)].isEnabled()) {
		switch (m_usageType){
			case Utilities::UT_Residential:
				percOfBikeParkingSpotsWithLoadingDocks = (m_para[P_Tec3_1_3_1IAFSBTEB_NumberOfBicycleParkingSpotsEquippedWithLoadingDock].get_value()) / (m_para[P_Tec3_1_3_1IAFSBTEB_NumberOfRequiredBicycleParkingSpots].get_value());

				if (percOfBikeParkingSpotsWithLoadingDocks > 0 && m_para[P_Tec3_1_3_1IAFSBTEB_NumberOfBicycleParkingSpotsEquippedWithLoadingDock].get_value() > 1){
					std::vector<double> xVal_tec3_1_3_1{0.05, 0.4};
					std::vector<double> yVal_tec3_1_3_1{1, 10};

					IBK::LinearSpline ls_tec3_1_3_1;
					ls_tec3_1_3_1.setValues(xVal_tec3_1_3_1, yVal_tec3_1_3_1);
					tec3_1_3 += ls_tec3_1_3_1.value(percOfBikeParkingSpotsWithLoadingDocks);
				}
				break;

			default:
				percOfBikeParkingSpotsWithLoadingDocks = (m_para[P_Tec3_1_3_1IAFSBTEB_NumberOfBicycleParkingSpotsEquippedWithLoadingDock].get_value()) / (m_para[P_Tec3_1_3_1IAFSBTEB_NumberOfRequiredBicycleParkingSpots].get_value());

				if (percOfBikeParkingSpotsWithLoadingDocks > 0 && m_para[P_Tec3_1_3_1IAFSBTEB_NumberOfBicycleParkingSpotsEquippedWithLoadingDock].get_value() > 1){
					std::vector<double> xVal_tec3_1_3_1{0.05, 0.4};
					std::vector<double> yVal_tec3_1_3_1{1, 10};

					IBK::LinearSpline ls_tec3_1_3_1;
					ls_tec3_1_3_1.setValues(xVal_tec3_1_3_1, yVal_tec3_1_3_1);
					tec3_1_3 += ls_tec3_1_3_1.value(percOfBikeParkingSpotsWithLoadingDocks);
				}
				break;
		}
	}

	// assigning points for Tec3.1.3.2 with respect to usage type
	if (m_flag_IAFSMIT[(IAFSMIT_ResultsSubmitted)].isEnabled()) {
		switch (m_usageType){
			case Utilities::UT_Residential:
				if (m_para[P_Tec3_1_3_2IAFSMIT_PercentageOfParkingsSpotsOfPermanentelyDesignatedOccupantsOrResidentsEquippedWithLoadingDock].get_value() >= 50) {
				// ToDO DGNB: assuming that the wording in the catalogue means that 50% of all parking spaces not already equipped with a loading dock need to be set up for one
				// furthermore assuming that following this logic if 75% of parking spaces are already equipped with a loading dock, this criteria is fulfilled, too
					if (m_para[P_Tec3_1_3_2IAFSMIT_PercentageOfParkingsSpotsOfPermanentelyDesignatedOccupantsOrResidentsEquippedWithLoadingDock].get_value() >= 75) {
						tec3_1_3 += 10;
					} else if ((m_para[P_Tec3_1_3_2IAFSMIT_PercentageOfOtherParkingsSpotsPreparedToBeEquippedWithLoadingDock].get_value() / (1 - m_para[P_Tec3_1_3_2IAFSMIT_PercentageOfParkingsSpotsOfPermanentelyDesignatedOccupantsOrResidentsEquippedWithLoadingDock].get_value())) > 0.5)
						tec3_1_3 += 10;
				}
				break;

			default:
				if (m_para[P_Tec3_1_3_2IAFSMIT_PercentageOfParkingsSpotsOfPermanentelyDesignatedOccupantsOrResidentsEquippedWithLoadingDock].get_value() >= 30) {
				// furthermore assuming that following this logic if 60% of parking spaces are already equipped with a loading dock, this criteria is fulfilled, too
					if (m_para[P_Tec3_1_3_2IAFSMIT_PercentageOfOtherParkingsSpotsEquippedWithLoadingDock].get_value() > 10 && m_para[P_Tec3_1_3_2IAFSMIT_PercentageOfParkingsSpotsOfPermanentelyDesignatedOccupantsOrResidentsEquippedWithLoadingDock].get_value() >= 60) {
						tec3_1_3 += 10;
					} else if (m_para[P_Tec3_1_3_2IAFSMIT_PercentageOfOtherParkingsSpotsEquippedWithLoadingDock].get_value() > 10 && m_para[P_Tec3_1_3_2IAFSMIT_PercentageOfOtherParkingsSpotsPreparedToBeEquippedWithLoadingDock].get_value() > 30)
						tec3_1_3 += 10;
				}
				break;
		}
	}

	tec3_1_3 += (m_flag_IAFSILTS[(IAFSILTS_IntegrationIntoBuildingEnergyManagement)].isEnabled() ? 2.5 : 0);

	if (m_para[P_Tec3_1_3_2IAFSMIT_TotalNumberOfParkingsSpotsEquippedWithLoadingDock].get_value() >= 5)
	tec3_1_3 += (m_flag_IAFSILTS[(IAFSILTS_IntegrationIntoLoadingManagementNetwork)].isEnabled() ? 2.5 : 0);


	return tec3_1_3;
} 	

double DGNB::Tec3_1_3::scoreBonus() {
	double tec3_1_3Bonus = 0;
	
	tec3_1_3Bonus += (m_flag_IAFSA2030CPG[(IAFSA2030CPG_VehicleToGrid_SetupForBidirectionalLoadingAndUnloadingOfElectricVehicles)].isEnabled() ? 10 : 0);
	
	return tec3_1_3Bonus;
	
} // Tec3.1.3

} // namespace DGNB
