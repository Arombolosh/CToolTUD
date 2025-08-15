#include "DGNB_Env2_4_6.h"

namespace DGNB {

double DGNB::Env2_4_6::score() {
	double env2_4_6 = 0;
	int bdosPCMMSCID = 0;

	for (unsigned int i = 0; i < NUM_BDOSPCMMSC; ++i)
		bdosPCMMSCID = (m_flag_BDOSPCMMSC[(BDOS_PreparativeCareAndMonitoringMonitoringAndSuccessControl)i].isEnabled() ? i+1 : 0);

	// assigning 5 points for Env2.4.6.1a
	env2_4_6 += (m_flag_BDOSPCMDMCC[(BDOS_PreparativeCareAndMonitoringDevelopmentAndMaintenanceCareContract)0].isEnabled() ? 5 : 0);
	// assigning 3 points for Env2.4.6.1b
	env2_4_6 += (m_flag_BDOSPCMDMCC[(BDOS_PreparativeCareAndMonitoringDevelopmentAndMaintenanceCareContract)1].isEnabled() ? 3 : 0);
	// assigning 4 points for Env2.4.6.1.1
	env2_4_6 += (m_flag_BDOSPCMDMCC[(BDOS_PreparativeCareAndMonitoringDevelopmentAndMaintenanceCareContract)2].isEnabled() ? 4 : 0);
	// assigning 2 points for Env2.4.6.1.2a
	env2_4_6 += (m_flag_BDOSPCMDMCC[(BDOS_PreparativeCareAndMonitoringDevelopmentAndMaintenanceCareContract)3].isEnabled() ? 2 : 0);
	// assigning 2 points for Env2.4.6.1.2b
	env2_4_6 += (m_flag_BDOSPCMDMCC[(BDOS_PreparativeCareAndMonitoringDevelopmentAndMaintenanceCareContract)4].isEnabled() ? 2 : 0);
	// assigning 2 points for Env2.4.6.1.3
	env2_4_6 += (m_flag_BDOSPCMDMCC[(BDOS_PreparativeCareAndMonitoringDevelopmentAndMaintenanceCareContract)5].isEnabled() ? 2 : 0);

	// assigning 3 or 5 points for Env2.4.6.2
	if (bdosPCMMSCID == 1)
		env2_4_6 += 3;
	else if (bdosPCMMSCID == 2)
		env2_4_6 += 5;

	return env2_4_6;
}



} // namespace DGNB
