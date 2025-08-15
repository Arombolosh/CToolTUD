#include "DGNB_Soc2_1.h"

#include <QDebug>

#define Macro_VariableToString(Variable) (void(Variable),#Variable)

namespace DGNB {


double DGNB::Soc2_1::score() {
	double scoreSoc2_1 = 0;

	// summing up points for Env1.1
	scoreSoc2_1 += m_soc2_1_1.score();
	
	return scoreSoc2_1;

} // scoreSoc2.1

} // namespace DGNB
