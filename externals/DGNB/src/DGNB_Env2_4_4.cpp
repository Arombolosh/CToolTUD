#include "DGNB_Env2_4_4.h"

namespace DGNB {

double DGNB::Env2_4_4::score() {
	double env2_4_4 = (m_flag_BDOSRSBI[(BDOS_RelationToSurroundingsBiotopeInterconnectivity)0].isEnabled() ? 7 : 0);
	return env2_4_4;
}



} // namespace DGNB
