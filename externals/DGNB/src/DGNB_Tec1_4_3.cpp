#include "DGNB_Tec1_4_3.h"

namespace DGNB {
	
double DGNB::Tec1_4_3::score() {
	double tec1_4_3 = 0;

	tec1_4_3 += ((m_flag_ABSSEC[(ABSSEC_GenerallyGoodAccessibilityOfAllSystemComponentsForReplacementAndRetrofitting)].isEnabled() && m_flag_ABSSEC[(ABSSEC_SufficientNumberAndSizeOfOpeningsDoorsAndHallways)].isEnabled() && m_flag_ABSSEC[(ABSSEC_TransportAndReplacementOfComponentsPossibleWithoutConstructionalMeasures)].isEnabled()) ? 10 : 0);
	
	if (m_flag_ABSDTA[(ABSDTA_VerticalDuctsAndTracesOfAllSubsectionsAccessible)].isEnabled() && m_flag_ABSDTA[(ABSDTA_PossibilityOfRetrofittingWithoutMajorDisturbanceToBuildingOperation)].isEnabled())
		tec1_4_3 += 10;
	else if (m_flag_ABSDTA[(ABSDTA_VerticalDuctsAndTracesOfAllSubsectionsAccessible)].isEnabled())
		tec1_4_3 += 5;

	return tec1_4_3;
} // Tec1.4.3

} // namespace DGNB
