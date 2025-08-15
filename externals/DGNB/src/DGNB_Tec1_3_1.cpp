#include "DGNB_Tec1_3_1.h"

namespace DGNB {
	
double DGNB::Tec1_3_1::score() {
	double tec1_3_1 = 0;

	tec1_3_1 += (m_flag_PABEPFE[(PABEPFE_PotentialOfSolarEnergy)].isEnabled() ? 10 : 0);
	tec1_3_1 += (m_flag_PABEPFE[(PABEPFE_PotentialOfGreening)].isEnabled() ? 10 : 0);
	tec1_3_1 += (m_flag_PABEPFE[(PABEPFE_AnalysisOfDifferentVariationsFocusedOnSustainabilityThroughoutLifeCycle)].isEnabled() ? 10 : 0);
	tec1_3_1 += (m_flag_PABEPFE[(PABEPFE_UseOfSustainableResourcesForInsulationAndCladding)].isEnabled() ? 5 : 0);
	tec1_3_1 += (m_flag_PABEPFE[(PABEPFE_PossibilityOfNondestructiveReplacementOfParts)].isEnabled() ? 5 : 0);
	tec1_3_1 += (m_flag_PABEPFE[(PABEPFE_AnalysisOfDifferentVariationsFocusedOnHeatLossOverBuildingEnvelope)].isEnabled() ? 5 : 0);

	tec1_3_1 = std::min<double>(30, tec1_3_1);

	return tec1_3_1;
} // Tec1.3.1

} // namespace DGNB
