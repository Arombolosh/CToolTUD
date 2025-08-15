#ifndef DGNB_Eco2_4_1H
#define DGNB_Eco2_4_1H

#include "DGNB_Utilities.h"

namespace DGNB {
/*! Eco2.4.1 analysis of site and building concept */
class Eco2_4_1	// max +10
{
public:

	/*! Eco2.4.1.1  */
	enum ASBC_SiteAnalysis {										// Not for HC: max +10
		ASBCSA_GeneralPerceptionOfSite,								// Keyword: ASBCSA_GeneralPerceptionOfSite
		ASBCSA_DemographicAndEconomicDevelopmentOfMacroSite,		// Keyword: ASBCSA_DemographicAndEconomicDevelopmentOfMacroSite
		ASBCSA_ImmediateNeighbourhood,								// Keyword: ASBCSA_ImmediateNeighbourhood
		NUM_ASBCSA
	};

	/*! Eco2.4.1.2a */
	enum ASBC_BuildingConceptAndSynergies {							// Not for HC: max +15
		ASBCBCS_ReactionOfBuildingConceptToSiteAnalysis,			// Keyword: ASBCBCS_ReactionOfBuildingConceptToSiteAnalysis
		ASBCBCS_UseAndProvisioningOfEnvironmentSynergyEffects,		// Keyword: ASBCBCS_UseAndProvisioningOfEnvironmentSynergyEffects
		NUM_ASBCBCS
	};

	/*! Eco2.4.1.2b */
	enum ASBC_HealthcareBuildingConceptAndSynergies {														// HC only: max +35
		ASBCHCBCS_PlanInvolvesRegionalAnalysisConductedByInterdisciplinaryTeam,								// Keyword: ASBCHCBCS_PlanInvolvesRegionalAnalysisConductedByInterdisciplinaryTeam
		ASBCHCBCS_ConceptInvolvesPatientAndPersonnelRoutes,													// Keyword: ASBCHCBCS_ConceptInvolvesPatientAndPersonnelRoutes
		ASBCHCBCS_ConceptInvolvesMaterialTransportAndStorageSpaces,											// Keyword: ASBCHCBCS_ConceptInvolvesMaterialTransportAndStorageSpaces
		ASBCHCBCS_ConceptInvolvesComplianceWithHygienicRequirements,										// Keyword: ASBCHCBCS_ConceptInvolvesComplianceWithHygienicRequirements
		ASBCHCBCS_ConceptInvolvesPositioningOfTechnicalUnitsInRegardToAccomodatedFunctionsAndMainBuilding,	// Keyword: ASBCHCBCS_ConceptInvolvesPositioningOfTechnicalUnitsInRegardToAccomodatedFunctionsAndMainBuilding
		ASBCHCBCS_ConceptInvolvesConsiderationOfFutureUsageScenarios,										// Keyword: ASBCHCBCS_ConceptInvolvesConsiderationOfFutureUsageScenarios
		ASBCHCBCS_ConsiderationOfCatastrophicScenariosAndEnsuranceOfContinuedOperation,						// Keyword: ASBCHCBCS_ConsiderationOfCatastrophicScenariosAndEnsuranceOfContinuedOperation
		NUM_ASBCHCBCS
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco2_4_1(){}

	Eco2_4_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag			m_flag_ASBCSA[NUM_ASBCSA];					// XML:E
	/*! List of flags. */
	IBK::Flag			m_flag_ASBCBCS[NUM_ASBCBCS];				// XML:E
	/*! List of flags. */
	IBK::Flag			m_flag_ASBCHCBCS[NUM_ASBCHCBCS];			// XML:E

	Utilities::UsageType			m_usageType;

}; // Eco 2.4.1

} // namespace DGNB

#endif // DGNB_Eco2_4_1H
