#ifndef DGNB_Pro1_1_3H
#define DGNB_Pro1_1_3H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

/*! Pro1.1.3 Contract Specifications */
class Pro1_1_3
{
public:

	/*! Pro1.1.3 Sustainability Requirements */
	enum CS_SustainabilityRequirements {										// max +20
		CSSR_SpecificationsIncludeDetailedRequirementsToBuildingsSustainabilityFromEcologicalEconomicalSocioculturalFunctionalTechnicalAspectsAsWellAsPlanningAndConstructionPhase,	// Keyword: CSSR_SpecificationsIncludeDetailedRequirementsToBuildingsSustainabilityFromEcologicalEconomicalSocioculturalFunctionalTechnicalAspectsAsWellAsPlanningAndConstructionPhase
		CSSR_SpecificationsFurtherIncludeDefinitionsOfResponsibilitiesAndPlanningMethodAndEssentialPlanningPhasesDecidedByAPlanningTeam,											// Keyword: CSSR_SpecificationsFurtherIncludeDefinitionsOfResponsibilitiesAndPlanningMethodAndEssentialPlanningPhasesDecidedByAPlanningTeam
		NUM_CSSR
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro1_1_3(){}

	Pro1_1_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_CSSR[NUM_CSSR];			// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro1_1_3H
