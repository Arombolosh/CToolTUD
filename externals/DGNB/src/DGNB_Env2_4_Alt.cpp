#include "DGNB_Env2_4_Alt.h"

namespace DGNB {

double DGNB::Env2_4_Alt::score() {
	double env2_4_alt = (m_flag_BDOSAC[(BDOS_AlternativeCertification)0].isEnabled() ? 100 : 0);

	return env2_4_alt;
}



} // namespace DGNB
