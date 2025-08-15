#include "DGNB_Env2_4_1.h"

namespace DGNB {

double DGNB::Env2_4_1::score() {
	double env2_4_1 = 0;

	//assigning 20 pts for development and execution
	env2_4_1 = (m_flag_BDOSCEBDS[(BDOSCEBDS_ExtensiveAndLongTermStrategy)].isEnabled() ? 20 : 0);

	return env2_4_1;
} // Env2.4.1



} // namespace DGNB
