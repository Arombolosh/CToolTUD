#include "DGNB_Soc1_4.h"

#include <QDebug>

#define Macro_VariableToString(Variable) (void(Variable),#Variable)

namespace DGNB {


double DGNB::Soc1_4::score() {
	double scoreSoc1_4 = 0;

	// summing up points for Soc1.4
	scoreSoc1_4 += m_soc1_4_1.score() + m_soc1_4_2.score() + m_soc1_4_3.score() + m_soc1_4_4.score() + m_soc1_4_5.score() + m_soc1_4_6.score();
	

	return scoreSoc1_4;

} // scoreSoc1.4

} // namespace DGNB
