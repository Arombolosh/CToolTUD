#include "DGNB_Env2_3.h"

#include <tinyxml.h>
#include <IBK_messages.h>
#include <QDebug>

#define Macro_VariableToString(Variable) (void(Variable),#Variable)

namespace DGNB {

double DGNB::Env2_3::score() {
	double scoreEnv2_3 = m_env2_3_1.score() + m_env2_3_2.score() + m_env2_3_3.score();

	scoreEnv2_3 = std::min<double>(100, scoreEnv2_3);

	return scoreEnv2_3;
}

double DGNB::Env2_3::scoreBonus() {
	double scoreBonusEnv2_3 = 0;
	scoreBonusEnv2_3 += m_env2_3_2.scoreBonus();
	scoreBonusEnv2_3 += m_env2_3_3.scoreBonus();

	return scoreBonusEnv2_3;
}   // Env2.3



} // namespace DGNB
