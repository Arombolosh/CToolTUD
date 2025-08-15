#include "DGNB_Env1_3.h"

#include <tinyxml.h>
#include <IBK_messages.h>
#include <QDebug>

#define Macro_VariableToString(Variable) (void(Variable),#Variable)

namespace DGNB {

double DGNB::Env1_3::score() {
	/*! responsible winning of resources */
	double scoreEnv1_3 = 0;
	if (m_env1_3_2.minimumRequirementsMet()) {
		scoreEnv1_3 += m_env1_3_1.score() + m_env1_3_2.score();
		scoreEnv1_3 = std::min<double>(100, scoreEnv1_3);
	}

	return scoreEnv1_3;
}



} // namespace DGNB
