#include "DGNB_Env2_4.h"

#include <tinyxml.h>
#include <IBK_messages.h>
#include <QDebug>

#define Macro_VariableToString(Variable) (void(Variable),#Variable)

namespace DGNB {

double DGNB::Env2_4::score() {
	double scoreEnv2_4 = 0;
	scoreEnv2_4 += m_env2_4_1.score() + m_env2_4_2.score() + m_env2_4_3.score() + m_env2_4_4.score() + m_env2_4_5.score() + m_env2_4_6.score();

	//capping at 100 pts
	scoreEnv2_4 = std::min<double>(100, scoreEnv2_4);

	//assigning 100 pts for alternative certification, no mentioning of any bonus pts
	if (m_env2_4_alt.score() > 0)
		scoreEnv2_4 = 100;

	return scoreEnv2_4;
}

double DGNB::Env2_4::scoreBonus() {
	double scoreBonusEnv2_4 = 0;

	// assigning bonus pts
	// ToDo DGNB: can bonus points be assigned if the project has received a biodiversity award?
	if (m_env2_4_alt.score() == 0)
		scoreBonusEnv2_4 += m_env2_4_2.scoreBonus() + m_env2_4_3.scoreBonus();

	return scoreBonusEnv2_4;
}	// Env2.4



} // namespace DGNB
