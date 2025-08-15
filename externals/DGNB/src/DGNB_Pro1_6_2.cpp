#include "DGNB_Pro1_6_2.h"

namespace DGNB {
	
double DGNB::Pro1_6_2::score() {
	double pro1_6_2 = 0;
	pro1_6_2 += (m_flag_RIDB[(RIDB_ProjectPresentationInFrontOfDesignBoardOfCommuneAndArchitecturalAssociation)].isEnabled() ? 5 : 0);
	pro1_6_2 += (m_flag_RIDB[(RIDB_ImplementationOfDesignBoardsRecommendations)].isEnabled() ? 10 : 0);

	return pro1_6_2;
} // Pro1.6.2

} // namespace DGNB
