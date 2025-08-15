#include "DGNB_Pro1_1.h"

#include <QDebug>

#define Macro_VariableToString(Variable) (void(Variable),#Variable)

namespace DGNB {


double DGNB::Pro1_1::score()
{	double scorePro1_1 = 0;

	// summing up points for Pro1.1
	scorePro1_1 += m_pro1_1_1.score() + m_pro1_1_3.score();

	// capping total points for Pro1.1 at 100
	scorePro1_1 = std::min<double>(100, scorePro1_1);

	return scorePro1_1;

}

double DGNB::Pro1_1::scoreBonus()
{	double scoreBonusPro1_1 = 0;

	// adding Bonus points from Agenda2030
	scoreBonusPro1_1 += m_pro1_1_1.scoreBonus() + m_pro1_1_2.scoreBonus();

	return scoreBonusPro1_1;

}	// scorePro1.1


}	// namespace DGNB
