#include "DGNB_Site1_4.h"

#include <QDebug>

#define Macro_VariableToString(Variable) (void(Variable),#Variable)

namespace DGNB {

double DGNB::Site1_4::score()
{	double scoreSite1_4 = 0;

	scoreSite1_4 += m_site1_4_1.score() + m_site1_4_2.score() + m_site1_4_3.score();

	// capping total points for Site1.4 at 100
	scoreSite1_4 = std::min<double>(100, scoreSite1_4);

	return scoreSite1_4;
}

double DGNB::Site1_4::scoreBonus()
{	double scoreBonusSite1_4 = 0;

	// adding Bonus points from Agenda2030
	scoreBonusSite1_4 += m_site1_4_3.scoreBonus();

	return scoreBonusSite1_4;
}	// scoreSite1.4


}	// namespace DGNB
