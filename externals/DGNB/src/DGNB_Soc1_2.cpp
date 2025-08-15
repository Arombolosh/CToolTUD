#include "DGNB_Soc1_2.h"

#include <QDebug>

#define Macro_VariableToString(Variable) (void(Variable),#Variable)

namespace DGNB {

double DGNB::Soc1_2::score()
{	double scoreSoc1_2 = 0;

	// summing up points for Soc1.2
	scoreSoc1_2 += m_soc1_2_1.score();
	scoreSoc1_2 += m_soc1_2_2.score();

	return scoreSoc1_2;
}

double DGNB::Soc1_2::scoreBonus()
{	double scoreBonusSoc1_2 = 0;

	// adding Bonus points from Agenda2030
	scoreBonusSoc1_2 += m_soc1_2_1.scoreBonus();

	return scoreBonusSoc1_2;

}	// scoreSoc1.2


}	// namespace DGNB
