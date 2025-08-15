#include "DGNB_Site.h"


namespace DGNB {


void Site::setUsageType(const Utilities::UsageType &ut) {
	m_site1_1 = Site1_1(ut);
	m_site1_3 = Site1_3(ut);
	m_site1_4 = Site1_4(ut);
	//m_eco1_1.m_eco1_1_1 = Eco1_1::Eco1_1_1(ut);
}

// double Site::score() {
// 	double sumSite = 0;

// 	// summing up all site categories including their individual weighing factors
// 	sumSite += m_para_PW[PW_Site1_1].get_value()/100 * m_site1_1.score();
// 	sumSite += m_para_PW[PW_Site1_3].get_value()/100 * m_site1_3.score();
// 	sumSite += m_para_PW[PW_Site1_4].get_value()/100 * m_site1_4.score();

// 	return sumSite;
// }

int Site::grading() {
	int siteGrading = 0;             // default Failed
	// this is not currently used as a requirement for Site as it is for Environment, Economy and Socioculture
	/*!
	if (minimumRequirementsMet()){
		if (platinumRequirementsMet() && score() >= 195) {
			siteGrading = 4;             // 65% of 300 pts for Platinum
		} else if (score() >= 150) {
			siteGrading = 3;             // 50% of 300 pts for Gold
		} else if (score() >= 105) {
			siteGrading = 2;             // 35% of 300 pts for Silver
		} else
			siteGrading = 1;             // Bronze
	}
	*/
	return siteGrading;
}

std::vector<bool> Site::minimumRequirementsMet() {
	std::vector<bool> minReqMet = {false, true, true};
	int minReqMetCounter = 0;

	minReqMetCounter+= ((m_site1_1.m_site1_1_1.m_flag_CRCA[(Site1_1_1::CRCA_ConductionOfQualifiedAnalysisByExperts)].isEnabled() || m_site1_1.m_site1_1_1.m_flag_CRCA[(Site1_1_1::CRCA_ConductionOfAnalysis)].isEnabled()) ? 1 : 0);
	minReqMetCounter+= ((m_site1_1.m_site1_1_1.m_flag_CRS[(Site1_1_1::CRS_AppendixA3TableB)].isEnabled() || m_site1_1.m_site1_1_1.m_flag_CRS[(Site1_1_1::CRS_AppendixA3TableA)].isEnabled()) ? 1 : 0);
	minReqMetCounter+= ((m_site1_1.m_site1_1_1.m_flag_CRSEP[(Site1_1_1::CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheEntireBuildingLifeExpectancy)].isEnabled() || m_site1_1.m_site1_1_1.m_flag_CRSEP[(Site1_1_1::CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheNext26To50Years)].isEnabled() || m_site1_1.m_site1_1_1.m_flag_CRSEP[(Site1_1_1::CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheNext10To25Years)].isEnabled()) ? 1 : 0);
	minReqMetCounter+= (m_site1_1.m_site1_1_1.m_flag_CRAT[(Site1_1_1::CRAT_EvaluationOfEnvironmentAndClimateHazardProbability)].isEnabled() ? 1 : 0);

	minReqMet[0] = (minReqMetCounter == 4 ? true : false);

	return minReqMet;
}

std::vector<bool> Site::platinumRequirementsMet() {
	std::vector<bool> platReqMet = {false, true, true};
	int platReqMetCounter = 0;

	platReqMetCounter+= (m_site1_1.m_site1_1_1.m_flag_CRAT[(Site1_1_1::CRAT_Vulnerability_EvaluationOfImpactOnBuildingOperationUsersAndAssetValue)].isEnabled() ? 1 : 0);
	platReqMetCounter+= (m_site1_1.m_site1_1_1.m_flag_CRSEP[(Site1_1_1::CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheEntireBuildingLifeExpectancy)].isEnabled() ? 1 : 0);

	platReqMet[0] = (platReqMetCounter == 2 ? true : false);

	return platReqMet;
}

} // DGNB_Site
