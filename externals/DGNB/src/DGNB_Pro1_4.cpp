#include "DGNB_Pro1_4.h"

#include <QDebug>

#define Macro_VariableToString(Variable) (void(Variable),#Variable)

namespace DGNB {

double DGNB::Pro1_4::score()
{	double scorePro1_4 = 0;

	// summing up points for Pro1.4
	scorePro1_4 += m_pro1_4_1.score();

	// capping total points for Pro1.4 at 100
	scorePro1_4 = std::min<double>(100, scorePro1_4);

	return scorePro1_4;

}

double DGNB::Pro1_4::scoreBonus()
{	double scoreBonusPro1_4 = 0;

	// adding Bonus points from Circular Economy
	scoreBonusPro1_4 += m_pro1_4_1.scoreBonus();

	return scoreBonusPro1_4;

}	// scorePro1.4


}	// namespace DGNB
