#include "DGNB_Project.h"

#include <IBK_Path.h>
#include <QtGlobal>


#define Macro_VariableToString(Variable) (void(Variable),#Variable)

namespace DGNB {

Project::Project() {}

void Project::readXML(const IBK::Path &filename) {

	m_usageType = Utilities::UT_Office;
	m_environment.setUsageType(m_usageType);
	m_economy.setUsageType(m_usageType);
	m_socioculture.setUsageType(m_usageType);
	m_technology.setUsageType(m_usageType);
	m_process.setUsageType(m_usageType);
	m_site.setUsageType(m_usageType);

	FUNCID(Project::readXML);

	TiXmlDocument doc;
	IBK::Path filenamePath(filename);
	std::map<std::string,IBK::Path> pathPlaceHolders; // only dummy for now, filenamePath does not contain placeholders
	TiXmlElement * xmlElem = NANDRAD::openXMLFile(pathPlaceHolders, filenamePath, "DGNB", doc); // NOTE: Throws exception in case of error
	if (!xmlElem)
		return; // empty project, this means we are using only defaults



	try{
		const TiXmlElement * c = xmlElem->FirstChildElement();
		while (c) {
			const std::string & cName = c->ValueStr();
			if (cName == "Project")
				readXML(c);

			c = c->NextSiblingElement();
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Project' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Project' element.").arg(ex2.what()), FUNC_ID);
	}

}

void Project::writeXML(const IBK::Path &filename) const {

	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "UTF-8", "" );
	doc.LinkEndChild( decl );

	TiXmlElement * root = new TiXmlElement( "DGNB" );
	doc.LinkEndChild(root);

	writeXML(root);

	doc.SaveFile( filename.c_str() );
}

int Project::grading() {
	/*!
	 * grading = 0 -> failed
	 *		Total fulfillment less than 35% or minimum requirements not met
	 * grading = 1 -> bronze
	 *		Total fulfillment needs to be 35%
	 * grading = 2 -> silver
	 *		Environment, Economy and Socioculture Fields need to be 35% fulfilled for Silver
	 *		Total fulfillment needs to be 50%
	 * grading = 3 -> gold
	 *		Environment, Economy and Socioculture Fields need to be 50% fulfilled for Gold
	 *		Total fulfillment needs to be 65%
	 * grading = 4 -> platinum
	 *		Environment, Economy and Socioculture Fields need to be 65% fulfilled for Platinum
	 *		Total fulfillment needs to be 80%
	 *		Platinum Requirements must be met.
	 */

	qDebug() << "Proceeding to calculate total score...";
	int grading = 0, minGrading = 0;				// default Failed
	double totalScore = 0;
	double sumEnvironment = 0;
	double weighedSumEnvironment = 0;
	double sumEconomy = 0;
	double weighedSumEconomy = 0;
	double sumSociocultural = 0;
	double weighedSumSociocultural = 0;
	double weighedSumTechnology = 0;
	double weighedSumProcess = 0;
	double weighedSumSite = 0;
	bool overallMinimumRequirementsMet = true;
	bool overallPlatinumRequirementsMet = true;
	int counter = 0;
	std::vector<double> envScores = {
		m_environment.m_env1_1.score(),
		m_environment.m_env1_2.score(),
		m_environment.m_env1_3.score(),
		m_environment.m_env2_2.score(),
		m_environment.m_env2_3.score(),
		m_environment.m_env2_4.score()};
	std::vector<double> envBonusScores = {m_environment.m_env1_1.scoreBonus(), m_environment.m_env1_2.scoreBonus(), 0, m_environment.m_env2_2.scoreBonus(), m_environment.m_env2_3.scoreBonus(), m_environment.m_env2_4.scoreBonus()};
	std::vector<bool> envMinReq = m_environment.minimumRequirementsMet();
	std::vector<bool> envPlatReq = m_environment.platinumRequirementsMet();
	std::vector<double> ecoScores = {m_economy.m_eco1_1.score(), m_economy.m_eco2_4.score(), m_economy.m_eco2_6.score(), m_economy.m_eco2_7.score()};
	std::vector<double> ecoBonusScores = {m_economy.m_eco1_1.scoreBonus(), m_economy.m_eco2_4.scoreBonus(), m_economy.m_eco2_6.scoreBonus(), m_economy.m_eco2_7.scoreBonus()};
	std::vector<bool> ecoMinReq = m_economy.minimumRequirementsMet();
	std::vector<bool> ecoPlatReq = m_economy.platinumRequirementsMet();
	std::vector<double> socScores =			{m_socioculture.m_soc1_1.score(),		m_socioculture.m_soc1_2.score(),		m_socioculture.m_soc1_3.score(),		m_socioculture.m_soc1_4.score(),	m_socioculture.m_soc1_6.score(),		m_socioculture.m_soc2_1.score()};
	std::vector<double> socBonusScores =	{m_socioculture.m_soc1_1.scoreBonus(),	m_socioculture.m_soc1_2.scoreBonus(),	m_socioculture.m_soc1_3.scoreBonus(),	0,									m_socioculture.m_soc1_6.scoreBonus(),	0};
	std::vector<bool> socMinReq = m_socioculture.minimumRequirementsMet();
	std::vector<bool> socPlatReq = m_socioculture.platinumRequirementsMet();
	std::vector<double> tecScores =			{m_technology.m_tec1_3.score(),	m_technology.m_tec1_4.score(),		m_technology.m_tec1_6.score(),		m_technology.m_tec3_1.score()};
	std::vector<double> tecBonusScores =	{0,								m_technology.m_tec1_4.scoreBonus(),	m_technology.m_tec1_6.scoreBonus(),	m_technology.m_tec3_1.scoreBonus()};
	std::vector<bool> tecMinReq = m_technology.minimumRequirementsMet();
	std::vector<bool> tecPlatReq = m_technology.platinumRequirementsMet();
	std::vector<double> proScores = {m_process.m_pro1_1.score(), m_process.m_pro1_4.score(), m_process.m_pro1_6.score(), m_process.m_pro2_1.score(), m_process.m_pro2_3.score(), m_process.m_pro2_5.score()};
	std::vector<double> proBonusScores = {m_process.m_pro1_1.scoreBonus(), m_process.m_pro1_4.scoreBonus(), 0, m_process.m_pro2_1.scoreBonus(), 0, m_process.m_pro2_5.scoreBonus()};
	std::vector<bool> proMinReq = m_process.minimumRequirementsMet();
	std::vector<bool> proPlatReq = m_process.platinumRequirementsMet();
	std::vector<double> siteScores = {m_site.m_site1_1.score(), m_site.m_site1_3.score(), m_site.m_site1_4.score()};
	std::vector<double> siteBonusScores = {m_site.m_site1_1.scoreBonus(), m_site.m_site1_3.scoreBonus(), m_site.m_site1_4.scoreBonus(), };
	std::vector<bool> siteMinReq = m_site.minimumRequirementsMet();
	std::vector<bool> sitePlatReq = m_site.platinumRequirementsMet();

	std::vector<double> scores =		{envScores[0],		envScores[1],		envScores[2],		envScores[3],		envScores[4],		envScores[5],		ecoScores[0],		ecoScores[1],		ecoScores[2],		ecoScores[3],		socScores[0],		socScores[1],		socScores[2],		socScores[3],		socScores[4],		socScores[5],		tecScores[0],		tecScores[1],		tecScores[2],		tecScores[3],		proScores[0],		proScores[1],		proScores[2],		proScores[3],		proScores[4],		proScores[5],		siteScores[0],		siteScores[1],		siteScores[2]};
	std::vector<double> bonusScores =	{envBonusScores[0],	envBonusScores[1],	envBonusScores[2],	envBonusScores[3],	envBonusScores[4],	envBonusScores[5],	ecoBonusScores[0],	ecoBonusScores[1],	ecoBonusScores[2],	ecoBonusScores[3],	socBonusScores[0],	socBonusScores[1],	socBonusScores[2],	socBonusScores[3],	socBonusScores[4],	socBonusScores[5],	tecBonusScores[0],	tecBonusScores[1],	tecBonusScores[2],	tecBonusScores[3],	proBonusScores[0],	proBonusScores[1],	proBonusScores[2],	proBonusScores[3],	proBonusScores[4],	proBonusScores[5],	siteBonusScores[0],	siteBonusScores[1],	siteBonusScores[2]};
	std::vector<bool> minReq =			{envMinReq[0],		envMinReq[1],		envMinReq[2],		envMinReq[3],		envMinReq[4],		envMinReq[5],		ecoMinReq[0],		ecoMinReq[1],		ecoMinReq[2],		ecoMinReq[3],		socMinReq[0],		socMinReq[1],		socMinReq[2],		socMinReq[3],		socMinReq[4],		socMinReq[5],		tecMinReq[0],		tecMinReq[1],		tecMinReq[2],		tecMinReq[3],		proMinReq[0],		proMinReq[1],		proMinReq[2],		proMinReq[3],		proMinReq[4],		proMinReq[5],		siteMinReq[0],		siteMinReq[1],		siteMinReq[2]};
	std::vector<bool> platReq =			{envPlatReq[0],		envPlatReq[1],		envPlatReq[2],		envPlatReq[3],		envPlatReq[4],		envPlatReq[5],		ecoPlatReq[0],		ecoPlatReq[1],		ecoPlatReq[2],		ecoPlatReq[3],		socPlatReq[0],		socPlatReq[1],		socPlatReq[2],		socPlatReq[3],		socPlatReq[4],		socPlatReq[5],		tecPlatReq[0],		tecPlatReq[1],		tecPlatReq[2],		tecPlatReq[3],		proPlatReq[0],		proPlatReq[1],		proPlatReq[2],		proPlatReq[3],		proPlatReq[4],		proPlatReq[5],		sitePlatReq[0],		sitePlatReq[1],		sitePlatReq[2]};
	std::vector<double> weighingFactors = {m_environment.m_para_PW[0].get_value(),		m_environment.m_para_PW[1].get_value(),		m_environment.m_para_PW[2].get_value(),		m_environment.m_para_PW[3].get_value(),		m_environment.m_para_PW[4].get_value(),		m_environment.m_para_PW[5].get_value(),
											m_economy.m_para_PW[0].get_value(),			m_economy.m_para_PW[1].get_value(),			m_economy.m_para_PW[2].get_value(),			m_economy.m_para_PW[3].get_value(),
											m_socioculture.m_para_PW[0].get_value(),	m_socioculture.m_para_PW[1].get_value(),	m_socioculture.m_para_PW[2].get_value(),	m_socioculture.m_para_PW[3].get_value(),	m_socioculture.m_para_PW[4].get_value(),	m_socioculture.m_para_PW[5].get_value(),
											m_technology.m_para_PW[0].get_value(),		m_technology.m_para_PW[1].get_value(),		m_technology.m_para_PW[2].get_value(),		m_technology.m_para_PW[3].get_value(),
											m_process.m_para_PW[0].get_value(),			m_process.m_para_PW[1].get_value(),			m_process.m_para_PW[2].get_value(),			m_process.m_para_PW[3].get_value(),			m_process.m_para_PW[4].get_value(),			m_process.m_para_PW[5].get_value(),
											m_site.m_para_PW[0].get_value(),			m_site.m_para_PW[1].get_value(),			m_site.m_para_PW[2].get_value()};

	std::vector<double> pointGoals =	{m_environment.m_para_PG[0].get_value(),	m_environment.m_para_PG[1].get_value(),		m_environment.m_para_PG[2].get_value(),		m_environment.m_para_PG[3].get_value(),		m_environment.m_para_PG[4].get_value(),		m_environment.m_para_PG[5].get_value(),
										m_economy.m_para_PG[0].get_value(),			m_economy.m_para_PG[1].get_value(),			m_economy.m_para_PG[2].get_value(),			m_economy.m_para_PG[3].get_value(),
										m_socioculture.m_para_PG[0].get_value(),	m_socioculture.m_para_PG[1].get_value(),	m_socioculture.m_para_PG[2].get_value(),	m_socioculture.m_para_PG[3].get_value(),	m_socioculture.m_para_PG[4].get_value(),	m_socioculture.m_para_PG[5].get_value(),
										m_technology.m_para_PG[0].get_value(),		m_technology.m_para_PG[1].get_value(),		m_technology.m_para_PG[2].get_value(),		m_technology.m_para_PG[3].get_value(),
										m_process.m_para_PG[0].get_value(),			m_process.m_para_PG[1].get_value(),			m_process.m_para_PG[2].get_value(),			m_process.m_para_PG[3].get_value(),			m_process.m_para_PG[4].get_value(),			m_process.m_para_PG[5].get_value(),
										m_site.m_para_PG[0].get_value(),			m_site.m_para_PG[1].get_value(),			m_site.m_para_PG[2].get_value()};

	// summing up all environment categories including their individual weighing factors
	weighedSumEnvironment += weighingFactors[0]/100 * (envScores[0] + envBonusScores[0]);
	weighedSumEnvironment += weighingFactors[1]/100 * (envScores[1] + envBonusScores[1]);
	weighedSumEnvironment += weighingFactors[2]/100 * (envScores[2] + envBonusScores[2]);
	// ToDo DGNB why are we capping this at 100 instead of 110 and disregard the potential bonus overflow?
	weighedSumEnvironment += weighingFactors[3]/100 * (std::min<double>(100, (envScores[3] + envBonusScores[3])));
	// ToDo DGNB why are we capping this at 110 instead of 125 if there are 100 normal pts and 25 bonus pts available?
	weighedSumEnvironment += weighingFactors[4]/100 * (std::min<double>(110, (envScores[4] + envBonusScores[4])));
	weighedSumEnvironment += weighingFactors[5]/100 * (envScores[5] + envBonusScores[5]);

	totalScore += weighedSumEnvironment;

	sumEnvironment += (envScores[0] + envBonusScores[0]);
	sumEnvironment += (envScores[1] + envBonusScores[1]);
	sumEnvironment += (envScores[2] + envBonusScores[2]);
	// ToDo DGNB why are we capping this at 100 instead of 110 and disregard the potential bonus overflow?
	sumEnvironment += (std::min<double>(100, (envScores[3] + envBonusScores[3])));
	// ToDo DGNB why are we capping this at 110 instead of 125 if there are 100 normal pts and 25 bonus pts available?
	sumEnvironment += (std::min<double>(110, (envScores[4] + envBonusScores[4])));
	sumEnvironment += (envScores[5] + envBonusScores[5]);

	counter += envScores.size();

	// summing up all economy categories including their individual weighing factors
	weighedSumEconomy += weighingFactors[counter+0]/100 * (ecoScores[0] + ecoBonusScores[0]);
	// ToDo DGNB why are we capping this at 110 instead of 125 if there are 100 normal pts and 25 bonus pts available?
	weighedSumEconomy += weighingFactors[counter+1]/100 * (std::min<double>(110, (ecoScores[1] + ecoBonusScores[1])));
	weighedSumEconomy += weighingFactors[counter+2]/100 * (ecoScores[2] + ecoBonusScores[2]);
	weighedSumEconomy += weighingFactors[counter+3]/100 * (ecoScores[3] + ecoBonusScores[3]);

	totalScore += weighedSumEconomy;

	sumEconomy += (ecoScores[0] + ecoBonusScores[0]);
	// ToDo DGNB why are we capping this at 110 instead of 130 if there are 100 normal pts and 30 bonus pts available?
	sumEconomy += (std::min<double>(110, (ecoScores[1] + ecoBonusScores[1])));
	sumEconomy += (ecoScores[2] + ecoBonusScores[2]);
	sumEconomy += (ecoScores[3] + ecoBonusScores[3]);

	counter += ecoScores.size();

	// summing up all economy categories including their individual weighing factors
	// assuming that Soc1.6 CAN actually receive Bonus points from Agenda 2030 past the limit of 100 points
	for (unsigned int i = 0; i < m_socioculture.NUM_PW; ++i) {
		weighedSumSociocultural += weighingFactors[counter+i]/100 * (socScores[i] + socBonusScores[i]);
		sumSociocultural += (socScores[i] + socBonusScores[i]);
	}

	totalScore += weighedSumSociocultural;

	counter += socScores.size();

	// summing up all technology categories including their individual weighing factors
	for (unsigned int i = 0; i < m_technology.NUM_PW; ++i)
		weighedSumTechnology += weighingFactors[counter+i]/100 * (tecScores[i] + tecBonusScores[i]);

	totalScore += weighedSumTechnology;

	counter += tecScores.size();

	// summing up all process categories including their individual weighing factors
	for (unsigned int i = 0; i < m_process.NUM_PW; ++i)
		weighedSumProcess += weighingFactors[counter+i]/100 * (proScores[i] + proBonusScores[i]);

	totalScore += weighedSumProcess;

	counter += proScores.size();

	// summing up all site categories including their individual weighing factors
	for (unsigned int i = 0; i < m_site.NUM_PW; ++i)
		weighedSumSite += weighingFactors[counter+i]/100 * (siteScores[i] + siteBonusScores[i]);

	totalScore += weighedSumSite;

	qDebug() << "Total score is " << totalScore;
	qDebug() << "Proceeding to calculate grading...";

	// summing up all the individual scores by field, already including their respective weighing factors
	int envGrading = m_environment.grading(sumEnvironment);
	int ecoGrading = m_economy.grading(sumEconomy);
	int socGrading = m_socioculture.grading(sumSociocultural);
	minGrading = std::min<int>(envGrading, ecoGrading);
	minGrading = std::min<int>(minGrading, socGrading);

	int reqCounter = 0;
	while (overallMinimumRequirementsMet == true && reqCounter < minReq.size()) {
		overallMinimumRequirementsMet = minReq[reqCounter];
		reqCounter++;
	}

	reqCounter = 0;
	while (overallPlatinumRequirementsMet == true && reqCounter < platReq.size()) {
		overallPlatinumRequirementsMet = platReq[reqCounter];
		reqCounter++;
	}

	QString rating;
	if (overallMinimumRequirementsMet) {
		if (totalScore > 80 && minGrading == 4 && overallPlatinumRequirementsMet) {
			grading = 4;
			rating = "Project will likely be rated Platinum";
		} else if (totalScore > 65 && minGrading >= 3) {
			grading = 3;
			rating = "Project will likely be rated Gold";
		} else if (totalScore > 50 && minGrading >= 2){
			grading = 2;
			rating = "Project will likely be rated Silver";
		} else if (totalScore > 35) {
			grading = 1;
			rating = "Project will likely be rated Bronze";
		}
	} else
		rating = "Minimum Requirements not met.";

	qDebug() << rating;
	std::vector<int> gradings = {envGrading, ecoGrading, socGrading, grading};

	/*! Chart needs to be fed:
	 *  scores
	 *  bonus scores
	 *  weighing factors
	 *  minimum requirements
	 *  platinum requirements
	 *  individual gradings
	 *  total score
	 *  grading
	 */

	// m_chart = new DGNB_Chart(pointGoals, scores, bonusScores, weighingFactors, minReq, platReq, gradings, totalScore);
	// m_chart->show();

	return grading;
}

void Project::setValuesTest01() {

	m_usageType = Utilities::UT_Office;
	m_environment.setUsageType(m_usageType);
	m_economy.setUsageType(m_usageType);
	m_socioculture.setUsageType(m_usageType);
	m_technology.setUsageType(m_usageType);
	m_process.setUsageType(m_usageType);
	m_site.setUsageType(m_usageType);

	/*!
	 * assigning weighing factors according to usage type
	 */
	switch (m_usageType) {
		case Utilities::UT_Office: {
			m_environment.m_para_PW[Environment::PW_Env1_1].set("PW_Env1_1", 10.4, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env1_2].set("PW_Env1_2", 5.2, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env1_3].set("PW_Env1_3", 2.1, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_2].set("PW_Env2_2", 2.1, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_3].set("PW_Env2_3", 2.1, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_4].set("PW_Env2_4", 3.1, IBK::Unit("-"));

			m_economy.m_para_PW[Economy::PW_Eco1_1].set("PW_Eco1_1", 10.0, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_4].set("PW_Eco2_4", 7.5, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_6].set("PW_Eco2_6", 5.0, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_7].set("PW_Eco2_7", 2.5, IBK::Unit("-"));

			m_socioculture.m_para_PW[Socioculture::PW_Soc1_1].set("PW_Soc1_1", 4.2, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_2].set("PW_Soc1_2", 4.2, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_3].set("PW_Soc1_3", 4.2, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_4].set("PW_Soc1_4", 4.2, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_6].set("PW_Soc1_6", 4.2, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc2_1].set("PW_Soc2_1", 4.2, IBK::Unit("-"));

			m_technology.m_para_PW[Technology::PW_Tec1_3].set("PW_Tec1_3", 2.2, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec1_4].set("PW_Tec1_4", 2.2, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec1_6].set("PW_Tec1_6", 3.3, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec3_1].set("PW_Tec3_1", 2.2, IBK::Unit("-"));

			m_process.m_para_PW[Process::PW_Pro1_1].set("PW_Pro1_1", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro1_4].set("PW_Pro1_4", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro1_6].set("PW_Pro1_6", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_1].set("PW_Pro2_1", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_3].set("PW_Pro2_3", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_5].set("PW_Pro2_5", 1.7, IBK::Unit("-"));

			m_site.m_para_PW[Site::PW_Site1_1].set("PW_Site1_1", 2.5, IBK::Unit("-"));
			m_site.m_para_PW[Site::PW_Site1_3].set("PW_Site1_3", 1.3, IBK::Unit("-"));
			m_site.m_para_PW[Site::PW_Site1_4].set("PW_Site1_4", 1.3, IBK::Unit("-"));

		} break;

		case Utilities::UT_Education: {
			m_environment.m_para_PW[Environment::PW_Env1_1].set("PW_Env1_1", 10.4, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env1_2].set("PW_Env1_2", 5.2, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env1_3].set("PW_Env1_3", 2.1, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_2].set("PW_Env2_2", 2.1, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_3].set("PW_Env2_3", 2.1, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_4].set("PW_Env2_4", 3.1, IBK::Unit("-"));

			m_economy.m_para_PW[Economy::PW_Eco1_1].set("PW_Eco1_1", 10.0, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_4].set("PW_Eco2_4", 7.5, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_6].set("PW_Eco2_6", 5.0, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_7].set("PW_Eco2_7", 2.5, IBK::Unit("-"));

			m_socioculture.m_para_PW[Socioculture::PW_Soc1_1].set("PW_Soc1_1", 4.2, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_2].set("PW_Soc1_2", 4.2, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_3].set("PW_Soc1_3", 4.2, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_4].set("PW_Soc1_4", 4.2, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_6].set("PW_Soc1_6", 4.2, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc2_1].set("PW_Soc2_1", 4.2, IBK::Unit("-"));

			m_technology.m_para_PW[Technology::PW_Tec1_3].set("PW_Tec1_3", 2.2, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec1_4].set("PW_Tec1_4", 2.2, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec1_6].set("PW_Tec1_6", 3.3, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec3_1].set("PW_Tec3_1", 2.2, IBK::Unit("-"));

			m_process.m_para_PW[Process::PW_Pro1_1].set("PW_Pro1_1", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro1_4].set("PW_Pro1_4", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro1_6].set("PW_Pro1_6", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_1].set("PW_Pro2_1", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_3].set("PW_Pro2_3", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_5].set("PW_Pro2_5", 1.7, IBK::Unit("-"));

			m_site.m_para_PW[Site::PW_Site1_1].set("PW_Site1_1", 2.5, IBK::Unit("-"));
			m_site.m_para_PW[Site::PW_Site1_3].set("PW_Site1_3", 1.3, IBK::Unit("-"));
			m_site.m_para_PW[Site::PW_Site1_4].set("PW_Site1_4", 1.3, IBK::Unit("-"));

		} break;

		case Utilities::UT_Residential: {
			m_environment.m_para_PW[Environment::PW_Env1_1].set("PW_Env1_1", 10.0, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env1_2].set("PW_Env1_2", 5.0, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env1_3].set("PW_Env1_3", 2.0, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_2].set("PW_Env2_2", 3.0, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_3].set("PW_Env2_3", 2.0, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_4].set("PW_Env2_4", 3.0, IBK::Unit("-"));

			m_economy.m_para_PW[Economy::PW_Eco1_1].set("PW_Eco1_1", 10.0, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_4].set("PW_Eco2_4", 7.5, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_6].set("PW_Eco2_6", 5.0, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_7].set("PW_Eco2_7", 2.5, IBK::Unit("-"));

			m_socioculture.m_para_PW[Socioculture::PW_Soc1_1].set("PW_Soc1_1", 4.2, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_2].set("PW_Soc1_2", 4.2, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_3].set("PW_Soc1_3", 4.2, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_4].set("PW_Soc1_4", 4.2, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_6].set("PW_Soc1_6", 4.2, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc2_1].set("PW_Soc2_1", 4.2, IBK::Unit("-"));

			m_technology.m_para_PW[Technology::PW_Tec1_3].set("PW_Tec1_3", 2.2, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec1_4].set("PW_Tec1_4", 2.2, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec1_6].set("PW_Tec1_6", 3.3, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec3_1].set("PW_Tec3_1", 2.2, IBK::Unit("-"));

			m_process.m_para_PW[Process::PW_Pro1_1].set("PW_Pro1_1", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro1_4].set("PW_Pro1_4", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro1_6].set("PW_Pro1_6", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_1].set("PW_Pro2_1", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_3].set("PW_Pro2_3", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_5].set("PW_Pro2_5", 1.7, IBK::Unit("-"));

			m_site.m_para_PW[Site::PW_Site1_1].set("PW_Site1_1", 2.5, IBK::Unit("-"));
			m_site.m_para_PW[Site::PW_Site1_3].set("PW_Site1_3", 1.3, IBK::Unit("-"));
			m_site.m_para_PW[Site::PW_Site1_4].set("PW_Site1_4", 1.3, IBK::Unit("-"));

		} break;

		case Utilities::UT_Hotel: {
			m_environment.m_para_PW[Environment::PW_Env1_1].set("PW_Env1_1", 10.0, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env1_2].set("PW_Env1_2", 5.0, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env1_3].set("PW_Env1_3", 2.0, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_2].set("PW_Env2_2", 3.0, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_3].set("PW_Env2_3", 2.0, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_4].set("PW_Env2_4", 3.0, IBK::Unit("-"));

			m_economy.m_para_PW[Economy::PW_Eco1_1].set("PW_Eco1_1", 10.0, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_4].set("PW_Eco2_4", 7.5, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_6].set("PW_Eco2_6", 5.0, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_7].set("PW_Eco2_7", 2.5, IBK::Unit("-"));

			m_socioculture.m_para_PW[Socioculture::PW_Soc1_1].set("PW_Soc1_1", 4.2, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_2].set("PW_Soc1_2", 4.2, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_3].set("PW_Soc1_3", 6.3, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_4].set("PW_Soc1_4", 2.1, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_6].set("PW_Soc1_6", 4.2, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc2_1].set("PW_Soc2_1", 4.2, IBK::Unit("-"));

			m_technology.m_para_PW[Technology::PW_Tec1_3].set("PW_Tec1_3", 2.2, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec1_4].set("PW_Tec1_4", 2.2, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec1_6].set("PW_Tec1_6", 3.3, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec3_1].set("PW_Tec3_1", 2.2, IBK::Unit("-"));

			m_process.m_para_PW[Process::PW_Pro1_1].set("PW_Pro1_1", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro1_4].set("PW_Pro1_4", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro1_6].set("PW_Pro1_6", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_1].set("PW_Pro2_1", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_3].set("PW_Pro2_3", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_5].set("PW_Pro2_5", 1.7, IBK::Unit("-"));

			m_site.m_para_PW[Site::PW_Site1_1].set("PW_Site1_1", 2.5, IBK::Unit("-"));
			m_site.m_para_PW[Site::PW_Site1_3].set("PW_Site1_3", 1.3, IBK::Unit("-"));
			m_site.m_para_PW[Site::PW_Site1_4].set("PW_Site1_4", 1.3, IBK::Unit("-"));

		} break;

		case Utilities::UT_ConvenienceStore: {
			m_environment.m_para_PW[Environment::PW_Env1_1].set("PW_Env1_1", 10.0, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env1_2].set("PW_Env1_2", 5.0, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env1_3].set("PW_Env1_3", 2.0, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_2].set("PW_Env2_2", 2.0, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_3].set("PW_Env2_3", 2.0, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_4].set("PW_Env2_4", 4.0, IBK::Unit("-"));

			m_economy.m_para_PW[Economy::PW_Eco1_1].set("PW_Eco1_1", 10.0, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_4].set("PW_Eco2_4", 7.5, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_6].set("PW_Eco2_6", 5.0, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_7].set("PW_Eco2_7", 2.5, IBK::Unit("-"));

			m_socioculture.m_para_PW[Socioculture::PW_Soc1_1].set("PW_Soc1_1", 5.6, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_2].set("PW_Soc1_2", 5.6, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_3].set("PW_Soc1_3", 0.0, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_4].set("PW_Soc1_4", 5.6, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_6].set("PW_Soc1_6", 2.8, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc2_1].set("PW_Soc2_1", 5.6, IBK::Unit("-"));

			m_technology.m_para_PW[Technology::PW_Tec1_3].set("PW_Tec1_3", 2.7, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec1_4].set("PW_Tec1_4", 1.8, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec1_6].set("PW_Tec1_6", 2.7, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec3_1].set("PW_Tec3_1", 2.7, IBK::Unit("-"));

			m_process.m_para_PW[Process::PW_Pro1_1].set("PW_Pro1_1", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro1_4].set("PW_Pro1_4", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro1_6].set("PW_Pro1_6", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_1].set("PW_Pro2_1", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_3].set("PW_Pro2_3", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_5].set("PW_Pro2_5", 1.7, IBK::Unit("-"));

			m_site.m_para_PW[Site::PW_Site1_1].set("PW_Site1_1", 2.2, IBK::Unit("-"));
			m_site.m_para_PW[Site::PW_Site1_3].set("PW_Site1_3", 1.7, IBK::Unit("-"));
			m_site.m_para_PW[Site::PW_Site1_4].set("PW_Site1_4", 1.1, IBK::Unit("-"));

		} break;

		case Utilities::UT_ShoppingCenter: {
			m_environment.m_para_PW[Environment::PW_Env1_1].set("PW_Env1_1", 10.0, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env1_2].set("PW_Env1_2", 5.0, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env1_3].set("PW_Env1_3", 2.0, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_2].set("PW_Env2_2", 2.0, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_3].set("PW_Env2_3", 2.0, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_4].set("PW_Env2_4", 4.0, IBK::Unit("-"));

			m_economy.m_para_PW[Economy::PW_Eco1_1].set("PW_Eco1_1", 10.0, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_4].set("PW_Eco2_4", 7.5, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_6].set("PW_Eco2_6", 5.0, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_7].set("PW_Eco2_7", 2.5, IBK::Unit("-"));

			m_socioculture.m_para_PW[Socioculture::PW_Soc1_1].set("PW_Soc1_1", 5.0, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_2].set("PW_Soc1_2", 5.0, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_3].set("PW_Soc1_3", 0.0, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_4].set("PW_Soc1_4", 5.0, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_6].set("PW_Soc1_6", 5.0, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc2_1].set("PW_Soc2_1", 5.0, IBK::Unit("-"));

			m_technology.m_para_PW[Technology::PW_Tec1_3].set("PW_Tec1_3", 2.0, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec1_4].set("PW_Tec1_4", 2.0, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec1_6].set("PW_Tec1_6", 3.0, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec3_1].set("PW_Tec3_1", 3.0, IBK::Unit("-"));

			m_process.m_para_PW[Process::PW_Pro1_1].set("PW_Pro1_1", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro1_4].set("PW_Pro1_4", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro1_6].set("PW_Pro1_6", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_1].set("PW_Pro2_1", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_3].set("PW_Pro2_3", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_5].set("PW_Pro2_5", 1.7, IBK::Unit("-"));

			m_site.m_para_PW[Site::PW_Site1_1].set("PW_Site1_1", 2.2, IBK::Unit("-"));
			m_site.m_para_PW[Site::PW_Site1_3].set("PW_Site1_3", 1.7, IBK::Unit("-"));
			m_site.m_para_PW[Site::PW_Site1_4].set("PW_Site1_4", 1.1, IBK::Unit("-"));

		} break;

		case Utilities::UT_CommercialBuilding: {
			m_environment.m_para_PW[Environment::PW_Env1_1].set("PW_Env1_1", 10.4, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env1_2].set("PW_Env1_2", 5.2, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env1_3].set("PW_Env1_3", 2.1, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_2].set("PW_Env2_2", 2.1, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_3].set("PW_Env2_3", 2.1, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_4].set("PW_Env2_4", 3.1, IBK::Unit("-"));

			m_economy.m_para_PW[Economy::PW_Eco1_1].set("PW_Eco1_1", 10.0, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_4].set("PW_Eco2_4", 7.5, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_6].set("PW_Eco2_6", 5.0, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_7].set("PW_Eco2_7", 2.5, IBK::Unit("-"));

			m_socioculture.m_para_PW[Socioculture::PW_Soc1_1].set("PW_Soc1_1", 5.0, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_2].set("PW_Soc1_2", 5.0, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_3].set("PW_Soc1_3", 0.0, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_4].set("PW_Soc1_4", 5.0, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_6].set("PW_Soc1_6", 5.0, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc2_1].set("PW_Soc2_1", 5.0, IBK::Unit("-"));

			m_technology.m_para_PW[Technology::PW_Tec1_3].set("PW_Tec1_3", 2.0, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec1_4].set("PW_Tec1_4", 2.0, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec1_6].set("PW_Tec1_6", 3.0, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec3_1].set("PW_Tec3_1", 3.0, IBK::Unit("-"));

			m_process.m_para_PW[Process::PW_Pro1_1].set("PW_Pro1_1", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro1_4].set("PW_Pro1_4", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro1_6].set("PW_Pro1_6", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_1].set("PW_Pro2_1", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_3].set("PW_Pro2_3", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_5].set("PW_Pro2_5", 1.7, IBK::Unit("-"));

			m_site.m_para_PW[Site::PW_Site1_1].set("PW_Site1_1", 2.2, IBK::Unit("-"));
			m_site.m_para_PW[Site::PW_Site1_3].set("PW_Site1_3", 1.7, IBK::Unit("-"));
			m_site.m_para_PW[Site::PW_Site1_4].set("PW_Site1_4", 1.1, IBK::Unit("-"));

		} break;

		case Utilities::UT_Logistics: {
			m_environment.m_para_PW[Environment::PW_Env1_1].set("PW_Env1_1", 9.6, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env1_2].set("PW_Env1_2", 4.8, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env1_3].set("PW_Env1_3", 1.9, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_2].set("PW_Env2_2", 1.9, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_3].set("PW_Env2_3", 2.9, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_4].set("PW_Env2_4", 3.8, IBK::Unit("-"));

			m_economy.m_para_PW[Economy::PW_Eco1_1].set("PW_Eco1_1", 10.0, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_4].set("PW_Eco2_4", 7.5, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_6].set("PW_Eco2_6", 5.0, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_7].set("PW_Eco2_7", 2.5, IBK::Unit("-"));

			m_socioculture.m_para_PW[Socioculture::PW_Soc1_1].set("PW_Soc1_1", 5.0, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_2].set("PW_Soc1_2", 5.0, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_3].set("PW_Soc1_3", 0.0, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_4].set("PW_Soc1_4", 5.0, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_6].set("PW_Soc1_6", 5.0, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc2_1].set("PW_Soc2_1", 5.0, IBK::Unit("-"));

			m_technology.m_para_PW[Technology::PW_Tec1_3].set("PW_Tec1_3", 3.0, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec1_4].set("PW_Tec1_4", 2.0, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec1_6].set("PW_Tec1_6", 3.0, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec3_1].set("PW_Tec3_1", 2.0, IBK::Unit("-"));

			m_process.m_para_PW[Process::PW_Pro1_1].set("PW_Pro1_1", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro1_4].set("PW_Pro1_4", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro1_6].set("PW_Pro1_6", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_1].set("PW_Pro2_1", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_3].set("PW_Pro2_3", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_5].set("PW_Pro2_5", 1.7, IBK::Unit("-"));

			m_site.m_para_PW[Site::PW_Site1_1].set("PW_Site1_1", 2.5, IBK::Unit("-"));
			m_site.m_para_PW[Site::PW_Site1_3].set("PW_Site1_3", 1.3, IBK::Unit("-"));
			m_site.m_para_PW[Site::PW_Site1_4].set("PW_Site1_4", 1.3, IBK::Unit("-"));

		} break;

		case Utilities::UT_Production: {
			m_environment.m_para_PW[Environment::PW_Env1_1].set("PW_Env1_1", 9.6, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env1_2].set("PW_Env1_2", 4.8, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env1_3].set("PW_Env1_3", 1.9, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_2].set("PW_Env2_2", 1.9, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_3].set("PW_Env2_3", 2.9, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_4].set("PW_Env2_4", 3.8, IBK::Unit("-"));

			m_economy.m_para_PW[Economy::PW_Eco1_1].set("PW_Eco1_1", 10.0, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_4].set("PW_Eco2_4", 7.5, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_6].set("PW_Eco2_6", 5.0, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_7].set("PW_Eco2_7", 2.5, IBK::Unit("-"));

			m_socioculture.m_para_PW[Socioculture::PW_Soc1_1].set("PW_Soc1_1", 5.0, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_2].set("PW_Soc1_2", 5.0, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_3].set("PW_Soc1_3", 0.0, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_4].set("PW_Soc1_4", 5.0, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_6].set("PW_Soc1_6", 5.0, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc2_1].set("PW_Soc2_1", 5.0, IBK::Unit("-"));

			m_technology.m_para_PW[Technology::PW_Tec1_3].set("PW_Tec1_3", 3.0, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec1_4].set("PW_Tec1_4", 2.0, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec1_6].set("PW_Tec1_6", 3.0, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec3_1].set("PW_Tec3_1", 2.0, IBK::Unit("-"));

			m_process.m_para_PW[Process::PW_Pro1_1].set("PW_Pro1_1", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro1_4].set("PW_Pro1_4", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro1_6].set("PW_Pro1_6", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_1].set("PW_Pro2_1", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_3].set("PW_Pro2_3", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_5].set("PW_Pro2_5", 1.7, IBK::Unit("-"));

			m_site.m_para_PW[Site::PW_Site1_1].set("PW_Site1_1", 2.5, IBK::Unit("-"));
			m_site.m_para_PW[Site::PW_Site1_3].set("PW_Site1_3", 1.3, IBK::Unit("-"));
			m_site.m_para_PW[Site::PW_Site1_4].set("PW_Site1_4", 1.3, IBK::Unit("-"));

		} break;

		case Utilities::UT_Assembly: {
			m_environment.m_para_PW[Environment::PW_Env1_1].set("PW_Env1_1", 10.4, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env1_2].set("PW_Env1_2", 5.2, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env1_3].set("PW_Env1_3", 2.1, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_2].set("PW_Env2_2", 2.1, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_3].set("PW_Env2_3", 2.1, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_4].set("PW_Env2_4", 3.1, IBK::Unit("-"));

			m_economy.m_para_PW[Economy::PW_Eco1_1].set("PW_Eco1_1", 10, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_4].set("PW_Eco2_4", 7.5, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_6].set("PW_Eco2_6", 5.0, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_7].set("PW_Eco2_7", 2.5, IBK::Unit("-"));

			m_socioculture.m_para_PW[Socioculture::PW_Soc1_1].set("PW_Soc1_1", 3.8, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_2].set("PW_Soc1_2", 3.8, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_3].set("PW_Soc1_3", 3.8, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_4].set("PW_Soc1_4", 3.8, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_6].set("PW_Soc1_6", 3.8, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc2_1].set("PW_Soc2_1", 5.8, IBK::Unit("-"));

			m_technology.m_para_PW[Technology::PW_Tec1_3].set("PW_Tec1_3", 2.0, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec1_4].set("PW_Tec1_4", 2.0, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec1_6].set("PW_Tec1_6", 3.0, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec3_1].set("PW_Tec3_1", 3.0, IBK::Unit("-"));

			m_process.m_para_PW[Process::PW_Pro1_1].set("PW_Pro1_1", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro1_4].set("PW_Pro1_4", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro1_6].set("PW_Pro1_6", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_1].set("PW_Pro2_1", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_3].set("PW_Pro2_3", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_5].set("PW_Pro2_5", 1.7, IBK::Unit("-"));

			m_site.m_para_PW[Site::PW_Site1_1].set("PW_Site1_1", 2.2, IBK::Unit("-"));
			m_site.m_para_PW[Site::PW_Site1_3].set("PW_Site1_3", 1.7, IBK::Unit("-"));
			m_site.m_para_PW[Site::PW_Site1_4].set("PW_Site1_4", 1.1, IBK::Unit("-"));

		} break;

		case Utilities::UT_Healthcare: {
			m_environment.m_para_PW[Environment::PW_Env1_1].set("PW_Env1_1", 10.4, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env1_2].set("PW_Env1_2", 5.2, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env1_3].set("PW_Env1_3", 2.1, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_2].set("PW_Env2_2", 2.1, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_3].set("PW_Env2_3", 2.1, IBK::Unit("-"));
			m_environment.m_para_PW[Environment::PW_Env2_4].set("PW_Env2_4", 3.1, IBK::Unit("-"));

			m_economy.m_para_PW[Economy::PW_Eco1_1].set("PW_Eco1_1", 10, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_4].set("PW_Eco2_4", 7.5, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_6].set("PW_Eco2_6", 5.0, IBK::Unit("-"));
			m_economy.m_para_PW[Economy::PW_Eco2_7].set("PW_Eco2_7", 2.5, IBK::Unit("-"));

			m_socioculture.m_para_PW[Socioculture::PW_Soc1_1].set("PW_Soc1_1", 3.8, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_2].set("PW_Soc1_2", 3.8, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_3].set("PW_Soc1_3", 3.8, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_4].set("PW_Soc1_4", 3.8, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc1_6].set("PW_Soc1_6", 5.8, IBK::Unit("-"));
			m_socioculture.m_para_PW[Socioculture::PW_Soc2_1].set("PW_Soc2_1", 3.8, IBK::Unit("-"));

			m_technology.m_para_PW[Technology::PW_Tec1_3].set("PW_Tec1_3", 2.2, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec1_4].set("PW_Tec1_4", 2.2, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec1_6].set("PW_Tec1_6", 3.3, IBK::Unit("-"));
			m_technology.m_para_PW[Technology::PW_Tec3_1].set("PW_Tec3_1", 2.2, IBK::Unit("-"));

			m_process.m_para_PW[Process::PW_Pro1_1].set("PW_Pro1_1", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro1_4].set("PW_Pro1_4", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro1_6].set("PW_Pro1_6", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_1].set("PW_Pro2_1", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_3].set("PW_Pro2_3", 1.7, IBK::Unit("-"));
			m_process.m_para_PW[Process::PW_Pro2_5].set("PW_Pro2_5", 1.7, IBK::Unit("-"));

			m_site.m_para_PW[Site::PW_Site1_1].set("PW_Site1_1", 2.2, IBK::Unit("-"));
			m_site.m_para_PW[Site::PW_Site1_3].set("PW_Site1_3", 1.7, IBK::Unit("-"));
			m_site.m_para_PW[Site::PW_Site1_4].set("PW_Site1_4", 1.1, IBK::Unit("-"));

		} break;
		case Utilities::NUM_UT:
		break;
	}

	/*!
	 * reading user's point goals
	 */
	m_environment.m_para_PG[Environment::PG_Env1_1].set("PG_Env1_1", 130, IBK::Unit("-"));
	m_environment.m_para_PG[Environment::PG_Env1_2].set("PG_Env1_2", 117.5, IBK::Unit("-"));
	m_environment.m_para_PG[Environment::PG_Env1_3].set("PG_Env1_3", 100, IBK::Unit("-"));
	m_environment.m_para_PG[Environment::PG_Env2_2].set("PG_Env2_2", 100, IBK::Unit("-"));
	m_environment.m_para_PG[Environment::PG_Env2_3].set("PG_Env2_3", 110, IBK::Unit("-"));
	m_environment.m_para_PG[Environment::PG_Env2_4].set("PG_Env2_4", 115, IBK::Unit("-"));

	m_economy.m_para_PG[Economy::PG_Eco1_1].set("PG_Eco1_1", 110, IBK::Unit("-"));
	m_economy.m_para_PG[Economy::PG_Eco2_4].set("PG_Eco2_4", 110, IBK::Unit("-"));
	m_economy.m_para_PG[Economy::PG_Eco2_6].set("PG_Eco2_6", 110, IBK::Unit("-"));
	m_economy.m_para_PG[Economy::PG_Eco2_7].set("PG_Eco2_7", 130, IBK::Unit("-"));

	m_socioculture.m_para_PG[Socioculture::PG_Soc1_1].set("PG_Soc1_1", 105, IBK::Unit("-"));
	m_socioculture.m_para_PG[Socioculture::PG_Soc1_2].set("PG_Soc1_2", 110, IBK::Unit("-"));
	m_socioculture.m_para_PG[Socioculture::PG_Soc1_3].set("PG_Soc1_3", 110, IBK::Unit("-"));
	m_socioculture.m_para_PG[Socioculture::PG_Soc1_4].set("PG_Soc1_4", 100, IBK::Unit("-"));
	m_socioculture.m_para_PG[Socioculture::PG_Soc1_6].set("PG_Soc1_6", 100, IBK::Unit("-"));
	m_socioculture.m_para_PG[Socioculture::PG_Soc2_1].set("PG_Soc2_1", 100, IBK::Unit("-"));

	m_technology.m_para_PG[Technology::PG_Tec1_3].set("PG_Tec1_3", 100, IBK::Unit("-"));
	m_technology.m_para_PG[Technology::PG_Tec1_4].set("PG_Tec1_4", 130, IBK::Unit("-"));
	m_technology.m_para_PG[Technology::PG_Tec1_6].set("PG_Tec1_6", 155, IBK::Unit("-"));
	m_technology.m_para_PG[Technology::PG_Tec3_1].set("PG_Tec3_1", 115, IBK::Unit("-"));

	m_process.m_para_PG[Process::PG_Pro1_1].set("PG_Pro1_1", 115, IBK::Unit("-"));
	m_process.m_para_PG[Process::PG_Pro1_4].set("PG_Pro1_4", 110, IBK::Unit("-"));
	m_process.m_para_PG[Process::PG_Pro1_6].set("PG_Pro1_6", 100, IBK::Unit("-"));
	m_process.m_para_PG[Process::PG_Pro2_1].set("PG_Pro2_1", 110, IBK::Unit("-"));
	m_process.m_para_PG[Process::PG_Pro2_3].set("PG_Pro2_3", 100, IBK::Unit("-"));
	m_process.m_para_PG[Process::PG_Pro2_5].set("PG_Pro2_5", 105, IBK::Unit("-"));

	m_site.m_para_PG[Site::PG_Site1_1].set("PG_Site1_1", 105, IBK::Unit("-"));
	m_site.m_para_PG[Site::PG_Site1_3].set("PG_Site1_3", 105, IBK::Unit("-"));
	m_site.m_para_PG[Site::PG_Site1_4].set("PG_Site1_4", 110, IBK::Unit("-"));
	/*!
	 * Environment
	 */
	// Env1_1_1
	m_environment.m_env1_1.m_env1_1_1.m_flag_ESOE[DGNB::Env1_1_1::CO2ESOE_HighEnergyStandard].set("CO2ESOE_HighEnergyStandard",true);
	m_environment.m_env1_1.m_env1_1_1.m_flag_ESOE[DGNB::Env1_1_1::CO2ESOE_CO2NeutralOperation].set("CO2ESOE_CO2NeutralOperation",true);
	m_environment.m_env1_1.m_env1_1_1.m_flag_ESOE[DGNB::Env1_1_1::CO2ESOE_PreparedCO2NeutralOperation].set("CO2ESOE_PreparedCO2NeutralOperation",true);
	m_environment.m_env1_1.m_env1_1_1.m_flag_ESOE[DGNB::Env1_1_1::CO2ESOE_SufficiencyStandard].set("CO2ESOE_SufficiencyStandard",true);

	m_environment.m_env1_1.m_env1_1_1.m_flag_ESFV[DGNB::Env1_1_1::CO2ESFV_MaterialOptimization].set("CO2ESFV_MaterialOptimization",true);
	m_environment.m_env1_1.m_env1_1_1.m_flag_ESFV[DGNB::Env1_1_1::CO2ESFV_CO2ReducedMaterials].set("CO2ESFV_CO2ReducedMaterials",true);
	m_environment.m_env1_1.m_env1_1_1.m_flag_ESFV[DGNB::Env1_1_1::CO2ESFV_LowTech].set("CO2ESFV_LowTech",true);
	m_environment.m_env1_1.m_env1_1_1.m_flag_ESFV[DGNB::Env1_1_1::CO2ESFV_CircularDesign].set("CO2ESFV_CircularDesign",true);
	m_environment.m_env1_1.m_env1_1_1.m_flag_ESFV[DGNB::Env1_1_1::CO2ESFV_Longevity].set("CO2ESFV_Longevity",true);

	m_environment.m_env1_1.m_env1_1_1.m_flag_PSOE[DGNB::Env1_1_1::CO2PSOE_ElevatedEnergeticStandard].set("CO2PSOE_ElevatedEnergeticStandard",true);
	m_environment.m_env1_1.m_env1_1_1.m_flag_PSOE[DGNB::Env1_1_1::CO2PSOE_NettoGreenhouseGasNeutralOperation].set("CO2PSOE_NettoGreenhouseGasNeutralOperation",true);
	m_environment.m_env1_1.m_env1_1_1.m_flag_PSOE[DGNB::Env1_1_1::CO2PSOE_SufficiencyStandard].set("CO2PSOE_SufficiencyStandard",true);

	m_environment.m_env1_1.m_env1_1_1.m_flag_PSFV[DGNB::Env1_1_1::CO2PSFV_MaterialOptimization].set("CO2PSFV_MaterialOptimization",true);
	m_environment.m_env1_1.m_env1_1_1.m_flag_PSFV[DGNB::Env1_1_1::CO2PSFV_CO2ReducedMaterials].set("CO2PSFV_CO2ReducedMaterials",true);
	m_environment.m_env1_1.m_env1_1_1.m_flag_PSFV[DGNB::Env1_1_1::CO2PSFV_LowTech].set("CO2PSFV_LowTech",true);
	m_environment.m_env1_1.m_env1_1_1.m_flag_PSFV[DGNB::Env1_1_1::CO2PSFV_CircularDesign].set("CO2PSFV_CircularDesign",true);
	m_environment.m_env1_1.m_env1_1_1.m_flag_PSFV[DGNB::Env1_1_1::CO2PSFV_Longevity].set("CO2PSFV_Longevity",true);

	m_environment.m_env1_1.m_env1_1_1.m_flag_PSEO[DGNB::Env1_1_1::CO2PSEO_LogisticsAndSiteOperationsOptimizedForEmission].set("CO2PSEO_LogisticsAndSiteOperationsOptimizedForEmission",true);

	m_environment.m_env1_1.m_env1_1_1.m_flag_A2030IPB[DGNB::Env1_1_1::CO2A2030IPB_IntegrationOfPreexistingBuilding].set("CO2A2030IPB_IntegrationOfPreexistingBuilding",true);

	m_environment.m_env1_1.m_env1_1_1.m_flag_A2030MO[DGNB::Env1_1_1::CO2A2030MO_ForEmission].set("CO2A2030MO_ForEmission",true);

	// Env1.1.2
	m_environment.m_env1_1.m_env1_1_2.m_flag_LCCO2DISC[DGNB::Env1_1_2::LCCO2Disc_GreenHouseGasBalance].set("LCCO2Disc_GreenHouseGasBalance",true);
	m_environment.m_env1_1.m_env1_1_2.m_flag_LCCO2DISC[DGNB::Env1_1_2::LCCO2Disc_NonRenewablePrimaryEnergyBalance].set("LCCO2Disc_NonRenewablePrimaryEnergyBalance",true);

	m_environment.m_env1_1.m_env1_1_2.m_flag_LCCO2IER[DGNB::Env1_1_2::LCCO2IER_ResultsSubmitted].set("LCCO2IER_ResultsSubmitted",true);

	m_environment.m_env1_1.m_env1_1_2.m_flag_LCCO2A2030LCCPA[DGNB::Env1_1_2::LCCO2A2030LCCPA_AgendaSubmitted].set("LCCO2A2030LCCPA_AgendaSubmitted",true);

	m_environment.m_env1_1.m_env1_1_2.m_flag_LCCO2A2030CPTS[DGNB::Env1_1_2::LCCO2A2030CPTS_AgendaSubmitted].set("LCCO2A2030CPTS_AgendaSubmitted",true);

	m_environment.m_env1_1.m_env1_1_2.m_flag_LCCO2BFO[DGNB::Env1_1_2::LCCO2BFO_ClimateProtectionAgendaClimateNeutralOperation].set("LCCO2BFO_ClimateProtectionAgendaClimateNeutralOperation",true);
	m_environment.m_env1_1.m_env1_1_2.m_flag_LCCO2BFO[DGNB::Env1_1_2::LCCO2BFO_AmbitiousClimateProtectionAgenda].set("LCCO2BFO_AmbitiousClimateProtectionAgenda",true);
	m_environment.m_env1_1.m_env1_1_2.m_flag_LCCO2BFO[DGNB::Env1_1_2::LCCO2BFO_NetGreenhouseHeutrallyClimateNeutrallyOperatedBuilding].set("LCCO2BFO_NetGreenhouseHeutrallyClimateNeutrallyOperatedBuilding",true);

	m_environment.m_env1_1.m_env1_1_2.m_flag_LCCO2BFSCO2RCP[DGNB::Env1_1_2::LCCO2BFSCO2RCP_ResultsSubmitted].set("LCCO2BFSCO2RCP_ResultsSubmitted",true);

	m_environment.m_env1_1.m_env1_1_2.m_para[Env1_1_2::P_RefEnv1_1_2_2_1].set("RefEnv1_1_2_2_1", 100, IBK::Unit("-"));							// ToDo Einheit kg/m2a	[kg pro m² und Jahr]
	m_environment.m_env1_1.m_env1_1_2.m_para[Env1_1_2::P_CurrentValueEnv1_1_2_2_1].set("CurrentValueEnv1_1_2_2_1", 45, IBK::Unit("-"));			// ToDo Einheit kg/m2a	[kg pro m² und Jahr]
	m_environment.m_env1_1.m_env1_1_2.m_para[Env1_1_2::P_RefEnv1_1_2_5_1].set("RefEnv1_1_2_5_1", 100, IBK::Unit("-"));							// ToDo Einheit kg/m2a	[kg pro m² und Jahr]
	m_environment.m_env1_1.m_env1_1_2.m_para[Env1_1_2::P_CurrentValueEnv1_1_2_5_1].set("CurrentValueEnv1_1_2_5_1", 45, IBK::Unit("-"));			// ToDo Einheit kg/m2a	[kg pro m² und Jahr]

	// Ent1.1.3
	m_environment.m_env1_1.m_env1_1_3.m_flag_CVAEILCPEB[DGNB::Env1_1_3::CVAEILCPEB_ResultsSubmitted].set("CVAEILCPEB_ResultsSubmitted",true);

	m_environment.m_env1_1.m_env1_1_3.m_flag_CVAEIWRAEI[DGNB::Env1_1_3::CVAEIWRAEI_ResultsSubmitted].set("CVAEIWRAEI_ResultsSubmitted",true);

	m_environment.m_env1_1.m_env1_1_3.m_para[Env1_1_3::P_RefEnv1_1_3_1_1].set("RefEnv1_1_3_1_1", 10, IBK::Unit("kWh/m2a"));						// ToDo? Einheit kWh/m2a	[kWh pro m² und Jahr]
	m_environment.m_env1_1.m_env1_1_3.m_para[Env1_1_3::P_CurrentValueEnv1_1_3_1_1].set("CurrentValueEnv1_1_3_1_1", 4, IBK::Unit("kWh/m2a"));	// ToDo? Einheit kWh/m2a	[kWh pro m² und Jahr]
	m_environment.m_env1_1.m_env1_1_3.m_para[Env1_1_3::P_RefEnv1_1_3_1_2POCP].set("RefEnv1_1_3_1_2POCP", 10, IBK::Unit("-"));					// ToDo Einheit C2H4e/m2a	[troposphärisches Ozon pro m² und Jahr]
	m_environment.m_env1_1.m_env1_1_3.m_para[Env1_1_3::P_CurrentValueEnv1_1_3_1_2POCP].set("CurrentValueEnv1_1_3_1_2POCP", 4, IBK::Unit("-"));	// ToDo Einheit C2H4e/m2a	[troposphärisches Ozon pro m² und Jahr]
	m_environment.m_env1_1.m_env1_1_3.m_para[Env1_1_3::P_RefEnv1_1_3_1_2AP].set("RefEnv1_1_3_1_2AP", 10, IBK::Unit("-"));						// ToDo Einheit SO2e/m2a	[Versauerungspotenzial Boden&Wasser pro m² und Jahr]
	m_environment.m_env1_1.m_env1_1_3.m_para[Env1_1_3::P_CurrentValueEnv1_1_3_1_2AP].set("CurrentValueEnv1_1_3_1_2AP", 4, IBK::Unit("-"));		// ToDo Einheit SO2e/m2a	[Versauerungspotenzial Boden&Wasser pro m² und Jahr]
	m_environment.m_env1_1.m_env1_1_3.m_para[Env1_1_3::P_RefEnv1_1_3_1_2EP].set("RefEnv1_1_3_1_2EP", 10, IBK::Unit("-"));						// ToDo Einheit PO43/m2a	[Eutrophierungspotenzial pro m² und Jahr]
	m_environment.m_env1_1.m_env1_1_3.m_para[Env1_1_3::P_CurrentValueEnv1_1_3_1_2EP].set("CurrentValueEnv1_1_3_1_2EP", 4, IBK::Unit("-"));		// ToDo Einheit PO43/m2a	[Eutrophierungspotenzial pro m² und Jahr]
	m_environment.m_env1_1.m_env1_1_3.m_para[Env1_1_3::P_RefEnv1_1_3_1_2FW].set("RefEnv1_1_3_1_2FW", 10, IBK::Unit("-"));						// ToDo Einheit m3/m2a	[m3 Frischwasser pro m² und Jahr]
	m_environment.m_env1_1.m_env1_1_3.m_para[Env1_1_3::P_CurrentValueEnv1_1_3_1_2FW].set("CurrentValueEnv1_1_3_1_2FW", 4, IBK::Unit("-"));		// ToDo Einheit m3/m2a	[m3 Frischwasser pro m² und Jahr]

	// Env1.2.1
	m_environment.m_env1_2.m_env1_2_1.m_flag_EFMA[DGNB::Env1_2_1::EFMA_QS1SimplifiedDocumentation].set("EFMA_QS1SimplifiedDocumentation",true);
	m_environment.m_env1_2.m_env1_2_1.m_flag_EFMA[DGNB::Env1_2_1::EFMA_QS2SimplifiedDocumentation].set("EFMA_QS2SimplifiedDocumentation",true);
	m_environment.m_env1_2.m_env1_2_1.m_flag_EFMA[DGNB::Env1_2_1::EFMA_QS2MaterialEcologicalComponentCatalogue].set("EFMA_QS2MaterialEcologicalComponentCatalogue",true);
	m_environment.m_env1_2.m_env1_2_1.m_flag_EFMA[DGNB::Env1_2_1::EFMA_QS3MaterialEcologicalComponentCatalogue].set("EFMA_QS3MaterialEcologicalComponentCatalogue",true);
	m_environment.m_env1_2.m_env1_2_1.m_flag_EFMA[DGNB::Env1_2_1::EFMA_QS4MaterialEcologicalComponentCatalogue].set("EFMA_QS4MaterialEcologicalComponentCatalogue",true);

	m_environment.m_env1_2.m_env1_2_1.m_flag_EFMBRC[DGNB::Env1_2_1::EFMBRC_QS1SimplifiedDocumentation].set("EFMBRC_QS1SimplifiedDocumentation",true);
	m_environment.m_env1_2.m_env1_2_1.m_flag_EFMBRC[DGNB::Env1_2_1::EFMBRC_QS2SimplifiedDocumentation].set("EFMBRC_QS2SimplifiedDocumentation",true);
	m_environment.m_env1_2.m_env1_2_1.m_flag_EFMBRC[DGNB::Env1_2_1::EFMBRC_QS2MaterialEcologicalComponentCatalogue].set("EFMBRC_QS2MaterialEcologicalComponentCatalogue",true);
	m_environment.m_env1_2.m_env1_2_1.m_flag_EFMBRC[DGNB::Env1_2_1::EFMBRC_QS3MaterialEcologicalComponentCatalogue].set("EFMBRC_QS3MaterialEcologicalComponentCatalogue",true);
	m_environment.m_env1_2.m_env1_2_1.m_flag_EFMBRC[DGNB::Env1_2_1::EFMBRC_QS4MaterialEcologicalComponentCatalogue].set("EFMBRC_QS4MaterialEcologicalComponentCatalogue",true);

	m_environment.m_env1_2.m_env1_2_1.m_flag_EFMBSC[DGNB::Env1_2_1::EFMBSC_QS1SimplifiedDocumentation].set("EFMBSC_QS1SimplifiedDocumentation",true);
	m_environment.m_env1_2.m_env1_2_1.m_flag_EFMBSC[DGNB::Env1_2_1::EFMBSC_QS2SimplifiedDocumentation].set("EFMBSC_QS2SimplifiedDocumentation",true);
	m_environment.m_env1_2.m_env1_2_1.m_flag_EFMBSC[DGNB::Env1_2_1::EFMBSC_QS2MaterialEcologicalComponentCatalogue].set("EFMBSC_QS2MaterialEcologicalComponentCatalogue",true);
	m_environment.m_env1_2.m_env1_2_1.m_flag_EFMBSC[DGNB::Env1_2_1::EFMBSC_QS3MaterialEcologicalComponentCatalogue].set("EFMBSC_QS3MaterialEcologicalComponentCatalogue",true);
	m_environment.m_env1_2.m_env1_2_1.m_flag_EFMBSC[DGNB::Env1_2_1::EFMBSC_QS4MaterialEcologicalComponentCatalogue].set("EFMBSC_QS4MaterialEcologicalComponentCatalogue",true);

	m_environment.m_env1_2.m_env1_2_1.m_flag_EFMA2030[DGNB::Env1_2_1::EFMA2030_1WaivingOfCrossOutCriterionQS3].set("EFMA2030_1WaivingOfCrossOutCriterionQS3",true);
	m_environment.m_env1_2.m_env1_2_1.m_flag_EFMA2030[DGNB::Env1_2_1::EFMA2030_2WaivingOfCrossOutCriterionQS4].set("EFMA2030_2WaivingOfCrossOutCriterionQS4",true);
	m_environment.m_env1_2.m_env1_2_1.m_flag_EFMA2030[DGNB::Env1_2_1::EFMA2030_MeasurementsTakenForSufficientStructure].set("EFMA2030_MeasurementsTakenForSufficientStructure",true);
	m_environment.m_env1_2.m_env1_2_1.m_flag_EFMA2030[DGNB::Env1_2_1::EFMA2030_WaivingOfUnsolveableConnections].set("EFMA2030_WaivingOfUnsolveableConnections",true);
	m_environment.m_env1_2.m_env1_2_1.m_flag_EFMA2030[DGNB::Env1_2_1::EFMA2030_AllRowsOnlyFeatureProductsOfSVHCOfMax0_1Percent].set("EFMA2030_AllRowsOnlyFeatureProductsOfSVHCOfMax0_1Percent",true);

	m_environment.m_env1_2.m_env1_2_1.m_flag_EFMEPQS123[DGNB::Env1_2_1::EFMEPQS123_RealizationOfCoolingSystemWithoutHalogenatedCoolingAgent].set("EFMEPQS123_RealizationOfCoolingSystemWithoutHalogenatedCoolingAgent",true);

	m_environment.m_env1_2.m_env1_2_1.m_para[Env1_2_1::P_EFMA2030_MeasurementsTakenForSufficientStructureNumberOfRows].set("EFMA2030_MeasurementsTakenForSufficientStructureNumberOfRows", 5, IBK::Unit("-"));
	m_environment.m_env1_2.m_env1_2_1.m_para[Env1_2_1::P_EFMA2030_WaivingOfUnsolveableConnectionsNumberOfRows].set("EFMA2030_WaivingOfUnsolveableConnectionsNumberOfRows", 5, IBK::Unit("-"));

	// Env1.3.1
	m_environment.m_env1_3.m_env1_3_1.m_flag_RURPESCD[DGNB::Env1_3_1::RURPESCD_DeclarationOfDiligenceGiven].set("RURPESCD_DeclarationOfDiligenceGiven",true);

	m_environment.m_env1_3.m_env1_3_1.m_flag_RURPERURP[DGNB::Env1_3_1::RURPERURP_RegularIntegrationOfMeasures].set("RURPERURP_RegularIntegrationOfMeasures",true);

	m_environment.m_env1_3.m_env1_3_1.m_flag_RURPERURED[DGNB::Env1_3_1::RURPERURED_PartsCatalogue].set("RURPERURED_PartsCatalogue",true);

	// Env1.3.2
	m_environment.m_env1_3.m_env1_3_2.m_flag_RRMCRRM[DGNB::Env1_3_2::RRMCRRM_ResultSumbitted].set("RRMCRRM_ResultSumbitted",true);

	m_environment.m_env1_3.m_env1_3_2.m_flag_RRMRRWPSR[DGNB::Env1_3_2::RRMRRWPSR_DetailedMethod].set("RRMRRWPSR_DetailedMethod",true);
	m_environment.m_env1_3.m_env1_3_2.m_flag_RRMRRWPSR[DGNB::Env1_3_2::RRMRRWPSR_SimplifiedMethod].set("RRMRRWPSR_SimplifiedMethod",false);

	m_environment.m_env1_3.m_env1_3_2.m_flag_RRMPWMSF[DGNB::Env1_3_2::RRMPWMSF_PercentageMinimum50].set("RRMPWMSF_PercentageMinimum50",true);

	m_environment.m_env1_3.m_env1_3_2.m_flag_RRMPRCEWMPS[DGNB::Env1_3_2::RRMPRCEWMPS_Percentage].set("RRMPRCEWMPS_Percentage",true);

	m_environment.m_env1_3.m_env1_3_2.m_para[Env1_3_2::P_Env1_3_2_1NumberOfPartsFromDiffManufacturers].set("Env1_3_2_1NumberOfPartsFromDiffManufacturers", 10, IBK::Unit("-"));
	m_environment.m_env1_3.m_env1_3_2.m_para[Env1_3_2::P_ReferenceValueEnv1_3_2_2RRMRRWPSR_WeightingCostGroup].set("ReferenceValueEnv1_3_2_2RRMRRWPSR_WeightingCostGroup", 1, IBK::Unit("-"));
	m_environment.m_env1_3.m_env1_3_2.m_para[Env1_3_2::P_CurrentValueEnv1_3_2_2RRMRRWPSR_DetailedMethodSumOfMassPercentOfPartsOfQS4].set("CurrentValueEnv1_3_2_2RRMRRWPSR_DetailedMethodSumOfMassPercentOfPartsOfQS4", 100, IBK::Unit("-"));
	m_environment.m_env1_3.m_env1_3_2.m_para[Env1_3_2::P_CurrentValueEnv1_3_2_2RRMRRWPSR_DetailedMethodSumOfMassPercentOfPartsOfQS2].set("CurrentValueEnv1_3_2_2RRMRRWPSR_DetailedMethodSumOfMassPercentOfPartsOfQS2", 0, IBK::Unit("-"));
	m_environment.m_env1_3.m_env1_3_2.m_para[Env1_3_2::P_CurrentValueEnv1_3_2_2RRMRRWPSR_SimplifiedMethodSumOfNumberOfPartsOfQS4].set("CurrentValueEnv1_3_2_2RRMRRWPSR_SimplifiedMethodSumOfNumberOfPartsOfQS4", 0, IBK::Unit("-"));
	m_environment.m_env1_3.m_env1_3_2.m_para[Env1_3_2::P_CurrentValueEnv1_3_2_2RRMRRWPSR_SimplifiedMethodSumOfNumberOfPartsOfQS2].set("CurrentValueEnv1_3_2_2RRMRRWPSR_SimplifiedMethodSumOfNumberOfPartsOfQS2", 0, IBK::Unit("-"));

	// Env2.2.1
	m_environment.m_env2_2.m_env2_2_1.m_flag_DWDWWVSCWU[DGNB::Env2_2_1::DWDWWVSCWU_ConceptDevelopedInEarlyPlanningStage].set("DWDWWVSCWU_ConceptDevelopedInEarlyPlanningStage",true);
	m_environment.m_env2_2.m_env2_2_1.m_flag_DWDWWVSCWU[DGNB::Env2_2_1::DWDWWVSCWU_FlowClassesOfSanitaryEquipment].set("DWDWWVSCWU_FlowClassesOfSanitaryEquipment",true);
	m_environment.m_env2_2.m_env2_2_1.m_flag_DWDWWVSCWU[DGNB::Env2_2_1::DWDWWVSCWU_LocalWaterUsageIndex].set("DWDWWVSCWU_LocalWaterUsageIndex",true);
	m_environment.m_env2_2.m_env2_2_1.m_flag_DWDWWVSCWU[DGNB::Env2_2_1::DWDWWVSCWU_PotentialOfRainAndGrayWaterUsage].set("DWDWWVSCWU_PotentialOfRainAndGrayWaterUsage",true);
	m_environment.m_env2_2.m_env2_2_1.m_flag_DWDWWVSCWU[DGNB::Env2_2_1::DWDWWVSCWU_EfficentWateringOfOutsideAreas].set("DWDWWVSCWU_EfficentWateringOfOutsideAreas",true);
	m_environment.m_env2_2.m_env2_2_1.m_flag_DWDWWVSCWU[DGNB::Env2_2_1::DWDWWVSCWU_EdequatePlanningOfWaterUsageMeteringPoint].set("DWDWWVSCWU_EdequatePlanningOfWaterUsageMeteringPoint",true);

	m_environment.m_env2_2.m_env2_2_1.m_flag_DWDWWVUSC[DGNB::Env2_2_1::DWDWWVUSC_ConceptUpdatedToPlanningProgress].set("DWDWWVUSC_ConceptUpdatedToPlanningProgress",true);
	m_environment.m_env2_2.m_env2_2_1.m_flag_DWDWWVUSC[DGNB::Env2_2_1::DWDWWVUSC_ImplementationOfDemonstrablyRelevantAspects].set("DWDWWVUSC_ImplementationOfDemonstrablyRelevantAspects",true);

	// Env2.2.2
	m_environment.m_env2_2.m_env2_2_2.m_flag_DWDWWVWUI[DGNB::Env2_2_2::DWDWWVWUI_ResultsSubmitted].set("DWDWWVWUI_ResultsSubmitted",true);

	m_environment.m_env2_2.m_env2_2_2.m_para[DGNB::Env2_2_2::P_CurrentValue_env2_2WaterUsageIndex].set("CurrentValue_env2_2WaterUsageIndex", 50, IBK::Unit("-"));						// ToDo Einheit m2/a
	m_environment.m_env2_2.m_env2_2_2.m_para[DGNB::Env2_2_2::P_RefValue_env2_2DWDWWVWUI_DynamicThreshold].set("RefValue_env2_2DWDWWVWUI_DynamicThreshold", 200, IBK::Unit("-"));		// ToDo Einheit m2/a

	// Env2.2.3
	m_environment.m_env2_2.m_env2_2_3.m_flag_DWDWWVIR[DGNB::Env2_2_3::DWDWWVIR_NoPlannedIrrigationWithDrinkingWater].set("DWDWWVIR_NoPlannedIrrigationWithDrinkingWater",true);
	m_environment.m_env2_2.m_env2_2_3.m_flag_DWDWWVIR[DGNB::Env2_2_3::DWDWWVIR_OutsideAreasIncludeRainwaterIrrigationSetup].set("DWDWWVIR_OutsideAreasIncludeRainwaterIrrigationSetup",true);

	// Env2.2.4
	m_environment.m_env2_2.m_env2_2_4.m_flag_DWDWWVDIQI[DGNB::Env2_2_4::DWDWWVDIQI_DegreeOfIntegrationIntoPreexistingInfrastructureAndUseOfSeparationReductionEtc].set("DWDWWVDIQI_DegreeOfIntegrationIntoPreexistingInfrastructureAndUseOfSeparationReductionEtc",true);

	// Env2.2.5
	m_environment.m_env2_2.m_env2_2_5.m_flag_DWDWWVSC[DGNB::Env2_2_5::DWDWWVSC_ResultsSubmitted].set("DWDWWVSC_ResultsSubmitted",true);
	m_environment.m_env2_2.m_env2_2_5.m_flag_DWDWWVSC[DGNB::Env2_2_5::DWDWWVSC_InfiltrationPossible].set("DWDWWVSC_InfiltrationPossible",true);
	m_environment.m_env2_2.m_env2_2_5.m_flag_DWDWWVSC[DGNB::Env2_2_5::DWDWWVSC_UndercuttingTheDrainagePortion].set("DWDWWVSC_UndercuttingTheDrainagePortion",true);

	m_environment.m_env2_2.m_env2_2_5.m_flag_DWDWWVDWS[DGNB::Env2_2_5::DWDWWVDWS_LowEnergyDrinkingWaterManagementSystem].set("DWDWWVDWS_LowEnergyDrinkingWaterManagementSystem",true);
	m_environment.m_env2_2.m_env2_2_5.m_flag_DWDWWVDWS[DGNB::Env2_2_5::DWDWWVDWS_ObservationOfDrinkingWaterSanitation].set("DWDWWVDWS_ObservationOfDrinkingWaterSanitation",true);
	m_environment.m_env2_2.m_env2_2_5.m_flag_DWDWWVDWS[DGNB::Env2_2_5::DWDWWVDWS_WarmWaterReducedToOperativeMinimum].set("DWDWWVDWS_WarmWaterReducedToOperativeMinimum",true);
	m_environment.m_env2_2.m_env2_2_5.m_flag_DWDWWVDWS[DGNB::Env2_2_5::DWDWWVDWS_ColdWaterLessThan20Degrees].set("DWDWWVDWS_ColdWaterLessThan20Degrees",true);

	m_environment.m_env2_2.m_env2_2_5.m_para[DGNB::Env2_2_5::P_CurrentValue_env2_2DWDWWVSC_WaterEconomyTotalDeviation].set("CurrentValue_env2_2DWDWWVSC_WaterEconomyTotalDeviation", 8, IBK::Unit("---"));				// ToDo Einheit % SO oder anders?
	m_environment.m_env2_2.m_env2_2_5.m_para[DGNB::Env2_2_5::P_CurrentValue_env2_2DWDWWVSC_DeviationFromEvaporationPortion].set("CurrentValue_env2_2DWDWWVSC_DeviationFromEvaporationPortion", 6, IBK::Unit("---"));	// ToDo Einheit % SO oder anders?
	m_environment.m_env2_2.m_env2_2_5.m_para[DGNB::Env2_2_5::P_CurrentValue_env2_2DWDWWVSC_DeviationFromInfiltrationPortion].set("CurrentValue_env2_2DWDWWVSC_DeviationFromInfiltrationPortion", 6, IBK::Unit("---"));	// ToDo Einheit % SO oder anders?

	// Env2.3.1
	m_environment.m_env2_3.m_env2_3_1.m_flag_ADDC[DGNB::Env2_3_1::ADDC_OutlyingDevelopmentArea].set("ADDC_OutlyingDevelopmentArea",true);
	m_environment.m_env2_3.m_env2_3_1.m_flag_ADDC[DGNB::Env2_3_1::ADDC_InternalDevelopmentArea].set("ADDC_InternalDevelopmentArea",true);
	m_environment.m_env2_3.m_env2_3_1.m_flag_ADDC[DGNB::Env2_3_1::ADDC_DevelopmentAreaInPriorStructuralOrInfrastructuralUse].set("ADDC_DevelopmentAreaInPriorStructuralOrInfrastructuralUse",true);

	// Env2.3.2
	m_environment.m_env2_3.m_env2_3_2.m_flag_ADDSAM[DGNB::Env2_3_2::ADDSAM_ResultsSubmitted].set("ADDSAM_ResultsSubmitted",true);
	m_environment.m_env2_3.m_env2_3_2.m_flag_ADDSAM[DGNB::Env2_3_2::ADDSAM_ImplementationOfAdjustmentMeasures].set("ADDSAM_ImplementationOfAdjustmentMeasures",true);

	m_environment.m_env2_3.m_env2_3_2.m_flag_ADCEBU[DGNB::Env2_3_2::ADCEBU_30PercentOfAreaUnsealedPreConstruction].set("ADCEBU_30PercentOfAreaUnsealedPreConstruction",true);

	m_environment.m_env2_3.m_env2_3_2.m_para[DGNB::Env2_3_2::P_CurrentValue_env2_3_2ADDSAM_DegreeOfSealing].set("CurrentValue_env2_3_2ADDSAM_DegreeOfSealing", 40, IBK::Unit("---"));			// ToDo Einheit % SO oder anders?

	// Env2.3.3
	m_environment.m_env2_3.m_env2_3_3.m_flag_ADSQISR[DGNB::Env2_3_3::ADSQISR_ExaminationOfSiteAndPreexistingBuildingForContamination].set("ADSQISR_ExaminationOfSiteAndPreexistingBuildingForContamination",true);
	m_environment.m_env2_3.m_env2_3_3.m_flag_ADSQISR[DGNB::Env2_3_3::ADSQISR_LowContaminationRecyclingAndDisposal].set("ADSQISR_LowContaminationRecyclingAndDisposal",true);
	m_environment.m_env2_3.m_env2_3_3.m_flag_ADSQISR[DGNB::Env2_3_3::ADSQISR_HighContaminationDisposal].set("ADSQISR_HighContaminationDisposal",true);

	m_environment.m_env2_3.m_env2_3_3.m_flag_ADSQICEBISSRS[DGNB::Env2_3_3::ADSQICEBISSRS_InSituRestorationChemicalOrBiologicalNoSoilExchange].set("ADSQICEBISSRS_InSituRestorationChemicalOrBiologicalNoSoilExchange",true);
	m_environment.m_env2_3.m_env2_3_3.m_flag_ADSQICEBISSRS[DGNB::Env2_3_3::ADSQICEBISSRS_LowDegreeOfTransformationOfSoilAndSafeguardingOfContaminants].set("ADSQICEBISSRS_LowDegreeOfTransformationOfSoilAndSafeguardingOfContaminants",true);
	m_environment.m_env2_3.m_env2_3_3.m_flag_ADSQICEBISSRS[DGNB::Env2_3_3::ADSQICEBISSRS_RestorationOfGroundWaterDamages].set("ADSQICEBISSRS_RestorationOfGroundWaterDamages",true);

	// Env2.4.1
	m_environment.m_env2_4.m_env2_4_1.m_flag_BDOSCEBDS[DGNB::Env2_4_1::BDOSCEBDS_ExtensiveAndLongTermStrategy].set("BDOSCEBDS_ExtensiveAndLongTermStrategy",true);

	// Env2.4.2
	m_environment.m_env2_4.m_env2_4_2.m_flag_BDOSBBSA[DGNB::Env2_4_2::BDOSBBSA_ResultsSubmitted].set("BDOSBBSA_ResultsSubmitted",true);

	m_environment.m_env2_4.m_env2_4_2.m_flag_BDOSBGR[DGNB::Env2_4_2::BDOSBGR_ResultsSubmitted].set("BDOSBGR_ResultsSubmitted",true);

	m_environment.m_env2_4.m_env2_4_2.m_flag_BDOSBAFA2030VB[DGNB::Env2_4_2::BDOSBAFA2030VB_ResultsSubmitted].set("BDOSBAFA2030VB_ResultsSubmitted",true);

	m_environment.m_env2_4.m_env2_4_2.m_flag_BDOSDS[DGNB::Env2_4_2::BDOSDS_StructureTypesEmbeddedInBiodiversitySupportingConcept].set("BDOSDS_StructureTypesEmbeddedInBiodiversitySupportingConcept",true);
	m_environment.m_env2_4.m_env2_4_2.m_flag_BDOSDS[DGNB::Env2_4_2::BDOSDS_TwoBiotopeStructureTypesAvailable].set("BDOSDS_TwoBiotopeStructureTypesAvailable",true);

	m_environment.m_env2_4.m_env2_4_2.m_flag_BDOSA2030FS[DGNB::Env2_4_2::BDOSA2030FS_EmploymentOfSOTAMethodsForImprovementOfSoilQualityAndCultivationOfHumus].set("BDOSA2030FS_EmploymentOfSOTAMethodsForImprovementOfSoilQualityAndCultivationOfHumus",true);

	m_environment.m_env2_4.m_env2_4_2.m_para[DGNB::Env2_4_2::P_CurrentValue_env2_4_2BDOSBBSA_PercentageOfBiodiversitySupportingOutdoorArea].set("CurrentValue_env2_4_2BDOSBBSA_PercentageOfBiodiversitySupportingOutdoorArea", 100, IBK::Unit("---"));		// ToDo Einheit % SO oder anders?
	m_environment.m_env2_4.m_env2_4_2.m_para[DGNB::Env2_4_2::P_CurrentValue_env2_4_2BDOSBGR_PercentageOfGreenRoof].set("CurrentValue_env2_4_2BDOSBGR_PercentageOfGreenRoof", 70, IBK::Unit("---"));															// ToDo Einheit % SO oder anders?
	m_environment.m_env2_4.m_env2_4_2.m_para[DGNB::Env2_4_2::P_CurrentValue_env2_4_2BDOSBAFA2030VB_BFFOfSite].set("CurrentValue_env2_4_2BDOSBAFA2030VB_BFFOfSite", 0.85, IBK::Unit("-"));

	// Env2.4.3
	m_environment.m_env2_4.m_env2_4_3.m_flag_BDOSVNEIPS[DGNB::Env2_4_3::BDOSVNEIPS_NoFurtherEmploymentOfInvasivePlantSpecies].set("BDOSVNEIPS_NoFurtherEmploymentOfInvasivePlantSpecies",true);
	m_environment.m_env2_4.m_env2_4_3.m_flag_BDOSVNEIPS[DGNB::Env2_4_3::BDOSVNEIPS_PlanForControlOfPreexistingInvasiveSpecies].set("BDOSVNEIPS_PlanForControlOfPreexistingInvasiveSpecies",true);

	m_environment.m_env2_4.m_env2_4_3.m_flag_BDOSVEDLSSS[DGNB::Env2_4_3::BDOSVEDLSSS_SelectionBasedOnBiodiversitySupportingConcept].set("BDOSVEDLSSS_SelectionBasedOnBiodiversitySupportingConcept",true);
	m_environment.m_env2_4.m_env2_4_3.m_flag_BDOSVEDLSSS[DGNB::Env2_4_3::BDOSVEDLSSS_ResultSubmitted].set("BDOSVEDLSSS_ResultSubmitted",true);

	m_environment.m_env2_4.m_env2_4_3.m_flag_BDOSVA2030PVHEV[DGNB::Env2_4_3::BDOSVA2030PVHEV_PreservationOfSaidVegetationDuringConstructionAndAfter].set("BDOSVA2030PVHEV_PreservationOfSaidVegetationDuringConstructionAndAfter",true);

	m_environment.m_env2_4.m_env2_4_3.m_para[DGNB::Env2_4_3::P_CurrentValue_env2_4_3BDOSVEDLSSS_SelectionIsLocalDiverseAndSuitedToSitePointResult].set("CurrentValue_env2_4_3BDOSVEDLSSS_SelectionIsLocalDiverseAndSuitedToSitePointResult", 20, IBK::Unit("-"));

	// Env2.4.4
	m_environment.m_env2_4.m_env2_4_4.m_flag_BDOSRSBI[DGNB::Env2_4_4::BDOSRSBI_ConceptDeveloped].set("BDOSRSBI_ConceptDeveloped",true);

	// Env2.4.5
	m_environment.m_env2_4.m_env2_4_5.m_flag_BDOSRNIIC[DGNB::Env2_4_5::BDOSRNIIC_IlluminationConceptForAvoidanceOfLightPollution].set("BDOSRNIIC_IlluminationConceptForAvoidanceOfLightPollution",true);
	m_environment.m_env2_4.m_env2_4_5.m_flag_BDOSRNIIC[DGNB::Env2_4_5::BDOSRNIIC_HarmlessLightSourceOrientation].set("BDOSRNIIC_HarmlessLightSourceOrientation",true);
	m_environment.m_env2_4.m_env2_4_5.m_flag_BDOSRNIIC[DGNB::Env2_4_5::BDOSRNIIC_HarmlessLightColourAndLightSourceTemperature].set("BDOSRNIIC_HarmlessLightColourAndLightSourceTemperature",true);
	m_environment.m_env2_4.m_env2_4_5.m_flag_BDOSRNIIC[DGNB::Env2_4_5::BDOSRNIIC_NoUnwantedBlindingEffects].set("BDOSRNIIC_NoUnwantedBlindingEffects",true);

	m_environment.m_env2_4.m_env2_4_5.m_flag_BDOSRNIAT[DGNB::Env2_4_5::BDOSRNIAT_EvaluationOfDangersToAnimals].set("BDOSRNIAT_EvaluationOfDangersToAnimals",true);

	m_environment.m_env2_4.m_env2_4_5.m_flag_BDOSRNICSP[DGNB::Env2_4_5::BDOSRNICSP_AccordanceWithEnvironmentProtectionAndBiodiversityInterests].set("BDOSRNICSP_AccordanceWithEnvironmentProtectionAndBiodiversityInterests",true);

	// Env2.4.6
	m_environment.m_env2_4.m_env2_4_6.m_flag_BDOSPCMDMCC[DGNB::Env2_4_6::BDOSPCMDMCC_ContractSubmitted].set("BDOSPCMDMCC_ContractSubmitted",true);
	m_environment.m_env2_4.m_env2_4_6.m_flag_BDOSPCMDMCC[DGNB::Env2_4_6::BDOSPCMDMCC_EcologicalCarePlanSubmitted].set("BDOSPCMDMCC_EcologicalCarePlanSubmitted",true);
	m_environment.m_env2_4.m_env2_4_6.m_flag_BDOSPCMDMCC[DGNB::Env2_4_6::BDOSPCMDMCC_NoUseOfTurfMaterials].set("BDOSPCMDMCC_NoUseOfTurfMaterials",true);
	m_environment.m_env2_4.m_env2_4_6.m_flag_BDOSPCMDMCC[DGNB::Env2_4_6::BDOSPCMDMCC_NoUseOfHerbicidesOnSite].set("BDOSPCMDMCC_NoUseOfHerbicidesOnSite",true);
	m_environment.m_env2_4.m_env2_4_6.m_flag_BDOSPCMDMCC[DGNB::Env2_4_6::BDOSPCMDMCC_NoUseOfBiocidesOnSite].set("BDOSPCMDMCC_NoUseOfBiocidesOnSite",true);
	m_environment.m_env2_4.m_env2_4_6.m_flag_BDOSPCMDMCC[DGNB::Env2_4_6::BDOSPCMDMCC_NoUseOfChemicalFertiliserOnSite].set("BDOSPCMDMCC_NoUseOfChemicalFertiliserOnSite",true);

	m_environment.m_env2_4.m_env2_4_6.m_flag_BDOSPCMMSC[DGNB::Env2_4_6::BDOSPCMMSC_SimpleMonitoringOfNestingAids].set("BDOSPCMMSC_SimpleMonitoringOfNestingAids",true);
	m_environment.m_env2_4.m_env2_4_6.m_flag_BDOSPCMMSC[DGNB::Env2_4_6::BDOSPCMMSC_ExtensiveMonitoring].set("BDOSPCMMSC_ExtensiveMonitoring",true);

	// Env2.4.Alt
	m_environment.m_env2_4.m_env2_4_alt.m_flag_BDOSAC[DGNB::Env2_4_Alt::BDOSAC_AlternativeCertificationSubmitted].set("BDOSAC_AlternativeCertificationSubmitted",false);

	/*!
	 * Economy
	 */
	// Eco1.1.1
	m_economy.m_eco1_1.m_eco1_1_1.m_flag_LCCCPIES[DGNB::Eco1_1_1::LCCCPIES_Var1SubmissionOfCO2OrClimateCosts].set("LCCCPIES_Var1SubmissionOfCO2OrClimateCosts",true);
	m_economy.m_eco1_1.m_eco1_1_1.m_flag_LCCCPIES[DGNB::Eco1_1_1::LCCCPIES_Var2SubmissionOfEcologicalSuggestions].set("LCCCPIES_Var2SubmissionOfEcologicalSuggestions",true);

	m_economy.m_eco1_1.m_eco1_1_1.m_flag_LCCCPICO[DGNB::Eco1_1_1::LCCCPICO_CalculationAndDisclosureOfConstructionAndUtilisationCosts].set("LCCCPICO_CalculationAndDisclosureOfConstructionAndUtilisationCosts",true);

	m_economy.m_eco1_1.m_eco1_1_1.m_flag_LCCCPIPE[DGNB::Eco1_1_1::LCCCPIPE_PartialExaminationsDuringLP2].set("LCCCPIPE_PartialExaminationsDuringLP2",true);
	m_economy.m_eco1_1.m_eco1_1_1.m_flag_LCCCPIPE[DGNB::Eco1_1_1::LCCCPIPE_PartialExaminationsDuringLP3].set("LCCCPIPE_PartialExaminationsDuringLP3",true);
	m_economy.m_eco1_1.m_eco1_1_1.m_flag_LCCCPIPE[DGNB::Eco1_1_1::LCCCPIPE_PartialExaminationsDuringLP4].set("LCCCPIPE_PartialExaminationsDuringLP4",true);
	m_economy.m_eco1_1.m_eco1_1_1.m_flag_LCCCPIPE[DGNB::Eco1_1_1::LCCCPIPE_FundingAdviceSessionByEndOfLP4].set("LCCCPIPE_FundingAdviceSessionByEndOfLP4",true);
	m_economy.m_eco1_1.m_eco1_1_1.m_flag_LCCCPIPE[DGNB::Eco1_1_1::LCCCPIPE_SubmissionOfClimateProtectionAgendaDiscussionWithOwner].set("LCCCPIPE_SubmissionOfClimateProtectionAgendaDiscussionWithOwner",true);

	// Eco1.1.2
	m_economy.m_eco1_1.m_eco1_1_2.m_flag_EECBOBEB[DGNB::Eco1_1_2::EECBOBEB_BuildingUpToInnovationClauseStandards].set("EECBOBEB_BuildingUpToInnovationClauseStandards",true);
	m_economy.m_eco1_1.m_eco1_1_2.m_flag_EECBOBEB[DGNB::Eco1_1_2::EECBOBEB_AltBuildingReceivedKFWFundingForEnergyEfficiencyClassAOrBetter].set("EECBOBEB_AltBuildingReceivedKFWFundingForEnergyEfficiencyClassAOrBetter",true);

	m_economy.m_eco1_1.m_eco1_1_2.m_flag_EECBOCEBR[DGNB::Eco1_1_2::EECBOCEBR_CircularEconomySolutionsForReuseSubmitted].set("EECBOCEBR_CircularEconomySolutionsForReuseSubmitted",true);
	m_economy.m_eco1_1.m_eco1_1_2.m_flag_EECBOCEBR[DGNB::Eco1_1_2::EECBOCEBR_LCCModelIncludesEndOfLifeCosts].set("EECBOCEBR_LCCModelIncludesEndOfLifeCosts",true);
	m_economy.m_eco1_1.m_eco1_1_2.m_flag_EECBOCEBR[DGNB::Eco1_1_2::EECBOCEBR_DocumentationOfRawMaterialValue].set("EECBOCEBR_DocumentationOfRawMaterialValue",true);

	m_economy.m_eco1_1.m_eco1_1_2.m_para[Eco1_1_2::P_CurrentValue_eco1_1_2EECBOCEBR_NumberOfCircularEconomySolutionsForReuse].set("CurrentValue_eco1_1_2EECBOCEBR_NumberOfCircularEconomySolutionsForReuse", 5, IBK::Unit("-"));

	// Eco1.1.3
	m_economy.m_eco1_1.m_eco1_1_3.m_flag_BRLCCC[DGNB::Eco1_1_3::BRLCCC_NetLifeCycleCostsResultsSubmitted].set("BRLCCC_NetLifeCycleCostsResultsSubmitted",true);
	m_economy.m_eco1_1.m_eco1_1_3.m_flag_BRLCCC[DGNB::Eco1_1_3::BRLCCC_DisplayCaseFlag].set("BRLCCC_DisplayCaseFlag",true);
	m_economy.m_eco1_1.m_eco1_1_3.m_flag_BRLCCC[DGNB::Eco1_1_3::BRLCCC_HealthCareTypeIIFlag].set("BRLCCC_HealthCareTypeIIFlag",true);

	m_economy.m_eco1_1.m_eco1_1_3.m_para[Eco1_1_3::P_ReferenceValue_eco1_1_3netLCCPerBuildingTypeUpperValue].set("ReferenceValue_eco1_1_3netLCCPerBuildingTypeUpperValue", 7595, IBK::Unit("-"));											// ToDo Einheit EUR/m2
	m_economy.m_eco1_1.m_eco1_1_3.m_para[Eco1_1_3::P_ReferenceValue_eco1_1_3netLCCPerBuildingTypeIntermediateValue].set("ReferenceValue_eco1_1_3netLCCPerBuildingTypeIntermediateValue", 5838, IBK::Unit("-"));								// ToDo Einheit EUR/m2
	m_economy.m_eco1_1.m_eco1_1_3.m_para[Eco1_1_3::P_ReferenceValue_eco1_1_3netLCCPerBuildingTypeLowerValue].set("ReferenceValue_eco1_1_3netLCCPerBuildingTypeLowerValue", 4522, IBK::Unit("-"));											// ToDo Einheit EUR/m2
	m_economy.m_eco1_1.m_eco1_1_3.m_para[Eco1_1_3::P_CurrentValue_eco1_1_3BRLCCC_NetLifeCycleCosts].set("CurrentValue_eco1_1_3BRLCCC_NetLifeCycleCosts", 4500, IBK::Unit("-"));																// ToDo Einheit EUR/m2
	m_economy.m_eco1_1.m_eco1_1_3.m_para[Eco1_1_3::P_CurrentValue_eco1_1_3BRLCCC_CSAnnualEnergyConsumptionPerMeterRefrigeratedDC].set("CurrentValue_eco1_1_3BRLCCC_CSAnnualEnergyConsumptionPerMeterRefrigeratedDC", 0, IBK::Unit("-"));	// ToDo Einheit EUR/m2
	m_economy.m_eco1_1.m_eco1_1_3.m_para[Eco1_1_3::P_ReferenceValue_eco1_1_3BRLCCC_HealthCareTypeII].set("ReferenceValue_eco1_1_3BRLCCC_HealthCareTypeII", 0, IBK::Unit("-"));																// ToDo Einheit EUR/m2

	// Eco2.4.1
	m_economy.m_eco2_4.m_eco2_4_1.m_flag_ASBCSA[DGNB::Eco2_4_1::ASBCSA_GeneralPerceptionOfSite].set("ASBCSA_GeneralPerceptionOfSite",true);
	m_economy.m_eco2_4.m_eco2_4_1.m_flag_ASBCSA[DGNB::Eco2_4_1::ASBCSA_DemographicAndEconomicDevelopmentOfMacroSite].set("ASBCSA_DemographicAndEconomicDevelopmentOfMacroSite",true);
	m_economy.m_eco2_4.m_eco2_4_1.m_flag_ASBCSA[DGNB::Eco2_4_1::ASBCSA_ImmediateNeighbourhood].set("ASBCSA_ImmediateNeighbourhood",true);

	m_economy.m_eco2_4.m_eco2_4_1.m_flag_ASBCBCS[DGNB::Eco2_4_1::ASBCBCS_ReactionOfBuildingConceptToSiteAnalysis].set("ASBCBCS_ReactionOfBuildingConceptToSiteAnalysis",true);
	m_economy.m_eco2_4.m_eco2_4_1.m_flag_ASBCBCS[DGNB::Eco2_4_1::ASBCBCS_UseAndProvisioningOfEnvironmentSynergyEffects].set("ASBCBCS_UseAndProvisioningOfEnvironmentSynergyEffects",true);

	m_economy.m_eco2_4.m_eco2_4_1.m_flag_ASBCHCBCS[DGNB::Eco2_4_1::ASBCHCBCS_PlanInvolvesRegionalAnalysisConductedByInterdisciplinaryTeam].set("ASBCHCBCS_PlanInvolvesRegionalAnalysisConductedByInterdisciplinaryTeam",true);
	m_economy.m_eco2_4.m_eco2_4_1.m_flag_ASBCHCBCS[DGNB::Eco2_4_1::ASBCHCBCS_ConceptInvolvesPatientAndPersonnelRoutes].set("ASBCHCBCS_ConceptInvolvesPatientAndPersonnelRoutes",true);
	m_economy.m_eco2_4.m_eco2_4_1.m_flag_ASBCHCBCS[DGNB::Eco2_4_1::ASBCHCBCS_ConceptInvolvesMaterialTransportAndStorageSpaces].set("ASBCHCBCS_ConceptInvolvesMaterialTransportAndStorageSpaces",true);
	m_economy.m_eco2_4.m_eco2_4_1.m_flag_ASBCHCBCS[DGNB::Eco2_4_1::ASBCHCBCS_ConceptInvolvesComplianceWithHygienicRequirements].set("ASBCHCBCS_ConceptInvolvesComplianceWithHygienicRequirements",true);
	m_economy.m_eco2_4.m_eco2_4_1.m_flag_ASBCHCBCS[DGNB::Eco2_4_1::ASBCHCBCS_ConceptInvolvesPositioningOfTechnicalUnitsInRegardToAccomodatedFunctionsAndMainBuilding].set("ASBCHCBCS_ConceptInvolvesPositioningOfTechnicalUnitsInRegardToAccomodatedFunctionsAndMainBuilding",true);
	m_economy.m_eco2_4.m_eco2_4_1.m_flag_ASBCHCBCS[DGNB::Eco2_4_1::ASBCHCBCS_ConceptInvolvesConsiderationOfFutureUsageScenarios].set("ASBCHCBCS_ConceptInvolvesConsiderationOfFutureUsageScenarios",true);
	m_economy.m_eco2_4.m_eco2_4_1.m_flag_ASBCHCBCS[DGNB::Eco2_4_1::ASBCHCBCS_ConsiderationOfCatastrophicScenariosAndEnsuranceOfContinuedOperation].set("ASBCHCBCS_ConsiderationOfCatastrophicScenariosAndEnsuranceOfContinuedOperation",true);

	// Eco2.4.2
	m_economy.m_eco2_4.m_eco2_4_2.m_flag_ATPUSPR[DGNB::Eco2_4_2::ATPUSPR_SameUsageType].set("ATPUSPR_SameUsageType",true);
	m_economy.m_eco2_4.m_eco2_4_2.m_flag_ATPUSPR[DGNB::Eco2_4_2::ATPUSPR_DifferentUsageType].set("ATPUSPR_DifferentUsageType",true);

	m_economy.m_eco2_4.m_eco2_4_2.m_flag_ATPUSPAIF[DGNB::Eco2_4_2::ATPUSPAIF_CeilingHeight].set("ATPUSPAIF_CeilingHeight",true);
	m_economy.m_eco2_4.m_eco2_4_2.m_flag_ATPUSPAIF[DGNB::Eco2_4_2::ATPUSPAIF_BuildingDepth].set("ATPUSPAIF_BuildingDepth",true);
	m_economy.m_eco2_4.m_eco2_4_2.m_flag_ATPUSPAIF[DGNB::Eco2_4_2::ATPUSPAIF_FloorAllotment].set("ATPUSPAIF_FloorAllotment",true);
	m_economy.m_eco2_4.m_eco2_4_2.m_flag_ATPUSPAIF[DGNB::Eco2_4_2::ATPUSPAIF_GroundPlanFlexibility].set("ATPUSPAIF_GroundPlanFlexibility",true);
	m_economy.m_eco2_4.m_eco2_4_2.m_flag_ATPUSPAIF[DGNB::Eco2_4_2::ATPUSPAIF_Construction].set("ATPUSPAIF_Construction",true);
	m_economy.m_eco2_4.m_eco2_4_2.m_flag_ATPUSPAIF[DGNB::Eco2_4_2::ATPUSPAIF_BuildingServices].set("ATPUSPAIF_BuildingServices",true);

	// Eco2.4.3
	m_economy.m_eco2_4.m_eco2_4_3.m_flag_DUTTCDUT[DGNB::Eco2_4_3::DUTTCDUT_ResultsSubmitted].set("DUTTCDUT_ResultsSubmitted",true);

	m_economy.m_eco2_4.m_eco2_4_3.m_flag_DUTTCCEUT[DGNB::Eco2_4_3::DUTTCCEUT_AtLeastOneUserOrTenantContributesToCircularEconomy].set("DUTTCCEUT_AtLeastOneUserOrTenantContributesToCircularEconomy",true);

	m_economy.m_eco2_4.m_eco2_4_3.m_para[Eco2_4_3::P_CurrentValue_eco2_4_3DegreeOfUseOrTenancy].set("CurrentValue_eco2_4_3DegreeOfUseOrTenancy", 100, IBK::Unit("---"));		// ToDo Einheit % SO oder anders?

	// Eco2.4.4
	m_economy.m_eco2_4.m_eco2_4_4.m_flag_SERUSGS[DGNB::Eco2_4_4::SERUSGS_ResultsSubmitted].set("SERUSGS_ResultsSubmitted",true);
	m_economy.m_eco2_4.m_eco2_4_4.m_flag_SERUSGS[DGNB::Eco2_4_4::SERUSGS_LogisticsAndProductionCostOptimisation].set("SERUSGS_LogisticsAndProductionCostOptimisation",true);
	m_economy.m_eco2_4.m_eco2_4_4.m_flag_SERUSGS[DGNB::Eco2_4_4::SERUSGS_LogisticsAndProductionEnvironmentalOptimisation].set("SERUSGS_LogisticsAndProductionEnvironmentalOptimisation",true);
	m_economy.m_eco2_4.m_eco2_4_4.m_flag_SERUSGS[DGNB::Eco2_4_4::SERUSGS_LogisticsAndProductionSocialOptimisation].set("SERUSGS_LogisticsAndProductionSocialOptimisation",true);

	m_economy.m_eco2_4.m_eco2_4_4.m_flag_SEMUS[DGNB::Eco2_4_4::SEMUS_ConceptIncludesMultipleUseOfRelevantPortionOfSpace].set("SEMUS_ConceptIncludesMultipleUseOfRelevantPortionOfSpace",true);
	m_economy.m_eco2_4.m_eco2_4_4.m_flag_SEMUS[DGNB::Eco2_4_4::SEMUS_UseIncludesMultipleUseOfRelevantPortionOfSpace].set("SEMUS_UseIncludesMultipleUseOfRelevantPortionOfSpace",true);

	m_economy.m_eco2_4.m_eco2_4_4.m_flag_SEA2030S[DGNB::Eco2_4_4::SEA2030S_SubmissionAndImplementationOfSufficiencyStrategy].set("SEA2030S_SubmissionAndImplementationOfSufficiencyStrategy",true);

	m_economy.m_eco2_4.m_eco2_4_4.m_para[Eco2_4_4::P_CurrentValue_eco2_4_4RatioOfUsableSpaceToGroundSpace].set("CurrentValue_eco2_4_4RatioOfUsableSpaceToGroundSpace", 0.8, IBK::Unit("-"));
	m_economy.m_eco2_4.m_eco2_4_4.m_para[Eco2_4_4::P_ReferenceValueeco2_4_4RatioOfUsableSpaceToGroundSpace_lower].set("ReferenceValueeco2_4_4RatioOfUsableSpaceToGroundSpace_lower", 0.48, IBK::Unit("-"));
	m_economy.m_eco2_4.m_eco2_4_4.m_para[Eco2_4_4::P_ReferenceValueeco2_4_4RatioOfUsableSpaceToGroundSpace_upper].set("ReferenceValueeco2_4_4RatioOfUsableSpaceToGroundSpace_upper", 0.75, IBK::Unit("-"));

	// Eco2.4.5
	m_economy.m_eco2_4.m_eco2_4_5.m_flag_RAAEF[DGNB::Eco2_4_5::RAAEF_RiskAnalysisDuringEarlyPlanningPhases].set("RAAEF_RiskAnalysisDuringEarlyPlanningPhases",true);

	m_economy.m_eco2_4.m_eco2_4_5.m_flag_RABCT[DGNB::Eco2_4_5::RABCT_AspirationsForVerification].set("RABCT_AspirationsForVerification",true);
	m_economy.m_eco2_4.m_eco2_4_5.m_flag_RABCT[DGNB::Eco2_4_5::RABCT_ImplementationOfStandards].set("RABCT_ImplementationOfStandards",true);

	// Eco2.4.6
	m_economy.m_eco2_4.m_eco2_4_6.m_flag_A2030CDI[DGNB::Eco2_4_6::A2030CDI_QualityOfInternetConnection].set("A2030CDI_QualityOfInternetConnection",true);

	// Eco2.4.7
	m_economy.m_eco2_4.m_eco2_4_7.m_flag_A2030E[DGNB::Eco2_4_7::A2030E_Concept].set("A2030E_Concept",true);

	m_economy.m_eco2_4.m_eco2_4_7.m_flag_A2030IA[DGNB::Eco2_4_7::A2030IA_AddressEffect].set("A2030IA_AddressEffect",true);

	// Eco2.6.1
	m_economy.m_eco2_6.m_eco2_6_1.m_flag_BCRMPVPrePH4[DGNB::Eco2_6_1::BCRMPVPrePH4_ConceptSubmitted].set("BCRMPVPrePH4_ConceptSubmitted",true);

	m_economy.m_eco2_6.m_eco2_6_1.m_flag_BCRMPVPostPH4[DGNB::Eco2_6_1::BCRMPVPostPH4_ConceptSubmitted].set("BCRMPVPostPH4_ConceptSubmitted",true);
	m_economy.m_eco2_6.m_eco2_6_1.m_flag_BCRMPVPostPH4[DGNB::Eco2_6_1::BCRMPVPostPH4_ProofOfNoNegativeConcequences].set("BCRMPVPostPH4_ProofOfNoNegativeConcequences",true);

	m_economy.m_eco2_6.m_eco2_6_1.m_flag_A2030CBA[DGNB::Eco2_6_1::A2030CBA_Evaluation].set("A2030CBA_Evaluation",true);

	// Eco2.6.2
	m_economy.m_eco2_6.m_eco2_6_2.m_flag_ACCQEM[DGNB::Eco2_6_2::ACCQEM_RecommendedMeasuresToReduceClimateRisksImplemented].set("ACCQEM_RecommendedMeasuresToReduceClimateRisksImplemented",true);
	m_economy.m_eco2_6.m_eco2_6_2.m_flag_ACCQEM[DGNB::Eco2_6_2::ACCQEM_MeasuresImproveResilienceAndInlcudeReductionOfAllHighRiskFactors].set("ACCQEM_MeasuresImproveResilienceAndInlcudeReductionOfAllHighRiskFactors",true);
	m_economy.m_eco2_6.m_eco2_6_2.m_flag_ACCQEM[DGNB::Eco2_6_2::ACCQEM_MeasuresFurtherIncludeReductionOfAllModerateRiskFactors].set("ACCQEM_MeasuresFurtherIncludeReductionOfAllModerateRiskFactors",true);
	m_economy.m_eco2_6.m_eco2_6_2.m_flag_ACCQEM[DGNB::Eco2_6_2::ACCQEM_MeasuresReduceProbableFutureRisksOnSite].set("ACCQEM_MeasuresReduceProbableFutureRisksOnSite",true);

	m_economy.m_eco2_6.m_eco2_6_2.m_flag_ACCQIAM[DGNB::Eco2_6_2::ACCQIAM_PreferentialUseOfNaturalAndPassiveSolutions].set("ACCQIAM_PreferentialUseOfNaturalAndPassiveSolutions",true);
	m_economy.m_eco2_6.m_eco2_6_2.m_flag_ACCQIAM[DGNB::Eco2_6_2::ACCQIAM_MeasuresInAccordanceWithLocalRegionalPlans].set("ACCQIAM_MeasuresInAccordanceWithLocalRegionalPlans",true);
	m_economy.m_eco2_6.m_eco2_6_2.m_flag_ACCQIAM[DGNB::Eco2_6_2::ACCQIAM_MeasuresInAccordanceWithNationalStrategy].set("ACCQIAM_MeasuresInAccordanceWithNationalStrategy",true);
	m_economy.m_eco2_6.m_eco2_6_2.m_flag_ACCQIAM[DGNB::Eco2_6_2::ACCQIAM_SurveillanceOfImplementedOrPreparedMeasures].set("ACCQIAM_SurveillanceOfImplementedOrPreparedMeasures",true);
	m_economy.m_eco2_6.m_eco2_6_2.m_flag_ACCQIAM[DGNB::Eco2_6_2::ACCQIAM_RegulationOfRemedialMeasures].set("ACCQIAM_RegulationOfRemedialMeasures",true);

	m_economy.m_eco2_6.m_eco2_6_2.m_flag_ACCGRED[DGNB::Eco2_6_2::ACCGRED_EssentialMeasuresTaken].set("ACCGRED_EssentialMeasuresTaken",true);
	m_economy.m_eco2_6.m_eco2_6_2.m_flag_ACCGRED[DGNB::Eco2_6_2::ACCGRED_GeneralResilienceExists].set("ACCGRED_GeneralResilienceExists",true);

	m_economy.m_eco2_6.m_eco2_6_2.m_flag_ACCA2030HL[DGNB::Eco2_6_2::ACCA2030HL_ProbableHighHeatLoad].set("ACCA2030HL_ProbableHighHeatLoad",true);
	m_economy.m_eco2_6.m_eco2_6_2.m_flag_ACCA2030HL[DGNB::Eco2_6_2::ACCA2030HL_MeasuresTakenToReduceHeatLoadRisksToHealth].set("ACCA2030HL_MeasuresTakenToReduceHeatLoadRisksToHealth",true);

	// Eco2.6.3
	m_economy.m_eco2_6.m_eco2_6_3.m_flag_ASBCSA[DGNB::Eco2_6_3::MAFERSCMAQ_PositiveInfluenceOnImmissionInVicinity].set("MAFERSCMAQ_PositiveInfluenceOnImmissionInVicinity",true);
	m_economy.m_eco2_6.m_eco2_6_3.m_flag_ASBCSA[DGNB::Eco2_6_3::MAFERSCMAQ_RiskAnalysisConducted].set("MAFERSCMAQ_RiskAnalysisConducted",true);
	m_economy.m_eco2_6.m_eco2_6_3.m_flag_ASBCSA[DGNB::Eco2_6_3::MAFERSCMAQ_RiskAnalysisProtectionMeasuresImplemented].set("MAFERSCMAQ_RiskAnalysisProtectionMeasuresImplemented",true);

	m_economy.m_eco2_6.m_eco2_6_3.m_flag_MAFERSCMN[DGNB::Eco2_6_3::MAFERSCMN_NoiseProtectionConstruction].set("MAFERSCMN_NoiseProtectionConstruction",true);
	m_economy.m_eco2_6.m_eco2_6_3.m_flag_MAFERSCMN[DGNB::Eco2_6_3::MAFERSCMN_InclusionOfNoiseProtectionGroundPlans].set("MAFERSCMN_InclusionOfNoiseProtectionGroundPlans",true);
	m_economy.m_eco2_6.m_eco2_6_3.m_flag_MAFERSCMN[DGNB::Eco2_6_3::MAFERSCMN_SurveyReportForBuildingAndSurroundingsOnOptimisationmeasures].set("MAFERSCMN_SurveyReportForBuildingAndSurroundingsOnOptimisationmeasures",true);
	m_economy.m_eco2_6.m_eco2_6_3.m_flag_MAFERSCMN[DGNB::Eco2_6_3::MAFERSCMN_OptimisationmeasuresImplemented].set("MAFERSCMN_OptimisationmeasuresImplemented",true);

	m_economy.m_eco2_6.m_eco2_6_3.m_flag_MAFERSRRR[DGNB::Eco2_6_3::MAFERSRRR_RadonAccessPreventedOrHeavilyHindered].set("MAFERSRRR_RadonAccessPreventedOrHeavilyHindered",true);

	// Eco2.7.1
	m_economy.m_eco2_7.m_eco2_7_1.m_flag_DCBCPD[DGNB::Eco2_7_1::DCBCPD_CalculationByBGFSmallerThan5000m2Method].set("DCBCPD_CalculationByBGFSmallerThan5000m2Method",true);
	m_economy.m_eco2_7.m_eco2_7_1.m_flag_DCBCPD[DGNB::Eco2_7_1::DCBCPD_ModelMatchesBuildingAndWasHandedOverToClient].set("DCBCPD_ModelMatchesBuildingAndWasHandedOverToClient",true);
	m_economy.m_eco2_7.m_eco2_7_1.m_flag_DCBCPD[DGNB::Eco2_7_1::DCBCPD_RelevantCertificationsAndCalculationsMatchBuilding].set("DCBCPD_RelevantCertificationsAndCalculationsMatchBuilding",true);

	m_economy.m_eco2_7.m_eco2_7_1.m_flag_DCBCSBD[DGNB::Eco2_7_1::DCBCSBD_CalculationByBGFSmallerThan5000m2Method].set("DCBCSBD_CalculationByBGFSmallerThan5000m2Method",true);
	m_economy.m_eco2_7.m_eco2_7_1.m_flag_DCBCSBD[DGNB::Eco2_7_1::DCBCSBD_PartsCatalogueIncludesEcologicalBalanceData].set("DCBCSBD_PartsCatalogueIncludesEcologicalBalanceData",true);
	m_economy.m_eco2_7.m_eco2_7_1.m_flag_DCBCSBD[DGNB::Eco2_7_1::DCBCSBD_PartsCatalogueIncludesEcologicalProductInformation].set("DCBCSBD_PartsCatalogueIncludesEcologicalProductInformation",true);
	m_economy.m_eco2_7.m_eco2_7_1.m_flag_DCBCSBD[DGNB::Eco2_7_1::DCBCSBD_PartsCatalogueIncludesCircularPropertiesMatchingBuilding].set("DCBCSBD_PartsCatalogueIncludesCircularPropertiesMatchingBuilding",true);
	m_economy.m_eco2_7.m_eco2_7_1.m_flag_DCBCSBD[DGNB::Eco2_7_1::DCBCSBD_PartsCatalogueHandedOverToClient].set("DCBCSBD_PartsCatalogueHandedOverToClient",true);

	m_economy.m_eco2_7.m_eco2_7_1.m_flag_DCBCEBDBUM[DGNB::Eco2_7_1::DCBCEDBUM_BuildingRessourcePassIsPartOfSuperordinateDataBaseForUrbanMines].set("DCBCEDBUM_BuildingRessourcePassIsPartOfSuperordinateDataBaseForUrbanMines",true);

	m_economy.m_eco2_7.m_eco2_7_1.m_flag_DCBA2030DF[DGNB::Eco2_7_1::DCBA2030DF_DigitalFootprintHeavilyReduced].set("DCBA2030DF_DigitalFootprintHeavilyReduced",true);

	// Eco2.7.2
	m_economy.m_eco2_7.m_eco2_7_2.m_flag_ODBUROMP[DGNB::Eco2_7_2::ODBUROMP_CalculationByBGFSmallerThan5000m2Method].set("ODBUROMP_CalculationByBGFSmallerThan5000m2Method",true);
	m_economy.m_eco2_7.m_eco2_7_2.m_flag_ODBUROMP[DGNB::Eco2_7_2::ODBUROMP_CompleteObjectDocumentationChecklistHandedOverToClient].set("ODBUROMP_CompleteObjectDocumentationChecklistHandedOverToClient",true);
	m_economy.m_eco2_7.m_eco2_7_2.m_flag_ODBUROMP[DGNB::Eco2_7_2::ODBUROMP_AllDataKeptOnFileForFiveYearsAndHandedOverToOperatorCompany].set("ODBUROMP_AllDataKeptOnFileForFiveYearsAndHandedOverToOperatorCompany",true);

	m_economy.m_eco2_7.m_eco2_7_2.m_flag_ODBUOFBM[DGNB::Eco2_7_2::ODBUOFBM_CalculationByBGFSmallerThan5000m2Method].set("ODBUOFBM_CalculationByBGFSmallerThan5000m2Method",true);
	m_economy.m_eco2_7.m_eco2_7_2.m_flag_ODBUOFBM[DGNB::Eco2_7_2::ODBUOFBM_UpToDateCompleteOperatorFriendlyModelHandedOvertoOperatorCompany].set("ODBUOFBM_UpToDateCompleteOperatorFriendlyModelHandedOvertoOperatorCompany",true);
	m_economy.m_eco2_7.m_eco2_7_2.m_flag_ODBUOFBM[DGNB::Eco2_7_2::ODBUOFBM_LifeCycleGreenhouseGasAndEnergyBalanceIncludedOrPreparedForMonitoring].set("ODBUOFBM_LifeCycleGreenhouseGasAndEnergyBalanceIncludedOrPreparedForMonitoring",true);

	// Eco2.7.3
	m_economy.m_eco2_7.m_eco2_7_3.m_flag_PPBIMP[DGNB::Eco2_7_3::PPBIMP_CalculationByBGFSmallerThan5000m2Method].set("PPBIMP_CalculationByBGFSmallerThan5000m2Method",true);
	m_economy.m_eco2_7.m_eco2_7_3.m_flag_PPBIMP[DGNB::Eco2_7_3::PPBIMP_UseOfSharedDataEnvironment].set("PPBIMP_UseOfSharedDataEnvironment",true);
	m_economy.m_eco2_7.m_eco2_7_3.m_flag_PPBIMP[DGNB::Eco2_7_3::PPBIMP_NecessaryBasicDocuments].set("PPBIMP_NecessaryBasicDocuments",true);
	m_economy.m_eco2_7.m_eco2_7_3.m_flag_PPBIMP[DGNB::Eco2_7_3::PPBIMP_BIMCoordinatorSurveilingModelQuality].set("PPBIMP_BIMCoordinatorSurveilingModelQuality",true);
	m_economy.m_eco2_7.m_eco2_7_3.m_flag_PPBIMP[DGNB::Eco2_7_3::PPBIMP_CompetenceCheckAndCoordinationOfBEP].set("PPBIMP_CompetenceCheckAndCoordinationOfBEP",true);
	m_economy.m_eco2_7.m_eco2_7_3.m_flag_PPBIMP[DGNB::Eco2_7_3::PPBIMP_BIMInformationRequirementsAndGoalsCommunicated].set("PPBIMP_BIMInformationRequirementsAndGoalsCommunicated",true);

	m_economy.m_eco2_7.m_eco2_7_3.m_flag_PPBIMC[DGNB::Eco2_7_3::PPBIMC_CalculationByBGFSmallerThan5000m2Method].set("PPBIMC_CalculationByBGFSmallerThan5000m2Method",true);
	m_economy.m_eco2_7.m_eco2_7_3.m_flag_PPBIMC[DGNB::Eco2_7_3::PPBIMC_Level0to1_CAD3D].set("PPBIMC_Level0to1_CAD3D",true);
	m_economy.m_eco2_7.m_eco2_7_3.m_flag_PPBIMC[DGNB::Eco2_7_3::PPBIMC_Level2_BIM4to5D].set("PPBIMC_Level2_BIM4to5D",true);
	m_economy.m_eco2_7.m_eco2_7_3.m_flag_PPBIMC[DGNB::Eco2_7_3::PPBIMC_Level3_IntegratedBIM6to7D].set("PPBIMC_Level3_IntegratedBIM6to7D",true);

	m_economy.m_eco2_7.m_eco2_7_3.m_flag_PPBIMSO[DGNB::Eco2_7_3::PPBIMSO_CalculationByBGFSmallerThan5000m2Method].set("PPBIMSO_CalculationByBGFSmallerThan5000m2Method",true);
	m_economy.m_eco2_7.m_eco2_7_3.m_flag_PPBIMSO[DGNB::Eco2_7_3::PPBIMSO_VariantsCalculatedAndDocumented].set("PPBIMSO_VariantsCalculatedAndDocumented",true);

	m_economy.m_eco2_7.m_eco2_7_3.m_flag_PPBIMCEBIM2FMOC[DGNB::Eco2_7_3::PPBIMCEBIM2FMOC_SustainableOperatorConcept].set("PPBIMCEBIM2FMOC_SustainableOperatorConcept",true);

	m_economy.m_eco2_7.m_eco2_7_3.m_flag_PPBIMA2030SC[DGNB::Eco2_7_3::PPBIMA2030SC_ModelBasedBuildingSustainabilityCheckConducted].set("PPBIMA2030SC_ModelBasedBuildingSustainabilityCheckConducted",true);

	// Eco2.7.4
	m_economy.m_eco2_7.m_eco2_7_4.m_flag_DTOPCHDBM[DGNB::Eco2_7_4::DTOPCHDBM_CalculationByBGFSmallerThan5000m2Method].set("DTOPCHDBM_CalculationByBGFSmallerThan5000m2Method",true);
	m_economy.m_eco2_7.m_eco2_7_4.m_flag_DTOPCHDBM[DGNB::Eco2_7_4::DTOPCHDBM_AsBuiltControlImplementedAndDocumented].set("DTOPCHDBM_AsBuiltControlImplementedAndDocumented",true);
	m_economy.m_eco2_7.m_eco2_7_4.m_flag_DTOPCHDBM[DGNB::Eco2_7_4::DTOPCHDBM_BuildingDocumentationOrModelHasAsBuiltQuality].set("DTOPCHDBM_BuildingDocumentationOrModelHasAsBuiltQuality",true);
	m_economy.m_eco2_7.m_eco2_7_4.m_flag_DTOPCHDBM[DGNB::Eco2_7_4::DTOPCHDBM_DigitalBuildingRessourcePassIsPartOfDigitalTwinAndAvailable].set("DTOPCHDBM_DigitalBuildingRessourcePassIsPartOfDigitalTwinAndAvailable",true);

	m_economy.m_eco2_7.m_eco2_7_4.m_flag_DTOPCEDPC[DGNB::Eco2_7_4::DTOPCEDPC_DigitalisationConducted].set("DTOPCEDPC_DigitalisationConducted",true);

	// Eco2.7.5
	m_economy.m_eco2_7.m_eco2_7_5.m_flag_DCIBR[DGNB::Eco2_7_5::DCIBR_CompleteDocumentationOnRemovabilityHandedOverToClient].set("DCIBR_CompleteDocumentationOnRemovabilityHandedOverToClient",true);

	// Eco2.7.Alt
	m_economy.m_eco2_7.m_eco2_7_alt.m_flag_ACCDT[DGNB::Eco2_7_Alt::ACCDT_CircularDigitalTwinImplemented].set("ACCDT_CircularDigitalTwinImplemented",true);

	/*!
	 * SocioculturalFunctional
	 */
	// Soc1.1.1
	m_socioculture.m_soc1_1.m_soc1_1_1.m_flag_OTRTOT[DGNB::Soc1_1_1::OTRTOT_Max5PercentDeviationFromDIN_EN_16798_1_Category3].set("OTRTOT_Max5PercentDeviationFromDIN_EN_16798_1_Category3", true);
	m_socioculture.m_soc1_1.m_soc1_1_1.m_flag_OTRTOT[DGNB::Soc1_1_1::OTRTOT_Max5PercentDeviationFromDIN_EN_16798_1_Category1and2].set("OTRTOT_Max5PercentDeviationFromDIN_EN_16798_1_Category1and2", true);
	m_socioculture.m_soc1_1.m_soc1_1_1.m_flag_OTRTOT[DGNB::Soc1_1_1::OTRTOT_ShoppingCenterRentalAreaCoolingLoadCertification].set("OTRTOT_ShoppingCenterRentalAreaCoolingLoadCertification", true);
	m_socioculture.m_soc1_1.m_soc1_1_1.m_flag_OTRTOT[DGNB::Soc1_1_1::OTRTOT_ShoppingCenterMallStreetMax5PercentDeviationFromDIN_EN_16798_1_Category3].set("OTRTOT_ShoppingCenterMallStreetMax5PercentDeviationFromDIN_EN_16798_1_Category3", true);
	m_socioculture.m_soc1_1.m_soc1_1_1.m_flag_OTRTOT[DGNB::Soc1_1_1::OTRTOT_ShoppingCenterMallStreetMax5PercentDeviationFromDIN_EN_16798_1_Category1and2].set("OTRTOT_ShoppingCenterMallStreetMax5PercentDeviationFromDIN_EN_16798_1_Category1and2", true);
	m_socioculture.m_soc1_1.m_soc1_1_1.m_flag_OTRTOT[DGNB::Soc1_1_1::OTRTOT_LogisticsAndProductionMeasuresTakenAbove26Degrees].set("OTRTOT_LogisticsAndProductionMeasuresTakenAbove26Degrees", true);
	m_socioculture.m_soc1_1.m_soc1_1_1.m_flag_OTRTOT[DGNB::Soc1_1_1::OTRTOT_LogisticsAndProductionLimitationTo30Degrees].set("OTRTOT_LogisticsAndProductionLimitationTo30Degrees", true);

	m_socioculture.m_soc1_1.m_soc1_1_1.m_para[DGNB::Soc1_1_1::P_CurrentValue_soc1_1_1_ShoppingCenterRentalAreaCoolingLoad].set("CurrentValue_soc1_1_1_ShoppingCenterRentalAreaCoolingLoad", 0, IBK::Unit("W/m2"));

	// Soc1.1.2
	m_socioculture.m_soc1_1.m_soc1_1_2.m_flag_RHHP[DGNB::Soc1_1_2::RHHP_RelativeHumidityHigherThan30Percent].set("RHHP_RelativeHumidityHigherThan30Percent", true);
	m_socioculture.m_soc1_1.m_soc1_1_2.m_flag_RHHP[DGNB::Soc1_1_2::RHHP_HotelRelativeHumidityLowerThan70Percent].set("RHHP_HotelRelativeHumidityLowerThan70Percent", true);
	m_socioculture.m_soc1_1.m_soc1_1_2.m_flag_RHHP[DGNB::Soc1_1_2::RHHP_ConditionMetFor95PercentOfTime].set("RHHP_ConditionMetFor95PercentOfTime", true);

	m_socioculture.m_soc1_1.m_soc1_1_2.m_flag_RHCP[DGNB::Soc1_1_2::RHCP_MaxHumidity12GramPerKilogram].set("RHCP_MaxHumidity12GramPerKilogram", true);

	// Soc1.1.3
	m_socioculture.m_soc1_1.m_soc1_1_3.m_flag_DCP[DGNB::Soc1_1_3::DCP_ObservationOfDIN_EN_ISO_7730_A_A2_KatB].set("DCP_ObservationOfDIN_EN_ISO_7730_A_A2_KatB", true);
	m_socioculture.m_soc1_1.m_soc1_1_3.m_flag_DCP[DGNB::Soc1_1_3::DCP_ShoppingCenterPreventionOfDraught].set("DCP_ShoppingCenterPreventionOfDraught", true);

	// Soc1.1.4
	m_socioculture.m_soc1_1.m_soc1_1_4.m_flag_RTAFTCP[DGNB::Soc1_1_4::RTAFTCP_CeilingMin16Degrees].set("RTAFTCP_CeilingMin16Degrees", true);
	m_socioculture.m_soc1_1.m_soc1_1_4.m_flag_RTAFTCP[DGNB::Soc1_1_4::RTAFTCP_CeilingMax35Degrees].set("RTAFTCP_CeilingMax35Degrees", true);
	m_socioculture.m_soc1_1.m_soc1_1_4.m_flag_RTAFTCP[DGNB::Soc1_1_4::RTAFTCP_GlassSurfacesMin18Degrees].set("RTAFTCP_GlassSurfacesMin18Degrees", true);
	m_socioculture.m_soc1_1.m_soc1_1_4.m_flag_RTAFTCP[DGNB::Soc1_1_4::RTAFTCP_GlassSurfacesMax35Degrees].set("RTAFTCP_GlassSurfacesMax35Degrees", true);
	m_socioculture.m_soc1_1.m_soc1_1_4.m_flag_RTAFTCP[DGNB::Soc1_1_4::RTAFTCP_FloorMin19Degrees].set("RTAFTCP_FloorMin19Degrees", true);
	m_socioculture.m_soc1_1.m_soc1_1_4.m_flag_RTAFTCP[DGNB::Soc1_1_4::RTAFTCP_FloorMax29Degrees].set("RTAFTCP_FloorMax29Degrees", true);
	m_socioculture.m_soc1_1.m_soc1_1_4.m_flag_RTAFTCP[DGNB::Soc1_1_4::RTAFTCP_LogisticAndProductionMeasuresTakenToPreventRTA].set("RTAFTCP_LogisticAndProductionMeasuresTakenToPreventRTA", true);

	// Soc1.1.5
	m_socioculture.m_soc1_1.m_soc1_1_5.m_flag_A2030CARTC[DGNB::Soc1_1_5::A2030CARTC_ExceedanceFrequencyEvaluatedBasedOnPrognosticationsDWDTRYFuture].set("A2030CARTC_ExceedanceFrequencyEvaluatedBasedOnPrognosticationsDWDTRYFuture", true);
	m_socioculture.m_soc1_1.m_soc1_1_5.m_flag_A2030CARTC[DGNB::Soc1_1_5::A2030CARTC_ResultsHaveBeenIncludedInPlanningProcess].set("A2030CARTC_ResultsHaveBeenIncludedInPlanningProcess", true);

	// Soc1.1.6
	m_socioculture.m_soc1_1.m_soc1_1_6.m_flag_UI[DGNB::Soc1_1_6::UI_PossibilityOfReuse].set("UI_PossibilityOfReuse", true);
	m_socioculture.m_soc1_1.m_soc1_1_6.m_flag_UI[DGNB::Soc1_1_6::UI_RoomAirCycleIndividuallyManipulable].set("UI_RoomAirCycleIndividuallyManipulable", true);
	m_socioculture.m_soc1_1.m_soc1_1_6.m_flag_UI[DGNB::Soc1_1_6::UI_RoomTemperatureIndividuallyManipulable].set("UI_RoomTemperatureIndividuallyManipulable", true);
	m_socioculture.m_soc1_1.m_soc1_1_6.m_flag_UI[DGNB::Soc1_1_6::UI_SurveyOnUserSatisfactionAndEnergyEfficiency].set("UI_SurveyOnUserSatisfactionAndEnergyEfficiency", true);

	// Soc1.1.Alt
	m_socioculture.m_soc1_1.m_soc1_1_alt.m_flag_AC[DGNB::Soc1_1_Alt::AC_AlternativeCertificationForIndicators1to4].set("AC_AlternativeCertificationForIndicators1to4", true);

	// Soc1.2.1
	m_socioculture.m_soc1_2.m_soc1_2_1.m_flag_IHTVOCM[DGNB::Soc1_2_1::IHTVOCM_TVOCResultsSubmitted].set("IHTVOCM_TVOCResultsSubmitted", true);
	m_socioculture.m_soc1_2.m_soc1_2_1.m_flag_IHTVOCM[DGNB::Soc1_2_1::IHTVOCM_FormaldehydeResultsSubmitted].set("IHTVOCM_FormaldehydeResultsSubmitted", true);
	m_socioculture.m_soc1_2.m_soc1_2_1.m_flag_IHTVOCM[DGNB::Soc1_2_1::IHTVOCM_AlternativeCertification].set("IHTVOCM_AlternativeCertification", false);
	m_socioculture.m_soc1_2.m_soc1_2_1.m_flag_IHTVOCM[DGNB::Soc1_2_1::IHTVOCM_ResidentialDegreeOfRentExtensionHigherThan80Percent].set("IHTVOCM_ResidentialDegreeOfRentExtensionHigherThan80Percent", true);
	m_socioculture.m_soc1_2.m_soc1_2_1.m_flag_IHTVOCM[DGNB::Soc1_2_1::IHTVOCM_LP_DeclarationAndVerificationOfProductsForFloors].set("IHTVOCM_LP_DeclarationAndVerificationOfProductsForFloors", true);
	m_socioculture.m_soc1_2.m_soc1_2_1.m_flag_IHTVOCM[DGNB::Soc1_2_1::IHTVOCM_LP_DeclarationAndVerificationOfProductsForAllInteriorSurfaces].set("IHTVOCM_LP_DeclarationAndVerificationOfProductsForAllInteriorSurfaces", true);

	m_socioculture.m_soc1_2.m_soc1_2_1.m_flag_IHTVOCSCCBCS[DGNB::Soc1_2_1::IHTVOCSCCBCS_OnlyLowEmissionMaterialsUsed].set("IHTVOCSCCBCS_OnlyLowEmissionMaterialsUsed", true);
	m_socioculture.m_soc1_2.m_soc1_2_1.m_flag_IHTVOCSCCBCS[DGNB::Soc1_2_1::IHTVOCSCCBCS_RentersHoldUpEnv1_2QS3In50PercentOfSpaces].set("IHTVOCSCCBCS_RentersHoldUpEnv1_2QS3In50PercentOfSpaces", true);
	m_socioculture.m_soc1_2.m_soc1_2_1.m_flag_IHTVOCSCCBCS[DGNB::Soc1_2_1::IHTVOCSCCBCS_RentersHoldUpEnv1_2QS3In80PercentOfSpaces].set("IHTVOCSCCBCS_RentersHoldUpEnv1_2QS3In80PercentOfSpaces", true);

	m_socioculture.m_soc1_2.m_soc1_2_1.m_flag_IHTVOCA2030IATMRHC[DGNB::Soc1_2_1::IHTVOCA2030IATMRHC_NonSmokerProtection].set("IHTVOCA2030IATMRHC_NonSmokerProtection", true);
	m_socioculture.m_soc1_2.m_soc1_2_1.m_flag_IHTVOCA2030IATMRHC[DGNB::Soc1_2_1::IHTVOCA2030IATMRHC_RespirableDustPrevention].set("IHTVOCA2030IATMRHC_RespirableDustPrevention", true);

	m_socioculture.m_soc1_2.m_soc1_2_1.m_flag_IHTVOCWWB[DGNB::Soc1_2_1::IHTVOCWWB_WoodworkApplicable].set("IHTVOCWWB_WoodworkApplicable", true);
	m_socioculture.m_soc1_2.m_soc1_2_1.m_flag_IHTVOCWWB[DGNB::Soc1_2_1::IHTVOCWWB_LimoneneBelowNOW].set("IHTVOCWWB_LimoneneBelowNOW", true);
	m_socioculture.m_soc1_2.m_soc1_2_1.m_flag_IHTVOCWWB[DGNB::Soc1_2_1::IHTVOCWWB_AlphaPineneBelowNOW].set("IHTVOCWWB_AlphaPineneBelowNOW", true);

	m_socioculture.m_soc1_2.m_soc1_2_1.m_para[DGNB::Soc1_2_1::P_CurrentValue_soc1_2_TVOC].set("CurrentValue_soc1_2_TVOC", 250 * 1e-9, IBK::Unit("kg/m3"));
	m_socioculture.m_soc1_2.m_soc1_2_1.m_para[DGNB::Soc1_2_1::P_CurrentValue_soc1_2_Formaldehyde].set("CurrentValue_soc1_2_Formaldehyde", 25 * 1e-9, IBK::Unit("kg/m3"));
	m_socioculture.m_soc1_2.m_soc1_2_1.m_para[DGNB::Soc1_2_1::P_CurrentValue_soc1_2_TVOCRenterPromise].set("CurrentValue_soc1_2_TVOCRenterPromise", 250 * 1e-9, IBK::Unit("kg/m3"));
	m_socioculture.m_soc1_2.m_soc1_2_1.m_para[DGNB::Soc1_2_1::P_CurrentValue_soc1_2_FormaldehydeRenterPromise].set("CurrentValue_soc1_2_FormaldehydeRenterPromise", 25 * 1e-9, IBK::Unit("kg/m3"));

	// Soc1.2.2
	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFOEHAH[DGNB::Soc1_2_2::IHACFOEHAH_RatioSubmitted].set("IHACFOEHAH_RatioSubmitted", true);
	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFOEHAH[DGNB::Soc1_2_2::IHACFOEHAH_ZonalStreamingSimulation].set("IHACFOEHAH_ZonalStreamingSimulation", true);
	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFOEHAH[DGNB::Soc1_2_2::IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat3].set("IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat3", true);
	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFOEHAH[DGNB::Soc1_2_2::IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat2].set("IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat2", true);
	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFOEHAH[DGNB::Soc1_2_2::IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat1].set("IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat1", true);
	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFOEHAH[DGNB::Soc1_2_2::IHACFOEHAH_ManualNoCertification].set("IHACFOEHAH_ManualNoCertification", true);
	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFOEHAH[DGNB::Soc1_2_2::IHACFOEHAH_ManualObservationOfASR3_6].set("IHACFOEHAH_ManualObservationOfASR3_6", true);
	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFOEHAH[DGNB::Soc1_2_2::IHACFOEHAH_ManualObservationOfASR3_6AndSensorMonitoring].set("IHACFOEHAH_ManualObservationOfASR3_6AndSensorMonitoring", true);
	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFOEHAH[DGNB::Soc1_2_2::IHACFOEHAH_ZonalDIN_EN_16798_1_Kat4].set("IHACFOEHAH_ZonalDIN_EN_16798_1_Kat4", true);
	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFOEHAH[DGNB::Soc1_2_2::IHACFOEHAH_ZonalDIN_EN_16798_1_Kat3].set("IHACFOEHAH_ZonalDIN_EN_16798_1_Kat3", true);
	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFOEHAH[DGNB::Soc1_2_2::IHACFOEHAH_ZonalDIN_EN_16798_1_Kat1and2].set("IHACFOEHAH_ZonalDIN_EN_16798_1_Kat1and2", true);

	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFSCCBCS[DGNB::Soc1_2_2::IHACFSCCBCS_DIN_EN_16798_1_Kat4_CBCSandSCShops].set("IHACFSCCBCS_DIN_EN_16798_1_Kat4_CBCSandSCShops", true);
	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFSCCBCS[DGNB::Soc1_2_2::IHACFSCCBCS_DIN_EN_16798_1_Kat3_CBCSandSCShops].set("IHACFSCCBCS_DIN_EN_16798_1_Kat3_CBCSandSCShops", true);
	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFSCCBCS[DGNB::Soc1_2_2::IHACFSCCBCS_DIN_EN_16798_1_Kat1and2_CBCSandSCShops].set("IHACFSCCBCS_DIN_EN_16798_1_Kat1and2_CBCSandSCShops", true);
	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFSCCBCS[DGNB::Soc1_2_2::IHACFSCCBCS_DIN_EN_16798_1_Kat4_SCMalls].set("IHACFSCCBCS_DIN_EN_16798_1_Kat4_SCMalls", true);
	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFSCCBCS[DGNB::Soc1_2_2::IHACFSCCBCS_DIN_EN_16798_1_Kat3_SCMalls].set("IHACFSCCBCS_DIN_EN_16798_1_Kat3_SCMalls", true);
	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFSCCBCS[DGNB::Soc1_2_2::IHACFSCCBCS_DIN_EN_16798_1_Kat1and2_SCMalls].set("IHACFSCCBCS_DIN_EN_16798_1_Kat1and2_SCMalls", true);

	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFR[DGNB::Soc1_2_2::IHACFR_AerationMeasuresAccordingToLevelsFL].set("IHACFR_AerationMeasuresAccordingToLevelsFL", true);
	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFR[DGNB::Soc1_2_2::IHACFR_AerationMeasuresAccordingToLevelsRL].set("IHACFR_AerationMeasuresAccordingToLevelsRL", true);
	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFR[DGNB::Soc1_2_2::IHACFR_AerationMeasuresAccordingToLevelsNL].set("IHACFR_AerationMeasuresAccordingToLevelsNL", true);

	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFLP[DGNB::Soc1_2_2::IHACFLP_NoCertification].set("IHACFLP_NoCertification", true);
	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFLP[DGNB::Soc1_2_2::IHACFLP_ObservationOfASR3_6].set("IHACFLP_ObservationOfASR3_6", true);
	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFLP[DGNB::Soc1_2_2::IHACFLP_NeedbasedAeration].set("IHACFLP_NeedbasedAeration", true);
	m_socioculture.m_soc1_2.m_soc1_2_2.m_flag_IHACFLP[DGNB::Soc1_2_2::IHACFLP_AerationExceedsMinimumRateByAtLeast20Percent].set("IHACFLP_AerationExceedsMinimumRateByAtLeast20Percent", true);

	m_socioculture.m_soc1_2.m_soc1_2_2.m_para[DGNB::Soc1_2_2::P_CurrentValue_soc1_2_2_1_a_PercentageOfMechanicalAeration].set("CurrentValue_soc1_2_2_1_a_PercentageOfMechanicalAeration", 100, IBK::Unit("---"));					// ToDo Einheit % SO oder anders?
	m_socioculture.m_soc1_2.m_soc1_2_2.m_para[DGNB::Soc1_2_2::P_CurrentValue_soc1_2_2_1_a_ZonalStreamingSimulationResult].set("CurrentValue_soc1_2_2_1_a_ZonalStreamingSimulationResult", 500, IBK::Unit("-"));						// ToDo Einheit ppm

	// Soc1.3.1
	m_socioculture.m_soc1_3.m_soc1_3_1.m_flag_ORSRHcHA[DGNB::Soc1_3_1::ORSRHcHA_DIN_4109_5_RaisedSoundproofingMet].set("ORSRHcHA_DIN_4109_5_RaisedSoundproofingMet", true);

	m_socioculture.m_soc1_3.m_soc1_3_1.m_flag_ORSRO[DGNB::Soc1_3_1::ORSRO_ObservationOfVDI_2569_ClassAorBRequirements].set("ORSRO_ObservationOfVDI_2569_ClassAorBRequirements", true);

	m_socioculture.m_soc1_3.m_soc1_3_1.m_flag_ORSRR[DGNB::Soc1_3_1::ORSRR_DIN_4109_5_RequirementsMet].set("ORSRR_DIN_4109_5_RequirementsMet", true);
	m_socioculture.m_soc1_3.m_soc1_3_1.m_flag_ORSRR[DGNB::Soc1_3_1::ORSRR_SoundproofingPassClassCOrBetter].set("ORSRR_SoundproofingPassClassCOrBetter", true);

	m_socioculture.m_soc1_3.m_soc1_3_1.m_flag_BAMOEHAHcR[DGNB::Soc1_3_1::BAMOEHAHcR_ConfirmationThroughMeasuring].set("BAMOEHAHcR_ConfirmationThroughMeasuring", true);

	// Soc1.3.2
	m_socioculture.m_soc1_3.m_soc1_3_2.m_flag_PAACRAC[DGNB::Soc1_3_2::PAACRAC_CreationOfPlanningAccompanyingRoomAcousticConcept].set("PAACRAC_CreationOfPlanningAccompanyingRoomAcousticConcept", true);

	// Soc1.3.3
	m_socioculture.m_soc1_3.m_soc1_3_3.m_flag_RAHHcAEO[DGNB::Soc1_3_3::RAHHcAEO_ObservationOfDIN_18041ForRoomTypesAAndB].set("RAHHcAEO_ObservationOfDIN_18041ForRoomTypesAAndB", true);
	m_socioculture.m_soc1_3.m_soc1_3_3.m_flag_RAHHcAEO[DGNB::Soc1_3_3::RAHHcAEO_ObservationOfDIN_18041ForInclusiveUse].set("RAHHcAEO_ObservationOfDIN_18041ForInclusiveUse", true);
	m_socioculture.m_soc1_3.m_soc1_3_3.m_flag_RAHHcAEO[DGNB::Soc1_3_3::RAHHcAEO_ObservationOfVDI_2569ClassA].set("RAHHcAEO_ObservationOfVDI_2569ClassA", true);
	m_socioculture.m_soc1_3.m_soc1_3_3.m_flag_RAHHcAEO[DGNB::Soc1_3_3::RAHHcAEO_ObservationOfVDI_2569ClassB].set("RAHHcAEO_ObservationOfVDI_2569ClassB", true);
	m_socioculture.m_soc1_3.m_soc1_3_3.m_flag_RAHHcAEO[DGNB::Soc1_3_3::RAHHcAEO_MeasuresTakenAndVerified].set("RAHHcAEO_MeasuresTakenAndVerified", true);

	m_socioculture.m_soc1_3.m_soc1_3_3.m_flag_RAR[DGNB::Soc1_3_3::RAR_RoomAcousticMeasuresTakenForSharedHallwaysAndStairways].set("RAR_RoomAcousticMeasuresTakenForSharedHallwaysAndStairways", true);
	m_socioculture.m_soc1_3.m_soc1_3_3.m_flag_RAR[DGNB::Soc1_3_3::RAR_RoomAcousticMeasuresTakenForSharedGroupMealAndLectureRooms].set("RAR_RoomAcousticMeasuresTakenForSharedGroupMealAndLectureRooms", true);

	// Soc1.4.1
	m_socioculture.m_soc1_4.m_soc1_4_1.m_flag_DSOEARHHcP[DGNB::Soc1_4_1::DSOEARHHcP_ResultsSubmitted].set("DSOEARHHcP_ResultsSubmitted", true);
	m_socioculture.m_soc1_4.m_soc1_4_1.m_flag_DSOEARHHcP[DGNB::Soc1_4_1::DSOEARHHcP_HotelAlternativeCertification].set("DSOEARHHcP_HotelAlternativeCertification", true);

	m_socioculture.m_soc1_4.m_soc1_4_1.m_flag_DSOCSSCCB[DGNB::Soc1_4_1::DSOCSSCCB_ResultsSubmitted].set("DSOCSSCCB_ResultsSubmitted", true);
	m_socioculture.m_soc1_4.m_soc1_4_1.m_flag_DSOCSSCCB[DGNB::Soc1_4_1::DSOCSSCCB_ConvenienceStoreEqualDistributionOfCeilingLight].set("DSOCSSCCB_ConvenienceStoreEqualDistributionOfCeilingLight", true);

	m_socioculture.m_soc1_4.m_soc1_4_1.m_para[DGNB::Soc1_4_1::P_CurrentValue_soc1_4_1ET].set("CurrentValue_soc1_4_1ET", 350, IBK::Unit("Lux"));															// TODO? Einheit lx
	m_socioculture.m_soc1_4.m_soc1_4_1.m_para[DGNB::Soc1_4_1::P_CurrentValue_soc1_4_1D].set("CurrentValue_soc1_4_1D", 2.5, IBK::Unit("---"));															// ToDo Einheit % SO oder anders?
	m_socioculture.m_soc1_4.m_soc1_4_1.m_para[DGNB::Soc1_4_1::P_CurrentValue_soc1_4_1LitAreaPercentageOfUsableArea].set("CurrentValue_soc1_4_1LitAreaPercentageOfUsableArea", 70, IBK::Unit("---"));		// ToDo Einheit % SO oder anders?

	// Soc1.4.2
	m_socioculture.m_soc1_4.m_soc1_4_2.m_flag_ARULOEALHc[DGNB::Soc1_4_2::ARULOEALHc_UsageLightingResultsSubmitted].set("ARULOEALHc_UsageLightingResultsSubmitted", true);
	m_socioculture.m_soc1_4.m_soc1_4_2.m_flag_ARULOEALHc[DGNB::Soc1_4_2::ARULOEALHc_TranslucentCeilingLightPortionResultsSubmitted].set("ARULOEALHc_TranslucentCeilingLightPortionResultsSubmitted", true);
	m_socioculture.m_soc1_4.m_soc1_4_2.m_flag_ARULOEALHc[DGNB::Soc1_4_2::ARULOEALHc_AssemblyAreaType1].set("ARULOEALHc_AssemblyAreaType1", true);
	m_socioculture.m_soc1_4.m_soc1_4_2.m_flag_ARULOEALHc[DGNB::Soc1_4_2::ARULOEALHc_AssemblyAreaType2].set("ARULOEALHc_AssemblyAreaType2", true);

	m_socioculture.m_soc1_4.m_soc1_4_2.m_para[DGNB::Soc1_4_2::P_CurrentValue_soc1_4_2UsageLighting].set("CurrentValue_soc1_4_2UsageLighting", 80, IBK::Unit("---"));										// ToDo Einheit % SO oder anders?
	m_socioculture.m_soc1_4.m_soc1_4_2.m_para[DGNB::Soc1_4_2::P_CurrentValue_soc1_4_2TranslucentCeilingLightPortion].set("CurrentValue_soc1_4_2TranslucentCeilingLightPortion", 5, IBK::Unit("---"));	// ToDo Einheit % SO oder anders?

	// Soc1.4.3
	m_socioculture.m_soc1_4.m_soc1_4_3.m_flag_LOSOCSCBSC[DGNB::Soc1_4_3::LOSOCSCBSC_QSMedium_DirectOutsideLOSForAllOfficesAnd80PercentOfBreakAndSocialRooms].set("LOSOCSCBSC_QSMedium_DirectOutsideLOSForAllOfficesAnd80PercentOfBreakAndSocialRooms", true);
	m_socioculture.m_soc1_4.m_soc1_4_3.m_flag_LOSOCSCBSC[DGNB::Soc1_4_3::LOSOCSCBSC_QSLow_CBSC_PercentageOfOpenFacadeResultsSubmitted].set("LOSOCSCBSC_QSLow_CBSC_PercentageOfOpenFacadeResultsSubmitted", true);
	m_socioculture.m_soc1_4.m_soc1_4_3.m_flag_LOSOCSCBSC[DGNB::Soc1_4_3::LOSOCSCBSC_QSMediumC_BSC_ShopsHaveOutsideLOS].set("LOSOCSCBSC_QSMediumC_BSC_ShopsHaveOutsideLOS", true);
	m_socioculture.m_soc1_4.m_soc1_4_3.m_flag_LOSOCSCBSC[DGNB::Soc1_4_3::LOSOCSCBSC_QSLOW_CBSC_PercentageOfDirectLOSOfShopAreasToOutsideResultsSubmitted].set("LOSOCSCBSC_QSLOW_CBSC_PercentageOfDirectLOSOfShopAreasToOutsideResultsSubmitted", true);
	m_socioculture.m_soc1_4.m_soc1_4_3.m_flag_LOSOCSCBSC[DGNB::Soc1_4_3::LOSOCSCBSC_QSLOW_CashierAreasOutsideLOS].set("LOSOCSCBSC_QSLOW_CashierAreasOutsideLOS", true);

	m_socioculture.m_soc1_4.m_soc1_4_3.m_flag_LOSOOEHLARHc[DGNB::Soc1_4_3::LOSOOEHLARHc_QSLow_OutsideAreasIntervisibility].set("LOSOOEHLARHc_QSLow_OutsideAreasIntervisibility", true);
	m_socioculture.m_soc1_4.m_soc1_4_3.m_flag_LOSOOEHLARHc[DGNB::Soc1_4_3::LOSOOEHLARHc_QSMedium_WorkplaceResidentialAreaHotelRoomCommonRoomIntervisibility].set("LOSOOEHLARHc_QSMedium_WorkplaceResidentialAreaHotelRoomCommonRoomIntervisibility", true);
	m_socioculture.m_soc1_4.m_soc1_4_3.m_flag_LOSOOEHLARHc[DGNB::Soc1_4_3::LOSOOEHLARHc_QShigh_WorkplaceResidentialAreaHotelRoomCommonRoomIntervisibility].set("LOSOOEHLARHc_QShigh_WorkplaceResidentialAreaHotelRoomCommonRoomIntervisibility", true);
	m_socioculture.m_soc1_4.m_soc1_4_3.m_flag_LOSOOEHLARHc[DGNB::Soc1_4_3::LOSOOEHLARHc_RHHc_AlternativeRequirementsMet].set("LOSOOEHLARHc_RHHc_AlternativeRequirementsMet", true);
	m_socioculture.m_soc1_4.m_soc1_4_3.m_flag_LOSOOEHLARHc[DGNB::Soc1_4_3::LOSOOEHLARHc_AssemblyType1].set("LOSOOEHLARHc_AssemblyType1", true);
	m_socioculture.m_soc1_4.m_soc1_4_3.m_flag_LOSOOEHLARHc[DGNB::Soc1_4_3::LOSOOEHLARHc_AssemblyType2].set("LOSOOEHLARHc_AssemblyType2", true);
	m_socioculture.m_soc1_4.m_soc1_4_3.m_flag_LOSOOEHLARHc[DGNB::Soc1_4_3::LOSOOEHLARHc_AnyDaylightInCommonAreas].set("LOSOOEHLARHc_AnyDaylightInCommonAreas", true);
	m_socioculture.m_soc1_4.m_soc1_4_3.m_flag_LOSOOEHLARHc[DGNB::Soc1_4_3::LOSOOEHLARHc_QSLow_OutsideAreaIntervisibility].set("LOSOOEHLARHc_QSLow_OutsideAreaIntervisibility", true);
	m_socioculture.m_soc1_4.m_soc1_4_3.m_flag_LOSOOEHLARHc[DGNB::Soc1_4_3::LOSOOEHLARHc_QSLow_OutsideAreaDirectIntervisibility].set("LOSOOEHLARHc_QSLow_OutsideAreaDirectIntervisibility", true);

	m_socioculture.m_soc1_4.m_soc1_4_3.m_para[DGNB::Soc1_4_3::P_CurrentValue_soc1_4_3_1aPercentageOfOpenFacade].set("CurrentValue_soc1_4_3_1aPercentageOfOpenFacade", 0, IBK::Unit("---"));												// ToDo Einheit % SO oder anders?
	m_socioculture.m_soc1_4.m_soc1_4_3.m_para[DGNB::Soc1_4_3::P_CurrentValue_soc1_4_3_1aPercentageOfDirectLOSOfShopAreasToOutside].set("CurrentValue_soc1_4_3_1aPercentageOfDirectLOSOfShopAreasToOutside", 0, IBK::Unit("---"));		// ToDo Einheit % SO oder anders?

	// Soc1.4.4
	m_socioculture.m_soc1_4.m_soc1_4_4.m_flag_DGSOEA12Hc[DGNB::Soc1_4_4::DGSOEA12Hc_DGPResultsSubmitted].set("DGSOEA12Hc_DGPResultsSubmitted", true);
	m_socioculture.m_soc1_4.m_soc1_4_4.m_flag_DGSOEA12Hc[DGNB::Soc1_4_4::DGSOEA12Hc_AssemblyType1].set("DGSOEA12Hc_AssemblyType1", true);
	m_socioculture.m_soc1_4.m_soc1_4_4.m_flag_DGSOEA12Hc[DGNB::Soc1_4_4::DGSOEA12Hc_AssemblyType2].set("DGSOEA12Hc_AssemblyType2", true);
	m_socioculture.m_soc1_4.m_soc1_4_4.m_flag_DGSOEA12Hc[DGNB::Soc1_4_4::DGSOEA12Hc_A2_CombinationOfLightDivertingSystemsAndGlareShields].set("DGSOEA12Hc_A2_CombinationOfLightDivertingSystemsAndGlareShields", true);
	m_socioculture.m_soc1_4.m_soc1_4_4.m_flag_DGSOEA12Hc[DGNB::Soc1_4_4::DGSOEA12Hc_A2_UseOfHighNorthLightDiffusionCeilingLights].set("DGSOEA12Hc_A2_UseOfHighNorthLightDiffusionCeilingLights", true);

	m_socioculture.m_soc1_4.m_soc1_4_4.m_flag_DGSCS[DGNB::Soc1_4_4::DGSCS_ObservationOfASRA3_4Chapter4_2].set("DGSCS_ObservationOfASRA3_4Chapter4_2", true);

	m_socioculture.m_soc1_4.m_soc1_4_4.m_flag_DGSL[DGNB::Soc1_4_4::DGSL_UncertifiedGlareShieldSystem].set("DGSL_UncertifiedGlareShieldSystem", true);
	m_socioculture.m_soc1_4.m_soc1_4_4.m_flag_DGSL[DGNB::Soc1_4_4::DGSL_Class2GlareShieldSystem].set("DGSL_Class2GlareShieldSystem", true);
	m_socioculture.m_soc1_4.m_soc1_4_4.m_flag_DGSL[DGNB::Soc1_4_4::DGSL_Class3OrHigherGlareShieldSystem].set("DGSL_Class3OrHigherGlareShieldSystem", true);

	m_socioculture.m_soc1_4.m_soc1_4_4.m_flag_DGSP[DGNB::Soc1_4_4::DGSP_CombinationOfLightDivertingSystemsAndGlareShields].set("DGSP_CombinationOfLightDivertingSystemsAndGlareShields", true);
	m_socioculture.m_soc1_4.m_soc1_4_4.m_flag_DGSP[DGNB::Soc1_4_4::DGSP_UseOfHighNorthLightDiffusionCeilingLights].set("DGSP_UseOfHighNorthLightDiffusionCeilingLights", true);

	m_socioculture.m_soc1_4.m_soc1_4_4.m_para[DGNB::Soc1_4_4::P_CurrentValue_soc1_4_4_1DaylightGlareProbability].set("CurrentValue_soc1_4_4_1DaylightGlareProbability", 0.3, IBK::Unit("---"));											// ToDo Einheit % SO oder anders?

	// Soc1.4.5
	m_socioculture.m_soc1_4.m_soc1_4_5.m_flag_ALLC[DGNB::Soc1_4_5::ALLC_CreationOfLightingConcept].set("ALLC_CreationOfLightingConcept", true);

	m_socioculture.m_soc1_4.m_soc1_4_5.m_flag_ALIPCOR[DGNB::Soc1_4_5::ALIPCOR_DIN_EN_12464_1_IlluminationRequirementsMet].set("ALIPCOR_DIN_EN_12464_1_IlluminationRequirementsMet", true);
	m_socioculture.m_soc1_4.m_soc1_4_5.m_flag_ALIPCOR[DGNB::Soc1_4_5::ALIPCOR_AtLeastTwoOptimisationMeasuresTaken].set("ALIPCOR_AtLeastTwoOptimisationMeasuresTaken", true);
	m_socioculture.m_soc1_4.m_soc1_4_5.m_flag_ALIPCOR[DGNB::Soc1_4_5::ALIPCOR_AdditionalOptimisationMeasuresTaken].set("ALIPCOR_AdditionalOptimisationMeasuresTaken", true);

	// Soc1.4.6
	m_socioculture.m_soc1_4.m_soc1_4_6.m_flag_SEDR[DGNB::Soc1_4_6::SEDR_1_5HoursExposureOfAtLeastOneRoomOfResidentialUnit].set("SEDR_1_5HoursExposureOfAtLeastOneRoomOfResidentialUnit", true);
	m_socioculture.m_soc1_4.m_soc1_4_6.m_flag_SEDR[DGNB::Soc1_4_6::SEDR_2HoursExposureOfAtLeastOneRoomOfResidentialUnit].set("SEDR_2HoursExposureOfAtLeastOneRoomOfResidentialUnit", true);
	m_socioculture.m_soc1_4.m_soc1_4_6.m_flag_SEDR[DGNB::Soc1_4_6::SEDR_3HoursExposureOfAtLeastOneRoomOfResidentialUnit].set("SEDR_3HoursExposureOfAtLeastOneRoomOfResidentialUnit", true);

	m_socioculture.m_soc1_4.m_soc1_4_6.m_flag_SEDHHC[DGNB::Soc1_4_6::SEDHHC_1_5HoursExposureIn100PercentOfUnitsOrRooms].set("SEDHHC_1_5HoursExposureIn100PercentOfUnitsOrRooms", true);
	m_socioculture.m_soc1_4.m_soc1_4_6.m_flag_SEDHHC[DGNB::Soc1_4_6::SEDHHC_2HoursExposureIn50PercentOfUnitsOrRooms].set("SEDHHC_2HoursExposureIn50PercentOfUnitsOrRooms", true);
	m_socioculture.m_soc1_4.m_soc1_4_6.m_flag_SEDHHC[DGNB::Soc1_4_6::SEDHHC_2HoursExposureIn60PercentOfUnitsOrRoomsAnd1_5HoursExposureInRemaining40Percent].set("SEDHHC_2HoursExposureIn60PercentOfUnitsOrRoomsAnd1_5HoursExposureInRemaining40Percent", true);
	m_socioculture.m_soc1_4.m_soc1_4_6.m_flag_SEDHHC[DGNB::Soc1_4_6::SEDHHC_3HoursExposureIn60PercentOfUnitsOrRoomsAnd1_5HoursExposureInRemaining40Percent].set("SEDHHC_3HoursExposureIn60PercentOfUnitsOrRoomsAnd1_5HoursExposureInRemaining40Percent", true);

	// Soc1.6.1
	m_socioculture.m_soc1_6.m_soc1_6_1.m_flag_CSOCZMU[DGNB::Soc1_6_1::CSOCZMU_DifferentCommunicationZones].set("CSOCZMU_DifferentCommunicationZones", true);
	m_socioculture.m_soc1_6.m_soc1_6_1.m_flag_CSOCZMU[DGNB::Soc1_6_1::CSOCZMU_CommunicationSupportingRoomDesign].set("CSOCZMU_CommunicationSupportingRoomDesign", true);
	m_socioculture.m_soc1_6.m_soc1_6_1.m_flag_CSOCZMU[DGNB::Soc1_6_1::CSOCZMU_InnovationRoomAlternativeCertification].set("CSOCZMU_InnovationRoomAlternativeCertification", true);

	m_socioculture.m_soc1_6.m_soc1_6_1.m_para[DGNB::Soc1_6_1::P_AlternativeInnovativeCommunicationConstellations].set("AlternativeInnovativeCommunicationConstellations", 5, IBK::Unit("-"));

	// Soc1.6.2
	m_socioculture.m_soc1_6.m_soc1_6_2.m_flag_AOUAOS[DGNB::Soc1_6_2::AOUAOS_AdditionalOffersMultifunctionRoomsCommonRooms].set("AOUAOS_AdditionalOffersMultifunctionRoomsCommonRooms", true);
	m_socioculture.m_soc1_6.m_soc1_6_2.m_flag_AOUAOS[DGNB::Soc1_6_2::AOUAOS_CSCBSC_LockersChangingRooms].set("AOUAOS_CSCBSC_LockersChangingRooms", true);
	m_socioculture.m_soc1_6.m_soc1_6_2.m_flag_AOUAOS[DGNB::Soc1_6_2::AOUAOS_Residential_CommonRoomsAvailableToEveryone].set("AOUAOS_Residential_CommonRoomsAvailableToEveryone", true);
	m_socioculture.m_soc1_6.m_soc1_6_2.m_flag_AOUAOS[DGNB::Soc1_6_2::AOUAOS_Residential_LaundryAndDryingRoomsFunctionAsCommonRooms_PartialWaivingOfLaundryMachineConnectionsInResidentialUnits].set("AOUAOS_Residential_LaundryAndDryingRoomsFunctionAsCommonRooms_PartialWaivingOfLaundryMachineConnectionsInResidentialUnits", true);
	m_socioculture.m_soc1_6.m_soc1_6_2.m_flag_AOUAOS[DGNB::Soc1_6_2::AOUAOS_Hc_AdditionalOffersAvailableToEveryone].set("AOUAOS_Hc_AdditionalOffersAvailableToEveryone", true);
	m_socioculture.m_soc1_6.m_soc1_6_2.m_flag_AOUAOS[DGNB::Soc1_6_2::AOUAOS_InnovationRoomAlternativeCertification].set("AOUAOS_InnovationRoomAlternativeCertification", true);

	m_socioculture.m_soc1_6.m_soc1_6_2.m_flag_AOUOI[DGNB::Soc1_6_2::AOUOI_Signage].set("AOUOI_Signage", true);
	m_socioculture.m_soc1_6.m_soc1_6_2.m_flag_AOUOI[DGNB::Soc1_6_2::AOUOI_InformationDesk].set("AOUOI_InformationDesk", true);
	m_socioculture.m_soc1_6.m_soc1_6_2.m_flag_AOUOI[DGNB::Soc1_6_2::AOUOI_InnovationRoomAlternativeCertification].set("AOUOI_InnovationRoomAlternativeCertification", true);

	m_socioculture.m_soc1_6.m_soc1_6_2.m_para[DGNB::Soc1_6_2::P_Soc1_6_2_1AlternativeInnovativeSolutions].set("Soc1_6_2_1AlternativeInnovativeSolutions", 5, IBK::Unit("-"));
	m_socioculture.m_soc1_6.m_soc1_6_2.m_para[DGNB::Soc1_6_2::P_Soc1_6_2_2AlternativeInnovativeSolutions].set("Soc1_6_2_2AlternativeInnovativeSolutions", 5, IBK::Unit("-"));

	// Soc1.6.3
	m_socioculture.m_soc1_6.m_soc1_6_3.m_flag_FCEFOSO[DGNB::Soc1_6_3::FCEFOSO_Daycare].set("FCEFOSO_Daycare", true);
	m_socioculture.m_soc1_6.m_soc1_6_3.m_flag_FCEFOSO[DGNB::Soc1_6_3::FCEFOSO_BabyChangeAndSeparateBreastFeedingRooms].set("FCEFOSO_BabyChangeAndSeparateBreastFeedingRooms", true);
	m_socioculture.m_soc1_6.m_soc1_6_3.m_flag_FCEFOSO[DGNB::Soc1_6_3::FCEFOSO_Playground].set("FCEFOSO_Playground", true);
	m_socioculture.m_soc1_6.m_soc1_6_3.m_flag_FCEFOSO[DGNB::Soc1_6_3::FCEFOSO_ElderlyCommonRoomsPlayrooms].set("FCEFOSO_ElderlyCommonRoomsPlayrooms", true);
	m_socioculture.m_soc1_6.m_soc1_6_3.m_flag_FCEFOSO[DGNB::Soc1_6_3::FCEFOSO_FamilyFriendlyParking].set("FCEFOSO_FamilyFriendlyParking", true);
	m_socioculture.m_soc1_6.m_soc1_6_3.m_flag_FCEFOSO[DGNB::Soc1_6_3::FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithBabyChange].set("FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithBabyChange", true);
	m_socioculture.m_soc1_6.m_soc1_6_3.m_flag_FCEFOSO[DGNB::Soc1_6_3::FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithCrib].set("FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithCrib", true);
	m_socioculture.m_soc1_6.m_soc1_6_3.m_flag_FCEFOSO[DGNB::Soc1_6_3::FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithKitchenette].set("FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithKitchenette", true);
	m_socioculture.m_soc1_6.m_soc1_6_3.m_flag_FCEFOSO[DGNB::Soc1_6_3::FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithDarkeningBlind].set("FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithDarkeningBlind", true);
	m_socioculture.m_soc1_6.m_soc1_6_3.m_flag_FCEFOSO[DGNB::Soc1_6_3::FCEFOSO_InnovationRoomAlternativeCertification].set("FCEFOSO_InnovationRoomAlternativeCertification", true);

	m_socioculture.m_soc1_6.m_soc1_6_3.m_para[DGNB::Soc1_6_3::P_Soc1_6_3_1AlternativeInnovativeSolutions].set("Soc1_6_3_1AlternativeInnovativeSolutions", 5, IBK::Unit("-"));

	// Soc1.6.4
	m_socioculture.m_soc1_6.m_soc1_6_4.m_flag_QSIAA[DGNB::Soc1_6_4::QSIAA_WideningsGalleriesNichesStairwellsOfSufficientWidthAndAirSpaceForCrossFloorCommunication].set("QSIAA_WideningsGalleriesNichesStairwellsOfSufficientWidthAndAirSpaceForCrossFloorCommunication", true);
	m_socioculture.m_soc1_6.m_soc1_6_4.m_flag_QSIAA[DGNB::Soc1_6_4::QSIAA_DaylightAvailabilityInAllotmentAreas].set("QSIAA_DaylightAvailabilityInAllotmentAreas", true);
	m_socioculture.m_soc1_6.m_soc1_6_4.m_flag_QSIAA[DGNB::Soc1_6_4::QSIAA_DoorwayOpeningsToBalconiesRoofTerracesAtria].set("QSIAA_DoorwayOpeningsToBalconiesRoofTerracesAtria", true);
	m_socioculture.m_soc1_6.m_soc1_6_4.m_flag_QSIAA[DGNB::Soc1_6_4::QSIAA_AllotmentAreasFeatureHeightenedThermalAcousticOrSoundproofingRequirementsEnablingFlexibleUse].set("QSIAA_AllotmentAreasFeatureHeightenedThermalAcousticOrSoundproofingRequirementsEnablingFlexibleUse", true);
	m_socioculture.m_soc1_6.m_soc1_6_4.m_flag_QSIAA[DGNB::Soc1_6_4::QSIAA_InnovationRoomAlternativeCertification].set("QSIAA_InnovationRoomAlternativeCertification", true);

	m_socioculture.m_soc1_6.m_soc1_6_4.m_para[DGNB::Soc1_6_4::P_Soc1_6_4_1AlternativeInnovativeSolutions].set("Soc1_6_4_1AlternativeInnovativeSolutions", 5, IBK::Unit("-"));

	// Soc1.6.5
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSDCOA[DGNB::Soc1_6_5::QSDCOA_DesignConceptFulfillsUserRequirementsAndFeaturesDifferentFunctions].set("QSDCOA_DesignConceptFulfillsUserRequirementsAndFeaturesDifferentFunctions", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSDCOA[DGNB::Soc1_6_5::QSDCOA_DesignConsidersMaterialQuality].set("QSDCOA_DesignConsidersMaterialQuality", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSDCOA[DGNB::Soc1_6_5::QSDCOA_DesignConsidersEnvironmentFriendlyAndSociallyAcceptableLighting].set("QSDCOA_DesignConsidersEnvironmentFriendlyAndSociallyAcceptableLighting", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSDCOA[DGNB::Soc1_6_5::QSDCOA_DesignConsidersIntuitiveOrientation].set("QSDCOA_DesignConsidersIntuitiveOrientation", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSDCOA[DGNB::Soc1_6_5::QSDCOA_DesignAvoidsPlacesOfAnxiety].set("QSDCOA_DesignAvoidsPlacesOfAnxiety", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSDCOA[DGNB::Soc1_6_5::QSDCOA_DesignConsidersIntegrationAndGreeningOfTechnicalFacilities].set("QSDCOA_DesignConsidersIntegrationAndGreeningOfTechnicalFacilities", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSDCOA[DGNB::Soc1_6_5::QSDCOA_AlternativeCertification_DesignGuidelinesFeatureIndividualPreferencesOfResidents].set("QSDCOA_AlternativeCertification_DesignGuidelinesFeatureIndividualPreferencesOfResidents", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSDCOA[DGNB::Soc1_6_5::QSDCOA_Healthcare_CommonAreasNotExposedToNoiseMalodorOrSimilarConstrictions].set("QSDCOA_Healthcare_CommonAreasNotExposedToNoiseMalodorOrSimilarConstrictions", true);

	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSOCA[DGNB::Soc1_6_5::QSOCA_MoreThan10PercentOfRooftopAtLeast5m2].set("QSOCA_MoreThan10PercentOfRooftopAtLeast5m2", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSOCA[DGNB::Soc1_6_5::QSOCA_CSCBSC_MoreThan1PercentOfRooftop].set("QSOCA_CSCBSC_MoreThan1PercentOfRooftop", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSOCA[DGNB::Soc1_6_5::QSOCA_BalconiesLoggiasWinterGardenOfAtLeast3m2PerUnit].set("QSOCA_BalconiesLoggiasWinterGardenOfAtLeast3m2PerUnit", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSOCA[DGNB::Soc1_6_5::QSOCA_MoreThan25PercentOfOutdoorAreaAtLeast30m2_AccordingToDIN_277].set("QSOCA_MoreThan25PercentOfOutdoorAreaAtLeast30m2_AccordingToDIN_277", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSOCA[DGNB::Soc1_6_5::QSOCA_Healthcare_BalconiesLoggiasWinterGardenAccessbileForMostUsers].set("QSOCA_Healthcare_BalconiesLoggiasWinterGardenAccessbileForMostUsers", true);

	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSOCASU[DGNB::Soc1_6_5::QSOCASU_AllotmentAndNetworkingFunction].set("QSOCASU_AllotmentAndNetworkingFunction", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSOCASU[DGNB::Soc1_6_5::QSOCASU_AccessibilityToPublic].set("QSOCASU_AccessibilityToPublic", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSOCASU[DGNB::Soc1_6_5::QSOCASU_MeetupAndCommunicationFunction].set("QSOCASU_MeetupAndCommunicationFunction", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSOCASU[DGNB::Soc1_6_5::QSOCASU_ExerciseAndPlayFunction].set("QSOCASU_ExerciseAndPlayFunction", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSOCASU[DGNB::Soc1_6_5::QSOCASU_WorkAndConcentrationFunction].set("QSOCASU_WorkAndConcentrationFunction", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSOCASU[DGNB::Soc1_6_5::QSOCASU_RestAndRecuperationFunction].set("QSOCASU_RestAndRecuperationFunction", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSOCASU[DGNB::Soc1_6_5::QSOCASU_SocialControlOfOutdoorAreasThroughBuildingExteriorRelation].set("QSOCASU_SocialControlOfOutdoorAreasThroughBuildingExteriorRelation", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSOCASU[DGNB::Soc1_6_5::QSOCASU_EnvironmentFriendlyAndSociallyAcceptableLighting].set("QSOCASU_EnvironmentFriendlyAndSociallyAcceptableLighting", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSOCASU[DGNB::Soc1_6_5::QSOCASU_InnovationRoomAlternativeCertification].set("QSOCASU_InnovationRoomAlternativeCertification", true);

	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSDCOAC[DGNB::Soc1_6_5::QSDCOAC_SolarisationOnDec21AtLeast1Hour].set("QSDCOAC_SolarisationOnDec21AtLeast1Hour", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSDCOAC[DGNB::Soc1_6_5::QSDCOAC_SolarisationOnDec21AtLeast3Hours].set("QSDCOAC_SolarisationOnDec21AtLeast3Hours", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSDCOAC[DGNB::Soc1_6_5::QSDCOAC_SummerSunblindThroughTreesShadingOrBuildingsOn10PercentOrMore].set("QSDCOAC_SummerSunblindThroughTreesShadingOrBuildingsOn10PercentOrMore", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSDCOAC[DGNB::Soc1_6_5::QSDCOAC_SummerSunblindThroughTreesShadingOrBuildingsOn30PercentOrMore].set("QSDCOAC_SummerSunblindThroughTreesShadingOrBuildingsOn30PercentOrMore", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSDCOAC[DGNB::Soc1_6_5::QSDCOAC_WindShieldNoNegativeEffectsOnCommonAreasOrPreventativeMeasures].set("QSDCOAC_WindShieldNoNegativeEffectsOnCommonAreasOrPreventativeMeasures", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSDCOAC[DGNB::Soc1_6_5::QSDCOAC_InnovationRoomAlternativeCertification].set("QSDCOAC_InnovationRoomAlternativeCertification", true);

	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSA2030[DGNB::Soc1_6_5::QSA2030_ClimateProtectionFactorOfSurfaceStructures].set("QSA2030_ClimateProtectionFactorOfSurfaceStructures", true);
	m_socioculture.m_soc1_6.m_soc1_6_5.m_flag_QSA2030[DGNB::Soc1_6_5::QSA2030_ClimateProtectionProtectionOptimisationOfOutdoorAreas].set("QSA2030_ClimateProtectionProtectionOptimisationOfOutdoorAreas", true);

	m_socioculture.m_soc1_6.m_soc1_6_5.m_para[DGNB::Soc1_6_5::P_Soc1_6_5_3AlternativeInnovativeSolutions].set("Soc1_6_5_3AlternativeInnovativeSolutions", 5, IBK::Unit("-"));
	m_socioculture.m_soc1_6.m_soc1_6_5.m_para[DGNB::Soc1_6_5::P_Soc1_6_5_4AlternativeInnovativePoints].set("Soc1_6_5_4AlternativeInnovativePoints", 5, IBK::Unit("-"));

	// Soc2.1.1
	m_socioculture.m_soc2_1.m_soc2_1_1.m_flag_AQST[DGNB::Soc2_1_1::AQST_ResultsSubmitted].set("AQST_ResultsSubmitted", true);
	m_socioculture.m_soc2_1.m_soc2_1_1.m_flag_AQST[DGNB::Soc2_1_1::AQST_Residential_StudentHostelBoardingHouses].set("AQST_Residential_StudentHostelBoardingHouses", true);
	m_socioculture.m_soc2_1.m_soc2_1_1.m_flag_AQST[DGNB::Soc2_1_1::AQST_Residential_NursingHomesHospicesDisabledElderly].set("AQST_Residential_NursingHomesHospicesDisabledElderly", true);

	m_socioculture.m_soc2_1.m_soc2_1_1.m_para[DGNB::Soc2_1_1::P_Soc2_1_1Qualitystage].set("Soc2_1_1Qualitystage", 6, IBK::Unit("-"));

	/*!
	 * Technology
	 */
	// Tec1.3.1
	m_technology.m_tec1_3.m_tec1_3_1.m_flag_PABEPFE[DGNB::Tec1_3_1::PABEPFE_PotentialOfSolarEnergy].set("PABEPFE_PotentialOfSolarEnergy", true);
	m_technology.m_tec1_3.m_tec1_3_1.m_flag_PABEPFE[DGNB::Tec1_3_1::PABEPFE_PotentialOfGreening].set("PABEPFE_PotentialOfGreening", true);
	m_technology.m_tec1_3.m_tec1_3_1.m_flag_PABEPFE[DGNB::Tec1_3_1::PABEPFE_AnalysisOfDifferentVariationsFocusedOnSustainabilityThroughoutLifeCycle].set("PABEPFE_AnalysisOfDifferentVariationsFocusedOnSustainabilityThroughoutLifeCycle", true);
	m_technology.m_tec1_3.m_tec1_3_1.m_flag_PABEPFE[DGNB::Tec1_3_1::PABEPFE_UseOfSustainableResourcesForInsulationAndCladding].set("PABEPFE_UseOfSustainableResourcesForInsulationAndCladding", true);
	m_technology.m_tec1_3.m_tec1_3_1.m_flag_PABEPFE[DGNB::Tec1_3_1::PABEPFE_PossibilityOfNondestructiveReplacementOfParts].set("PABEPFE_PossibilityOfNondestructiveReplacementOfParts", true);
	m_technology.m_tec1_3.m_tec1_3_1.m_flag_PABEPFE[DGNB::Tec1_3_1::PABEPFE_AnalysisOfDifferentVariationsFocusedOnHeatLossOverBuildingEnvelope].set("PABEPFE_AnalysisOfDifferentVariationsFocusedOnHeatLossOverBuildingEnvelope", true);

	// Tec1.3.2
	m_technology.m_tec1_3.m_tec1_3_2.m_flag_TOESEP[DGNB::Tec1_3_2::TOESEP_NominalRoomTemperature19Degrees].set("TOESEP_NominalRoomTemperature19Degrees", true);
	m_technology.m_tec1_3.m_tec1_3_2.m_flag_TOESEP[DGNB::Tec1_3_2::TOESEP_19Degrees_OpaqueExteriorBuildingElementsHTCLessThan0_18].set("TOESEP_19Degrees_OpaqueExteriorBuildingElementsHTCLessThan0_18", true);
	m_technology.m_tec1_3.m_tec1_3_2.m_flag_TOESEP[DGNB::Tec1_3_2::TOESEP_19Degrees_TransparentExteriorBuildingElementsAndFrontsHTCLessThan1_0].set("TOESEP_19Degrees_TransparentExteriorBuildingElementsAndFrontsHTCLessThan1_0", true);
	m_technology.m_tec1_3.m_tec1_3_2.m_flag_TOESEP[DGNB::Tec1_3_2::TOESEP_19Degrees_OtherTransparentElementsLikeGlassRoofsLightBandsLightDomesHTCLessThan1_6].set("TOESEP_19Degrees_OtherTransparentElementsLikeGlassRoofsLightBandsLightDomesHTCLessThan1_6", true);
	m_technology.m_tec1_3.m_tec1_3_2.m_flag_TOESEP[DGNB::Tec1_3_2::TOESEP_NominalRoomTemperatureBetween12And19Degrees].set("TOESEP_NominalRoomTemperatureBetween12And19Degrees", true);
	m_technology.m_tec1_3.m_tec1_3_2.m_flag_TOESEP[DGNB::Tec1_3_2::TOESEP_12to19Degrees_OpaqueExteriorBuildingElementsHTCLessThan0_24].set("TOESEP_12to19Degrees_OpaqueExteriorBuildingElementsHTCLessThan0_24", true);
	m_technology.m_tec1_3.m_tec1_3_2.m_flag_TOESEP[DGNB::Tec1_3_2::TOESEP_12to19Degrees_TransparentExteriorBuildingElementsAndFrontsHTCLessThan1_3].set("TOESEP_12to19Degrees_TransparentExteriorBuildingElementsAndFrontsHTCLessThan1_3", true);
	m_technology.m_tec1_3.m_tec1_3_2.m_flag_TOESEP[DGNB::Tec1_3_2::TOESEP_12to19Degrees_OtherTransparentElementsLikeGlassRoofsLightBandsLightDomesHTCLessThan2_0].set("TOESEP_12to19Degrees_OtherTransparentElementsLikeGlassRoofsLightBandsLightDomesHTCLessThan2_0", true);
	m_technology.m_tec1_3.m_tec1_3_2.m_flag_TOESEP[DGNB::Tec1_3_2::TOESEP_Residential_TransmissionOverHullSurfaceComparedToReferenceBuildingLessThan55Percent].set("TOESEP_Residential_TransmissionOverHullSurfaceComparedToReferenceBuildingLessThan55Percent", true);

	m_technology.m_tec1_3.m_tec1_3_2.m_flag_TOESTBS[DGNB::Tec1_3_2::TOESTBS_EvaluationImpossible].set("TOESTBS_EvaluationImpossible", true);
	m_technology.m_tec1_3.m_tec1_3_2.m_flag_TOESTBS[DGNB::Tec1_3_2::TOESTBS_SurchargeLessThan0_05].set("TOESTBS_SurchargeLessThan0_05", true);
	m_technology.m_tec1_3.m_tec1_3_2.m_flag_TOESTBS[DGNB::Tec1_3_2::TOESTBS_SurchargeLessThan0_01].set("TOESTBS_SurchargeLessThan0_01", true);

	// Tec1.3.3
	m_technology.m_tec1_3.m_tec1_3_3.m_flag_ABEM[DGNB::Tec1_3_3::ABEM_BuildingAirVolumeGreaterThan1500sqm].set("ABEM_BuildingAirVolumeGreaterThan1500sqm", true);
	m_technology.m_tec1_3.m_tec1_3_3.m_flag_ABEM[DGNB::Tec1_3_3::ABEM_BuildingAirVolumeLessThan1500sqm].set("ABEM_BuildingAirVolumeLessThan1500sqm", true);
	m_technology.m_tec1_3.m_tec1_3_3.m_flag_ABEM[DGNB::Tec1_3_3::ABEM_ResultsSubmitted].set("ABEM_ResultsSubmitted", true);

	m_technology.m_tec1_3.m_tec1_3_3.m_para[DGNB::Tec1_3_3::P_Tec1_3_3AirExchangeRateThroughBuildingEnvelope].set("Tec1_3_3AirExchangeRateThroughBuildingEnvelope", 0.5, IBK::Unit("1/h"));
	m_technology.m_tec1_3.m_tec1_3_3.m_para[DGNB::Tec1_3_3::P_Tec1_3_3AirExchangeRateRelativeToEnvelopeSurface].set("Tec1_3_3AirExchangeRateRelativeToEnvelopeSurface", 1.7, IBK::Unit("m3/m2h"));	// ToDo? Einheit m3/m2h

	// Tec1.3.4
	m_technology.m_tec1_3.m_tec1_3_4.m_flag_HISVV[DGNB::Tec1_3_4::HISVV_ExaminationOfDifferentVariations].set("HISVV_ExaminationOfDifferentVariations", true);
	m_technology.m_tec1_3.m_tec1_3_4.m_flag_HISVV[DGNB::Tec1_3_4::HISVV_ExaminationOfNonCommonRooms].set("HISVV_ExaminationOfNonCommonRooms", true);
	m_technology.m_tec1_3.m_tec1_3_4.m_flag_HISVV[DGNB::Tec1_3_4::HISVV_ExaminationOfBuildingWithLocalClimateDataAndImplementationOfResultsDuringPlanning].set("HISVV_ExaminationOfBuildingWithLocalClimateDataAndImplementationOfResultsDuringPlanning", true);
	m_technology.m_tec1_3.m_tec1_3_4.m_flag_HISVV[DGNB::Tec1_3_4::HISVV_UndercuttingLegalMinimumRequirementsByAtLeast20PercentResultsSubmitted].set("HISVV_UndercuttingLegalMinimumRequirementsByAtLeast20PercentResultsSubmitted", true);

	m_technology.m_tec1_3.m_tec1_3_4.m_para[DGNB::Tec1_3_4::P_Tec1_3_4UntercuttingOfLegalRequirements].set("Tec1_3_4UntercuttingOfLegalRequirements", 80, IBK::Unit("---"));					// ToDo Einheit % SO oder anders?

	// Tec1.3.5
	m_technology.m_tec1_3.m_tec1_3_5.m_flag_QAMQC[DGNB::Tec1_3_5::QAMQC_BlowerDoorTest].set("QAMQC_BlowerDoorTest", true);
	m_technology.m_tec1_3.m_tec1_3_5.m_flag_QAMQC[DGNB::Tec1_3_5::QAMQC_BuildingThermographyDuringBuildingPhase].set("QAMQC_BuildingThermographyDuringBuildingPhase", true);
	m_technology.m_tec1_3.m_tec1_3_5.m_flag_QAMQC[DGNB::Tec1_3_5::QAMQC_OtherRelevantMeasurements].set("QAMQC_OtherRelevantMeasurements", true);

	// Tec1.4.1
	m_technology.m_tec1_4.m_tec1_4_1.m_flag_PSP[DGNB::Tec1_4_1::PSP_HighCompactness].set("PSP_HighCompactness", true);
	m_technology.m_tec1_4.m_tec1_4_1.m_flag_PSP[DGNB::Tec1_4_1::PSP_BalancedWindowAreaRatioUnderConsiderationOfShading].set("PSP_BalancedWindowAreaRatioUnderConsiderationOfShading", true);
	m_technology.m_tec1_4.m_tec1_4_1.m_flag_PSP[DGNB::Tec1_4_1::PSP_ConstructionalSunblindToPreventDirectSunlightOnWindowsDuringSummer].set("PSP_ConstructionalSunblindToPreventDirectSunlightOnWindowsDuringSummer", true);
	m_technology.m_tec1_4.m_tec1_4_1.m_flag_PSP[DGNB::Tec1_4_1::PSP_AsManyNaturallyLightedRoomsAsPossible].set("PSP_AsManyNaturallyLightedRoomsAsPossible", true);
	m_technology.m_tec1_4.m_tec1_4_1.m_flag_PSP[DGNB::Tec1_4_1::PSP_UseOfHighMassElementsForHeatStorage].set("PSP_UseOfHighMassElementsForHeatStorage", true);
	m_technology.m_tec1_4.m_tec1_4_1.m_flag_PSP[DGNB::Tec1_4_1::PSP_PassiveCooling].set("PSP_PassiveCooling", true);
	m_technology.m_tec1_4.m_tec1_4_1.m_flag_PSP[DGNB::Tec1_4_1::PSP_EffectiveNaturalAeration].set("PSP_EffectiveNaturalAeration", true);

	m_technology.m_tec1_4.m_tec1_4_1.m_flag_PSI[DGNB::Tec1_4_1::PSI_HighCompactness].set("PSI_HighCompactness", true);
	m_technology.m_tec1_4.m_tec1_4_1.m_flag_PSI[DGNB::Tec1_4_1::PSI_BalancedWindowAreaRatioUnderConsiderationOfShading].set("PSI_BalancedWindowAreaRatioUnderConsiderationOfShading", true);
	m_technology.m_tec1_4.m_tec1_4_1.m_flag_PSI[DGNB::Tec1_4_1::PSI_ConstructionalSunblindToPreventDirectSunlightOnWindowsDuringSummer].set("PSI_ConstructionalSunblindToPreventDirectSunlightOnWindowsDuringSummer", true);
	m_technology.m_tec1_4.m_tec1_4_1.m_flag_PSI[DGNB::Tec1_4_1::PSI_AsManyNaturallyLightedRoomsAsPossible].set("PSI_AsManyNaturallyLightedRoomsAsPossible", true);
	m_technology.m_tec1_4.m_tec1_4_1.m_flag_PSI[DGNB::Tec1_4_1::PSI_UseOfHighMassElementsForHeatStorage].set("PSI_UseOfHighMassElementsForHeatStorage", true);
	m_technology.m_tec1_4.m_tec1_4_1.m_flag_PSI[DGNB::Tec1_4_1::PSI_PassiveCooling].set("PSI_PassiveCooling", true);
	m_technology.m_tec1_4.m_tec1_4_1.m_flag_PSI[DGNB::Tec1_4_1::PSI_EffectiveNaturalAeration].set("PSI_EffectiveNaturalAeration", true);

	// Tec1.4.2
	m_technology.m_tec1_4.m_tec1_4_2.m_flag_AAOTIREW[DGNB::Tec1_4_2::AAOTIREW_AverageTemperatureOf50DegreesOrMore].set("AAOTIREW_AverageTemperatureOf50DegreesOrMore", true);
	m_technology.m_tec1_4.m_tec1_4_2.m_flag_AAOTIREW[DGNB::Tec1_4_2::AAOTIREW_AverageTemperatureBetween35and50Degrees].set("AAOTIREW_AverageTemperatureBetween35and50Degrees", true);
	m_technology.m_tec1_4.m_tec1_4_2.m_flag_AAOTIREW[DGNB::Tec1_4_2::AAOTIREW_AverageTemperatureOf35DegreesOrLess].set("AAOTIREW_AverageTemperatureOf35DegreesOrLess", true);
	m_technology.m_tec1_4.m_tec1_4_2.m_flag_AAOTIREW[DGNB::Tec1_4_2::AAOTIREW_NoHeatingSystemInBuilding].set("AAOTIREW_NoHeatingSystemInBuilding", true);
	m_technology.m_tec1_4.m_tec1_4_2.m_flag_AAOTIREW[DGNB::Tec1_4_2::AAOTIREW_100PercentOfWarmthDemandCoveredByRegenerativeEnergy].set("AAOTIREW_100PercentOfWarmthDemandCoveredByRegenerativeEnergy", true);

	m_technology.m_tec1_4.m_tec1_4_2.m_flag_AAOTIREC[DGNB::Tec1_4_2::AAOTIREC_AverageTemperatureOf14DegreesOrLess].set("AAOTIREC_AverageTemperatureOf14DegreesOrLess", true);
	m_technology.m_tec1_4.m_tec1_4_2.m_flag_AAOTIREC[DGNB::Tec1_4_2::AAOTIREC_AverageTemperatureBetween14and19Degrees].set("AAOTIREC_AverageTemperatureBetween14and19Degrees", true);
	m_technology.m_tec1_4.m_tec1_4_2.m_flag_AAOTIREC[DGNB::Tec1_4_2::AAOTIREC_AverageTemperatureOf19DegreesOrMore].set("AAOTIREC_AverageTemperatureOf19DegreesOrMore", true);
	m_technology.m_tec1_4.m_tec1_4_2.m_flag_AAOTIREC[DGNB::Tec1_4_2::AAOTIREC_NoCoolingSystemInBuilding].set("AAOTIREC_NoCoolingSystemInBuilding", true);
	m_technology.m_tec1_4.m_tec1_4_2.m_flag_AAOTIREC[DGNB::Tec1_4_2::AAOTIREC_100PercentOfCoolingDemandCoveredByRegenerativeEnergy].set("AAOTIREC_100PercentOfCoolingDemandCoveredByRegenerativeEnergy", true);

	// Tec1.4.3
	m_technology.m_tec1_4.m_tec1_4_3.m_flag_ABSSEC[DGNB::Tec1_4_3::ABSSEC_GenerallyGoodAccessibilityOfAllSystemComponentsForReplacementAndRetrofitting].set("ABSSEC_GenerallyGoodAccessibilityOfAllSystemComponentsForReplacementAndRetrofitting", true);
	m_technology.m_tec1_4.m_tec1_4_3.m_flag_ABSSEC[DGNB::Tec1_4_3::ABSSEC_SufficientNumberAndSizeOfOpeningsDoorsAndHallways].set("ABSSEC_SufficientNumberAndSizeOfOpeningsDoorsAndHallways", true);
	m_technology.m_tec1_4.m_tec1_4_3.m_flag_ABSSEC[DGNB::Tec1_4_3::ABSSEC_TransportAndReplacementOfComponentsPossibleWithoutConstructionalMeasures].set("ABSSEC_TransportAndReplacementOfComponentsPossibleWithoutConstructionalMeasures", true);

	m_technology.m_tec1_4.m_tec1_4_3.m_flag_ABSDTA[DGNB::Tec1_4_3::ABSDTA_VerticalDuctsAndTracesOfAllSubsectionsAccessible].set("ABSDTA_VerticalDuctsAndTracesOfAllSubsectionsAccessible", true);
	m_technology.m_tec1_4.m_tec1_4_3.m_flag_ABSDTA[DGNB::Tec1_4_3::ABSDTA_PossibilityOfRetrofittingWithoutMajorDisturbanceToBuildingOperation].set("ABSDTA_PossibilityOfRetrofittingWithoutMajorDisturbanceToBuildingOperation", true);

	// Tec1.4.4
	m_technology.m_tec1_4.m_tec1_4_4.m_flag_ISSU[DGNB::Tec1_4_4::ISSU_PlanningAndImplementationAccordingToDIN_EN_ISO_16484_1].set("ISSU_PlanningAndImplementationAccordingToDIN_EN_ISO_16484_1", true);
	m_technology.m_tec1_4.m_tec1_4_4.m_flag_ISSU[DGNB::Tec1_4_4::ISSU_OpenAndStandardizedProtocolsInExistingNetworks].set("ISSU_OpenAndStandardizedProtocolsInExistingNetworks", true);

	m_technology.m_tec1_4.m_tec1_4_4.m_flag_ISIFSS[DGNB::Tec1_4_4::ISIFSS_Sunblind].set("ISIFSS_Sunblind", true);
	m_technology.m_tec1_4.m_tec1_4_4.m_flag_ISIFSS[DGNB::Tec1_4_4::ISIFSS_Lighting].set("ISIFSS_Lighting", true);
	m_technology.m_tec1_4.m_tec1_4_4.m_flag_ISIFSS[DGNB::Tec1_4_4::ISIFSS_Heating].set("ISIFSS_Heating", true);
	m_technology.m_tec1_4.m_tec1_4_4.m_flag_ISIFSS[DGNB::Tec1_4_4::ISIFSS_Aeration].set("ISIFSS_Aeration", true);
	m_technology.m_tec1_4.m_tec1_4_4.m_flag_ISIFSS[DGNB::Tec1_4_4::ISIFSS_Cooling].set("ISIFSS_Cooling", true);
	m_technology.m_tec1_4.m_tec1_4_4.m_flag_ISIFSS[DGNB::Tec1_4_4::ISIFSS_EnergyManagement].set("ISIFSS_EnergyManagement", true);
	m_technology.m_tec1_4.m_tec1_4_4.m_flag_ISIFSS[DGNB::Tec1_4_4::ISIFSS_PresenceDetection].set("ISIFSS_PresenceDetection", true);
	m_technology.m_tec1_4.m_tec1_4_4.m_flag_ISIFSS[DGNB::Tec1_4_4::ISIFSS_Lifts].set("ISIFSS_Lifts", true);

	m_technology.m_tec1_4.m_tec1_4_4.m_flag_ISPITSMQDS[DGNB::Tec1_4_4::ISPITSMQDS_AnalysisOfExistingEnergyPotentialAndPossibleNetworkingWithExistingSurroundingEnergyInfrastructure].set("ISPITSMQDS_AnalysisOfExistingEnergyPotentialAndPossibleNetworkingWithExistingSurroundingEnergyInfrastructure", true);
	m_technology.m_tec1_4.m_tec1_4_4.m_flag_ISPITSMQDS[DGNB::Tec1_4_4::ISPITSMQDS_CreationOfQuarterRelatedEnergyBalancesForHeatingCoolingAndElectricityEcologicalComparisonOfTheEmissionsOfAtLeast3PeripheralAndOrCentralHeatSupplyVariants].set("ISPITSMQDS_CreationOfQuarterRelatedEnergyBalancesForHeatingCoolingAndElectricityEcologicalComparisonOfTheEmissionsOfAtLeast3PeripheralAndOrCentralHeatSupplyVariants", true);
	m_technology.m_tec1_4.m_tec1_4_4.m_flag_ISPITSMQDS[DGNB::Tec1_4_4::ISPITSMQDS_EconomicalAssessmentOfInvestmentsAndOperatingCostsForAtLeast3SupplyVariants].set("ISPITSMQDS_EconomicalAssessmentOfInvestmentsAndOperatingCostsForAtLeast3SupplyVariants", true);
	m_technology.m_tec1_4.m_tec1_4_4.m_flag_ISPITSMQDS[DGNB::Tec1_4_4::ISPITSMQDS_AnalysisOfAppropriationOfRegenerativelyProducedEnergyForQuarterAndSurroudingsUnterInclusionOfPossibleConsumers].set("ISPITSMQDS_AnalysisOfAppropriationOfRegenerativelyProducedEnergyForQuarterAndSurroudingsUnterInclusionOfPossibleConsumers", true);

	m_technology.m_tec1_4.m_tec1_4_4.m_flag_ISIITSMQDS[DGNB::Tec1_4_4::ISIITSMQDS_ImplementationWithTheGoalOfSynergisticUseInRelationToQuarterAndDirectSurroundings].set("ISIITSMQDS_ImplementationWithTheGoalOfSynergisticUseInRelationToQuarterAndDirectSurroundings", true);

	m_technology.m_tec1_4.m_tec1_4_4.m_flag_ISIEIQDSQS[DGNB::Tec1_4_4::ISIEIQDSQS_BuildingUsesEnergyFromNearbyQuartersOrDirectSurroundingsToFulfillEnergyDemand].set("ISIEIQDSQS_BuildingUsesEnergyFromNearbyQuartersOrDirectSurroundingsToFulfillEnergyDemand", true);
	m_technology.m_tec1_4.m_tec1_4_4.m_flag_ISIEIQDSQS[DGNB::Tec1_4_4::ISIEIQDSQS_BuildingProvidesGeneratedRegenerativeEnergyToNearbyQuartersAndDirectSurroundings].set("ISIEIQDSQS_BuildingProvidesGeneratedRegenerativeEnergyToNearbyQuartersAndDirectSurroundings", true);

	m_technology.m_tec1_4.m_tec1_4_4.m_flag_ISIITSMQNES[DGNB::Tec1_4_4::ISIITSMQNES_BuildingProvidesRelevantStorageCapacity].set("ISIITSMQNES_BuildingProvidesRelevantStorageCapacity", true);
	m_technology.m_tec1_4.m_tec1_4_4.m_flag_ISIITSMQNES[DGNB::Tec1_4_4::ISIITSMQNES_BuildingUsesExistingIntegratedEnergyAndLoadManagement].set("ISIITSMQNES_BuildingUsesExistingIntegratedEnergyAndLoadManagement", true);

	// Tec1.4.5
	m_technology.m_tec1_4.m_tec1_4_5.m_flag_UREES[DGNB::Tec1_4_5::UREES_PortionOfEnergyFromRenewableSourcesAtLeast85Percent].set("UREES_PortionOfEnergyFromRenewableSourcesAtLeast85Percent", true);
	m_technology.m_tec1_4.m_tec1_4_5.m_flag_UREES[DGNB::Tec1_4_5::UREES_PortionOfEnergyFromRenewableSourcesAtLeast95Percent].set("UREES_PortionOfEnergyFromRenewableSourcesAtLeast95Percent", true);

	m_technology.m_tec1_4.m_tec1_4_5.m_flag_UREP[DGNB::Tec1_4_5::UREP_AtLeast60PercentOfSuitableRoofAreaUsedForSolarEnergyProduction].set("UREP_AtLeast60PercentOfSuitableRoofAreaUsedForSolarEnergyProduction", true);
	m_technology.m_tec1_4.m_tec1_4_5.m_flag_UREP[DGNB::Tec1_4_5::UREP_AtLeast60PercentOfSuitableParkingAreaUsedForSolarEnergyProduction].set("UREP_AtLeast60PercentOfSuitableParkingAreaUsedForSolarEnergyProduction", true);
	m_technology.m_tec1_4.m_tec1_4_5.m_flag_UREP[DGNB::Tec1_4_5::UREP_Residential_MinimumPowerOf0_06kWPeakPerSQMOfPlot].set("UREP_Residential_MinimumPowerOf0_06kWPeakPerSQMOfPlot", true);
	m_technology.m_tec1_4.m_tec1_4_5.m_flag_UREP[DGNB::Tec1_4_5::UREP_AtLeast80PercentOfSuitableRoofAreaUsedForSolarEnergyProduction].set("UREP_AtLeast80PercentOfSuitableRoofAreaUsedForSolarEnergyProduction", true);
	m_technology.m_tec1_4.m_tec1_4_5.m_flag_UREP[DGNB::Tec1_4_5::UREP_AtLeast80PercentOfSuitableParkingAreaUsedForSolarEnergyProduction].set("UREP_AtLeast80PercentOfSuitableParkingAreaUsedForSolarEnergyProduction", true);
	m_technology.m_tec1_4.m_tec1_4_5.m_flag_UREP[DGNB::Tec1_4_5::UREP_Residential_MinimumPowerOf0_08kWPeakPerSQMOfPlot].set("UREP_Residential_MinimumPowerOf0_08kWPeakPerSQMOfPlot", true);

	// Tec1.6.1
	m_technology.m_tec1_6.m_tec1_6_1.m_flag_CCPID161[DGNB::Tec1_6_1::CCPID161_DemolitionOrPartialDemolition].set("CCPID161_DemolitionOrPartialDemolition", true);

	m_technology.m_tec1_6.m_tec1_6_1.m_flag_SSAPPDA[DGNB::Tec1_6_1::SSAPPDA_CircularConstructionPotentialsOfSiteAndRegionResourcesHasBeenAnalysed].set("SSAPPDA_CircularConstructionPotentialsOfSiteAndRegionResourcesHasBeenAnalysed", true);

	m_technology.m_tec1_6.m_tec1_6_1.m_flag_SSAPPDCEBSPU[DGNB::Tec1_6_1::SSAPPDCEBSPU_StockPreserved].set("SSAPPDCEBSPU_StockPreserved", true);
	m_technology.m_tec1_6.m_tec1_6_1.m_flag_SSAPPDCEBSPU[DGNB::Tec1_6_1::SSAPPDCEBSPU_StockExpanded].set("SSAPPDCEBSPU_StockExpanded", true);
	m_technology.m_tec1_6.m_tec1_6_1.m_flag_SSAPPDCEBSPU[DGNB::Tec1_6_1::SSAPPDCEBSPU_StockElementsPutToUse].set("SSAPPDCEBSPU_StockElementsPutToUse", true);

	m_technology.m_tec1_6.m_tec1_6_1.m_flag_SSAPPDDJ[DGNB::Tec1_6_1::SSAPPDDJ_JustificationProvided].set("SSAPPDDJ_JustificationProvided", true);
	m_technology.m_tec1_6.m_tec1_6_1.m_flag_SSAPPDDJ[DGNB::Tec1_6_1::SSAPPDDJ_InventoryOfPartsMaterialFlowBalanceStockAnalysisTaken].set("SSAPPDDJ_InventoryOfPartsMaterialFlowBalanceStockAnalysisTaken", true);

	m_technology.m_tec1_6.m_tec1_6_1.m_flag_SSAPPDDE[DGNB::Tec1_6_1::SSAPPDDE_ProactiveSearchForBuyersOrAcceptorsOfPartsAndProductsDuringDemolition].set("SSAPPDDE_ProactiveSearchForBuyersOrAcceptorsOfPartsAndProductsDuringDemolition", true);
	m_technology.m_tec1_6.m_tec1_6_1.m_flag_SSAPPDDE[DGNB::Tec1_6_1::SSAPPDDE_InventoryTakenForMassesAndTransportDistances].set("SSAPPDDE_InventoryTakenForMassesAndTransportDistances", true);
	m_technology.m_tec1_6.m_tec1_6_1.m_flag_SSAPPDDE[DGNB::Tec1_6_1::SSAPPDDE_MeasuresTakenToOptimiseReuseAndDisposal].set("SSAPPDDE_MeasuresTakenToOptimiseReuseAndDisposal", true);
	m_technology.m_tec1_6.m_tec1_6_1.m_flag_SSAPPDDE[DGNB::Tec1_6_1::SSAPPDDE_RecommendedOrOtherSuitableMeasuresAgainstHazardousMaterialsTaken].set("SSAPPDDE_RecommendedOrOtherSuitableMeasuresAgainstHazardousMaterialsTaken", true);

	m_technology.m_tec1_6.m_tec1_6_1.m_flag_SSAPPDDAC[DGNB::Tec1_6_1::SSAPPDDAC_DGNBDemolitionCertificationFollowed].set("SSAPPDDAC_DGNBDemolitionCertificationFollowed", true);

	m_technology.m_tec1_6.m_tec1_6_1.m_flag_SSAPPDCERS[DGNB::Tec1_6_1::SSAPPDCERS_MaterialsOrElementsLeftFromDemolitionReusedInProject].set("SSAPPDCERS_MaterialsOrElementsLeftFromDemolitionReusedInProject", true);

	// Tec1.6.2
	m_technology.m_tec1_6.m_tec1_6_2.m_flag_CCPID162[DGNB::Tec1_6_2::CCPID162_DemolitionOrPartialDemolition].set("CCPID162_DemolitionOrPartialDemolition", true);

	m_technology.m_tec1_6.m_tec1_6_2.m_flag_CCCPGFD[DGNB::Tec1_6_2::CCCPGFD_PlanningWithCircularGoal].set("CCCPGFD_PlanningWithCircularGoal", true);
	m_technology.m_tec1_6.m_tec1_6_2.m_flag_CCCPGFD[DGNB::Tec1_6_2::CCCPGFD_Alt_PlanIncludesPreexistingRecyclableMaterials].set("CCCPGFD_Alt_PlanIncludesPreexistingRecyclableMaterials", true);

	m_technology.m_tec1_6.m_tec1_6_2.m_flag_CCCPPRCDCEP[DGNB::Tec1_6_2::CCCPPRCDCEP_CreationAndEvaluationOfVariantsOfAtLeast4Topics].set("CCCPPRCDCEP_CreationAndEvaluationOfVariantsOfAtLeast4Topics", true);
	m_technology.m_tec1_6.m_tec1_6_2.m_flag_CCCPPRCDCEP[DGNB::Tec1_6_2::CCCPPRCDCEP_Alt_UseOfToolsForCreationOfCircularityOptimisationBalancesAndIndices].set("CCCPPRCDCEP_Alt_UseOfToolsForCreationOfCircularityOptimisationBalancesAndIndices", true);

	m_technology.m_tec1_6.m_tec1_6_2.m_flag_CCCPPRCDCAEP[DGNB::Tec1_6_2::CCCPPRCDCAEP_CreationAndEvaluationOfVariantsOfAtLeast4Topics].set("CCCPPRCDCAEP_CreationAndEvaluationOfVariantsOfAtLeast4Topics", true);
	m_technology.m_tec1_6.m_tec1_6_2.m_flag_CCCPPRCDCAEP[DGNB::Tec1_6_2::CCCPPRCDCAEP_Alt_UseOfToolsForCreationOfCircularityOptimisationBalancesAndIndices].set("CCCPPRCDCAEP_Alt_UseOfToolsForCreationOfCircularityOptimisationBalancesAndIndices", true);
	m_technology.m_tec1_6.m_tec1_6_2.m_flag_CCCPPRCDCAEP[DGNB::Tec1_6_2::CCCPPRCDCAEP_Alt_GenerationOfABuildingResourcePass].set("CCCPPRCDCAEP_Alt_GenerationOfABuildingResourcePass", true);
	m_technology.m_tec1_6.m_tec1_6_2.m_flag_CCCPPRCDCAEP[DGNB::Tec1_6_2::CCCPPRCDCAEP_ParallelEvaluationOfClimateInfluenceAndCosts].set("CCCPPRCDCAEP_ParallelEvaluationOfClimateInfluenceAndCosts", true);

	// Tec1.6.3
	m_technology.m_tec1_6.m_tec1_6_3.m_flag_CCPID163[DGNB::Tec1_6_3::CCPID163_DemolitionOrPartialDemolition].set("CCPID163_DemolitionOrPartialDemolition", true);

	m_technology.m_tec1_6.m_tec1_6_3.m_flag_CCEDDCBPBP[DGNB::Tec1_6_3::CCEDDCBPBP_ReducedBuildingPass].set("CCEDDCBPBP_ReducedBuildingPass", true);
	m_technology.m_tec1_6.m_tec1_6_3.m_flag_CCEDDCBPBP[DGNB::Tec1_6_3::CCEDDCBPBP_CompleteBuildingPass].set("CCEDDCBPBP_CompleteBuildingPass", true);

	m_technology.m_tec1_6.m_tec1_6_3.m_flag_CCEDERCPBL[DGNB::Tec1_6_3::CCEDERCPBL_ModerateGoalQuotaReachedForAllProperties].set("CCEDERCPBL_ModerateGoalQuotaReachedForAllProperties", true);
	m_technology.m_tec1_6.m_tec1_6_3.m_flag_CCEDERCPBL[DGNB::Tec1_6_3::CCEDERCPBL_HighGoalQuotaReachedForAtLeast2Properties].set("CCEDERCPBL_HighGoalQuotaReachedForAtLeast2Properties", true);

	m_technology.m_tec1_6.m_tec1_6_3.m_flag_CCEDUCPCEL[DGNB::Tec1_6_3::CCEDUCPCEL_UseOfProductsOfQS4].set("CCEDUCPCEL_UseOfProductsOfQS4", true);
	m_technology.m_tec1_6.m_tec1_6_3.m_flag_CCEDUCPCEL[DGNB::Tec1_6_3::CCEDUCPCEL_UseOfProductsOfQS3].set("CCEDUCPCEL_UseOfProductsOfQS3", true);
	m_technology.m_tec1_6.m_tec1_6_3.m_flag_CCEDUCPCEL[DGNB::Tec1_6_3::CCEDUCPCEL_UseOfProductsOfQS2].set("CCEDUCPCEL_UseOfProductsOfQS2", true);
	m_technology.m_tec1_6.m_tec1_6_3.m_flag_CCEDUCPCEL[DGNB::Tec1_6_3::CCEDUCPCEL_UseOfProductsOfQS1].set("CCEDUCPCEL_UseOfProductsOfQS1", true);
	m_technology.m_tec1_6.m_tec1_6_3.m_flag_CCEDUCPCEL[DGNB::Tec1_6_3::CCEDUCPCEL_RequirementsOfSimplifiedMethodFulfilled].set("CCEDUCPCEL_RequirementsOfSimplifiedMethodFulfilled", true);

	m_technology.m_tec1_6.m_tec1_6_3.m_flag_CCEDCERMACAMMCI[DGNB::Tec1_6_3::CCEDCERMACAMMCI_UseOfRecycledMaterials].set("CCEDCERMACAMMCI_UseOfRecycledMaterials", true);
	m_technology.m_tec1_6.m_tec1_6_3.m_flag_CCEDCERMACAMMCI[DGNB::Tec1_6_3::CCEDCERMACAMMCI_NumberOfConstructionsUsingMaterialAppropriateConstructionsResultsSubmitted].set("CCEDCERMACAMMCI_NumberOfConstructionsUsingMaterialAppropriateConstructionsResultsSubmitted", true);
	m_technology.m_tec1_6.m_tec1_6_3.m_flag_CCEDCERMACAMMCI[DGNB::Tec1_6_3::CCEDCERMACAMMCI_NumberOfConstructionsAvoidingMaterialMixingOrLayeringResultsSubmitted].set("CCEDCERMACAMMCI_NumberOfConstructionsAvoidingMaterialMixingOrLayeringResultsSubmitted", true);
	m_technology.m_tec1_6.m_tec1_6_3.m_flag_CCEDCERMACAMMCI[DGNB::Tec1_6_3::CCEDCERMACAMMCI_CircularAspectsImplementedInConstructiveIntegrations].set("CCEDCERMACAMMCI_CircularAspectsImplementedInConstructiveIntegrations", true);

	m_technology.m_tec1_6.m_tec1_6_3.m_flag_CCEDRRDI[DGNB::Tec1_6_3::CCEDRRDI_InstructionsIncludeReuseRebuildingAndDemolition].set("CCEDRRDI_InstructionsIncludeReuseRebuildingAndDemolition", true);
	m_technology.m_tec1_6.m_tec1_6_3.m_flag_CCEDRRDI[DGNB::Tec1_6_3::CCEDRRDI_InstructionsIncludeRebuildingAndDemolition].set("CCEDRRDI_InstructionsIncludeRebuildingAndDemolition", true);

	m_technology.m_tec1_6.m_tec1_6_3.m_flag_CCEDCECBACE[DGNB::Tec1_6_3::CCEDCECBACE_MoreThan90PercentOfPartsOriginateFromCircularEconomy].set("CCEDCECBACE_MoreThan90PercentOfPartsOriginateFromCircularEconomy", true);
	m_technology.m_tec1_6.m_tec1_6_3.m_flag_CCEDCECBACE[DGNB::Tec1_6_3::CCEDCECBACE_MoreThan90PercentOfBuildingMassSuitedForReuseInCircularEconomy].set("CCEDCECBACE_MoreThan90PercentOfBuildingMassSuitedForReuseInCircularEconomy", true);
	m_technology.m_tec1_6.m_tec1_6_3.m_flag_CCEDCECBACE[DGNB::Tec1_6_3::CCEDCECBACE_AggregatedCircularyIndexEvaluationDocumentedInBuildingPassAndRatedGoodOrAbove].set("CCEDCECBACE_AggregatedCircularyIndexEvaluationDocumentedInBuildingPassAndRatedGoodOrAbove", true);

	m_technology.m_tec1_6.m_tec1_6_3.m_para[DGNB::Tec1_6_3::P_CCEDCERMACAMMCI_NumberOfConstructionsUsingMaterialAppropriateConstructions].set("CCEDCERMACAMMCI_NumberOfConstructionsUsingMaterialAppropriateConstructions", 5, IBK::Unit("-"));
	m_technology.m_tec1_6.m_tec1_6_3.m_para[DGNB::Tec1_6_3::P_CCEDCERMACAMMCI_NumberOfConstructionsAvoidingMaterialMixingOrLayering].set("CCEDCERMACAMMCI_NumberOfConstructionsAvoidingMaterialMixingOrLayering", 5, IBK::Unit("-"));

	// Tec3.1.1
	m_technology.m_tec3_1.m_tec3_1_1.m_flag_MIMC[DGNB::Tec3_1_1::MIMC_ConceptIncludesGoalsForSustainableMobility].set("MIMC_ConceptIncludesGoalsForSustainableMobility", true);
	m_technology.m_tec3_1.m_tec3_1_1.m_flag_MIMC[DGNB::Tec3_1_1::MIMC_ConceptIncludesFutureTrafficDemands].set("MIMC_ConceptIncludesFutureTrafficDemands", true);

	// Tec3.1.2
	m_technology.m_tec3_1.m_tec3_1_2.m_flag_IPI[DGNB::Tec3_1_2::IPI_TransparentSafeAndBarrierFreeRoutingVisibleAndComprehensiveSignage].set("IPI_TransparentSafeAndBarrierFreeRoutingVisibleAndComprehensiveSignage", true);
	m_technology.m_tec3_1.m_tec3_1_2.m_flag_IPI[DGNB::Tec3_1_2::IPI_DesignatedParkingSpotsForMobilityAidsLikeWalkersOrStrollers].set("IPI_DesignatedParkingSpotsForMobilityAidsLikeWalkersOrStrollers", true);

	m_technology.m_tec3_1.m_tec3_1_2.m_flag_IBI[DGNB::Tec3_1_2::IBI_AtLeast80PerceptOfBicycleParkingSpotsAreClearlyRelatedToTheBuildingNearTheEntranceAccessibleAndHaveProtectionAgainstTheft].set("IBI_AtLeast80PerceptOfBicycleParkingSpotsAreClearlyRelatedToTheBuildingNearTheEntranceAccessibleAndHaveProtectionAgainstTheft", true);
	m_technology.m_tec3_1.m_tec3_1_2.m_flag_IBI[DGNB::Tec3_1_2::IBI_Residential100PercentAllOthers80PercentOfParkingSpotsAreEquippedWithWeatherProtection].set("IBI_Residential100PercentAllOthers80PercentOfParkingSpotsAreEquippedWithWeatherProtection", true);
	m_technology.m_tec3_1.m_tec3_1_2.m_flag_IBI[DGNB::Tec3_1_2::IBI_SufficientNumberOfParkingSpotsForCargoBikesWithTheftProtection].set("IBI_SufficientNumberOfParkingSpotsForCargoBikesWithTheftProtection", true);

	m_technology.m_tec3_1.m_tec3_1_2.m_flag_IMIT[DGNB::Tec3_1_2::IMIT_ParkingSpacesReducedAccordingToRegulations].set("IMIT_ParkingSpacesReducedAccordingToRegulations", true);
	m_technology.m_tec3_1.m_tec3_1_2.m_flag_IMIT[DGNB::Tec3_1_2::IMIT_ReducedParkingDemandRedirectedToMobilityHubThatFeaturesFurtherReductionsOfTransportationNeeds].set("IMIT_ReducedParkingDemandRedirectedToMobilityHubThatFeaturesFurtherReductionsOfTransportationNeeds", true);
	m_technology.m_tec3_1.m_tec3_1_2.m_flag_IMIT[DGNB::Tec3_1_2::IMIT_ParkingSpacesOnSiteFulfillOrganisationalAndConstructionalRequirementsForCarsharing].set("IMIT_ParkingSpacesOnSiteFulfillOrganisationalAndConstructionalRequirementsForCarsharing", true);
	m_technology.m_tec3_1.m_tec3_1_2.m_flag_IMIT[DGNB::Tec3_1_2::IMIT_AtLeast80PercentOfParkingSpacesHaveNoDesignatedSpecificOccupant].set("IMIT_AtLeast80PercentOfParkingSpacesHaveNoDesignatedSpecificOccupant", true);
	m_technology.m_tec3_1.m_tec3_1_2.m_flag_IMIT[DGNB::Tec3_1_2::IMIT_Alternative_MobilityConceptForgoesParkingSpacesWithTheExceptionOfDisabledParkingAndCarsharingSpaces].set("IMIT_Alternative_MobilityConceptForgoesParkingSpacesWithTheExceptionOfDisabledParkingAndCarsharingSpaces", true);

	m_technology.m_tec3_1.m_tec3_1_2.m_flag_IA2030MMC[DGNB::Tec3_1_2::IA2030MMC_MobilityConceptIncludesMobilityManagementConcept].set("IA2030MMC_MobilityConceptIncludesMobilityManagementConcept", true);

	// Tec3.1.3
	m_technology.m_tec3_1.m_tec3_1_3.m_flag_IAFSBTEB[DGNB::Tec3_1_3::IAFSBTEB_ResultsSubmitted].set("IAFSBTEB_ResultsSubmitted", true);

	m_technology.m_tec3_1.m_tec3_1_3.m_flag_IAFSMIT[DGNB::Tec3_1_3::IAFSMIT_ResultsSubmitted].set("IAFSMIT_ResultsSubmitted", true);

	m_technology.m_tec3_1.m_tec3_1_3.m_flag_IAFSILTS[DGNB::Tec3_1_3::IAFSILTS_IntegrationIntoBuildingEnergyManagement].set("IAFSILTS_IntegrationIntoBuildingEnergyManagement", true);
	m_technology.m_tec3_1.m_tec3_1_3.m_flag_IAFSILTS[DGNB::Tec3_1_3::IAFSILTS_IntegrationIntoLoadingManagementNetwork].set("IAFSILTS_IntegrationIntoLoadingManagementNetwork", true);

	m_technology.m_tec3_1.m_tec3_1_3.m_flag_IAFSA2030CPG[DGNB::Tec3_1_3::IAFSA2030CPG_VehicleToGrid_SetupForBidirectionalLoadingAndUnloadingOfElectricVehicles].set("IAFSA2030CPG_VehicleToGrid_SetupForBidirectionalLoadingAndUnloadingOfElectricVehicles", true);

	m_technology.m_tec3_1.m_tec3_1_3.m_para[DGNB::Tec3_1_3::P_Tec3_1_3_1IAFSBTEB_NumberOfRequiredBicycleParkingSpots].set("Tec3_1_3_1IAFSBTEB_NumberOfRequiredBicycleParkingSpots", 20, IBK::Unit("-"));
	m_technology.m_tec3_1.m_tec3_1_3.m_para[DGNB::Tec3_1_3::P_Tec3_1_3_1IAFSBTEB_NumberOfBicycleParkingSpotsEquippedWithLoadingDock].set("Tec3_1_3_1IAFSBTEB_NumberOfBicycleParkingSpotsEquippedWithLoadingDock", 15, IBK::Unit("-"));
	m_technology.m_tec3_1.m_tec3_1_3.m_para[DGNB::Tec3_1_3::P_Tec3_1_3_2IAFSMIT_PercentageOfParkingsSpotsOfPermanentelyDesignatedOccupantsOrResidentsEquippedWithLoadingDock].set("Tec3_1_3_2IAFSMIT_PercentageOfParkingsSpotsOfPermanentelyDesignatedOccupantsOrResidentsEquippedWithLoadingDock", 60, IBK::Unit("---"));		// ToDo Einheit % SO oder anders?
	m_technology.m_tec3_1.m_tec3_1_3.m_para[DGNB::Tec3_1_3::P_Tec3_1_3_2IAFSMIT_PercentageOfOtherParkingsSpotsEquippedWithLoadingDock].set("Tec3_1_3_2IAFSMIT_PercentageOfOtherParkingsSpotsEquippedWithLoadingDock", 20, IBK::Unit("---"));																					// ToDo Einheit % SO oder anders?
	m_technology.m_tec3_1.m_tec3_1_3.m_para[DGNB::Tec3_1_3::P_Tec3_1_3_2IAFSMIT_TotalNumberOfParkingsSpotsEquippedWithLoadingDock].set("Tec3_1_3_2IAFSMIT_TotalNumberOfParkingsSpotsEquippedWithLoadingDock", 20, IBK::Unit("-"));
	m_technology.m_tec3_1.m_tec3_1_3.m_para[DGNB::Tec3_1_3::P_Tec3_1_3_2IAFSMIT_PercentageOfOtherParkingsSpotsPreparedToBeEquippedWithLoadingDock].set("Tec3_1_3_2IAFSMIT_PercentageOfOtherParkingsSpotsPreparedToBeEquippedWithLoadingDock", 40, IBK::Unit("---"));															// ToDo Einheit % SO oder anders?

	// Tec3.1.4
	m_technology.m_tec3_1.m_tec3_1_4.m_flag_IAFSBTEB[DGNB::Tec3_1_4::RSMS_ResultsSubmitted].set("RSMS_ResultsSubmitted", true);
	m_technology.m_tec3_1.m_tec3_1_4.m_flag_IAFSBTEB[DGNB::Tec3_1_4::RSMS_Alt_BuildingAndOccupantsArePartOfAQuarterMobilityConceptIncludingOrganisationAndSupportOfSharingsystems].set("RSMS_Alt_BuildingAndOccupantsArePartOfAQuarterMobilityConceptIncludingOrganisationAndSupportOfSharingsystems", true);

	m_technology.m_tec3_1.m_tec3_1_4.m_para[DGNB::Tec3_1_4::P_Tec3_1_4NumberOfIndividualNonOverlappingMobilitySharingOffers].set("Tec3_1_4NumberOfIndividualNonOverlappingMobilitySharingOffers", 3, IBK::Unit("-"));

	// Tec3.1.5
	m_technology.m_tec3_1.m_tec3_1_5.m_flag_OCBGO[DGNB::Tec3_1_5::OCBGO_SufficientAvailabilityOfShowers].set("OCBGO_SufficientAvailabilityOfShowers", true);
	m_technology.m_tec3_1.m_tec3_1_5.m_flag_OCBGO[DGNB::Tec3_1_5::OCBGO_SufficientAvailabilityOfChangingRoomsAndDryingRoomsForBikeWear].set("OCBGO_SufficientAvailabilityOfChangingRoomsAndDryingRoomsForBikeWear", true);
	m_technology.m_tec3_1.m_tec3_1_5.m_flag_OCBGO[DGNB::Tec3_1_5::OCBGO_SufficientAvailabilityOfMaintenanceFacilitiesForBikes].set("OCBGO_SufficientAvailabilityOfMaintenanceFacilitiesForBikes", true);
	m_technology.m_tec3_1.m_tec3_1_5.m_flag_OCBGO[DGNB::Tec3_1_5::OCBGO_Residential_ParkingSpacesForBikeTrailers].set("OCBGO_Residential_ParkingSpacesForBikeTrailers", true);

	/*!
	 * Process
	 */
	// Pro1.1.1
	m_process.m_pro1_1.m_pro1_1_1.m_flag_RPB[DGNB::Pro1_1_1::RPB_ImplementationOfDeclarationSustainabilityArchitecture].set("RPB_ImplementationOfDeclarationSustainabilityArchitecture", true);
	m_process.m_pro1_1.m_pro1_1_1.m_flag_RPB[DGNB::Pro1_1_1::RPB_ComplianceWithEuropeanSustainableReportFrameworkLevels].set("RPB_ComplianceWithEuropeanSustainableReportFrameworkLevels", true);

	m_process.m_pro1_1.m_pro1_1_1.m_flag_RPRP[DGNB::Pro1_1_1::RPRP_PlanFollowsChecklist1OrAnnexe1A].set("RPRP_PlanFollowsChecklist1OrAnnexe1A", true);
	m_process.m_pro1_1.m_pro1_1_1.m_flag_RPRP[DGNB::Pro1_1_1::RPRP_PlanFollowsChecklist12OrAnnexe1B].set("RPRP_PlanFollowsChecklist12OrAnnexe1B", true);
	m_process.m_pro1_1.m_pro1_1_1.m_flag_RPRP[DGNB::Pro1_1_1::RPRP_PlanFollowsChecklist123OrAnnexe1C].set("RPRP_PlanFollowsChecklist123OrAnnexe1C", true);

	m_process.m_pro1_1.m_pro1_1_1.m_flag_RPA2030FS[DGNB::Pro1_1_1::RPA2030FS_FeasibilitySurveyConductedAllowingForImplementationOfSustainableConcepts].set("RPA2030FS_FeasibilitySurveyConductedAllowingForImplementationOfSustainableConcepts", true);

	// Pro1.1.2
	m_process.m_pro1_1.m_pro1_1_2.m_flag_A2030P[DGNB::Pro1_1_2::A2030P_CounselDuringRequirementAnalysis].set("A2030P_CounselDuringRequirementAnalysis", true);
	m_process.m_pro1_1.m_pro1_1_2.m_flag_A2030P[DGNB::Pro1_1_2::A2030P_ParticipationDuringRequirementAnalysis].set("A2030P_ParticipationDuringRequirementAnalysis", true);
	m_process.m_pro1_1.m_pro1_1_2.m_flag_A2030P[DGNB::Pro1_1_2::A2030P_CounselDuringConceptionPhase].set("A2030P_CounselDuringConceptionPhase", true);
	m_process.m_pro1_1.m_pro1_1_2.m_flag_A2030P[DGNB::Pro1_1_2::A2030P_ParticipationDuringConceptionPhase].set("A2030P_ParticipationDuringConceptionPhase", true);
	m_process.m_pro1_1.m_pro1_1_2.m_flag_A2030P[DGNB::Pro1_1_2::A2030P_CounselDuringImplementationPhase].set("A2030P_CounselDuringImplementationPhase", true);
	m_process.m_pro1_1.m_pro1_1_2.m_flag_A2030P[DGNB::Pro1_1_2::A2030P_ParticipationDuringImplementationPhase].set("A2030P_ParticipationDuringImplementationPhase", true);

	// Pro1.1.3
	m_process.m_pro1_1.m_pro1_1_3.m_flag_CSSR[DGNB::Pro1_1_3::CSSR_SpecificationsIncludeDetailedRequirementsToBuildingsSustainabilityFromEcologicalEconomicalSocioculturalFunctionalTechnicalAspectsAsWellAsPlanningAndConstructionPhase].set("CSSR_SpecificationsIncludeDetailedRequirementsToBuildingsSustainabilityFromEcologicalEconomicalSocioculturalFunctionalTechnicalAspectsAsWellAsPlanningAndConstructionPhase", true);
	m_process.m_pro1_1.m_pro1_1_3.m_flag_CSSR[DGNB::Pro1_1_3::CSSR_SpecificationsFurtherIncludeDefinitionsOfResponsibilitiesAndPlanningMethodAndEssentialPlanningPhasesDecidedByAPlanningTeam].set("CSSR_SpecificationsFurtherIncludeDefinitionsOfResponsibilitiesAndPlanningMethodAndEssentialPlanningPhasesDecidedByAPlanningTeam", true);

	// Pro1.4.1
	m_process.m_pro1_4.m_pro1_4_1.m_flag_SATOEI[DGNB::Pro1_4_1::SATOEI_SelectSustainabilityAspectsOfHealthCompatibilityOrEnvironmentCompatibilityOrRelevantTechnicalAspectsIncludedInOffersGeneralPreliminaryRemarks].set("SATOEI_SelectSustainabilityAspectsOfHealthCompatibilityOrEnvironmentCompatibilityOrRelevantTechnicalAspectsIncludedInOffersGeneralPreliminaryRemarks", true);
	m_process.m_pro1_4.m_pro1_4_1.m_flag_SATOEI[DGNB::Pro1_4_1::SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAspectsOfConstructionProductsIncludedInOffersGeneralPreliminaryRemarks].set("SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAspectsOfConstructionProductsIncludedInOffersGeneralPreliminaryRemarks", true);
	m_process.m_pro1_4.m_pro1_4_1.m_flag_SATOEI[DGNB::Pro1_4_1::SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAspectsOfConstructionProductsIncludedCraftSpecificallyAndSelectivelyOnAServiceItemLevelInOffer].set("SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAspectsOfConstructionProductsIncludedCraftSpecificallyAndSelectivelyOnAServiceItemLevelInOffer", true);
	m_process.m_pro1_4.m_pro1_4_1.m_flag_SATOEI[DGNB::Pro1_4_1::SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAndTechnicalAspectsOfConstructionProductsIncludedCraftSpecificallyAndSelectivelyOnAServiceItemLevelInOffer].set("SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAndTechnicalAspectsOfConstructionProductsIncludedCraftSpecificallyAndSelectivelyOnAServiceItemLevelInOffer", true);

	m_process.m_pro1_4.m_pro1_4_1.m_flag_SATOCERM[DGNB::Pro1_4_1::SATOCERM_NoExclusionOfRecycledMaterialsInTenderOffer].set("SATOCERM_NoExclusionOfRecycledMaterialsInTenderOffer", true);

	// Pro1.6.1
	m_process.m_pro1_6.m_pro1_6_1.m_flag_CEVPEVPC[DGNB::Pro1_6_1::CEVPEVPC_PreemptiveExaminationButNoPlanningCompetitionConducted].set("CEVPEVPC_PreemptiveExaminationButNoPlanningCompetitionConducted", true);

	m_process.m_pro1_6.m_pro1_6_1.m_flag_CEVCAMSM[DGNB::Pro1_6_1::CEVCAMSM_ImplementationOfConceptAssignment].set("CEVCAMSM_ImplementationOfConceptAssignment", true);
	m_process.m_pro1_6.m_pro1_6_1.m_flag_CEVCAMSM[DGNB::Pro1_6_1::CEVCAMSM_ImplementationOfConceptAssignmentWithSpecialConcernForSustainableConstruction].set("CEVCAMSM_ImplementationOfConceptAssignmentWithSpecialConcernForSustainableConstruction", true);

	m_process.m_pro1_6.m_pro1_6_1.m_flag_CEVCAQE[DGNB::Pro1_6_1::CEVCAQE_CompetentDecisionMakingBoard].set("CEVCAQE_CompetentDecisionMakingBoard", true);
	m_process.m_pro1_6.m_pro1_6_1.m_flag_CEVCAQE[DGNB::Pro1_6_1::CEVCAQE_PostProcedureQualityEnsurance].set("CEVCAQE_PostProcedureQualityEnsurance", true);

	m_process.m_pro1_6.m_pro1_6_1.m_flag_CEVMASM[DGNB::Pro1_6_1::CEVMASM_ImplementationOfMultipleAssignments].set("CEVMASM_ImplementationOfMultipleAssignments", true);
	m_process.m_pro1_6.m_pro1_6_1.m_flag_CEVMASM[DGNB::Pro1_6_1::CEVMASM_ImplementationOfMultipleAssignmentsWithSpecialConcernForSustainableConstruction].set("CEVMASM_ImplementationOfMultipleAssignmentsWithSpecialConcernForSustainableConstruction", true);

	m_process.m_pro1_6.m_pro1_6_1.m_flag_CEVMAQE[DGNB::Pro1_6_1::CEVMAQE_CompetentDecisionMakingBoardOrSupervisionBySuch].set("CEVMAQE_CompetentDecisionMakingBoardOrSupervisionBySuch", true);

	m_process.m_pro1_6.m_pro1_6_1.m_flag_CEVMAIAWD[DGNB::Pro1_6_1::CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH3].set("CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH3", true);
	m_process.m_pro1_6.m_pro1_6_1.m_flag_CEVMAIAWD[DGNB::Pro1_6_1::CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH5].set("CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH5", true);
	m_process.m_pro1_6.m_pro1_6_1.m_flag_CEVMAIAWD[DGNB::Pro1_6_1::CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH8].set("CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH8", true);

	m_process.m_pro1_6.m_pro1_6_1.m_flag_CEVPCSQM[DGNB::Pro1_6_1::CEVPCSQM_ImplementationOfPlanningCompetition].set("CEVPCSQM_ImplementationOfPlanningCompetition", true);
	m_process.m_pro1_6.m_pro1_6_1.m_flag_CEVPCSQM[DGNB::Pro1_6_1::CEVPCSQM_ImplementationOfPlanningCompetitionWithSpecialConcernForSustainableConstruction].set("CEVPCSQM_ImplementationOfPlanningCompetitionWithSpecialConcernForSustainableConstruction", true);

	m_process.m_pro1_6.m_pro1_6_1.m_flag_CEVPCMCM[DGNB::Pro1_6_1::CEVPCMCM_CooperativeMethod].set("CEVPCMCM_CooperativeMethod", true);
	m_process.m_pro1_6.m_pro1_6_1.m_flag_CEVPCMCM[DGNB::Pro1_6_1::CEVPCMCM_OneOrTwoPhases_OpenCompetitionOrClosedCompetitionWithPreliminaryRound].set("CEVPCMCM_OneOrTwoPhases_OpenCompetitionOrClosedCompetitionWithPreliminaryRound", true);

	m_process.m_pro1_6.m_pro1_6_1.m_flag_CEVPCIAWD[DGNB::Pro1_6_1::CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH3].set("CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH3", true);
	m_process.m_pro1_6.m_pro1_6_1.m_flag_CEVPCIAWD[DGNB::Pro1_6_1::CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH5].set("CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH5", true);
	m_process.m_pro1_6.m_pro1_6_1.m_flag_CEVPCIAWD[DGNB::Pro1_6_1::CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH8].set("CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH8", true);

	m_process.m_pro1_6.m_pro1_6_1.m_flag_CEVPCCAWPT[DGNB::Pro1_6_1::CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH3].set("CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH3", true);
	m_process.m_pro1_6.m_pro1_6_1.m_flag_CEVPCCAWPT[DGNB::Pro1_6_1::CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH5].set("CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH5", true);
	m_process.m_pro1_6.m_pro1_6_1.m_flag_CEVPCCAWPT[DGNB::Pro1_6_1::CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH8].set("CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH8", true);

	// Pro1.6.2
	m_process.m_pro1_6.m_pro1_6_2.m_flag_RIDB[DGNB::Pro1_6_2::RIDB_ProjectPresentationInFrontOfDesignBoardOfCommuneAndArchitecturalAssociation].set("RIDB_ProjectPresentationInFrontOfDesignBoardOfCommuneAndArchitecturalAssociation", true);
	m_process.m_pro1_6.m_pro1_6_2.m_flag_RIDB[DGNB::Pro1_6_2::RIDB_ImplementationOfDesignBoardsRecommendations].set("RIDB_ImplementationOfDesignBoardsRecommendations", true);

	// Pro1.6.3
	m_process.m_pro1_6.m_pro1_6_3.m_flag_HAAR[DGNB::Pro1_6_3::HAAR_RecognitionOfGoodConstructionalCulturalQuality].set("HAAR_RecognitionOfGoodConstructionalCulturalQuality", true);
	m_process.m_pro1_6.m_pro1_6_3.m_flag_HAAR[DGNB::Pro1_6_3::HAAR_RecognitionOfFinishedProjectWithArchitectureAwardDGNBDiamond].set("HAAR_RecognitionOfFinishedProjectWithArchitectureAwardDGNBDiamond", true);

	// Pro2.1.1
	m_process.m_pro2_1.m_pro2_1_1.m_flag_NRCSC[DGNB::Pro2_1_1::NRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts].set("NRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts", true);

	m_process.m_pro2_1.m_pro2_1_1.m_flag_NRCSIO[DGNB::Pro2_1_1::NRCSIO_InstructionOrBriefungOfOperators].set("NRCSIO_InstructionOrBriefungOfOperators", true);

	m_process.m_pro2_1.m_pro2_1_1.m_flag_NRCSEI[DGNB::Pro2_1_1::NRCSEI_ExaminationOrVerificationOfImplementation].set("NRCSEI_ExaminationOrVerificationOfImplementation", true);

	// Pro2.1.2
	m_process.m_pro2_1.m_pro2_1_2.m_flag_DRCSC[DGNB::Pro2_1_2::DRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts].set("DRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts", true);

	m_process.m_pro2_1.m_pro2_1_2.m_flag_DRCSIO[DGNB::Pro2_1_2::DRCSIO_InstructionOrBriefungOfOperators].set("DRCSIO_InstructionOrBriefungOfOperators", true);

	m_process.m_pro2_1.m_pro2_1_2.m_flag_DRCSEI[DGNB::Pro2_1_2::DRCSEI_ExaminationOrVerificationOfImplementation].set("DRCSEI_ExaminationOrVerificationOfImplementation", true);

	// Pro2.1.3
	m_process.m_pro2_1.m_pro2_1_3.m_flag_SGPCSC[DGNB::Pro2_1_3::SGPCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts].set("SGPCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts", true);

	m_process.m_pro2_1.m_pro2_1_3.m_flag_SGPCSIO[DGNB::Pro2_1_3::SGPCSIO_InstructionOrBriefungOfOperators].set("SGPCSIO_InstructionOrBriefungOfOperators", true);

	m_process.m_pro2_1.m_pro2_1_3.m_flag_SGPCSEI[DGNB::Pro2_1_3::SGPCSEI_ExaminationOrVerificationOfImplementation].set("SGPCSEI_ExaminationOrVerificationOfImplementation", true);

	// Pro2.1.4
	m_process.m_pro2_1.m_pro2_1_4.m_flag_WRCSC[DGNB::Pro2_1_4::WRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts].set("WRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts", true);

	m_process.m_pro2_1.m_pro2_1_4.m_flag_WRCSIO[DGNB::Pro2_1_4::WRCSIO_InstructionOrBriefungOfOperators].set("WRCSIO_InstructionOrBriefungOfOperators", true);

	m_process.m_pro2_1.m_pro2_1_4.m_flag_WRCSEI[DGNB::Pro2_1_4::WRCSEI_ExaminationOrVerificationOfImplementation].set("WRCSEI_ExaminationOrVerificationOfImplementation", true);

	m_process.m_pro2_1.m_pro2_1_4.m_flag_WRCSCEWP[DGNB::Pro2_1_4::WRCSCEWP_UseOfNovelAndLargelyWastePreventiveConceptsMethodsAndTechnologies].set("WRCSCEWP_UseOfNovelAndLargelyWastePreventiveConceptsMethodsAndTechnologies", true);

	// Pro2.1.5
	m_process.m_pro2_1.m_pro2_1_5.m_flag_CESI[DGNB::Pro2_1_5::CESI_NotificationOfNearbyResidentsOnProjectAndSite].set("CESI_NotificationOfNearbyResidentsOnProjectAndSite", true);

	m_process.m_pro2_1.m_pro2_1_5.m_flag_CECR[DGNB::Pro2_1_5::CECR_DetailsOnHowResidentsAreInformedOnAndIncludedInProjectAsideFromSignage].set("CECR_DetailsOnHowResidentsAreInformedOnAndIncludedInProjectAsideFromSignage", true);

	m_process.m_pro2_1.m_pro2_1_5.m_flag_CISI[DGNB::Pro2_1_5::CISI_ParticipantsInProjectProvidedWithAllRelevantInformation].set("CISI_ParticipantsInProjectProvidedWithAllRelevantInformation", true);
	m_process.m_pro2_1.m_pro2_1_5.m_flag_CISI[DGNB::Pro2_1_5::CISI_GuaranteeOfFixedInformationFlowBetweenPlannersAndSite].set("CISI_GuaranteeOfFixedInformationFlowBetweenPlannersAndSite", true);
	m_process.m_pro2_1.m_pro2_1_5.m_flag_CISI[DGNB::Pro2_1_5::CISI_ContinuousCommunicationOfRelevantInformationOnConstructionProgress].set("CISI_ContinuousCommunicationOfRelevantInformationOnConstructionProgress", true);
	m_process.m_pro2_1.m_pro2_1_5.m_flag_CISI[DGNB::Pro2_1_5::CISI_AvailabilityOfCompleteAndUpToDateListsOfProvidersPlannersAndConstructors].set("CISI_AvailabilityOfCompleteAndUpToDateListsOfProvidersPlannersAndConstructors", true);
	m_process.m_pro2_1.m_pro2_1_5.m_flag_CISI[DGNB::Pro2_1_5::CISI_OnlineAvailabilityOfAllInformation].set("CISI_OnlineAvailabilityOfAllInformation", true);

	// Pro2.1.6
	m_process.m_pro2_1.m_pro2_1_6.m_flag_RCWUDT[DGNB::Pro2_1_6::RCWUDT_MeasuringAndDocumentationOfWaterUsageOnConstructionSite].set("RCWUDT_MeasuringAndDocumentationOfWaterUsageOnConstructionSite", true);

	m_process.m_pro2_1.m_pro2_1_6.m_flag_RCWUC[DGNB::Pro2_1_6::RCWUC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts].set("RCWUC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts", true);

	m_process.m_pro2_1.m_pro2_1_6.m_flag_RCWUIO[DGNB::Pro2_1_6::RCWUIO_InstructionOrBriefungOfOperators].set("RCWUIO_InstructionOrBriefungOfOperators", true);

	m_process.m_pro2_1.m_pro2_1_6.m_flag_RCWUEI[DGNB::Pro2_1_6::RCWUEI_ExaminationOrVerificationOfImplementation].set("RCWUEI_ExaminationOrVerificationOfImplementation", true);

	m_process.m_pro2_1.m_pro2_1_6.m_flag_RCEUDT[DGNB::Pro2_1_6::RCEUDT_MeasuringAndDocumentationOfWaterUsageOnConstructionSite].set("RCEUDT_MeasuringAndDocumentationOfWaterUsageOnConstructionSite", true);

	m_process.m_pro2_1.m_pro2_1_6.m_flag_RCEUC[DGNB::Pro2_1_6::RCEUC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts].set("RCEUC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts", true);

	m_process.m_pro2_1.m_pro2_1_6.m_flag_RCEUIO[DGNB::Pro2_1_6::RCEUIO_InstructionOrBriefungOfOperators].set("RCEUIO_InstructionOrBriefungOfOperators", true);

	m_process.m_pro2_1.m_pro2_1_6.m_flag_RCEUEI[DGNB::Pro2_1_6::RCEUEI_ExaminationOrVerificationOfImplementation].set("RCEUEI_ExaminationOrVerificationOfImplementation", true);

	// Pro2.1.7
	m_process.m_pro2_1.m_pro2_1_7.m_flag_MP[DGNB::Pro2_1_7::MP_CreationAndImplementationOfAnAerationProgrammSuitedToConstructionSituationGuaranteeingSufficientDryingOutOfSite].set("MP_CreationAndImplementationOfAnAerationProgrammSuitedToConstructionSituationGuaranteeingSufficientDryingOutOfSite", true);

	// Pro2.3.1
	m_process.m_pro2_3.m_pro2_3_1.m_flag_TMPP[DGNB::Pro2_3_1::TMPP_DesignOfAMonitoringConceptIncludingEnergeticMonitoring].set("TMPP_DesignOfAMonitoringConceptIncludingEnergeticMonitoring", true);
	m_process.m_pro2_3.m_pro2_3_1.m_flag_TMPP[DGNB::Pro2_3_1::TMPP_CertifiedAlternativeSolution].set("TMPP_CertifiedAlternativeSolution", true);

	// Pro2.3.2
	m_process.m_pro2_3.m_pro2_3_2.m_flag_TMCP[DGNB::Pro2_3_2::TMCP_ContinuationOfAMonitoringConcept].set("TMCP_ContinuationOfAMonitoringConcept", true);
	m_process.m_pro2_3.m_pro2_3_2.m_flag_TMCP[DGNB::Pro2_3_2::TMCP_CertifiedAlternativeSolution].set("TMCP_CertifiedAlternativeSolution", true);

	// Pro2.3.3
	m_process.m_pro2_3.m_pro2_3_3.m_flag_TO[DGNB::Pro2_3_3::TO_TrialOperationConductedPriorToApprovalAndHandover].set("TO_TrialOperationConductedPriorToApprovalAndHandover", true);
	m_process.m_pro2_3.m_pro2_3_3.m_flag_TO[DGNB::Pro2_3_3::TO_CertifiedAlternativeSolution].set("TO_CertifiedAlternativeSolution", true);

	// Pro2.3.4
	m_process.m_pro2_3.m_pro2_3_4.m_flag_TMFOP[DGNB::Pro2_3_4::TMFOP_AssignmentOfARegulationMonitoringToOptimiseOperation].set("TMFOP_AssignmentOfARegulationMonitoringToOptimiseOperation", true);
	m_process.m_pro2_3.m_pro2_3_4.m_flag_TMFOP[DGNB::Pro2_3_4::TMFOP_CertifiedAlternativeSolution].set("TMFOP_CertifiedAlternativeSolution", true);

	// Pro2.3.5
	m_process.m_pro2_3.m_pro2_3_5.m_flag_TMCM[DGNB::Pro2_3_5::TMCM_AssignmentOfACompleteTechnicalMonitoring].set("TMCM_AssignmentOfACompleteTechnicalMonitoring", true);

	// Pro2.3.6
	m_process.m_pro2_3.m_pro2_3_6.m_flag_OSUM[DGNB::Pro2_3_6::OSUM_StartUpManagementInAdditionToTechnicalManagement].set("OSUM_StartUpManagementInAdditionToTechnicalManagement", true);

	// Pro2.3.7
	m_process.m_pro2_3.m_pro2_3_7.m_flag_BP[DGNB::Pro2_3_7::BP_AssignmentOfContinuousImprovementProcessAfterHandover].set("BP_AssignmentOfContinuousImprovementProcessAfterHandover", true);

	// Pro2.5.1
	m_process.m_pro2_5.m_pro2_5_1.m_flag_FMC[DGNB::Pro2_5_1::FMC_ConductionWithRegardToAccessibilityOperationRoutingAndAreaUsage].set("FMC_ConductionWithRegardToAccessibilityOperationRoutingAndAreaUsage", true);

	// Pro2.5.2
	m_process.m_pro2_5.m_pro2_5_2.m_flag_MIOSI[DGNB::Pro2_5_2::MIOSI_CreationOfInstructionsAndHandoverToHiredServiceCompaniesOrConductors].set("MIOSI_CreationOfInstructionsAndHandoverToHiredServiceCompaniesOrConductors", true);
	m_process.m_pro2_5.m_pro2_5_2.m_flag_MIOSI[DGNB::Pro2_5_2::MIOSI_CreationOfMaintenanceAndUpkeepPlansForHighCareElementsOfCostGroups300And400].set("MIOSI_CreationOfMaintenanceAndUpkeepPlansForHighCareElementsOfCostGroups300And400", true);
	m_process.m_pro2_5.m_pro2_5_2.m_flag_MIOSI[DGNB::Pro2_5_2::MIOSI_IncorporationOfGuidelinesForSustainableBuildingOperation].set("MIOSI_IncorporationOfGuidelinesForSustainableBuildingOperation", true);

	// Pro2.5.3
	m_process.m_pro2_5.m_pro2_5_3.m_flag_FMG[DGNB::Pro2_5_3::FMG_CreationAndHandoverToFacilityManager].set("FMG_CreationAndHandoverToFacilityManager", true);

	// Pro2.5.4
	m_process.m_pro2_5.m_pro2_5_4.m_flag_CWU[DGNB::Pro2_5_4::CWU_CreationAndHandoverTechnicalOperationHandbook].set("CWU_CreationAndHandoverTechnicalOperationHandbook", true);
	m_process.m_pro2_5.m_pro2_5_4.m_flag_CWU[DGNB::Pro2_5_4::CWU_PreparationAndHandoverOfQuestionaryOnUserSatisfactionDuringOperationPhase].set("CWU_PreparationAndHandoverOfQuestionaryOnUserSatisfactionDuringOperationPhase", true);

	// Pro2.5.5
	m_process.m_pro2_5.m_pro2_5_5.m_flag_SISI[DGNB::Pro2_5_5::SISI_CreationOfConceptIncludingImplementationPlan].set("SISI_CreationOfConceptIncludingImplementationPlan", true);
	m_process.m_pro2_5.m_pro2_5_5.m_flag_SISI[DGNB::Pro2_5_5::SISI_InstallationOfSustainabilityInformationSystem].set("SISI_InstallationOfSustainabilityInformationSystem", true);

	m_process.m_pro2_5.m_pro2_5_5.m_flag_SISA2030NEKI[DGNB::Pro2_5_5::SISA2030NEKI_InfluenceOfNatureExperienceAndKnowledgeImpartationOnOutdoorAreaDesignConcept].set("SISA2030NEKI_InfluenceOfNatureExperienceAndKnowledgeImpartationOnOutdoorAreaDesignConcept", true);
	m_process.m_pro2_5.m_pro2_5_5.m_flag_SISA2030NEKI[DGNB::Pro2_5_5::SISA2030NEKI_AppealingOfferForUsersToExperienceNatureWithAllOrSeveralSenses].set("SISA2030NEKI_AppealingOfferForUsersToExperienceNatureWithAllOrSeveralSenses", true);

	// Pro2.5.6
	m_process.m_pro2_5.m_pro2_5_6.m_flag_OCPE[DGNB::Pro2_5_6::OCPE_CreationOfExtendedOperationCostPrognosis].set("OCPE_CreationOfExtendedOperationCostPrognosis", true);

	/*!
	 * Site
	 */
	// Site1.1.1
	m_site.m_site1_1.m_site1_1_1.m_flag_CRCA[DGNB::Site1_1_1::CRCA_ConductionOfAnalysis].set("CRCA_ConductionOfAnalysis", true);
	m_site.m_site1_1.m_site1_1_1.m_flag_CRCA[DGNB::Site1_1_1::CRCA_ConductionOfQualifiedAnalysisByExperts].set("CRCA_ConductionOfQualifiedAnalysisByExperts", true);

	m_site.m_site1_1.m_site1_1_1.m_flag_CRS[DGNB::Site1_1_1::CRS_AppendixA3TableA].set("CRS_AppendixA3TableA", true);
	m_site.m_site1_1.m_site1_1_1.m_flag_CRS[DGNB::Site1_1_1::CRS_AppendixA3TableB].set("CRS_AppendixA3TableB", true);
	m_site.m_site1_1.m_site1_1_1.m_flag_CRS[DGNB::Site1_1_1::CRS_AdditionallyAppendixA3TableC].set("CRS_AdditionallyAppendixA3TableC", true);

	m_site.m_site1_1.m_site1_1_1.m_flag_CRSEP[DGNB::Site1_1_1::CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheNext10To25Years].set("CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheNext10To25Years", true);
	m_site.m_site1_1.m_site1_1_1.m_flag_CRSEP[DGNB::Site1_1_1::CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheNext26To50Years].set("CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheNext26To50Years", true);
	m_site.m_site1_1.m_site1_1_1.m_flag_CRSEP[DGNB::Site1_1_1::CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheEntireBuildingLifeExpectancy].set("CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheEntireBuildingLifeExpectancy", true);


	m_site.m_site1_1.m_site1_1_1.m_flag_CRAT[DGNB::Site1_1_1::CRAT_EvaluationOfEnvironmentAndClimateHazardProbability].set("CRAT_EvaluationOfEnvironmentAndClimateHazardProbability", true);
	m_site.m_site1_1.m_site1_1_1.m_flag_CRAT[DGNB::Site1_1_1::CRAT_Vulnerability_EvaluationOfImpactOnBuildingOperationUsersAndAssetValue].set("CRAT_Vulnerability_EvaluationOfImpactOnBuildingOperationUsersAndAssetValue", true);

	m_site.m_site1_1.m_site1_1_1.m_flag_CRA2030CPG[DGNB::Site1_1_1::CRA2030CPG_ConsiderationOfSurroundingConditionsAndAdaptationSolutionsOfOthers].set("CRA2030CPG_ConsiderationOfSurroundingConditionsAndAdaptationSolutionsOfOthers", true);

	m_site.m_site1_1.m_site1_1_1.m_flag_CRDB[DGNB::Site1_1_1::CRDB_DamageProbabilityEvaluationBasedOnIPCCAssessmentReportWorstCaseScenarioRCP85].set("CRDB_DamageProbabilityEvaluationBasedOnIPCCAssessmentReportWorstCaseScenarioRCP85", true);
	m_site.m_site1_1.m_site1_1_1.m_flag_CRDB[DGNB::Site1_1_1::CRDB_AdditionallyScenarioRCP6_0].set("CRDB_AdditionallyScenarioRCP6_0", true);
	m_site.m_site1_1.m_site1_1_1.m_flag_CRDB[DGNB::Site1_1_1::CRDB_AdditionallyScenarioRCP4_5].set("CRDB_AdditionallyScenarioRCP4_5", true);
	m_site.m_site1_1.m_site1_1_1.m_flag_CRDB[DGNB::Site1_1_1::CRDB_AdditionallyScenarioRCP2_6].set("CRDB_AdditionallyScenarioRCP2_6", true);

	m_site.m_site1_1.m_site1_1_1.m_flag_CRRA[DGNB::Site1_1_1::CRRA_PhysicalRiskAndVulnerabilityAnalysisConductedPreConstruction].set("CRRA_PhysicalRiskAndVulnerabilityAnalysisConductedPreConstruction", true);

	// Site1.1.2
	m_site.m_site1_1.m_site1_1_2.m_flag_ECRSCFPRECC[DGNB::Site1_1_2::ECRSCFPRECC_DeterminedRisksAndVulnerabilitiesOnSiteExclusivelyMinorToOperationUsersAndAssetValue].set("ECRSCFPRECC_DeterminedRisksAndVulnerabilitiesOnSiteExclusivelyMinorToOperationUsersAndAssetValue", true);

	// Site1.1.3
	m_site.m_site1_1.m_site1_1_3.m_flag_EEISN[DGNB::Site1_1_3::EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan75dB].set("EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan75dB", true);
	m_site.m_site1_1.m_site1_1_3.m_flag_EEISN[DGNB::Site1_1_3::EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan65dB].set("EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan65dB", true);
	m_site.m_site1_1.m_site1_1_3.m_flag_EEISN[DGNB::Site1_1_3::EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan55dB].set("EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan55dB", true);

	m_site.m_site1_1.m_site1_1_3.m_flag_EEIAQ[DGNB::Site1_1_3::EEIAQ_PM10ExceedsLimitOnNoMoreThan35DaysAnnually].set("EEIAQ_PM10ExceedsLimitOnNoMoreThan35DaysAnnually", true);
	m_site.m_site1_1.m_site1_1_3.m_flag_EEIAQ[DGNB::Site1_1_3::EEIAQ_PM10NeverExceedsLimit].set("EEIAQ_PM10NeverExceedsLimit", true);
	m_site.m_site1_1.m_site1_1_3.m_flag_EEIAQ[DGNB::Site1_1_3::EEIAQ_PM2_5NeverExceedsLimit].set("EEIAQ_PM2_5NeverExceedsLimit", true);
	m_site.m_site1_1.m_site1_1_3.m_flag_EEIAQ[DGNB::Site1_1_3::EEIAQ_NO2ExceedsLimitOnNoMoreThan18IntervalsOf3HoursBeyondThe1HourDailyLimitAnnually].set("EEIAQ_NO2ExceedsLimitOnNoMoreThan18IntervalsOf3HoursBeyondThe1HourDailyLimitAnnually", true);
	m_site.m_site1_1.m_site1_1_3.m_flag_EEIAQ[DGNB::Site1_1_3::EEIAQ_NO2NeverExceedsExceedsLimit].set("EEIAQ_NO2NeverExceedsExceedsLimit", true);

	m_site.m_site1_1.m_site1_1_3.m_flag_EEIR[DGNB::Site1_1_3::EEIR_ExaminationIfSiteIsInARadonPreventionZoneBasedOnZonePassOrGovernmentalInformation].set("EEIR_ExaminationIfSiteIsInARadonPreventionZoneBasedOnZonePassOrGovernmentalInformation", true);
	m_site.m_site1_1.m_site1_1_3.m_flag_EEIR[DGNB::Site1_1_3::EEIR_ConclusionThatSiteIsNotInARadonPreventionZoneBasedOnZonePassOrGovernmentalInformation].set("EEIR_ConclusionThatSiteIsNotInARadonPreventionZoneBasedOnZonePassOrGovernmentalInformation", true);
	m_site.m_site1_1.m_site1_1_3.m_flag_EEIR[DGNB::Site1_1_3::EEIR_RadonConcentrationOfCompartmentOrBasementAirMeasured].set("EEIR_RadonConcentrationOfCompartmentOrBasementAirMeasured", true);
	m_site.m_site1_1.m_site1_1_3.m_flag_EEIR[DGNB::Site1_1_3::EEIR_ReferenceValueMeasuredOrExpectedInLessThan75PercentOfAdministrationUnitZoneOrNoMoreThan10PercentOfBuildings].set("EEIR_ReferenceValueMeasuredOrExpectedInLessThan75PercentOfAdministrationUnitZoneOrNoMoreThan10PercentOfBuildings", true);

	// Site1.3.1
	m_site.m_site1_3.m_site1_3_1.m_flag_MITS[DGNB::Site1_3_1::MITS_ConnectionToBundesstrasseA_Road].set("MITS_ConnectionToBundesstrasseA_Road", true);
	m_site.m_site1_3.m_site1_3_1.m_flag_MITS[DGNB::Site1_3_1::MITS_ConnectionToFreeway].set("MITS_ConnectionToFreeway", true);
	m_site.m_site1_3.m_site1_3_1.m_flag_MITS[DGNB::Site1_3_1::MITS_ConnectionToMainStreet].set("MITS_ConnectionToMainStreet", true);

	m_site.m_site1_3.m_site1_3_1.m_flag_MITRB[DGNB::Site1_3_1::MITRB_BuildingParkingSpacesAreIntegratedIntoSuperordinateParkingConceptOfParkingAreasUsedMostlyByUserGroupsOfSeveralBuildingsInTheQuarter].set("MITRB_BuildingParkingSpacesAreIntegratedIntoSuperordinateParkingConceptOfParkingAreasUsedMostlyByUserGroupsOfSeveralBuildingsInTheQuarter", true);

	// Site1.3.2
	m_site.m_site1_3.m_site1_3_2.m_flag_PTS[DGNB::Site1_3_2::PTS_DistancedWithin350Meters].set("PTS_DistancedWithin350Meters", true);

	m_site.m_site1_3.m_site1_3_2.m_flag_PTDTSHD[DGNB::Site1_3_2::PTDTSHD_NoMoreThan20Minutes].set("PTDTSHD_NoMoreThan20Minutes", true);
	m_site.m_site1_3.m_site1_3_2.m_flag_PTDTSHD[DGNB::Site1_3_2::PTDTSHD_NoMoreThan15Minutes].set("PTDTSHD_NoMoreThan15Minutes", true);
	m_site.m_site1_3.m_site1_3_2.m_flag_PTDTSHD[DGNB::Site1_3_2::PTDTSHD_NoMoreThan10Minutes].set("PTDTSHD_NoMoreThan10Minutes", true);

	m_site.m_site1_3.m_site1_3_2.m_flag_PTI[DGNB::Site1_3_2::PTI_NoMoreThan15Minutes].set("PTI_NoMoreThan15Minutes", true);
	m_site.m_site1_3.m_site1_3_2.m_flag_PTI[DGNB::Site1_3_2::PTI_NoMoreThan10Minutes].set("PTI_NoMoreThan10Minutes", true);
	m_site.m_site1_3.m_site1_3_2.m_flag_PTI[DGNB::Site1_3_2::PTI_NoMoreThan5Minutes].set("PTI_NoMoreThan5Minutes", true);

	m_site.m_site1_3.m_site1_3_2.m_flag_PTRB[DGNB::Site1_3_2::PTRB_BuildingBulletinBoardOrSimilarFeaturesNearbyStationSchedulesOrDigitalDisplay].set("PTRB_BuildingBulletinBoardOrSimilarFeaturesNearbyStationSchedulesOrDigitalDisplay", true);
	m_site.m_site1_3.m_site1_3_2.m_flag_PTRB[DGNB::Site1_3_2::PTRB_BuildingBulletinBoardOrSimilarFeaturesPlanOfSurroundingsWithStationsAndDistances].set("PTRB_BuildingBulletinBoardOrSimilarFeaturesPlanOfSurroundingsWithStationsAndDistances", true);
	m_site.m_site1_3.m_site1_3_2.m_flag_PTRB[DGNB::Site1_3_2::PTRB_BuildingFeaturesSignageToStations].set("PTRB_BuildingFeaturesSignageToStations", true);

	// Site1.3.3
	m_site.m_site1_3.m_site1_3_3.m_flag_BTCT500M[DGNB::Site1_3_3::BTCT500M_PartialMixWithMotorTraffic].set("BTCT500M_PartialMixWithMotorTraffic", true);
	m_site.m_site1_3.m_site1_3_3.m_flag_BTCT500M[DGNB::Site1_3_3::BTCT500M_NoMixWithMotorTrafficOrSharedSpaceOrCycleTracks].set("BTCT500M_NoMixWithMotorTrafficOrSharedSpaceOrCycleTracks", true);

	m_site.m_site1_3.m_site1_3_3.m_flag_BTC[DGNB::Site1_3_3::BTC_ContinuousRegionalConnection].set("BTC_ContinuousRegionalConnection", true);
	m_site.m_site1_3.m_site1_3_3.m_flag_BTC[DGNB::Site1_3_3::BTC_ContinuousInterregionalConnectionMoreThan10KM].set("BTC_ContinuousInterregionalConnectionMoreThan10KM", true);

	m_site.m_site1_3.m_site1_3_3.m_flag_BTRB[DGNB::Site1_3_3::BTRB_RoutingOnSiteAllowsRidingUpToBuildingOrBicycleRacks].set("BTRB_RoutingOnSiteAllowsRidingUpToBuildingOrBicycleRacks", true);

	// Site1.3.4
	m_site.m_site1_3.m_site1_3_4.m_flag_FTWN350M[DGNB::Site1_3_4::FTWN350M_50PercentOrMoreCoverage].set("FTWN350M_50PercentOrMoreCoverage", true);
	m_site.m_site1_3.m_site1_3_4.m_flag_FTWN350M[DGNB::Site1_3_4::FTWN350M_80PercentOrMoreCoverage].set("FTWN350M_80PercentOrMoreCoverage", true);
	m_site.m_site1_3.m_site1_3_4.m_flag_FTWN350M[DGNB::Site1_3_4::FTWN350M_100PercentCoverage].set("FTWN350M_100PercentCoverage", true);

	m_site.m_site1_3.m_site1_3_4.m_flag_FTCO350M[DGNB::Site1_3_4::FTCO350M_80PercentOfStreetsAreSafeToCrossAndCrossingsAreSafeToReach].set("FTCO350M_80PercentOfStreetsAreSafeToCrossAndCrossingsAreSafeToReach", true);
	m_site.m_site1_3.m_site1_3_4.m_flag_FTCO350M[DGNB::Site1_3_4::FTCO350M_100PercentOfStreetsAreSafeToCrossAndCrossingsAreSafeToReach].set("FTCO350M_100PercentOfStreetsAreSafeToCrossAndCrossingsAreSafeToReach", true);

	m_site.m_site1_3.m_site1_3_4.m_flag_FTSS[DGNB::Site1_3_4::FTSS_SignageCoversSurroundingArea].set("FTSS_SignageCoversSurroundingArea", true);
	m_site.m_site1_3.m_site1_3_4.m_flag_FTSS[DGNB::Site1_3_4::FTSS_SignageAndOrientationPlansCoverSurroundingArea].set("FTSS_SignageAndOrientationPlansCoverSurroundingArea", true);

	// Site1.3.5
	m_site.m_site1_3.m_site1_3_5.m_flag_ASW350M[DGNB::Site1_3_5::ASW350M_80PercentOfWalkwaysBetweenEntranceAndStationFeatureHeightDifferencesSmallerThan3cmAndMarkedBoardingSpots].set("ASW350M_80PercentOfWalkwaysBetweenEntranceAndStationFeatureHeightDifferencesSmallerThan3cmAndMarkedBoardingSpots", true);
	m_site.m_site1_3.m_site1_3_5.m_flag_ASW350M[DGNB::Site1_3_5::ASW350M_100PercentOfWalkwaysBetweenEntranceAndStationFeatureHeightDifferencesSmallerThan3cmAndMarkedBoardingSpots].set("ASW350M_100PercentOfWalkwaysBetweenEntranceAndStationFeatureHeightDifferencesSmallerThan3cmAndMarkedBoardingSpots", true);

	m_site.m_site1_3.m_site1_3_5.m_flag_ASADRBS[DGNB::Site1_3_5::ASADRBS_TactileGuidingElementsPrivateWalkwayLoweringsAndCrossingsSeparatedFromCycletracksNoSightObstructionOrStairs].set("ASADRBS_TactileGuidingElementsPrivateWalkwayLoweringsAndCrossingsSeparatedFromCycletracksNoSightObstructionOrStairs", true);

	// Site1.3.6
	m_site.m_site1_3.m_site1_3_6.m_flag_A2030UPLI[DGNB::Site1_3_6::A2030UPLI_PublicLoadingInfrastructureForMotorisedIndividualTransportWithin350Meters].set("A2030UPLI_PublicLoadingInfrastructureForMotorisedIndividualTransportWithin350Meters", true);

	// Site1.4.1
	m_site.m_site1_4.m_site1_4_1.m_flag_SIQS[DGNB::Site1_4_1::SIQS_DaycareWithin5MinutesOnFootOrByPublicTransportAndWithin350Meters].set("SIQS_DaycareWithin5MinutesOnFootOrByPublicTransportAndWithin350Meters", true);
	m_site.m_site1_4.m_site1_4_1.m_flag_SIQS[DGNB::Site1_4_1::SIQS_SecondaryOrVocationalSchoolWithin15MinutesOnFootOrByPublicTransportAndWithin1300Meters].set("SIQS_SecondaryOrVocationalSchoolWithin15MinutesOnFootOrByPublicTransportAndWithin1300Meters", true);
	m_site.m_site1_4.m_site1_4_1.m_flag_SIQS[DGNB::Site1_4_1::SIQS_CinemaTheatreOrGalleryWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters].set("SIQS_CinemaTheatreOrGalleryWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters", true);
	m_site.m_site1_4.m_site1_4_1.m_flag_SIQS[DGNB::Site1_4_1::SIQS_BookstoreWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters].set("SIQS_BookstoreWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters", true);
	m_site.m_site1_4.m_site1_4_1.m_flag_SIQS[DGNB::Site1_4_1::SIQS_QuarterCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters].set("SIQS_QuarterCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters", true);
	m_site.m_site1_4.m_site1_4_1.m_flag_SIQS[DGNB::Site1_4_1::SIQS_ParishHallWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters].set("SIQS_ParishHallWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters", true);
	m_site.m_site1_4.m_site1_4_1.m_flag_SIQS[DGNB::Site1_4_1::SIQS_YouthCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters].set("SIQS_YouthCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters", true);
	m_site.m_site1_4.m_site1_4_1.m_flag_SIQS[DGNB::Site1_4_1::SIQS_ElderlyCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters].set("SIQS_ElderlyCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters", true);
	m_site.m_site1_4.m_site1_4_1.m_flag_SIQS[DGNB::Site1_4_1::SIQS_FitnessCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters].set("SIQS_FitnessCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters", true);
	m_site.m_site1_4.m_site1_4_1.m_flag_SIQS[DGNB::Site1_4_1::SIQS_PubliclyAccessibleFitnessProgramInTheBuildingAndOpenToExternalUsers].set("SIQS_PubliclyAccessibleFitnessProgramInTheBuildingAndOpenToExternalUsers", true);
	m_site.m_site1_4.m_site1_4_1.m_flag_SIQS[DGNB::Site1_4_1::SIQS_PlaygroundWithin5MinutesOnFootOrByPublicTransportAndWithin350Meters].set("SIQS_PlaygroundWithin5MinutesOnFootOrByPublicTransportAndWithin350Meters", true);
	m_site.m_site1_4.m_site1_4_1.m_flag_SIQS[DGNB::Site1_4_1::SIQS_GymSportsFieldOrSwimmingPoolWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters].set("SIQS_GymSportsFieldOrSwimmingPoolWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters", true);

	m_site.m_site1_4.m_site1_4_1.m_flag_SIOUIOBS[DGNB::Site1_4_1::SIOUIOBS_ThirdPartiesHaveTheOptionToRentBuildingSpacesTemporarily].set("SIOUIOBS_ThirdPartiesHaveTheOptionToRentBuildingSpacesTemporarily", true);
	m_site.m_site1_4.m_site1_4_1.m_flag_SIOUIOBS[DGNB::Site1_4_1::SIOUIOBS_SC_NeccessaryRoutingAccessibleOutsideOfBusinessHours].set("SIOUIOBS_SC_NeccessaryRoutingAccessibleOutsideOfBusinessHours", true);
	m_site.m_site1_4.m_site1_4_1.m_flag_SIOUIOBS[DGNB::Site1_4_1::SIOUIOBS_OutdoorBuildingSpacesAccessibleToPublicAtAllTimes].set("SIOUIOBS_OutdoorBuildingSpacesAccessibleToPublicAtAllTimes", true);

	// Site1.4.2
	m_site.m_site1_4.m_site1_4_2.m_flag_POEIQS[DGNB::Site1_4_2::POEIQS_LocalAmeneties1_ShoppingCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters].set("POEIQS_LocalAmeneties1_ShoppingCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters", true);
	m_site.m_site1_4.m_site1_4_2.m_flag_POEIQS[DGNB::Site1_4_2::POEIQS_LocalAmeneties2_Retailers_BakeryButcherDrugstoreEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters].set("POEIQS_LocalAmeneties2_Retailers_BakeryButcherDrugstoreEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters", true);
	m_site.m_site1_4.m_site1_4_2.m_flag_POEIQS[DGNB::Site1_4_2::POEIQS_LocalAmeneties3_FarmersMarketWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters].set("POEIQS_LocalAmeneties3_FarmersMarketWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters", true);
	m_site.m_site1_4.m_site1_4_2.m_flag_POEIQS[DGNB::Site1_4_2::POEIQS_Gastronomy_RestaurantCafeBakeryEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters].set("POEIQS_Gastronomy_RestaurantCafeBakeryEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters", true);
	m_site.m_site1_4.m_site1_4_2.m_flag_POEIQS[DGNB::Site1_4_2::POEIQS_OtherServices_BankPostOfficeBarberFitnessCenterWellnessCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters].set("POEIQS_OtherServices_BankPostOfficeBarberFitnessCenterWellnessCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters", true);
	m_site.m_site1_4.m_site1_4_2.m_flag_POEIQS[DGNB::Site1_4_2::POEIQS_Healthcare1_GeneralPractitionerWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters].set("POEIQS_Healthcare1_GeneralPractitionerWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters", true);
	m_site.m_site1_4.m_site1_4_2.m_flag_POEIQS[DGNB::Site1_4_2::POEIQS_Healthcare2_MedicalSpecialistPharmacyEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters].set("POEIQS_Healthcare2_MedicalSpecialistPharmacyEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters", true);

	// Site1.4.3
	m_site.m_site1_4.m_site1_4_3.m_flag_BAIUDIHD[DGNB::Site1_4_3::BAIUDIHD_Daycare].set("BAIUDIHD_Daycare", true);
	m_site.m_site1_4.m_site1_4_3.m_flag_BAIUDIHD[DGNB::Site1_4_3::BAIUDIHD_SecondaryOrVocationalSchool].set("BAIUDIHD_SecondaryOrVocationalSchool", true);
	m_site.m_site1_4.m_site1_4_3.m_flag_BAIUDIHD[DGNB::Site1_4_3::BAIUDIHD_CinemaTheatreOrGallery].set("BAIUDIHD_CinemaTheatreOrGallery", true);
	m_site.m_site1_4.m_site1_4_3.m_flag_BAIUDIHD[DGNB::Site1_4_3::BAIUDIHD_Bookstore].set("BAIUDIHD_Bookstore", true);
	m_site.m_site1_4.m_site1_4_3.m_flag_BAIUDIHD[DGNB::Site1_4_3::BAIUDIHD_QuarterCenter].set("BAIUDIHD_QuarterCenter", true);
	m_site.m_site1_4.m_site1_4_3.m_flag_BAIUDIHD[DGNB::Site1_4_3::BAIUDIHD_ParishHall].set("BAIUDIHD_ParishHall", true);
	m_site.m_site1_4.m_site1_4_3.m_flag_BAIUDIHD[DGNB::Site1_4_3::BAIUDIHD_YouthCenter].set("BAIUDIHD_YouthCenter", true);
	m_site.m_site1_4.m_site1_4_3.m_flag_BAIUDIHD[DGNB::Site1_4_3::BAIUDIHD_ElderlyCenter].set("BAIUDIHD_ElderlyCenter", true);
	m_site.m_site1_4.m_site1_4_3.m_flag_BAIUDIHD[DGNB::Site1_4_3::BAIUDIHD_FitnessCenter].set("BAIUDIHD_FitnessCenter", true);
	m_site.m_site1_4.m_site1_4_3.m_flag_BAIUDIHD[DGNB::Site1_4_3::BAIUDIHD_FitnessProgramOpenToExternalUsers].set("BAIUDIHD_FitnessProgramOpenToExternalUsers", true);
	m_site.m_site1_4.m_site1_4_3.m_flag_BAIUDIHD[DGNB::Site1_4_3::BAIUDIHD_Playground].set("BAIUDIHD_Playground", true);
	m_site.m_site1_4.m_site1_4_3.m_flag_BAIUDIHD[DGNB::Site1_4_3::BAIUDIHD_GymSportsFieldOrSwimmingPool].set("BAIUDIHD_GymSportsFieldOrSwimmingPool", true);
	m_site.m_site1_4.m_site1_4_3.m_flag_BAIUDIHD[DGNB::Site1_4_3::BAIUDIHD_LocalAmeneties1_ShoppingCenter].set("BAIUDIHD_LocalAmeneties1_ShoppingCenter", true);
	m_site.m_site1_4.m_site1_4_3.m_flag_BAIUDIHD[DGNB::Site1_4_3::BAIUDIHD_LocalAmeneties2_Retailers_BakeryButcherDrugstoreEtc].set("BAIUDIHD_LocalAmeneties2_Retailers_BakeryButcherDrugstoreEtc", true);
	m_site.m_site1_4.m_site1_4_3.m_flag_BAIUDIHD[DGNB::Site1_4_3::BAIUDIHD_LocalAmeneties3_FarmersMarket].set("BAIUDIHD_LocalAmeneties3_FarmersMarket", true);
	m_site.m_site1_4.m_site1_4_3.m_flag_BAIUDIHD[DGNB::Site1_4_3::BAIUDIHD_Gastronomy_RestaurantCafeBakeryEtc].set("BAIUDIHD_Gastronomy_RestaurantCafeBakeryEtc", true);
	m_site.m_site1_4.m_site1_4_3.m_flag_BAIUDIHD[DGNB::Site1_4_3::BAIUDIHD_OtherServices_BankPostOfficeBarberFitnessCenterWellnessCenter].set("BAIUDIHD_OtherServices_BankPostOfficeBarberFitnessCenterWellnessCenter", true);
	m_site.m_site1_4.m_site1_4_3.m_flag_BAIUDIHD[DGNB::Site1_4_3::BAIUDIHD_Healthcare1_GeneralPractitioner].set("BAIUDIHD_Healthcare1_GeneralPractitioner", true);
	m_site.m_site1_4.m_site1_4_3.m_flag_BAIUDIHD[DGNB::Site1_4_3::BAIUDIHD_Healthcare2_MedicalSpecialistPharmacyEtc].set("BAIUDIHD_Healthcare2_MedicalSpecialistPharmacyEtc", true);

	m_site.m_site1_4.m_site1_4_3.m_flag_BAIUDCEODNE[DGNB::Site1_4_3::BAIUDCEODNE_UnconventionalOffersPresentedToUsersAndExternals].set("BAIUDCEODNE_UnconventionalOffersPresentedToUsersAndExternals", true);
	m_site.m_site1_4.m_site1_4_3.m_flag_BAIUDCEODNE[DGNB::Site1_4_3::BAIUDCEODNE_ConstructionalImplementationOrPreparationOfOffers].set("BAIUDCEODNE_ConstructionalImplementationOrPreparationOfOffers", true);

	return;
}

void Project::totalProcess() {
	bool read = true;

	if(!read)
		setValuesTest01();

	IBK::Path filename;
#ifdef Q_OS_WIN
	// filename = IBK::Path("T:/git/DGNBApp/data/testDGNB.xml");
	// filename = IBK::Path("T:/git/DGNBApp/data/exDGNB_01_nothing.xml");
	filename = IBK::Path("T:/git/DGNBApp/data/exDGNB_02_mixed.xml");
#elif defined(Q_OS_UNIX)
	//filename = IBK::Path("/home/dirk/git/EconomicEfficiencyCalculation/data/testDGNB.xml");
	filename = IBK::Path("/home/dirk/git/EconomicEfficiencyCalculation/data/exDGNB_02_mixed.xml");
#endif

	if(read) {
		qDebug()<<"Proceeding to read XML...";
		readXML(filename);
	} else {
		qDebug()<<"Proceeding to write XML...";
		writeXML(filename);
	}

	grading();
}

void Project::score() {
	m_environment.score();

}

} // namespace DGNB
