#include "DGNB_Env2_2_3.h"

namespace DGNB {

double DGNB::Env2_2_3::score() {
	double env2_2_3 = 0;

	env2_2_3 += (m_flag_DWDWWVIR[(DWDWWV_IrrigatioAndRetention)0].isEnabled()? 2 : 0);
	env2_2_3 += (m_flag_DWDWWVIR[(DWDWWV_IrrigatioAndRetention)1].isEnabled()? 4 : 0);

	return env2_2_3;
} // Env2.2.3



} // namespace DGNB
