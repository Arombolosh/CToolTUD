#include "DGNB_Env2_2.h"

#include <tinyxml.h>
#include <IBK_messages.h>
#include <QDebug>

#define Macro_VariableToString(Variable) (void(Variable),#Variable)

namespace DGNB {

double DGNB::Env2_2::score(){
	double env2_2 = 0;
	env2_2 += m_env2_2_1.score() + m_env2_2_2.score() + m_env2_2_3.score() + m_env2_2_4.score();
	// capping at 100 pts
	env2_2 = std::min<double>(100, env2_2);

	return env2_2;
}

double DGNB::Env2_2::scoreBonus(){
	double scoreBonusEnv2_2 = 0;
	scoreBonusEnv2_2 += m_env2_2_5.scoreBonus();
	// TODO DGNB Does Agenda2030 REALLY not give any bonus past Env2_2's total of 100 pts?

	return scoreBonusEnv2_2;
}	// Env2.2

} // namespace DGNB
