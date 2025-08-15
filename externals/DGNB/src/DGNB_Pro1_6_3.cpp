#include "DGNB_Pro1_6_3.h"

namespace DGNB {
	
double DGNB::Pro1_6_3::score() {
	double pro1_6_3 = 0;

	if (m_flag_HAAR[(HAAR_RecognitionOfFinishedProjectWithArchitectureAwardDGNBDiamond)].isEnabled())
		pro1_6_3 += 100;
	else if (m_flag_HAAR[(HAAR_RecognitionOfGoodConstructionalCulturalQuality)].isEnabled())
		pro1_6_3 += 40;

	return pro1_6_3;
} // Pro1.6.3

} // namespace DGNB
