#include "DGNB_Site1_3_4.h"

namespace DGNB {
	
double DGNB::Site1_3_4::score() {
	double site1_3_4 = 0;

	// assigning points for Site1.3.4.1
	if (m_flag_FTWN350M[(FTWN350M_100PercentCoverage)].isEnabled())
		site1_3_4 += 5;
	else if (m_flag_FTWN350M[(FTWN350M_80PercentOrMoreCoverage)].isEnabled())
		site1_3_4 += 3;
	else if (m_flag_FTWN350M[(FTWN350M_50PercentOrMoreCoverage)].isEnabled())
		site1_3_4 += 2;

	// assigning points for Site1.3.4.2
	if (m_flag_FTCO350M[(FTCO350M_100PercentOfStreetsAreSafeToCrossAndCrossingsAreSafeToReach)].isEnabled())
		site1_3_4 += 5;
	else if (m_flag_FTCO350M[(FTCO350M_80PercentOfStreetsAreSafeToCrossAndCrossingsAreSafeToReach)].isEnabled())
		site1_3_4 += 3;

	// assigning points for Site1.3.4.3
	if (m_flag_FTSS[(FTSS_SignageAndOrientationPlansCoverSurroundingArea)].isEnabled())
		site1_3_4 += 5;
	else if (m_flag_FTSS[(FTSS_SignageCoversSurroundingArea)].isEnabled())
		site1_3_4 += 3;

	return site1_3_4;
} // Site1.3.4

} // namespace DGNB
