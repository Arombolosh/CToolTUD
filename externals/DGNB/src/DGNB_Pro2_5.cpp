#include "DGNB_Pro2_5.h"

#include <QDebug>

#define Macro_VariableToString(Variable) (void(Variable),#Variable)

namespace DGNB {

double DGNB::Pro2_5::score()
{	double scorePro2_5 = 0;

	// summing up points for Pro2.5
	scorePro2_5 += m_pro2_5_1.score() + m_pro2_5_2.score() + m_pro2_5_3.score() + m_pro2_5_4.score() + m_pro2_5_5.score() + m_pro2_5_6.score();

	// capping total points for Pro2.5 at 100
	scorePro2_5 = std::min<double>(100, scorePro2_5);

	return scorePro2_5;
}

double DGNB::Pro2_5::scoreBonus()
{	double scoreBonusPro2_5 = 0;

	// adding Bonus points from Agenda2030
	scoreBonusPro2_5 += m_pro2_5_5.scoreBonus();

	return scoreBonusPro2_5;
}	// scorePro2.5


}	// namespace DGNB
