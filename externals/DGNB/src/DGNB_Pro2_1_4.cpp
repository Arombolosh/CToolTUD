#include "DGNB_Pro2_1_4.h"

namespace DGNB {
	
double DGNB::Pro2_1_4::score() {
	double pro2_1_4 = 0;

	pro2_1_4 += (m_flag_WRCSC[(WRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts)].isEnabled() ? 5 : 0);
	pro2_1_4 += (m_flag_WRCSIO[(WRCSIO_InstructionOrBriefungOfOperators)].isEnabled() ? 2.5 : 0);
	pro2_1_4 += (m_flag_WRCSEI[(WRCSEI_ExaminationOrVerificationOfImplementation)].isEnabled() ? 5 : 0);

	return pro2_1_4;
}

double DGNB::Pro2_1_4::scoreBonus() {
	double pro2_1_4Bonus = 0;

	pro2_1_4Bonus += (m_flag_WRCSCEWP[(WRCSCEWP_UseOfNovelAndLargelyWastePreventiveConceptsMethodsAndTechnologies)].isEnabled() ? 10 : 0);

	return pro2_1_4Bonus;
} // Pro2.1.4

} // namespace DGNB
