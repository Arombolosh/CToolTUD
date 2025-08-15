#include "DGNB_Soc1_1_Alt.h"

namespace DGNB {
	
double DGNB::Soc1_1_Alt::score() {
	double soc1_1_alt = 0;

	soc1_1_alt += (m_flag_AC[(AC_Innovation)0].isEnabled() ? 85 : 0);

	return soc1_1_alt;
} // Soc1.1.Alt

} // namespace DGNB
