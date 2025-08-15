#include "DGNB_Pro2_1_3.h"

namespace DGNB {
	
double DGNB::Pro2_1_3::score() {
	double pro2_1_3 = 0;

	pro2_1_3 += (m_flag_SGPCSC[(SGPCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts)].isEnabled() ? 5 : 0);
	pro2_1_3 += (m_flag_SGPCSIO[(SGPCSIO_InstructionOrBriefungOfOperators)].isEnabled() ? 2.5 : 0);
	pro2_1_3 += (m_flag_SGPCSEI[(SGPCSEI_ExaminationOrVerificationOfImplementation)].isEnabled() ? 5 : 0);

	return pro2_1_3;
} // Pro2.1.3

} // namespace DGNB
