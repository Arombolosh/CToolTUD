#include "DGNB_Env1_1.h"

#include <QDebug>

#define Macro_VariableToString(Variable) (void(Variable),#Variable)

namespace DGNB {

double DGNB::Env1_1::score()
{	double scoreEnv1_1 = 0;
	// summing up points for Env1.1
	scoreEnv1_1 += m_env1_1_1.score();
	scoreEnv1_1 += m_env1_1_2.score();
	scoreEnv1_1 += m_env1_1_3.score();
	// capping total points for Env1.1 at 100
	scoreEnv1_1 = std::min<double>(100, scoreEnv1_1);

	return scoreEnv1_1;

} // scoreEnv1.1

double DGNB::Env1_1::scoreBonus()
{	double scoreBonusEnv1_1 = 0;
	// adding total Bonus points from Agenda2030
	scoreBonusEnv1_1 += m_env1_1_1.scoreBonus();
	scoreBonusEnv1_1 += m_env1_1_2.scoreBonus();

	return scoreBonusEnv1_1;

} // scoreEnv1.1


} // namespace DGNB
