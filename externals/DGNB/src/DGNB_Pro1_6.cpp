#include "DGNB_Pro1_6.h"

#include <QDebug>

#define Macro_VariableToString(Variable) (void(Variable),#Variable)

namespace DGNB {


double DGNB::Pro1_6::score()
{	double scorePro1_6 = 0;

	// summing up points for Pro1.6
	// Pro1.6.3 offers alternative points for the entire criteria
	if (m_pro1_6_3.score() > 0)
		scorePro1_6 += m_pro1_6_3.score();
	else
		scorePro1_6 += m_pro1_6_1.score() + m_pro1_6_2.score();

	// capping total points for Pro1.6 at 100
	scorePro1_6 = std::min<double>(100, scorePro1_6);

	return scorePro1_6;

} // scorePro1.6


} // namespace DGNB
