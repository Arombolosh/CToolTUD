#include "DGNB_Tec1_3_2.h"

namespace DGNB {
	
double DGNB::Tec1_3_2::score() {
	double tec1_3_2 = 0;

	// assigning 10 pts for Tec1.3.2.1
	switch (m_usageType){
		case Utilities::UT_Residential:
			tec1_3_2 += (m_flag_TOESEP[(TOESEP_Residential_TransmissionOverHullSurfaceComparedToReferenceBuildingLessThan55Percent)].isEnabled() ? 10 : 0);
			break;

		default:
			if (m_flag_TOESEP[(TOESEP_NominalRoomTemperature19Degrees)].isEnabled()){
				if (m_flag_TOESEP[(TOESEP_19Degrees_OpaqueExteriorBuildingElementsHTCLessThan0_18)].isEnabled() && m_flag_TOESEP[(TOESEP_19Degrees_TransparentExteriorBuildingElementsAndFrontsHTCLessThan1_0)].isEnabled() && m_flag_TOESEP[(TOESEP_19Degrees_OtherTransparentElementsLikeGlassRoofsLightBandsLightDomesHTCLessThan1_6)].isEnabled())
					tec1_3_2 += 10;
			} else if (m_flag_TOESEP[(TOESEP_NominalRoomTemperatureBetween12And19Degrees)].isEnabled()){
				if (m_flag_TOESEP[(TOESEP_12to19Degrees_OpaqueExteriorBuildingElementsHTCLessThan0_24)].isEnabled() && m_flag_TOESEP[(TOESEP_12to19Degrees_TransparentExteriorBuildingElementsAndFrontsHTCLessThan1_3)].isEnabled() && m_flag_TOESEP[(TOESEP_12to19Degrees_OtherTransparentElementsLikeGlassRoofsLightBandsLightDomesHTCLessThan2_0)].isEnabled())
					tec1_3_2 += 10;
			}
		break;
	}

	// assigning 10 pts for Tec1.3.2.2
	if (m_flag_TOESTBS[(TOESTBS_SurchargeLessThan0_01)].isEnabled())
		tec1_3_2 += 10;
	else if (m_flag_TOESTBS[(TOESTBS_SurchargeLessThan0_05)].isEnabled())
		tec1_3_2 += 5;
	else if (m_flag_TOESTBS[(TOESTBS_EvaluationImpossible)].isEnabled())
		tec1_3_2 += 0;

	return tec1_3_2;
} // Tec1.3.2

} // namespace DGNB
