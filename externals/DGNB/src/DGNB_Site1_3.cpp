#include "DGNB_Site1_3.h"

#include <QDebug>

#define Macro_VariableToString(Variable) (void(Variable),#Variable)

namespace DGNB {

double DGNB::Site1_3::score()
{	double scoreSite1_3 = 0;

	scoreSite1_3 += m_site1_3_1.score() + m_site1_3_2.score() + m_site1_3_3.score() + m_site1_3_4.score() + m_site1_3_5.score();

	// capping total points for Site1.3 at 100
	scoreSite1_3 = std::min<double>(100, scoreSite1_3);

	return scoreSite1_3;
}

double DGNB::Site1_3::scoreBonus()
{	double scoreBonusSite1_3 = 0;

	// adding Bonus points from Agenda2030
	scoreBonusSite1_3 += m_site1_3_6.scoreBonus();

	return scoreBonusSite1_3;

}	// scoreSite1.3


} // namespace DGNB
