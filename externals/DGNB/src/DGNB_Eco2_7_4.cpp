#include "DGNB_Eco2_7_4.h"

namespace DGNB {
	
double DGNB::Eco2_7_4::score() {
	double scoreEco2_7_4 = 0;


	// assigning up to +0/+15 pts for Eco2.7.4.1 depending on selection
	if (m_flag_DTOPCHDBM[(DTOP_CreationAndHandoverOfAsBuiltDocumentationOrBuildingModel)0].isEnabled() == false) {
		scoreEco2_7_4 += (m_flag_DTOPCHDBM[(DTOP_CreationAndHandoverOfAsBuiltDocumentationOrBuildingModel)1].isEnabled() ? 5 : 0);
		scoreEco2_7_4 += (m_flag_DTOPCHDBM[(DTOP_CreationAndHandoverOfAsBuiltDocumentationOrBuildingModel)2].isEnabled() ? 5 : 0);
		scoreEco2_7_4 += (m_flag_DTOPCHDBM[(DTOP_CreationAndHandoverOfAsBuiltDocumentationOrBuildingModel)3].isEnabled() ? 5 : 0);
	}

	return scoreEco2_7_4;

}

double DGNB::Eco2_7_4::scoreBonus() {
	double scoreEco2_7_4Bonus = 0;


	// assigning up to +10 bonus pts for Eco2.7.4.2
	scoreEco2_7_4Bonus += (m_flag_DTOPCEDPC[(DTOP_CircularEconomyDigitalisationOfPreexistingConstructions)0].isEnabled() ? 10 : 0);

	return scoreEco2_7_4Bonus;
}

} // namespace DGNB
