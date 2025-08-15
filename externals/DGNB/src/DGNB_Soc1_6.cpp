#include "DGNB_Soc1_6.h"

#include <QDebug>

#define Macro_VariableToString(Variable) (void(Variable),#Variable)

namespace DGNB {


double DGNB::Soc1_6::score() {
	double scoreSoc1_6 = 0;

	// summing up points for Env1.1
	scoreSoc1_6 += m_soc1_6_1.score() + m_soc1_6_2.score() + m_soc1_6_3.score() + m_soc1_6_4.score() + m_soc1_6_5.score();
	// capping at 100 pts
	scoreSoc1_6 = std::min<double>(100, scoreSoc1_6);

	return scoreSoc1_6;
}

double DGNB::Soc1_6::scoreBonus() {
	double scoreBonusSoc1_6 = 0;

	// assigning Agenda2030 Bonus
	scoreBonusSoc1_6 += m_soc1_6_5.scoreBonus();

	return scoreBonusSoc1_6;
}	// scoreSoc1.6

}	// namespace DGNB
