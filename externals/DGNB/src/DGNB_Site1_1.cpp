#include "DGNB_Site1_1.h"

#include <QDebug>

#define Macro_VariableToString(Variable) (void(Variable),#Variable)

namespace DGNB {


double DGNB::Site1_1::score()
{	double scoreSite1_1 = 0;

	scoreSite1_1 += m_site1_1_1.score() + m_site1_1_2.score() + m_site1_1_3.score();

	// capping total points for Site1.1 at 100
	scoreSite1_1 = std::min<double>(100, scoreSite1_1);

	return scoreSite1_1;
}

double DGNB::Site1_1::scoreBonus()
{	double scoreBonusSite1_1 = 0;

	// adding Bonus points from Agenda2030
	scoreBonusSite1_1 += m_site1_1_1.scoreBonus();

	return scoreBonusSite1_1;
}	// scoreSite1.1


}	// namespace DGNB
