#include "DGNB_Eco2_7_Alt.h"

namespace DGNB {
	
double DGNB::Eco2_7_Alt::score() {
	double scoreEco2_7_Alt = 0;

	// assigning up to +5 pts for Eco2.7.4.2
	scoreEco2_7_Alt += (m_flag_ACCDT[(AC_CircularDigitalTwin)0].isEnabled() ? 100 : 0);

	return scoreEco2_7_Alt;
}

} // namespace DGNB
