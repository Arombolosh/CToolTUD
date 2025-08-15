#include "DGNB_Pro2_1.h"

#include <QDebug>

#define Macro_VariableToString(Variable) (void(Variable),#Variable)

namespace DGNB {


double DGNB::Pro2_1::score()
{	double scorePro2_1 = 0;

	// summing up points for Pro2.1
	scorePro2_1 += m_pro2_1_1.score() + m_pro2_1_2.score() + m_pro2_1_3.score() + m_pro2_1_4.score() + m_pro2_1_5.score() + m_pro2_1_6.score() + m_pro2_1_7.score();

	// capping total points for Pro2.1 at 100
	scorePro2_1 = std::min<double>(100, scorePro2_1);

	return scorePro2_1;
}

double DGNB::Pro2_1::scoreBonus()
{	double scoreBonusPro2_1 = 0;

	// adding Bonus points from Agenda2030
	scoreBonusPro2_1 += m_pro2_1_4.scoreBonus();

	return scoreBonusPro2_1;
}	// scorePro2.1


}	// namespace DGNB
