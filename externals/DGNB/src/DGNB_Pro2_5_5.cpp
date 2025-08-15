#include "DGNB_Pro2_5_5.h"

namespace DGNB {

double DGNB::Pro2_5_5::score() {
	double pro2_5_5 = 0;

	pro2_5_5 += (m_flag_SISI[(SISI_CreationOfConceptIncludingImplementationPlan)].isEnabled() ? 5 : 0);
	pro2_5_5 += (m_flag_SISI[(SISI_InstallationOfSustainabilityInformationSystem)].isEnabled() ? 10 : 0);
	pro2_5_5 = std::min<double>(10, pro2_5_5);

	return pro2_5_5;
}

double DGNB::Pro2_5_5::scoreBonus() {
	double pro2_5_5Bonus = 0;

	pro2_5_5Bonus += (m_flag_SISA2030NEKI[(SISA2030NEKI_InfluenceOfNatureExperienceAndKnowledgeImpartationOnOutdoorAreaDesignConcept)].isEnabled() ? 5 : 0);
	pro2_5_5Bonus += (m_flag_SISA2030NEKI[(SISA2030NEKI_AppealingOfferForUsersToExperienceNatureWithAllOrSeveralSenses)].isEnabled() ? 5 : 0);
	pro2_5_5Bonus = std::min<double>(5, pro2_5_5Bonus);

	return pro2_5_5Bonus;
} // Pro2.5.5

} // namespace DGNB
