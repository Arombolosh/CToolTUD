#include "DGNB_Pro2_3.h"

#include <QDebug>

#define Macro_VariableToString(Variable) (void(Variable),#Variable)

namespace DGNB {


double DGNB::Pro2_3::score()
{	double scorePro2_3 = 0;

	// summing up points for Pro2.3
	//Pro2.3.5 may replace Pro2.3.1-4
	if (m_pro2_3_5.score() > 0)
		scorePro2_3 += m_pro2_3_5.score() + m_pro2_3_6.score() + m_pro2_3_7.score();
	else scorePro2_3 += m_pro2_3_1.score() + m_pro2_3_2.score() + m_pro2_3_3.score() + m_pro2_3_4.score() + m_pro2_3_6.score() + m_pro2_3_7.score();

	// capping total points for Pro2.3 at 100
	scorePro2_3 = std::min<double>(100, scorePro2_3);


	return scorePro2_3;
} // scorePro2.3


} // namespace DGNB
