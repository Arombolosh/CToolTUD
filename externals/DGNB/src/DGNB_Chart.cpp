#include "DGNB_Chart.h"
#include "ui_DGNB_Chart.h"
#include <sstream>
#include <iomanip>


DGNB_Chart::DGNB_Chart(const std::vector<double> & pointGoals, const std::vector<double> & scores, const std::vector<double> & bonusScores, const std::vector<double> & weighingFactors, const std::vector<bool> & minReq, const std::vector<bool> & platReq, const std::vector<int> & gradings, const double & totalScore, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DGNB_Chart)
{
	ui->setupUi(this);

	// set dark background gradient:
	QLinearGradient gradient(0, 0, 0, 400);
	gradient.setColorAt(0, QColor(90, 90, 90));
	gradient.setColorAt(0.38, QColor(105, 105, 105));
	gradient.setColorAt(1, QColor(70, 70, 70));
	// ui->DGNB_ChartWidget->setBackground(QBrush(gradient));

	QColor black = {QColor(0, 0, 0)};
	QColor failed = {QColor(180, 0, 0)};
	QColor bronze = {QColor(205, 127, 50)};
	QColor silver = {QColor(144, 144, 144)};
	QColor gold = {QColor(196, 180, 84)};
	QColor platinum = {QColor(190, 240, 255)};
	QColor secondary = {QColor(0, 0, 150)};
	QColor bonus = {QColor(100, 240, 100)};

	// prepare x axis with country labels:
	QVector<double> ticks;
	QVector<QString> labels;
	std::vector<double> categoryTicks;
	ticks << 20;
	double tickSpace = 50;
	for (unsigned int i = 0; i < weighingFactors.size(); ++i) {
		tickSpace += weighingFactors[i]/2;
		ticks << tickSpace;
		categoryTicks.push_back(tickSpace);
		tickSpace += 10;
		if (i == 5 || i == 9 || i == 15 || i == 19 || i == 25)
			tickSpace += 10;
	}
	tickSpace += 10;
	std::stringstream stream;
	//labels << "Weighed Project Score" << "ENV1.1" << "ENV1.2" << "ENV1.3" << "ENV2.2" << "ENV2.3" << "ENV2.4" << "ECO1.1" << "ECO2.4" << "ECO2.6" << "ECO2.7" << "SOC1.1" << "SOC1.2" << "SOC1.3" << "SOC1.4" << "SOC1.6" << "SOC2.1" << "TEC1.3" << "TEC1.4" << "TEC1.6" << "TEC3.1" << "PRO1.1" << "PRO1.4" << "PRO1.6" << "PRO2.1" << "PRO2.3" << "PRO2.5" << "SITE1.1" << "SITE1.3" << "SITE1.4";
	std::vector<std::string> criteriaLabels = {"ENV1.1 -- ", "ENV1.2 -- ", "ENV1.3 -- ", "ENV2.2 -- ", "ENV2.3 -- ", "ENV2.4 -- ", "ECO1.1 -- ", "ECO2.4 -- ", "ECO2.6 -- ", "ECO2.7 -- ", "SOC1.1 -- ", "SOC1.2 -- ", "SOC1.3 -- ", "SOC1.4 -- ", "SOC1.6 -- ", "SOC2.1 -- ", "TEC1.3 -- ", "TEC1.4 -- ", "TEC1.6 -- ", "TEC3.1 -- ", "PRO1.1 -- ", "PRO1.4 -- ", "PRO1.6 -- ", "PRO2.1 -- ", "PRO2.3 -- ", "PRO2.5 -- ", "SITE1.1 -- ", "SITE1.3 -- ", "SITE1.4 -- "};
	labels << "Weighed Project Score";
	for (unsigned int i = 0; i < criteriaLabels.size(); ++i) {
		stream.str("");
		stream << std::fixed << std::setprecision(1) << weighingFactors[i];
		std::string factorString = stream.str();
		labels << QString::fromStdString(criteriaLabels[i]) + QString::fromStdString(factorString) + "%";
	}
	// QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);

	textTicker->addTicks(ticks, labels);
	// ui->DGNB_ChartWidget->xAxis->setTicker(textTicker);
	// ui->DGNB_ChartWidget->xAxis->setTickLabelRotation(30);
	// ui->DGNB_ChartWidget->xAxis->setSubTicks(false);
	// ui->DGNB_ChartWidget->xAxis->setTickLength(0, 2);
	// ui->DGNB_ChartWidget->xAxis->setRange(0, tickSpace);
	// ui->DGNB_ChartWidget->xAxis->setBasePen(QPen(Qt::white));
	// ui->DGNB_ChartWidget->xAxis->setTickPen(QPen(Qt::white));
	// ui->DGNB_ChartWidget->xAxis->grid()->setVisible(true);
	// ui->DGNB_ChartWidget->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
	// ui->DGNB_ChartWidget->xAxis->setTickLabelColor(Qt::white);
	// ui->DGNB_ChartWidget->xAxis->setLabelColor(Qt::white);

	// // prepare y axis:
	// ui->DGNB_ChartWidget->yAxis->setRange(0, 240);
	// ui->DGNB_ChartWidget->yAxis->setPadding(5); // a bit more space to the left border
	// ui->DGNB_ChartWidget->yAxis->setLabel("Points");
	// ui->DGNB_ChartWidget->yAxis->setBasePen(QPen(Qt::white));
	// ui->DGNB_ChartWidget->yAxis->setTickPen(QPen(Qt::white));
	// ui->DGNB_ChartWidget->yAxis->setSubTickPen(QPen(Qt::white));
	// ui->DGNB_ChartWidget->yAxis->grid()->setSubGridVisible(true);
	// ui->DGNB_ChartWidget->yAxis->setTickLabelColor(Qt::white);
	// ui->DGNB_ChartWidget->yAxis->setLabelColor(Qt::white);
	// ui->DGNB_ChartWidget->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
	// ui->DGNB_ChartWidget->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

	/*!
	 * Project
	 */
	// create empty bar chart objects:
	// QCPBars *failedProject = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	// QCPBars *bronzeProject = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	// QCPBars *silverProject = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	// QCPBars *goldProject = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	// QCPBars *platinumProject = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	// QCPBars *projectScore = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	// QCPBars *projectScoreSteps = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	projectScore->setAntialiased(false);
	// projectScoreSteps->setAntialiased(false);
	failedProject->setAntialiased(false);
	bronzeProject->setAntialiased(false);
	silverProject->setAntialiased(false);
	goldProject->setAntialiased(false);
	platinumProject->setAntialiased(false);
	// set names and colors:

	failedProject->setPen(QPen(QColor(180, 0, 0, 150)));
	failedProject->setBrush(QColor(180, 0, 0, 150));
	failedProject->setWidth(25);

	// QLinearGradient totalScoreGradient(0, 0, 0, 400);
	// totalScoreGradient.setColorAt(0, QColor(180, 0, 0, 150));
	// totalScoreGradient.setColorAt(0.349, QColor(180, 0, 0, 150));
	// totalScoreGradient.setColorAt(0.35, QColor(205, 127, 50, 150));
	// totalScoreGradient.setColorAt(0.499, QColor(205, 127, 50, 150));
	// totalScoreGradient.setColorAt(0.50, QColor(144, 144, 144, 150));
	// totalScoreGradient.setColorAt(0.649, QColor(144, 144, 144, 150));
	// totalScoreGradient.setColorAt(0.65, QColor(196, 180, 84, 150));
	// totalScoreGradient.setColorAt(0.799, QColor(196, 180, 84, 150));
	// totalScoreGradient.setColorAt(0.80, QColor(190, 240, 255, 150));
	// totalScoreGradient.setColorAt(1, QColor(190, 240, 255, 150));

	// projectScoreSteps->setPen(QPen(black));
	// projectScoreSteps->setBrush((totalScoreGradient));
	// projectScoreSteps->setWidth(25);

	bronzeProject->setPen(QPen(QColor(205, 127, 50, 150)));
	bronzeProject->setBrush(QColor(205, 127, 50, 150));
	bronzeProject->setWidth(25);
	bronzeProject->moveAbove(failedProject);

	silverProject->setPen(QPen(QColor(144, 144, 144, 150)));
	silverProject->setBrush(QColor(144, 144, 144, 150));
	silverProject->setWidth(25);
	silverProject->moveAbove(bronzeProject);

	goldProject->setPen(QPen(QColor(196, 180, 84, 150)));
	goldProject->setBrush(QColor(196, 180, 84, 150));
	goldProject->setWidth(25);
	goldProject->moveAbove(silverProject);

	platinumProject->setPen(QPen(QColor(190, 240, 255, 150)));
	platinumProject->setBrush(QColor(190, 240, 255, 150));
	platinumProject->setWidth(25);
	platinumProject->moveAbove(goldProject);

	projectScore->setPen(QPen(black));
	if (gradings[3] == 0)
		projectScore->setBrush(failed);
	else if (gradings[3] == 4 && platReq[0])
		projectScore->setBrush(platinum);
	else if (gradings[3] >= 3)
		projectScore->setBrush(gold);
	else if (gradings[3] >= 2)
		projectScore->setBrush(silver);
	else if (gradings[3] >= 1)
		projectScore->setBrush(bronze);


	projectScore->setWidth(15);

	// Add Project data:
	QVector<double>  projectScoreData, failedData, bronzeData, silverData, goldData, platinumData, projectTick, projectStepsData;
	projectScoreData << totalScore;
	projectStepsData << 100;
	failedData << 35;
	bronzeData << 15;
	silverData << 15;
	goldData << 15;
	platinumData << 20;
	projectTick << 20;

	failedProject->setData(projectTick, failedData);
	bronzeProject->setData(projectTick, bronzeData);
	silverProject->setData(projectTick, silverData);
	goldProject->setData(projectTick, goldData);
	platinumProject->setData(projectTick, platinumData);

	projectScore->setData(projectTick, projectScoreData);
	// projectScoreSteps->setData(projectTick, projectStepsData);

	/*!
	 * Env1.1
	 */
	// create empty bar chart objects:
	QCPBars *env1_1Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *env1_1Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *env1_1Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	env1_1Goal->setAntialiased(false);
	env1_1Score->setAntialiased(false);
	env1_1Bonus->setAntialiased(false);

	env1_1Score->setStackingGap(0);
	env1_1Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	env1_1Goal->setWidth(weighingFactors[0]+3);
	// set names and colors:
	env1_1Score->setName("Erreichte Bewertung");
	if (minReq[0] == false) {
		env1_1Score->setPen(QPen(failed.lighter(130)));
		env1_1Score->setBrush(failed);
	} else if (gradings[0] == 4 && platReq[0]) {
		env1_1Score->setPen(QPen(platinum.lighter(130)));
		env1_1Score->setBrush(platinum);
	} else if (gradings[0] >= 3) {
		env1_1Score->setPen(QPen(gold.lighter(130)));
		env1_1Score->setBrush(gold);
	} else if (gradings[0] >= 2) {
		env1_1Score->setPen(QPen(silver.lighter(130)));
		env1_1Score->setBrush(silver);
	} else if (gradings[0] >= 1) {
		env1_1Score->setPen(QPen(bronze.lighter(130)));
		env1_1Score->setBrush(bronze);
	}
	env1_1Score->setWidth(weighingFactors[0]);
	env1_1Bonus->setName("Boni");
	env1_1Bonus->setPen(QPen(bonus.lighter(130)));
	env1_1Bonus->setBrush(bonus);
	env1_1Bonus->setWidth(weighingFactors[0]);
	env1_1Bonus->moveAbove(env1_1Score);

	// Add Env1.1 data:
	QVector<double> env1_1GoalData, env1_1SoreData, env1_1BonusData, env1_1tick;
	env1_1GoalData << pointGoals[0];
	env1_1SoreData << scores[0];
	env1_1BonusData << bonusScores[0];
	env1_1tick << categoryTicks[0];
	env1_1Goal->setData(env1_1tick, env1_1GoalData);
	env1_1Score->setData(env1_1tick, env1_1SoreData);
	env1_1Bonus->setData(env1_1tick, env1_1BonusData);

	/*!
	 * Env1.2
	 */
	// create empty bar chart objects:

	std::vector<QCPBars*> test;
	test[0]->setAntialiased(true);

	QCPBars *env1_2Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *env1_2Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *env1_2Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// call function test wird übergeben
	// setze alle werte


	// gives more crisp, pixel aligned bar borders
	env1_2Goal->setAntialiased(false);
	env1_2Score->setAntialiased(false);
	env1_2Bonus->setAntialiased(false);

	env1_2Score->setStackingGap(0);
	env1_2Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	env1_2Goal->setWidth(weighingFactors[1]+3);
	// set names and colors:
	if (minReq[1] == false) {
		env1_2Score->setPen(QPen(failed.lighter(130)));
		env1_2Score->setBrush(failed);
	} else if (gradings[0] == 4 && platReq[1]) {
		env1_2Score->setPen(QPen(platinum.lighter(130)));
		env1_2Score->setBrush(platinum);
	} else if (gradings[0] >= 3) {
		env1_2Score->setPen(QPen(gold.lighter(130)));
		env1_2Score->setBrush(gold);
	} else if (gradings[0] >= 2) {
		env1_2Score->setPen(QPen(silver.lighter(130)));
		env1_2Score->setBrush(silver);
	} else if (gradings[0] >= 1) {
		env1_2Score->setPen(QPen(bronze.lighter(130)));
		env1_2Score->setBrush(bronze);
	}
	env1_2Score->setWidth(weighingFactors[1] );
	env1_2Bonus->setPen(QPen(bonus.lighter(130)));
	env1_2Bonus->setBrush(bonus);
	env1_2Bonus->setWidth(weighingFactors[1]);
	env1_2Bonus->moveAbove(env1_2Score);

	// Add Env1.2 data:
	QVector<double> env1_2GoalData, env1_2SoreData, env1_2BonusData, env1_2tick;
	env1_2GoalData << pointGoals[1];
	env1_2SoreData << scores[1];
	env1_2BonusData << bonusScores[1];
	env1_2tick << categoryTicks[1];
	env1_2Goal->setData(env1_2tick, env1_2GoalData);
	env1_2Score->setData(env1_2tick, env1_2SoreData);
	env1_2Bonus->setData(env1_2tick, env1_2BonusData);

	/*!
	 * Env1.3
	 */
	// create empty bar chart objects:
	QCPBars *env1_3Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *env1_3Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *env1_3Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	env1_3Goal->setAntialiased(false);
	env1_3Score->setAntialiased(false);
	env1_3Bonus->setAntialiased(false);

	env1_3Score->setStackingGap(0);
	env1_3Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	env1_3Goal->setWidth(weighingFactors[2]+3);
	// set names and colors:
	if (minReq[2] == false) {
		env1_3Score->setPen(QPen(failed.lighter(130)));
		env1_3Score->setBrush(failed);
	} else if (gradings[0] >= 4 && platReq[2]) {
		env1_3Score->setPen(QPen(platinum.lighter(130)));
		env1_3Score->setBrush(platinum);
	} else if (gradings[0] >= 3) {
		env1_3Score->setPen(QPen(gold.lighter(130)));
		env1_3Score->setBrush(gold);
	} else if (gradings[0] >= 2) {
		env1_3Score->setPen(QPen(silver.lighter(130)));
		env1_3Score->setBrush(silver);
	} else if (gradings[0] >= 1) {
		env1_3Score->setPen(QPen(bronze.lighter(130)));
		env1_3Score->setBrush(bronze);
	}
	env1_3Score->setWidth(weighingFactors[2]);
	env1_3Bonus->setPen(QPen(bonus.lighter(130)));
	env1_3Bonus->setBrush(bonus);
	env1_3Bonus->setWidth(weighingFactors[2]);
	env1_3Bonus->moveAbove(env1_3Score);

	// Add Env1.3 data:
	QVector<double> env1_3GoalData, env1_3SoreData, env1_3BonusData, env1_3tick;
	env1_3GoalData << pointGoals[2];
	env1_3SoreData << scores[2];
	env1_3BonusData << bonusScores[2];
	env1_3tick << categoryTicks[2];
	env1_3Goal->setData(env1_3tick, env1_3GoalData);
	env1_3Score->setData(env1_3tick, env1_3SoreData);
	env1_3Bonus->setData(env1_3tick, env1_3BonusData);

	/*!
	 * Env2.2
	 */
	// create empty bar chart objects:
	QCPBars *env2_2Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *env2_2Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *env2_2Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	env2_2Goal->setAntialiased(false);
	env2_2Score->setAntialiased(false);
	env2_2Bonus->setAntialiased(false);

	env2_2Score->setStackingGap(0);
	env2_2Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	env2_2Goal->setWidth(weighingFactors[3]+3);
	// set names and colors:
	if (minReq[3] == false) {
		env2_2Score->setPen(QPen(failed.lighter(130)));
		env2_2Score->setBrush(failed);
	} else if (gradings[0] == 4 && platReq[3]) {
		env2_2Score->setPen(QPen(platinum.lighter(130)));
		env2_2Score->setBrush(platinum);
	} else if (gradings[0] >= 3) {
		env2_2Score->setPen(QPen(gold.lighter(130)));
		env2_2Score->setBrush(gold);
	} else if (gradings[0] >= 2) {
		env2_2Score->setPen(QPen(silver.lighter(130)));
		env2_2Score->setBrush(silver);
	} else if (gradings[0] >= 1) {
		env2_2Score->setPen(QPen(bronze.lighter(130)));
		env2_2Score->setBrush(bronze);
	}
	env2_2Score->setWidth(weighingFactors[3]);
	env2_2Bonus->setPen(QPen(bonus.lighter(130)));
	env2_2Bonus->setBrush(bonus);
	env2_2Bonus->setWidth(weighingFactors[3]);
	env2_2Bonus->moveAbove(env2_2Score);

	// Add Env2.2 data:
	QVector<double> env2_2GoalData, env2_2SoreData, env2_2BonusData, env2_2tick;
	env2_2GoalData << pointGoals[3];
	env2_2SoreData << scores[3];
	// ToDo DGNB: capping criterion bonus points?
	double cappedBonus = 0;
	cappedBonus = std::min(100 - scores[3], bonusScores[3]);
	env2_2BonusData << cappedBonus;
	env2_2tick << categoryTicks[3];
	env2_2Goal->setData(env2_2tick, env2_2GoalData);
	env2_2Score->setData(env2_2tick, env2_2SoreData);
	env2_2Bonus->setData(env2_2tick, env2_2BonusData);

	/*!
	 * Env2.3
	 */
	// create empty bar chart objects:
	QCPBars *env2_3Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *env2_3Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *env2_3Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	env2_3Goal->setAntialiased(false);
	env2_3Score->setAntialiased(false);
	env2_3Bonus->setAntialiased(false);

	env2_3Score->setStackingGap(0);
	env2_3Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	env2_3Goal->setWidth(weighingFactors[4]+3);
	// set names and colors:
	if (minReq[4] == false) {
		env2_3Score->setPen(QPen(failed.lighter(130)));
		env2_3Score->setBrush(failed);
	} else if (gradings[0] == 4 && platReq[4]) {
		env2_3Score->setPen(QPen(platinum.lighter(130)));
		env2_3Score->setBrush(platinum);
	} else if (gradings[0] >= 3) {
		env2_3Score->setPen(QPen(gold.lighter(130)));
		env2_3Score->setBrush(gold);
	} else if (gradings[0] >= 2) {
		env2_3Score->setPen(QPen(silver.lighter(130)));
		env2_3Score->setBrush(silver);
	} else if (gradings[0] >= 1) {
		env2_3Score->setPen(QPen(bronze.lighter(130)));
		env2_3Score->setBrush(bronze);
	}
	env2_3Score->setWidth(weighingFactors[4]);
	env2_3Bonus->setPen(QPen(bonus.lighter(130)));
	env2_3Bonus->setBrush(bonus);
	env2_3Bonus->setWidth(weighingFactors[4]);
	env2_3Bonus->moveAbove(env2_3Score);

	// Add Env2.3 data:
	QVector<double> env2_3GoalData, env2_3SoreData, env2_3BonusData, env2_3tick;
	env2_3GoalData << pointGoals[4];
	env2_3SoreData << scores[4];
	// ToDo DGNB: capping Bonus?
	cappedBonus = std::min(110 - scores[4], bonusScores[4]);
	env2_3BonusData << cappedBonus;
	env2_3tick << categoryTicks[4];
	env2_3Goal->setData(env2_3tick, env2_3GoalData);
	env2_3Score->setData(env2_3tick, env2_3SoreData);
	env2_3Bonus->setData(env2_3tick, env2_3BonusData);

	/*!
	 * Env2.4
	 */
	// create empty bar chart objects:
	QCPBars *env2_4Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *env2_4Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *env2_4Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	env2_4Goal->setAntialiased(false);
	env2_4Score->setAntialiased(false);
	env2_4Bonus->setAntialiased(false);

	env2_4Score->setStackingGap(0);
	env2_4Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	env2_4Goal->setWidth(weighingFactors[5]+3);
	// set names and colors:
	if (minReq[5] == false) {
		env2_4Score->setPen(QPen(failed.lighter(130)));
		env2_4Score->setBrush(failed);
	} else if (gradings[0] == 4 && platReq[5]) {
		env2_4Score->setPen(QPen(platinum.lighter(130)));
		env2_4Score->setBrush(platinum);
	} else if (gradings[0] >= 3) {
		env2_4Score->setPen(QPen(gold.lighter(130)));
		env2_4Score->setBrush(gold);
	} else if (gradings[0] >= 2) {
		env2_4Score->setPen(QPen(silver.lighter(130)));
		env2_4Score->setBrush(silver);
	} else if (gradings[0] >= 1) {
		env2_4Score->setPen(QPen(bronze.lighter(130)));
		env2_4Score->setBrush(bronze);
	}
	env2_4Score->setWidth(weighingFactors[5]);
	env2_4Bonus->setPen(QPen(bonus.lighter(130)));
	env2_4Bonus->setBrush(bonus);
	env2_4Bonus->setWidth(weighingFactors[5]);
	env2_4Bonus->moveAbove(env2_4Score);

	// Add Env2.3 data:
	QVector<double> env2_4GoalData, env2_4SoreData, env2_4BonusData, env2_4tick;
	env2_4GoalData << pointGoals[5];
	env2_4SoreData << scores[5];
	env2_4BonusData << bonusScores[5];
	env2_4tick << categoryTicks[5];
	env2_4Goal->setData(env2_4tick, env2_4GoalData);
	env2_4Score->setData(env2_4tick, env2_4SoreData);
	env2_4Bonus->setData(env2_4tick, env2_4BonusData);

	/*!
	 * Eco1.1
	 */
	// create empty bar chart objects:
	QCPBars *eco1_1Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *eco1_1Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *eco1_1Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	eco1_1Goal->setAntialiased(false);
	eco1_1Score->setAntialiased(false);
	eco1_1Bonus->setAntialiased(false);

	eco1_1Score->setStackingGap(0);
	eco1_1Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	eco1_1Goal->setWidth(weighingFactors[6]+3);
	// set names and colors:
	if (minReq[6] == false) {
		eco1_1Score->setPen(QPen(failed.lighter(130)));
		eco1_1Score->setBrush(failed);
	} else if (gradings[1] == 4 && platReq[6]) {
		eco1_1Score->setPen(QPen(platinum.lighter(130)));
		eco1_1Score->setBrush(platinum);
	} else if (gradings[1] >= 3) {
		eco1_1Score->setPen(QPen(gold.lighter(130)));
		eco1_1Score->setBrush(gold);
	} else if (gradings[1] >= 2) {
		eco1_1Score->setPen(QPen(silver.lighter(130)));
		eco1_1Score->setBrush(silver);
	} else if (gradings[1] >= 1) {
		eco1_1Score->setPen(QPen(bronze.lighter(130)));
		eco1_1Score->setBrush(bronze);
	}
	eco1_1Score->setWidth(weighingFactors[6]);
	eco1_1Bonus->setPen(QPen(bonus.lighter(130)));
	eco1_1Bonus->setBrush(bonus);
	eco1_1Bonus->setWidth(weighingFactors[6]);
	eco1_1Bonus->moveAbove(eco1_1Score);

	// Add Eco1.1 data:
	QVector<double> eco1_1GoalData, eco1_1SoreData, eco1_1BonusData, eco1_1tick;
	eco1_1GoalData << pointGoals[6];
	eco1_1SoreData << scores[6];
	eco1_1BonusData << bonusScores[6];
	eco1_1tick << categoryTicks[6];
	eco1_1Goal->setData(eco1_1tick, eco1_1GoalData);
	eco1_1Score->setData(eco1_1tick, eco1_1SoreData);
	eco1_1Bonus->setData(eco1_1tick, eco1_1BonusData);

	/*!
	 * Eco2.4
	 */
	// create empty bar chart objects:
	QCPBars *eco2_4Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *eco2_4Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *eco2_4Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	eco2_4Goal->setAntialiased(false);
	eco2_4Score->setAntialiased(false);
	eco2_4Bonus->setAntialiased(false);

	eco2_4Score->setStackingGap(0);
	eco2_4Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	eco2_4Goal->setWidth(weighingFactors[7]+3);
	// set names and colors:
	if (minReq[7] == false) {
		eco2_4Score->setPen(QPen(failed.lighter(130)));
		eco2_4Score->setBrush(failed);
	} else if (gradings[1] == 4 && platReq[7]) {
		eco2_4Score->setPen(QPen(platinum.lighter(130)));
		eco2_4Score->setBrush(platinum);
	} else if (gradings[1] >= 3) {
		eco2_4Score->setPen(QPen(gold.lighter(130)));
		eco2_4Score->setBrush(gold);
	} else if (gradings[1] >= 2) {
		eco2_4Score->setPen(QPen(silver.lighter(130)));
		eco2_4Score->setBrush(silver);
	} else if (gradings[1] >= 1) {
		eco2_4Score->setPen(QPen(bronze.lighter(130)));
		eco2_4Score->setBrush(bronze);
	}
	eco2_4Score->setWidth(weighingFactors[7]);
	eco2_4Bonus->setPen(QPen(bonus.lighter(130)));
	eco2_4Bonus->setBrush(bonus);
	eco2_4Bonus->setWidth(weighingFactors[7]);
	eco2_4Bonus->moveAbove(eco2_4Score);

	// Add Eco2.4 data:
	QVector<double> eco2_4GoalData, eco2_4SoreData, eco2_4BonusData, eco2_4tick;
	eco2_4GoalData << pointGoals[7];
	eco2_4SoreData << scores[7];
	// ToDo DGNB: capping Bonus?
	cappedBonus = std::min(110 - scores[7], bonusScores[7]);
	eco2_4BonusData << cappedBonus;
	eco2_4tick << categoryTicks[7];
	eco2_4Goal->setData(eco2_4tick, eco2_4GoalData);
	eco2_4Score->setData(eco2_4tick, eco2_4SoreData);
	eco2_4Bonus->setData(eco2_4tick, eco2_4BonusData);

	/*!
	 * Eco2.6
	 */
	// create empty bar chart objects:
	QCPBars *eco2_6Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *eco2_6Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *eco2_6Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	eco2_6Goal->setAntialiased(false);
	eco2_6Score->setAntialiased(false);
	eco2_6Bonus->setAntialiased(false);

	eco2_6Score->setStackingGap(0);
	eco2_6Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	eco2_6Goal->setWidth(weighingFactors[8]+3);
	// set names and colors:
	if (minReq[8] == false) {
		eco2_6Score->setPen(QPen(failed.lighter(130)));
		eco2_6Score->setBrush(failed);
	} else if (gradings[1] == 4 && platReq[8]) {
		eco2_6Score->setPen(QPen(platinum.lighter(130)));
		eco2_6Score->setBrush(platinum);
	} else if (gradings[1] >= 3) {
		eco2_6Score->setPen(QPen(gold.lighter(130)));
		eco2_6Score->setBrush(gold);
	} else if (gradings[1] >= 2) {
		eco2_6Score->setPen(QPen(silver.lighter(130)));
		eco2_6Score->setBrush(silver);
	} else if (gradings[1] >= 1) {
		eco2_6Score->setPen(QPen(bronze.lighter(130)));
		eco2_6Score->setBrush(bronze);
	}
	eco2_6Score->setWidth(weighingFactors[8]);
	eco2_6Bonus->setPen(QPen(bonus.lighter(130)));
	eco2_6Bonus->setBrush(bonus);
	eco2_6Bonus->setWidth(weighingFactors[8]);
	eco2_6Bonus->moveAbove(eco2_6Score);

	// Add Eco2.6 data:
	QVector<double> eco2_6GoalData, eco2_6SoreData, eco2_6BonusData, eco2_6tick;
	eco2_6GoalData << pointGoals[8];
	eco2_6SoreData << scores[8];
	eco2_6BonusData << bonusScores[8];
	eco2_6tick << categoryTicks[8];
	eco2_6Goal->setData(eco2_6tick, eco2_6GoalData);
	eco2_6Score->setData(eco2_6tick, eco2_6SoreData);
	eco2_6Bonus->setData(eco2_6tick, eco2_6BonusData);

	/*!
	 * Eco2.7
	 */
	// create empty bar chart objects:
	QCPBars *eco2_7Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *eco2_7Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *eco2_7Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	eco2_7Goal->setAntialiased(false);
	eco2_7Score->setAntialiased(false);
	eco2_7Bonus->setAntialiased(false);

	eco2_7Score->setStackingGap(0);
	eco2_7Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	eco2_7Goal->setWidth(weighingFactors[9]+3);
	// set names and colors:
	if (minReq[9] == false) {
		eco2_7Score->setPen(QPen(failed.lighter(130)));
		eco2_7Score->setBrush(failed);
	} else if (gradings[1] == 4 && platReq[9]) {
		eco2_7Score->setPen(QPen(platinum.lighter(130)));
		eco2_7Score->setBrush(platinum);
	} else if (gradings[1] >= 3) {
		eco2_7Score->setPen(QPen(gold.lighter(130)));
		eco2_7Score->setBrush(gold);
	} else if (gradings[1] >= 2) {
		eco2_7Score->setPen(QPen(silver.lighter(130)));
		eco2_7Score->setBrush(silver);
	} else if (gradings[1] >= 1) {
		eco2_7Score->setPen(QPen(bronze.lighter(130)));
		eco2_7Score->setBrush(bronze);
	}
	eco2_7Score->setWidth(weighingFactors[9]);
	eco2_7Bonus->setPen(QPen(bonus.lighter(130)));
	eco2_7Bonus->setBrush(bonus);
	eco2_7Bonus->setWidth(weighingFactors[9]);
	eco2_7Bonus->moveAbove(eco2_7Score);

	// Add Eco2.7 data:
	QVector<double> eco2_7GoalData, eco2_7SoreData, eco2_7BonusData, eco2_7tick;
	eco2_7GoalData << pointGoals[9];
	eco2_7SoreData << scores[9];
	eco2_7BonusData << bonusScores[9];
	eco2_7tick << categoryTicks[9];
	eco2_7Goal->setData(eco2_7tick, eco2_7GoalData);
	eco2_7Score->setData(eco2_7tick, eco2_7SoreData);
	eco2_7Bonus->setData(eco2_7tick, eco2_7BonusData);

	/*!
	 * Soc1.1
	 */
	// create empty bar chart objects:
	QCPBars *soc1_1Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *soc1_1Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *soc1_1Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	soc1_1Goal->setAntialiased(false);
	soc1_1Score->setAntialiased(false);
	soc1_1Bonus->setAntialiased(false);

	soc1_1Score->setStackingGap(0);
	soc1_1Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	soc1_1Goal->setWidth(weighingFactors[10]+3);
	// set names and colors:
	if (minReq[10] == false) {
		soc1_1Score->setPen(QPen(failed.lighter(130)));
		soc1_1Score->setBrush(failed);
	} else if (gradings[2] == 4 && platReq[10]) {
		soc1_1Score->setPen(QPen(platinum.lighter(130)));
		soc1_1Score->setBrush(platinum);
	} else if (gradings[2] >= 3) {
		soc1_1Score->setPen(QPen(gold.lighter(130)));
		soc1_1Score->setBrush(gold);
	} else if (gradings[2] >= 2) {
		soc1_1Score->setPen(QPen(silver.lighter(130)));
		soc1_1Score->setBrush(silver);
	} else if (gradings[2] >= 1) {
		soc1_1Score->setPen(QPen(bronze.lighter(130)));
		soc1_1Score->setBrush(bronze);
	}
	soc1_1Score->setWidth(weighingFactors[10]);
	soc1_1Bonus->setPen(QPen(bonus.lighter(130)));
	soc1_1Bonus->setBrush(bonus);
	soc1_1Bonus->setWidth(weighingFactors[10]);
	soc1_1Bonus->moveAbove(soc1_1Score);

	// Add Soc1.1 data:
	QVector<double> soc1_1GoalData, soc1_1SoreData, soc1_1BonusData, soc1_1tick;
	soc1_1GoalData << pointGoals[10];
	soc1_1SoreData << scores[10];
	soc1_1BonusData << bonusScores[10];
	soc1_1tick << categoryTicks[10];
	soc1_1Goal->setData(soc1_1tick, soc1_1GoalData);
	soc1_1Score->setData(soc1_1tick, soc1_1SoreData);
	soc1_1Bonus->setData(soc1_1tick, soc1_1BonusData);

	/*!
	 * Soc1.2
	 */
	// create empty bar chart objects:
	QCPBars *soc1_2Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *soc1_2Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *soc1_2Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	soc1_2Goal->setAntialiased(false);
	soc1_2Score->setAntialiased(false);
	soc1_2Bonus->setAntialiased(false);

	soc1_2Score->setStackingGap(0);
	soc1_2Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	soc1_2Goal->setWidth(weighingFactors[11]+3);
	// set names and colors:
	if (minReq[11] == false) {
		soc1_2Score->setPen(QPen(failed.lighter(130)));
		soc1_2Score->setBrush(failed);
	} else if (gradings[2] == 4 && platReq[11]) {
		soc1_2Score->setPen(QPen(platinum.lighter(130)));
		soc1_2Score->setBrush(platinum);
	} else if (gradings[2] >= 3) {
		soc1_2Score->setPen(QPen(gold.lighter(130)));
		soc1_2Score->setBrush(gold);
	} else if (gradings[2] >= 2) {
		soc1_2Score->setPen(QPen(silver.lighter(130)));
		soc1_2Score->setBrush(silver);
	} else if (gradings[2] >= 1) {
		soc1_2Score->setPen(QPen(bronze.lighter(130)));
		soc1_2Score->setBrush(bronze);
	}
	soc1_2Score->setWidth(weighingFactors[11]);
	soc1_2Bonus->setPen(QPen(bonus.lighter(130)));
	soc1_2Bonus->setBrush(bonus);
	soc1_2Bonus->setWidth(weighingFactors[11]);
	soc1_2Bonus->moveAbove(soc1_2Score);

	// Add Soc1.2 data:
	QVector<double> soc1_2GoalData, soc1_2SoreData, soc1_2BonusData, soc1_2tick;
	soc1_2GoalData << pointGoals[11];
	soc1_2SoreData << scores[11];
	soc1_2BonusData << bonusScores[11];
	soc1_2tick << categoryTicks[11];
	soc1_2Goal->setData(soc1_2tick, soc1_2GoalData);
	soc1_2Score->setData(soc1_2tick, soc1_2SoreData);
	soc1_2Bonus->setData(soc1_2tick, soc1_2BonusData);

	/*!
	 * Soc1.3
	 */
	// create empty bar chart objects:
	QCPBars *soc1_3Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *soc1_3Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *soc1_3Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	soc1_3Goal->setAntialiased(false);
	soc1_3Score->setAntialiased(false);
	soc1_3Bonus->setAntialiased(false);

	soc1_3Score->setStackingGap(0);
	soc1_3Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	soc1_3Goal->setWidth(weighingFactors[12]+3);
	// set names and colors:
	if (minReq[12] == false) {
		soc1_3Score->setPen(QPen(failed.lighter(130)));
		soc1_3Score->setBrush(failed);
	} else if (gradings[2] == 4 && platReq[12]) {
		soc1_3Score->setPen(QPen(platinum.lighter(130)));
		soc1_3Score->setBrush(platinum);
	} else if (gradings[2] >= 3) {
		soc1_3Score->setPen(QPen(gold.lighter(130)));
		soc1_3Score->setBrush(gold);
	} else if (gradings[2] >= 2) {
		soc1_3Score->setPen(QPen(silver.lighter(130)));
		soc1_3Score->setBrush(silver);
	} else if (gradings[2] >= 1) {
		soc1_3Score->setPen(QPen(bronze.lighter(130)));
		soc1_3Score->setBrush(bronze);
	}
	soc1_3Score->setWidth(weighingFactors[12]);
	soc1_3Bonus->setPen(QPen(bonus.lighter(130)));
	soc1_3Bonus->setBrush(bonus);
	soc1_3Bonus->setWidth(weighingFactors[12]);
	soc1_3Bonus->moveAbove(soc1_3Score);

	// Add Soc1.3 data:
	QVector<double> soc1_3GoalData, soc1_3SoreData, soc1_3BonusData, soc1_3tick;
	soc1_3GoalData << pointGoals[12];
	soc1_3SoreData << scores[12];
	soc1_3BonusData << bonusScores[12];
	soc1_3tick << categoryTicks[12];
	soc1_3Goal->setData(soc1_3tick, soc1_3GoalData);
	soc1_3Score->setData(soc1_3tick, soc1_3SoreData);
	soc1_3Bonus->setData(soc1_3tick, soc1_3BonusData);

	/*!
	 * Soc1.4
	 */
	// create empty bar chart objects:
	QCPBars *soc1_4Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *soc1_4Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *soc1_4Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	soc1_4Goal->setAntialiased(false);
	soc1_4Score->setAntialiased(false);
	soc1_4Bonus->setAntialiased(false);

	soc1_4Score->setStackingGap(0);
	soc1_4Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	soc1_4Goal->setWidth(weighingFactors[13]+3);
	// set names and colors:
	if (minReq[13] == false) {
		soc1_4Score->setPen(QPen(failed.lighter(130)));
		soc1_4Score->setBrush(failed);
	} else if (gradings[2] == 4 && platReq[13]) {
		soc1_4Score->setPen(QPen(platinum.lighter(130)));
		soc1_4Score->setBrush(platinum);
	} else if (gradings[2] >= 3) {
		soc1_4Score->setPen(QPen(gold.lighter(130)));
		soc1_4Score->setBrush(gold);
	} else if (gradings[2] >= 2) {
		soc1_4Score->setPen(QPen(silver.lighter(130)));
		soc1_4Score->setBrush(silver);
	} else if (gradings[2] >= 1) {
		soc1_4Score->setPen(QPen(bronze.lighter(130)));
		soc1_4Score->setBrush(bronze);
	}
	soc1_4Score->setWidth(weighingFactors[13]);
	soc1_4Bonus->setPen(QPen(bonus.lighter(130)));
	soc1_4Bonus->setBrush(bonus);
	soc1_4Bonus->setWidth(weighingFactors[13]);
	soc1_4Bonus->moveAbove(soc1_4Score);

	// Add Soc1.4 data:
	QVector<double> soc1_4GoalData, soc1_4SoreData, soc1_4BonusData, soc1_4tick;
	soc1_4GoalData << pointGoals[13];
	soc1_4SoreData << scores[13];
	soc1_4BonusData << bonusScores[13];
	soc1_4tick << categoryTicks[13];
	soc1_4Goal->setData(soc1_4tick, soc1_4GoalData);
	soc1_4Score->setData(soc1_4tick, soc1_4SoreData);
	soc1_4Bonus->setData(soc1_4tick, soc1_4BonusData);

	/*!
	 * Soc1.6
	 */
	// create empty bar chart objects:
	QCPBars *soc1_6Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *soc1_6Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *soc1_6Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	soc1_6Goal->setAntialiased(false);
	soc1_6Score->setAntialiased(false);
	soc1_6Bonus->setAntialiased(false);

	soc1_6Score->setStackingGap(0);
	soc1_6Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	soc1_6Goal->setWidth(weighingFactors[14]+3);
	// set names and colors:
	if (minReq[14] == false) {
		soc1_6Score->setPen(QPen(failed.lighter(130)));
		soc1_6Score->setBrush(failed);
	} else if (gradings[2] == 4 && platReq[14]) {
		soc1_6Score->setPen(QPen(platinum.lighter(130)));
		soc1_6Score->setBrush(platinum);
	} else if (gradings[2] >= 3) {
		soc1_6Score->setPen(QPen(gold.lighter(130)));
		soc1_6Score->setBrush(gold);
	} else if (gradings[2] >= 2) {
		soc1_6Score->setPen(QPen(silver.lighter(130)));
		soc1_6Score->setBrush(silver);
	} else if (gradings[2] >= 1) {
		soc1_6Score->setPen(QPen(bronze.lighter(130)));
		soc1_6Score->setBrush(bronze);
	}
	soc1_6Score->setWidth(weighingFactors[14]);
	soc1_6Bonus->setPen(QPen(bonus.lighter(130)));
	soc1_6Bonus->setBrush(bonus);
	soc1_6Bonus->setWidth(weighingFactors[14]);
	soc1_6Bonus->moveAbove(soc1_6Score);

	// Add Soc1.6 data:
	QVector<double> soc1_6GoalData, soc1_6SoreData, soc1_6BonusData, soc1_6tick;
	soc1_6GoalData << pointGoals[14];
	soc1_6SoreData << scores[14];
	soc1_6BonusData << bonusScores[14];
	soc1_6tick << categoryTicks[14];
	soc1_6Goal->setData(soc1_6tick, soc1_6GoalData);
	soc1_6Score->setData(soc1_6tick, soc1_6SoreData);
	soc1_6Bonus->setData(soc1_6tick, soc1_6BonusData);

	/*!
	 * Soc2.1
	 */
	// create empty bar chart objects:
	QCPBars *soc2_1Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *soc2_1Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *soc2_1Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	soc2_1Goal->setAntialiased(false);
	soc2_1Score->setAntialiased(false);
	soc2_1Bonus->setAntialiased(false);

	soc2_1Score->setStackingGap(0);
	soc2_1Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	soc2_1Goal->setWidth(weighingFactors[15]+3);
	// set names and colors:
	if (minReq[15] == false) {
		soc2_1Score->setPen(QPen(failed.lighter(130)));
		soc2_1Score->setBrush(failed);
	} else if (gradings[2] == 4 && platReq[15]) {
		soc2_1Score->setPen(QPen(platinum.lighter(130)));
		soc2_1Score->setBrush(platinum);
	} else if (gradings[2] >= 3) {
		soc2_1Score->setPen(QPen(gold.lighter(130)));
		soc2_1Score->setBrush(gold);
	} else if (gradings[2] >= 2) {
		soc2_1Score->setPen(QPen(silver.lighter(130)));
		soc2_1Score->setBrush(silver);
	} else if (gradings[2] >= 1) {
		soc2_1Score->setPen(QPen(bronze.lighter(130)));
		soc2_1Score->setBrush(bronze);
	}
	soc2_1Score->setWidth(weighingFactors[15]);
	soc2_1Bonus->setPen(QPen(bonus.lighter(130)));
	soc2_1Bonus->setBrush(bonus);
	soc2_1Bonus->setWidth(weighingFactors[15]);
	soc2_1Bonus->moveAbove(soc2_1Score);

	// Add Soc2.1 data:
	QVector<double> soc2_1GoalData, soc2_1SoreData, soc2_1BonusData, soc2_1tick;
	soc2_1GoalData << pointGoals[15];
	soc2_1SoreData << scores[15];
	soc2_1BonusData << bonusScores[15];
	soc2_1tick << categoryTicks[15];
	soc2_1Goal->setData(soc2_1tick, soc2_1GoalData);
	soc2_1Score->setData(soc2_1tick, soc2_1SoreData);
	soc2_1Bonus->setData(soc2_1tick, soc2_1BonusData);

	/*!
	 * Tec1.3
	 */
	// create empty bar chart objects:
	QCPBars *tec1_3Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *tec1_3Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *tec1_3Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	tec1_3Goal->setAntialiased(false);
	tec1_3Score->setAntialiased(false);
	tec1_3Bonus->setAntialiased(false);

	tec1_3Score->setStackingGap(0);
	tec1_3Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	tec1_3Goal->setWidth(weighingFactors[16]+3);
	// set names and colors:
	if (minReq[16] == false) {
		tec1_3Score->setPen(QPen(failed.lighter(130)));
		tec1_3Score->setBrush(failed);
	} else if (platReq[16]) {
		tec1_3Score->setPen(QPen(platinum.lighter(130)));
		tec1_3Score->setBrush(platinum);
	} else {
		tec1_3Score->setPen(QPen(secondary.lighter(130)));
		tec1_3Score->setBrush(secondary);
	}

	tec1_3Score->setWidth(weighingFactors[16]);
	tec1_3Bonus->setPen(QPen(bonus.lighter(130)));
	tec1_3Bonus->setBrush(bonus);
	tec1_3Bonus->setWidth(weighingFactors[16]);
	tec1_3Bonus->moveAbove(tec1_3Score);

	// Add Tec1.3 data:
	QVector<double> tec1_3GoalData, tec1_3SoreData, tec1_3BonusData, tec1_3tick;
	tec1_3GoalData << pointGoals[16];
	tec1_3SoreData << scores[16];
	tec1_3BonusData << bonusScores[16];
	tec1_3tick << categoryTicks[16];
	tec1_3Goal->setData(tec1_3tick, tec1_3GoalData);
	tec1_3Score->setData(tec1_3tick, tec1_3SoreData);
	tec1_3Bonus->setData(tec1_3tick, tec1_3BonusData);

	/*!
	 * Tec1.4
	 */
	// create empty bar chart objects:
	QCPBars *tec1_4Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *tec1_4Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *tec1_4Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	tec1_4Goal->setAntialiased(false);
	tec1_4Score->setAntialiased(false);
	tec1_4Bonus->setAntialiased(false);

	tec1_4Score->setStackingGap(0);
	tec1_4Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	tec1_4Goal->setWidth(weighingFactors[17]+3);
	// set names and colors:
	if (minReq[17] == false) {
		tec1_4Score->setPen(QPen(failed.lighter(130)));
		tec1_4Score->setBrush(failed);
	} else if (platReq[17]) {
		tec1_4Score->setPen(QPen(platinum.lighter(130)));
		tec1_4Score->setBrush(platinum);
	} else {
		tec1_4Score->setPen(QPen(secondary.lighter(130)));
		tec1_4Score->setBrush(secondary);
	}

	tec1_4Score->setWidth(weighingFactors[17]);
	tec1_4Bonus->setPen(QPen(bonus.lighter(130)));
	tec1_4Bonus->setBrush(bonus);
	tec1_4Bonus->setWidth(weighingFactors[17]);
	tec1_4Bonus->moveAbove(tec1_4Score);

	// Add Tec1.4 data:
	QVector<double> tec1_4GoalData, tec1_4SoreData, tec1_4BonusData, tec1_4tick;
	tec1_4GoalData << pointGoals[17];
	tec1_4SoreData << scores[17];
	tec1_4BonusData << bonusScores[17];
	tec1_4tick << categoryTicks[17];
	tec1_4Goal->setData(tec1_4tick, tec1_4GoalData);
	tec1_4Score->setData(tec1_4tick, tec1_4SoreData);
	tec1_4Bonus->setData(tec1_4tick, tec1_4BonusData);

	/*!
	 * Tec1.6
	 */
	// create empty bar chart objects:
	QCPBars *tec1_6Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *tec1_6Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *tec1_6Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	tec1_6Goal->setAntialiased(false);
	tec1_6Score->setAntialiased(false);
	tec1_6Bonus->setAntialiased(false);

	tec1_6Score->setStackingGap(0);
	tec1_6Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	tec1_6Goal->setWidth(weighingFactors[18]+3);
	// set names and colors:
	if (minReq[18] == false) {
		tec1_6Score->setPen(QPen(failed.lighter(130)));
		tec1_6Score->setBrush(failed);
	} else if (platReq[18]) {
		tec1_6Score->setPen(QPen(platinum.lighter(130)));
		tec1_6Score->setBrush(platinum);
	} else {
		tec1_6Score->setPen(QPen(secondary.lighter(130)));
		tec1_6Score->setBrush(secondary);
	}

	tec1_6Score->setWidth(weighingFactors[18]);
	tec1_6Bonus->setPen(QPen(bonus.lighter(130)));
	tec1_6Bonus->setBrush(bonus);
	tec1_6Bonus->setWidth(weighingFactors[18]);
	tec1_6Bonus->moveAbove(tec1_6Score);

	// Add Tec1.6 data:
	QVector<double> tec1_6GoalData, tec1_6SoreData, tec1_6BonusData, tec1_6tick;
	tec1_6GoalData << pointGoals[18];
	tec1_6SoreData << scores[18];
	tec1_6BonusData << bonusScores[18];
	tec1_6tick << categoryTicks[18];
	tec1_6Goal->setData(tec1_6tick, tec1_6GoalData);
	tec1_6Score->setData(tec1_6tick, tec1_6SoreData);
	tec1_6Bonus->setData(tec1_6tick, tec1_6BonusData);

	/*!
	 * Tec3.1
	 */
	// create empty bar chart objects:
	QCPBars *tec3_1Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *tec3_1Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *tec3_1Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	tec3_1Goal->setAntialiased(false);
	tec3_1Score->setAntialiased(false);
	tec3_1Bonus->setAntialiased(false);

	tec3_1Score->setStackingGap(0);
	tec3_1Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	tec3_1Goal->setWidth(weighingFactors[19]+3);
	// set names and colors:
	if (minReq[19] == false) {
		tec3_1Score->setPen(QPen(failed.lighter(130)));
		tec3_1Score->setBrush(failed);
	} else if (platReq[19]) {
		tec3_1Score->setPen(QPen(platinum.lighter(130)));
		tec3_1Score->setBrush(platinum);
	} else {
		tec3_1Score->setPen(QPen(secondary.lighter(130)));
		tec3_1Score->setBrush(secondary);
	}

	tec3_1Score->setWidth(weighingFactors[19]);
	tec3_1Bonus->setPen(QPen(bonus.lighter(130)));
	tec3_1Bonus->setBrush(bonus);
	tec3_1Bonus->setWidth(weighingFactors[19]);
	tec3_1Bonus->moveAbove(tec3_1Score);

	// Add Tec3.1 data:
	QVector<double> tec3_1GoalData, tec3_1SoreData, tec3_1BonusData, tec3_1tick;
	tec3_1GoalData << pointGoals[19];
	tec3_1SoreData << scores[19];
	tec3_1BonusData << bonusScores[19];
	tec3_1tick << categoryTicks[19];
	tec3_1Goal->setData(tec3_1tick, tec3_1GoalData);
	tec3_1Score->setData(tec3_1tick, tec3_1SoreData);
	tec3_1Bonus->setData(tec3_1tick, tec3_1BonusData);

	/*!
	 * Pro1.1
	 */
	// create empty bar chart objects:
	QCPBars *pro1_1Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *pro1_1Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *pro1_1Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	pro1_1Goal->setAntialiased(false);
	pro1_1Score->setAntialiased(false);
	pro1_1Bonus->setAntialiased(false);

	pro1_1Score->setStackingGap(0);
	pro1_1Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	pro1_1Goal->setWidth(weighingFactors[20]+3);
	// set names and colors:
	if (minReq[20] == false) {
		pro1_1Score->setPen(QPen(failed.lighter(130)));
		pro1_1Score->setBrush(failed);
	} else if (platReq[20]) {
		pro1_1Score->setPen(QPen(platinum.lighter(130)));
		pro1_1Score->setBrush(platinum);
	} else {
		pro1_1Score->setPen(QPen(secondary.lighter(130)));
		pro1_1Score->setBrush(secondary);
	}

	pro1_1Score->setWidth(weighingFactors[20]);
	pro1_1Bonus->setPen(QPen(bonus.lighter(130)));
	pro1_1Bonus->setBrush(bonus);
	pro1_1Bonus->setWidth(weighingFactors[20]);
	pro1_1Bonus->moveAbove(pro1_1Score);

	// Add Pro1.1 data:
	QVector<double> pro1_1GoalData, pro1_1SoreData, pro1_1BonusData, pro1_1tick;
	pro1_1GoalData << pointGoals[20];
	pro1_1SoreData << scores[20];
	pro1_1BonusData << bonusScores[20];
	pro1_1tick << categoryTicks[20];
	pro1_1Goal->setData(pro1_1tick, pro1_1GoalData);
	pro1_1Score->setData(pro1_1tick, pro1_1SoreData);
	pro1_1Bonus->setData(pro1_1tick, pro1_1BonusData);

	/*!
	 * Pro1.4
	 */
	// create empty bar chart objects:
	QCPBars *pro1_4Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *pro1_4Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *pro1_4Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	pro1_4Goal->setAntialiased(false);
	pro1_4Score->setAntialiased(false);
	pro1_4Bonus->setAntialiased(false);

	pro1_4Score->setStackingGap(0);
	pro1_4Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	pro1_4Goal->setWidth(weighingFactors[21]+3);
	// set names and colors:
	if (minReq[21] == false) {
		pro1_4Score->setPen(QPen(failed.lighter(130)));
		pro1_4Score->setBrush(failed);
	} else if (platReq[21]) {
		pro1_4Score->setPen(QPen(platinum.lighter(130)));
		pro1_4Score->setBrush(platinum);
	} else {
		pro1_4Score->setPen(QPen(secondary.lighter(130)));
		pro1_4Score->setBrush(secondary);
	}

	pro1_4Score->setWidth(weighingFactors[21]);
	pro1_4Bonus->setPen(QPen(bonus.lighter(130)));
	pro1_4Bonus->setBrush(bonus);
	pro1_4Bonus->setWidth(weighingFactors[21]);
	pro1_4Bonus->moveAbove(pro1_4Score);

	// Add Pro1.4 data:
	QVector<double> pro1_4GoalData, pro1_4SoreData, pro1_4BonusData, pro1_4tick;
	pro1_4GoalData << pointGoals[21];
	pro1_4SoreData << scores[21];
	pro1_4BonusData << bonusScores[21];
	pro1_4tick << categoryTicks[21];
	pro1_4Goal->setData(pro1_4tick, pro1_4GoalData);
	pro1_4Score->setData(pro1_4tick, pro1_4SoreData);
	pro1_4Bonus->setData(pro1_4tick, pro1_4BonusData);

	/*!
	 * Pro1.6
	 */
	// create empty bar chart objects:
	QCPBars *pro1_6Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *pro1_6Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *pro1_6Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	pro1_6Goal->setAntialiased(false);
	pro1_6Score->setAntialiased(false);
	pro1_6Bonus->setAntialiased(false);

	pro1_6Score->setStackingGap(0);
	pro1_6Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	pro1_6Goal->setWidth(weighingFactors[22]+3);
	// set names and colors:
	if (minReq[22] == false) {
		pro1_6Score->setPen(QPen(failed.lighter(130)));
		pro1_6Score->setBrush(failed);
	} else if (platReq[22]) {
		pro1_6Score->setPen(QPen(platinum.lighter(130)));
		pro1_6Score->setBrush(platinum);
	} else {
		pro1_6Score->setPen(QPen(secondary.lighter(130)));
		pro1_6Score->setBrush(secondary);
	}

	pro1_6Score->setWidth(weighingFactors[22]);
	pro1_6Bonus->setPen(QPen(bonus.lighter(130)));
	pro1_6Bonus->setBrush(bonus);
	pro1_6Bonus->setWidth(weighingFactors[22]);
	pro1_6Bonus->moveAbove(pro1_6Score);

	// Add Pro1.6 data:
	QVector<double> pro1_6GoalData, pro1_6SoreData, pro1_6BonusData, pro1_6tick;
	pro1_6GoalData << pointGoals[22];
	pro1_6SoreData << scores[22];
	pro1_6BonusData << bonusScores[22];
	pro1_6tick << categoryTicks[22];
	pro1_6Goal->setData(pro1_6tick, pro1_6GoalData);
	pro1_6Score->setData(pro1_6tick, pro1_6SoreData);
	pro1_6Bonus->setData(pro1_6tick, pro1_6BonusData);

	/*!
	 * Pro2.1
	 */
	// create empty bar chart objects:
	QCPBars *pro2_1Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *pro2_1Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *pro2_1Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	pro2_1Goal->setAntialiased(false);
	pro2_1Score->setAntialiased(false);
	pro2_1Bonus->setAntialiased(false);

	pro2_1Score->setStackingGap(0);
	pro2_1Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	pro2_1Goal->setWidth(weighingFactors[23]+3);
	// set names and colors:
	if (minReq[23] == false) {
		pro2_1Score->setPen(QPen(failed.lighter(130)));
		pro2_1Score->setBrush(failed);
	} else if (platReq[23]) {
		pro2_1Score->setPen(QPen(platinum.lighter(130)));
		pro2_1Score->setBrush(platinum);
	} else {
		pro2_1Score->setPen(QPen(secondary.lighter(130)));
		pro2_1Score->setBrush(secondary);
	}

	pro2_1Score->setWidth(weighingFactors[23]);
	pro2_1Bonus->setPen(QPen(bonus.lighter(130)));
	pro2_1Bonus->setBrush(bonus);
	pro2_1Bonus->setWidth(weighingFactors[23]);
	pro2_1Bonus->moveAbove(pro2_1Score);

	// Add Pro2.1 data:
	QVector<double> pro2_1GoalData, pro2_1SoreData, pro2_1BonusData, pro2_1tick;
	pro2_1GoalData << pointGoals[23];
	pro2_1SoreData << scores[23];
	pro2_1BonusData << bonusScores[23];
	pro2_1tick << categoryTicks[23];
	pro2_1Goal->setData(pro2_1tick, pro2_1GoalData);
	pro2_1Score->setData(pro2_1tick, pro2_1SoreData);
	pro2_1Bonus->setData(pro2_1tick, pro2_1BonusData);

	/*!
	 * Pro2.3
	 */
	// create empty bar chart objects:
	QCPBars *pro2_3Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *pro2_3Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *pro2_3Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	pro2_3Goal->setAntialiased(false);
	pro2_3Score->setAntialiased(false);
	pro2_3Bonus->setAntialiased(false);

	pro2_3Score->setStackingGap(0);
	pro2_3Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	pro2_3Goal->setWidth(weighingFactors[24]+3);
	// set names and colors:
	if (minReq[24] == false) {
		pro2_3Score->setPen(QPen(failed.lighter(130)));
		pro2_3Score->setBrush(failed);
	} else if (platReq[24]) {
		pro2_3Score->setPen(QPen(platinum.lighter(130)));
		pro2_3Score->setBrush(platinum);
	} else {
		pro2_3Score->setPen(QPen(secondary.lighter(130)));
		pro2_3Score->setBrush(secondary);
	}

	pro2_3Score->setWidth(weighingFactors[24]);
	pro2_3Bonus->setPen(QPen(bonus.lighter(130)));
	pro2_3Bonus->setBrush(bonus);
	pro2_3Bonus->setWidth(weighingFactors[24]);
	pro2_3Bonus->moveAbove(pro2_3Score);

	// Add Pro2.3 data:
	QVector<double> pro2_3GoalData, pro2_3SoreData, pro2_3BonusData, pro2_3tick;
	pro2_3GoalData << pointGoals[24];
	pro2_3SoreData << scores[24];
	pro2_3BonusData << bonusScores[24];
	pro2_3tick << categoryTicks[24];
	pro2_3Goal->setData(pro2_3tick, pro2_3GoalData);
	pro2_3Score->setData(pro2_3tick, pro2_3SoreData);
	pro2_3Bonus->setData(pro2_3tick, pro2_3BonusData);

	/*!
	 * Pro2.5
	 */
	// create empty bar chart objects:
	QCPBars *pro2_5Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *pro2_5Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *pro2_5Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	pro2_5Goal->setAntialiased(false);
	pro2_5Score->setAntialiased(false);
	pro2_5Bonus->setAntialiased(false);

	pro2_5Score->setStackingGap(0);
	pro2_5Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	pro2_5Goal->setWidth(weighingFactors[25]+3);
	// set names and colors:
	if (minReq[25] == false) {
		pro2_5Score->setPen(QPen(failed.lighter(130)));
		pro2_5Score->setBrush(failed);
	} else if (platReq[25]) {
		pro2_5Score->setPen(QPen(platinum.lighter(130)));
		pro2_5Score->setBrush(platinum);
	} else {
		pro2_5Score->setPen(QPen(secondary.lighter(130)));
		pro2_5Score->setBrush(secondary);
	}

	pro2_5Score->setWidth(weighingFactors[25]);
	pro2_5Bonus->setPen(QPen(bonus.lighter(130)));
	pro2_5Bonus->setBrush(bonus);
	pro2_5Bonus->setWidth(weighingFactors[25]);
	pro2_5Bonus->moveAbove(pro2_5Score);

	// Add Pro2.5 data:
	QVector<double> pro2_5GoalData, pro2_5SoreData, pro2_5BonusData, pro2_5tick;
	pro2_5GoalData << pointGoals[25];
	pro2_5SoreData << scores[25];
	pro2_5BonusData << bonusScores[25];
	pro2_5tick << categoryTicks[25];
	pro2_5Goal->setData(pro2_5tick, pro2_5GoalData);
	pro2_5Score->setData(pro2_5tick, pro2_5SoreData);
	pro2_5Bonus->setData(pro2_5tick, pro2_5BonusData);

	/*!
	 * Site1.1
	 */
	// create empty bar chart objects:
	QCPBars *site1_1Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *site1_1Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *site1_1Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	site1_1Goal->setAntialiased(false);
	site1_1Score->setAntialiased(false);
	site1_1Bonus->setAntialiased(false);

	site1_1Score->setStackingGap(0);
	site1_1Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	site1_1Goal->setWidth(weighingFactors[26]+3);
	// set names and colors:
	if (minReq[26] == false) {
		site1_1Score->setPen(QPen(failed.lighter(130)));
		site1_1Score->setBrush(failed);
	} else if (platReq[26]) {
		site1_1Score->setPen(QPen(platinum.lighter(130)));
		site1_1Score->setBrush(platinum);
	} else {
		site1_1Score->setPen(QPen(secondary.lighter(130)));
		site1_1Score->setBrush(secondary);
	}

	site1_1Score->setWidth(weighingFactors[26]);
	site1_1Bonus->setPen(QPen(bonus.lighter(130)));
	site1_1Bonus->setBrush(bonus);
	site1_1Bonus->setWidth(weighingFactors[26]);
	site1_1Bonus->moveAbove(site1_1Score);

	// Add Site1.1 data:
	QVector<double> site1_1GoalData, site1_1SoreData, site1_1BonusData, site1_1tick;
	site1_1GoalData << pointGoals[26];
	site1_1SoreData << scores[26];
	site1_1BonusData << bonusScores[26];
	site1_1tick << categoryTicks[26];
	site1_1Goal->setData(site1_1tick, site1_1GoalData);
	site1_1Score->setData(site1_1tick, site1_1SoreData);
	site1_1Bonus->setData(site1_1tick, site1_1BonusData);

	/*!
	 * Site1.3
	 */
	// create empty bar chart objects:
	QCPBars *site1_3Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *site1_3Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *site1_3Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	site1_3Goal->setAntialiased(false);
	site1_3Score->setAntialiased(false);
	site1_3Bonus->setAntialiased(false);

	site1_3Score->setStackingGap(0);
	site1_3Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	site1_3Goal->setWidth(weighingFactors[27]+3);
	// set names and colors:
	if (minReq[27] == false) {
		site1_3Score->setPen(QPen(failed.lighter(130)));
		site1_3Score->setBrush(failed);
	} else if (platReq[27]) {
		site1_3Score->setPen(QPen(platinum.lighter(130)));
		site1_3Score->setBrush(platinum);
	} else {
		site1_3Score->setPen(QPen(secondary.lighter(130)));
		site1_3Score->setBrush(secondary);
	}

	site1_3Score->setWidth(weighingFactors[27]);
	site1_3Bonus->setPen(QPen(bonus.lighter(130)));
	site1_3Bonus->setBrush(bonus);
	site1_3Bonus->setWidth(weighingFactors[27]);
	site1_3Bonus->moveAbove(site1_3Score);

	// Add Site1.3 data:
	QVector<double> site1_3GoalData, site1_3SoreData, site1_3BonusData, site1_3tick;
	site1_3GoalData << pointGoals[27];
	site1_3SoreData << scores[27];
	site1_3BonusData << bonusScores[27];
	site1_3tick << categoryTicks[27];
	site1_3Goal->setData(site1_3tick, site1_3GoalData);
	site1_3Score->setData(site1_3tick, site1_3SoreData);
	site1_3Bonus->setData(site1_3tick, site1_3BonusData);

	/*!
	 * Site1.4
	 */
	// create empty bar chart objects:
	QCPBars *site1_4Goal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *site1_4Score = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *site1_4Bonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);

	// gives more crisp, pixel aligned bar borders
	site1_4Goal->setAntialiased(false);
	site1_4Score->setAntialiased(false);
	site1_4Bonus->setAntialiased(false);

	site1_4Score->setStackingGap(0);
	site1_4Goal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	// goal->setBrush(QColor(180, 180, 180));
	site1_4Goal->setWidth(weighingFactors[28]+3);
	// set names and colors:
	if (minReq[28] == false) {
		site1_4Score->setPen(QPen(failed.lighter(130)));
		site1_4Score->setBrush(failed);
	} else if (platReq[28]) {
		site1_4Score->setPen(QPen(platinum.lighter(130)));
		site1_4Score->setBrush(platinum);
	} else {
		site1_4Score->setPen(QPen(secondary.lighter(130)));
		site1_4Score->setBrush(secondary);
	}

	site1_4Score->setWidth(weighingFactors[28]);
	site1_4Bonus->setPen(QPen(bonus.lighter(130)));
	site1_4Bonus->setBrush(bonus);
	site1_4Bonus->setWidth(weighingFactors[28]);
	site1_4Bonus->moveAbove(site1_4Score);

	// Add Site1.4 data:
	QVector<double> site1_4GoalData, site1_4SoreData, site1_4BonusData, site1_4tick;
	site1_4GoalData << pointGoals[28];
	site1_4SoreData << scores[28];
	site1_4BonusData << bonusScores[28];
	site1_4tick << categoryTicks[28];
	site1_4Goal->setData(site1_4tick, site1_4GoalData);
	site1_4Score->setData(site1_4tick, site1_4SoreData);
	site1_4Bonus->setData(site1_4tick, site1_4BonusData);





	// setup legend:
	ui->DGNB_ChartWidget->legend->clearItems();
	ui->DGNB_ChartWidget->legend->insertColumn(1);
	ui->DGNB_ChartWidget->legend->setWrap(2);
	ui->DGNB_ChartWidget->legend->setRowSpacing(1);
	ui->DGNB_ChartWidget->legend->setColumnSpacing(2);
	ui->DGNB_ChartWidget->legend->setFillOrder(QCPLayoutGrid::FillOrder::foColumnsFirst,true);

	QCPBars *legendBronze = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *legendBonus = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *legendSilver = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *legendGoal = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *legendGold = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *legendMinReq = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *legendPlatinum = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *legendSecondary = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);
	QCPBars *legendBarWidth = new QCPBars(ui->DGNB_ChartWidget->xAxis, ui->DGNB_ChartWidget->yAxis);


	legendBronze->setPen(QPen(QColor(0, 0, 0)));
	legendBronze->setBrush(bronze);
	legendBronze->setName("Bronze");

	legendBonus->setPen(QPen(QColor(0, 0, 0)));
	legendBonus->setBrush(bonus);
	legendBonus->setName("Bonus Points");

	legendSilver->setPen(QPen(QColor(0, 0, 0)));
	legendSilver->setBrush(silver);
	legendSilver->setName("Silver");

	legendGoal->setPen(QPen(QColor(180, 180, 180).lighter(130)));
	legendGoal->setName("Preset Goals");

	legendGold->setPen(QPen(QColor(0, 0, 0)));
	legendGold->setBrush(gold);
	legendGold->setName("Gold");

	legendMinReq->setPen(QPen(QColor(0, 0, 0)));
	legendMinReq->setBrush(failed);
	legendMinReq->setName("Minimum Requirements not met");

	legendPlatinum->setPen(QPen(QColor(0, 0, 0)));
	legendPlatinum->setBrush(platinum);
	legendPlatinum->setName("Platinum");

	legendSecondary->setPen(QPen(QColor(0, 0, 0)));
	legendSecondary->setBrush(secondary);
	legendSecondary->setName("Secondary Criterion with unmet Platinum Requirement");

	legendBarWidth->setPen(QPen(QColor(255, 255, 255, 0)));
	legendBarWidth->setBrush(QColor(255, 255, 255, 0));
	legendBarWidth->setName("Bar width symbolises individual weighing factor");

	ui->DGNB_ChartWidget->legend->setVisible(true);
	ui->DGNB_ChartWidget->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
	ui->DGNB_ChartWidget->legend->setBrush(QColor(255, 255, 255, 100));
	ui->DGNB_ChartWidget->legend->setBorderPen(Qt::NoPen);
	QFont legendFont = font();
	legendFont.setPointSize(10);
	ui->DGNB_ChartWidget->legend->setFont(legendFont);
	ui->DGNB_ChartWidget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

DGNB_Chart::~DGNB_Chart()
{
	delete ui;
}
