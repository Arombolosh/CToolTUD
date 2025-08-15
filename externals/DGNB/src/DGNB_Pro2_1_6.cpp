#include "DGNB_Pro2_1_6.h"

namespace DGNB {
	
double DGNB::Pro2_1_6::score() {
	double pro2_1_6 = 0;

	// assigning points for Pro2.1.6.1 Water Usage
	pro2_1_6 += (m_flag_RCWUDT[(RCWUDT_MeasuringAndDocumentationOfWaterUsageOnConstructionSite)].isEnabled() ? 2.5 : 0);
	pro2_1_6 += (m_flag_RCWUC[(RCWUC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts)].isEnabled() ? 5 : 0);
	pro2_1_6 += (m_flag_RCWUIO[(RCWUIO_InstructionOrBriefungOfOperators)].isEnabled() ? 2.5 : 0);
	pro2_1_6 += (m_flag_RCWUEI[(RCWUEI_ExaminationOrVerificationOfImplementation)].isEnabled() ? 5 : 0);

	// assigning points for Pro2.1.6.2 Energy Usage
	pro2_1_6 += (m_flag_RCEUDT[(RCEUDT_MeasuringAndDocumentationOfWaterUsageOnConstructionSite)].isEnabled() ? 2.5 : 0);
	pro2_1_6 += (m_flag_RCEUC[(RCEUC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts)].isEnabled() ? 5 : 0);
	pro2_1_6 += (m_flag_RCEUIO[(RCEUIO_InstructionOrBriefungOfOperators)].isEnabled() ? 2.5 : 0);
	pro2_1_6 += (m_flag_RCEUEI[(RCEUEI_ExaminationOrVerificationOfImplementation)].isEnabled() ? 5 : 0);

	return pro2_1_6;
} // Pro2.1.6

} // namespace DGNB
