#include "DGNB_Env1_2.h"

#include <tinyxml.h>
#include <IBK_messages.h>
#include <QDebug>

#define Macro_VariableToString(Variable) (void(Variable),#Variable)

namespace DGNB {

double DGNB::Env1_2::score() {
	/*! environment-friendly materials */
	double scoreEnv1_2 = std::min<double>(100, m_env1_2_1.score());

	return scoreEnv1_2;
}  // Env1.2

double DGNB::Env1_2::scoreBonus() {
	/*! environment-friendly materials */
	double scoreBonusEnv1_2 = 0;

	scoreBonusEnv1_2 += m_env1_2_1.scoreBonus();
	return scoreBonusEnv1_2;
}  // Env1.2


} // namespace DGNB
