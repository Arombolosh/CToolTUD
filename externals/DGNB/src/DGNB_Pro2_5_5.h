#ifndef DGNB_Pro2_5_5H
#define DGNB_Pro2_5_5H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Pro2_5_5
{
public:

	/*! Pro2.5.5.1 Sustainability Information System: Implementation */
	enum SIS_Implementation {																			// max +10
		SISI_CreationOfConceptIncludingImplementationPlan,												// Keyword: SISI_CreationOfConceptIncludingImplementationPlan
		SISI_InstallationOfSustainabilityInformationSystem,												// Keyword: SISI_InstallationOfSustainabilityInformationSystem
		NUM_SISI
	};

	/*! Pro2.5.5.2 Sustainability Information System: Agenda2030 Bonus - Nature Experience and Knowledge Impartation */
	enum SIS_Agenda2030NatureExperienceAndKnowledgeImpartation {										// max +10
		SISA2030NEKI_InfluenceOfNatureExperienceAndKnowledgeImpartationOnOutdoorAreaDesignConcept,		// Keyword: SISA2030NEKI_InfluenceOfNatureExperienceAndKnowledgeImpartationOnOutdoorAreaDesignConcept
		SISA2030NEKI_AppealingOfferForUsersToExperienceNatureWithAllOrSeveralSenses,					// Keyword: SISA2030NEKI_AppealingOfferForUsersToExperienceNatureWithAllOrSeveralSenses
		NUM_SISA2030NEKI
	};
	

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_5_5(){}

	Pro2_5_5(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_SISI[NUM_SISI];						// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_SISA2030NEKI[NUM_SISA2030NEKI];		// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro2_5_5H
