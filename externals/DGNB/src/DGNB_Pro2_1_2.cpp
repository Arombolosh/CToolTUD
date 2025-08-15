#include "DGNB_Pro2_1_2.h"

namespace DGNB {
	
double DGNB::Pro2_1_2::score() {
	double pro2_1_2 = 0;

	pro2_1_2 += (m_flag_DRCSC[(DRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts)].isEnabled() ? 5 : 0);
	pro2_1_2 += (m_flag_DRCSIO[(DRCSIO_InstructionOrBriefungOfOperators)].isEnabled() ? 2.5 : 0);
	pro2_1_2 += (m_flag_DRCSEI[(DRCSEI_ExaminationOrVerificationOfImplementation)].isEnabled() ? 5 : 0);

	return pro2_1_2;
} // Pro2.1.2

} // namespace DGNB
