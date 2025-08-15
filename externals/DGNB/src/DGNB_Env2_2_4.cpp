#include "DGNB_Env2_2_4.h"

namespace DGNB {

double DGNB::Env2_2_4::score() {
	double env2_2_4 = 0;

	env2_2_4 += (m_flag_DWDWWVDIQI[(DWDWWV_DegreeOfIntegrationIntoQuartersInfrastructure)0].isEnabled()? 4 : 0);

	return env2_2_4;
}   // Env2.2.4



} // namespace DGNB
