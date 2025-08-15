#include "DGNB_Env1_2_1.h"

namespace DGNB {

double DGNB::Env1_2_1::score() {
	int efmACounter = 0, efmBRCCounter = 0, efmBSCCounter = 0, efmEPQS123Counter = 0;
	double env1_2_1 = 0;

	/*! environment-friendly materials - Part 1 (all) */
	for(unsigned int i=0; i<NUM_EFMA; ++i)
		efmACounter += (m_flag_EFMA[(EFM_A)i].isEnabled() ? 1 : 0);

	/*! environment-friendly materials - Part 2a (residential + commercial buildings ) */
	for(unsigned int i=0; i<NUM_EFMBRC; ++i)
		efmBRCCounter += (m_flag_EFMBRC[(EFM_BResidentialCommercial)i].isEnabled() ? 1 : 0);

	/*! environment-friendly materials - Part 2b (shopping centers) */
	for(unsigned int i=0; i<NUM_EFMBSC; ++i)
		efmBSCCounter += (m_flag_EFMBSC[(EFM_BShoppingCenter)i].isEnabled() ? 1 : 0);

	/*! Extra points for realization of a cooling system that does not use halogenated of semi-halogenated cooling agents in QS 1 through 3 */
	for(unsigned int i=0; i<NUM_EFMEPQS123; ++i) {
		efmEPQS123Counter += (m_flag_EFMBSC[(EFM_ExtraPointsForQS123)i].isEnabled() ? 1 : 0);
	}

	// summing up points
	switch (m_usageType){
		case Utilities::UT_Residential:
		case Utilities::UT_CommercialBuilding:
			switch (efmACounter){
				case 1:
					env1_2_1 += 5;				// QS 1: simple documentation
				case 2:
					env1_2_1 += 15;				// QS 2: simple documentation
				case 3:
					env1_2_1 += 25;				// QS 2: material ecological parts catalogue or comparable
				case 4:
					env1_2_1 += 35;				// QS 3: material ecological parts catalogue or comparable
				case 5:
					env1_2_1 += 50;				// QS 4: material ecological parts catalogue or comparable
			}
			switch (efmBRCCounter){
				case 1:
					env1_2_1 += 5;				// QS 1: simple documentation
				case 2:
					env1_2_1 += 15;				// QS 2: simple documentation
				case 3:
					env1_2_1 += 25;				// QS 2: material ecological parts catalogue or comparable
				case 4:
					env1_2_1 += 40;				// QS 3: material ecological parts catalogue or comparable
				case 5:
					env1_2_1 += 50;				// QS 4: material ecological parts catalogue or comparable
			}
		break;

		case Utilities::UT_ShoppingCenter:
			switch (efmACounter){
				case 1:
					env1_2_1 += 5;				// QS 1: simple documentation
				case 2:
					env1_2_1 += 15;				// QS 2: simple documentation
				case 3:
					env1_2_1 += 25;				// QS 2: material ecological parts catalogue or comparable
				case 4:
					env1_2_1 += 40;				// QS 3: material ecological parts catalogue or comparable
				case 5:
					env1_2_1 += 60;				// QS 4: material ecological parts catalogue or comparable
			}
			switch (efmBSCCounter){
				case 1:
					env1_2_1 += 5;				// QS 1: simple documentation
				case 2:
					env1_2_1 += 15;				// QS 2: simple documentation
				case 3:
					env1_2_1 += 25;				// QS 2: material ecological parts catalogue or comparable
				case 4:
					env1_2_1 += 35;				// QS 3: material ecological parts catalogue or comparable
				case 5:
					env1_2_1 += 40;				// QS 4: material ecological parts catalogue or comparable
			}
		break;

		default:								// all other usage types
			switch (efmACounter){
				case 1:
					env1_2_1 += 10;				// QS 1: simple documentation
				case 2:
					env1_2_1 += 30;				// QS 2: simple documentation
				case 3:
					env1_2_1 += 50;				// QS 2: material ecological parts catalogue or comparable
				case 4:
					env1_2_1 += 75;				// QS 3: material ecological parts catalogue or comparable
				case 5:
					env1_2_1 += 100;			// QS 4: material ecological parts catalogue or comparable
			}
		break;
	}

	if (efmEPQS123Counter > 0)
		env1_2_1 += 10;


	return env1_2_1;
}  // Env1.2.1

double DGNB::Env1_2_1::scoreBonus() {
	double env1_2_1Bonus = 0;
	double sufficientStructureRows = 0, waivedConnectionsRows = 0;
	/*! Agenda 2030 Bonus (several different) */
	if (m_flag_EFMA2030[(EFMA2030_MeasurementsTakenForSufficientStructure)].isEnabled()){
		sufficientStructureRows = m_para[(P_EFMA2030_MeasurementsTakenForSufficientStructureNumberOfRows)].get_value();
		sufficientStructureRows = std::min<double>(5, 2*sufficientStructureRows);
	}
	if (m_flag_EFMA2030[(EFMA2030_WaivingOfUnsolveableConnections)].isEnabled()){
		waivedConnectionsRows = m_para[(P_EFMA2030_WaivingOfUnsolveableConnectionsNumberOfRows)].get_value();
		waivedConnectionsRows = std::min<double>(5, 2*waivedConnectionsRows);
	}
	/*! summing up points for Agenda 2030 Bonus (several different) */
	// assigning only 2.5 pts for Bonus 2: "Waiving of cross out criterion for QS4" as Bonus 1 and 2 do not stack since bonus 2 condition relies on bonus 1 condition.
	// ToDo: make Bonus 1 checkbox check automatically when Bonus 2 checkbox is checked
	double env1_2_1Agenda2030BonusPoints[5] = {2.5, 2.5, sufficientStructureRows, waivedConnectionsRows, 2.5};
	for(unsigned int i=0; i<NUM_EFMA2030; ++i)
		env1_2_1Bonus += (m_flag_EFMBSC[(EFM_BShoppingCenter)i].isEnabled() ? env1_2_1Agenda2030BonusPoints[i] : 0);

	return env1_2_1Bonus;

}

bool DGNB::Env1_2_1::platinumRequirementsMet() {
	int efmACounter = 0, efmBRCCounter = 0, efmBSCCounter = 0;
	bool env1_2_1PlatinumRequirementsMet = false;

	/*! environment-friendly materials - Part 1 (all) */
	for(unsigned int i=0; i<NUM_EFMA; ++i)
		efmACounter += (m_flag_EFMA[(EFM_A)i].isEnabled() ? 1 : 0);

	/*! environment-friendly materials - Part 2a (residential + commercial buildings ) */
	for(unsigned int i=0; i<NUM_EFMBRC; ++i)
		efmBRCCounter += (m_flag_EFMBRC[(EFM_BResidentialCommercial)i].isEnabled() ? 1 : 0);

	/*! environment-friendly materials - Part 2b (shopping centers) */
	for(unsigned int i=0; i<NUM_EFMBSC; ++i)
		efmBSCCounter += (m_flag_EFMBSC[(EFM_BShoppingCenter)i].isEnabled() ? 1 : 0);

	// summing up points
	switch (m_usageType){
		case Utilities::UT_Residential:
		case Utilities::UT_CommercialBuilding:
			if (efmACounter > 3 && efmBRCCounter > 3)
				env1_2_1PlatinumRequirementsMet = true;
		break;

		case Utilities::UT_ShoppingCenter:
			if (efmACounter > 3 && efmBSCCounter > 3)
				env1_2_1PlatinumRequirementsMet = true;
		break;

		default:	// all other usage types
			if (efmACounter > 3)
				env1_2_1PlatinumRequirementsMet = true;
		break;
	}

	return env1_2_1PlatinumRequirementsMet;
}

} // namespace DGNB
