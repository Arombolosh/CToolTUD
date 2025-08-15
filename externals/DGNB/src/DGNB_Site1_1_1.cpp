#include "DGNB_Site1_1_1.h"

namespace DGNB {
	
double DGNB::Site1_1_1::score() {
	double site1_1_1 = 0;

	// assigning points for Site1.1.1.1
	if (m_flag_CRCA[(CRCA_ConductionOfQualifiedAnalysisByExperts)].isEnabled())
		site1_1_1 += 10;
	else if (m_flag_CRCA[(CRCA_ConductionOfAnalysis)].isEnabled())
		site1_1_1 += 5;

	// assigning points for Site1.1.1.2
	if (m_flag_CRS[(CRS_AppendixA3TableB)].isEnabled()) {
		site1_1_1 += 10;
		site1_1_1 += (m_flag_CRS[(CRS_AdditionallyAppendixA3TableC)].isEnabled() ? 5 : 0);
	} else if (m_flag_CRS[(CRS_AppendixA3TableA)].isEnabled()) {
		site1_1_1 += 5;
		site1_1_1 += (m_flag_CRS[(CRS_AdditionallyAppendixA3TableC)].isEnabled() ? 5 : 0);
	}

	// assigning points for Site1.1.1.3
	if (m_flag_CRSEP[(CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheEntireBuildingLifeExpectancy)].isEnabled())
		site1_1_1 += 5;
	else if (m_flag_CRSEP[(CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheNext26To50Years)].isEnabled())
		site1_1_1 += 2.5;
	else if (m_flag_CRSEP[(CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheNext10To25Years)].isEnabled())
		site1_1_1 += 1;

	// assigning points for Site1.1.1.4
	site1_1_1 += (m_flag_CRAT[(CRAT_EvaluationOfEnvironmentAndClimateHazardProbability)].isEnabled() ? 2.5 : 0);
	site1_1_1 += (m_flag_CRAT[(CRAT_Vulnerability_EvaluationOfImpactOnBuildingOperationUsersAndAssetValue)].isEnabled() ? 2.5 : 0);

	// assigning points for Site1.1.1.5
	if (m_flag_CRDB[(CRDB_DamageProbabilityEvaluationBasedOnIPCCAssessmentReportWorstCaseScenarioRCP85)].isEnabled()) {
		site1_1_1 += 7.5;
		site1_1_1 += (m_flag_CRDB[(CRDB_AdditionallyScenarioRCP6_0)].isEnabled() ? 2.5 : 0);
		site1_1_1 += (m_flag_CRDB[(CRDB_AdditionallyScenarioRCP4_5)].isEnabled() ? 2.5 : 0);
		site1_1_1 += (m_flag_CRDB[(CRDB_AdditionallyScenarioRCP2_6)].isEnabled() ? 2.5 : 0);
	}

	// assigning points for Site1.1.1.5
	site1_1_1 += (m_flag_CRRA[(CRRA_PhysicalRiskAndVulnerabilityAnalysisConductedPreConstruction)].isEnabled() ? 5 : 0);

	return site1_1_1;
}
	
double DGNB::Site1_1_1::scoreBonus() {
	double site1_1_1Bonus = 0;
	
	site1_1_1Bonus += (m_flag_CRA2030CPG[(CRA2030CPG_ConsiderationOfSurroundingConditionsAndAdaptationSolutionsOfOthers)].isEnabled() ? 5 : 0);

	return site1_1_1Bonus;
} // Site1.1.1

} // namespace DGNB
