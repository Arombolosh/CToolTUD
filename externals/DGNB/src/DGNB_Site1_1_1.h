#ifndef DGNB_Site1_1_1H
#define DGNB_Site1_1_1H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Site1.1.1 Climate Risk */
class Site1_1_1
{
public:

	/*! Site 1.1.1.1 Conduction of Climate Risk Analysis */
	enum CR_ConductionOfAnalysis {															// max +10
		CRCA_ConductionOfAnalysis,															// Keyword: CRCA_ConductionOfAnalysis
		CRCA_ConductionOfQualifiedAnalysisByExperts,										// Keyword: CRCA_ConductionOfQualifiedAnalysisByExperts
		NUM_CRCA
	};

	/*! Site 1.1.1.2 Screening of Environment and Climate Risks */
	enum CR_Screening {																		// max +15
		CRS_AppendixA3TableA,																// Keyword: CRS_AppendixA3TableA
		CRS_AppendixA3TableB,																// Keyword: CRS_AppendixA3TableB
		CRS_AdditionallyAppendixA3TableC,													// Keyword: CRS_AdditionallyAppendixA3TableC
		NUM_CRS
	};

	/*! Site 1.1.1.3 Setting the Evaluation Period */
	enum CR_SettingTheEvaluationPeriod {													// max +5
		CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheNext10To25Years,					// Keyword: CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheNext10To25Years
		CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheNext26To50Years,					// Keyword: CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheNext26To50Years
		CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheEntireBuildingLifeExpectancy,		// Keyword: CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheEntireBuildingLifeExpectancy
		NUM_CRSEP
	};

	/*! Site 1.1.1.4 Acting On The Evaluation */
	enum CR_ActingOnTheEvaluation {															// max +5
		CRAT_EvaluationOfEnvironmentAndClimateHazardProbability,							// Keyword: CRAT_EvaluationOfEnvironmentAndClimateHazardProbability
		CRAT_Vulnerability_EvaluationOfImpactOnBuildingOperationUsersAndAssetValue,			// Keyword: CRAT_Vulnerability_EvaluationOfImpactOnBuildingOperationUsersAndAssetValue
		NUM_CRAT
	};

	/*! Site 1.1.1.4.3 Agenda2030 - Climate Protection Goal */
	enum CR_Agenda2030ClimateProtectionGoal {												// max +5
		CRA2030CPG_ConsiderationOfSurroundingConditionsAndAdaptationSolutionsOfOthers,		// Keyword: CRA2030CPG_ConsiderationOfSurroundingConditionsAndAdaptationSolutionsOfOthers
		NUM_CRA2030CPG
	};

	/*! Site 1.1.1.5 Data Basis */
	enum CR_DataBasis {																		// max +15
		CRDB_DamageProbabilityEvaluationBasedOnIPCCAssessmentReportWorstCaseScenarioRCP85,	// Keyword: CRDB_DamageProbabilityEvaluationBasedOnIPCCAssessmentReportWorstCaseScenarioRCP85
		CRDB_AdditionallyScenarioRCP6_0,													// Keyword: CRDB_AdditionallyScenarioRCP6_0
		CRDB_AdditionallyScenarioRCP4_5,													// Keyword: CRDB_AdditionallyScenarioRCP4_5
		CRDB_AdditionallyScenarioRCP2_6,													// Keyword: CRDB_AdditionallyScenarioRCP2_6
		NUM_CRDB
	};

	/*! Site 1.1.1.6 Result Application*/
	enum CR_ResultApplication {																// max +5
		CRRA_PhysicalRiskAndVulnerabilityAnalysisConductedPreConstruction,					// Keyword: CRRA_PhysicalRiskAndVulnerabilityAnalysisConductedPreConstruction
		NUM_CRRA
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Site1_1_1(){}

	Site1_1_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_CRCA[NUM_CRCA];					// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CRS[NUM_CRS];					// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CRSEP[NUM_CRSEP];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CRAT[NUM_CRAT];					// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CRA2030CPG[NUM_CRA2030CPG];		// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CRDB[NUM_CRDB];					// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CRRA[NUM_CRRA];					// XML:E

	Utilities::UsageType			m_usageType;
};

} // namespace DGNB

#endif // DGNB_Site1_1_1H
