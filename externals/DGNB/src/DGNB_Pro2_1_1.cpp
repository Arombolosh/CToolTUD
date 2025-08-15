#include "DGNB_Pro2_1_1.h"

namespace DGNB {
	
double DGNB::Pro2_1_1::score() {
	double pro2_1_1 = 0;

	pro2_1_1 += (m_flag_NRCSC[(NRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts)].isEnabled() ? 5 : 0);
	pro2_1_1 += (m_flag_NRCSIO[(NRCSIO_InstructionOrBriefungOfOperators)].isEnabled() ? 2.5 : 0);
	pro2_1_1 += (m_flag_NRCSEI[(NRCSEI_ExaminationOrVerificationOfImplementation)].isEnabled() ? 5 : 0);

	return pro2_1_1;
} // Pro2.1.1

} // namespace DGNB
