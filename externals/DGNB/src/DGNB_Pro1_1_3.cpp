#include "DGNB_Pro1_1_3.h"

namespace DGNB {
	
double DGNB::Pro1_1_3::score() {
	double pro1_1_3 = 0;

	if (m_flag_CSSR[(CSSR_SpecificationsIncludeDetailedRequirementsToBuildingsSustainabilityFromEcologicalEconomicalSocioculturalFunctionalTechnicalAspectsAsWellAsPlanningAndConstructionPhase)].isEnabled() && m_flag_CSSR[(CSSR_SpecificationsFurtherIncludeDefinitionsOfResponsibilitiesAndPlanningMethodAndEssentialPlanningPhasesDecidedByAPlanningTeam)].isEnabled())
		pro1_1_3 += 30;
	else if (m_flag_CSSR[(CSSR_SpecificationsIncludeDetailedRequirementsToBuildingsSustainabilityFromEcologicalEconomicalSocioculturalFunctionalTechnicalAspectsAsWellAsPlanningAndConstructionPhase)].isEnabled())
		pro1_1_3 += 20;

	return pro1_1_3;
} // Pro1.1.3

} // namespace DGNB
