#ifndef DGNB_ChartH
#define DGNB_ChartH

// #include <qcustomplot.h>
#include <QMainWindow>
#include <QDialog>

namespace Ui {
class DGNB_Chart;
}

class DGNB_Chart : public QDialog
{
	Q_OBJECT

public:
	explicit DGNB_Chart(const std::vector<double> & pointGoals, const std::vector<double> & scores,
						const std::vector<double> & bonusScores, const std::vector<double> & weighingFactors,
						const std::vector<bool> & minReq, const std::vector<bool> & platReq,
						const std::vector<int> & ratings, const double & totalScore, QWidget *parent = nullptr);
	~DGNB_Chart();

private:
	Ui::DGNB_Chart *ui;
};

#endif // DGNB_ChartH
