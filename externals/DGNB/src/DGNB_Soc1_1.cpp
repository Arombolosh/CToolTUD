#include "DGNB_Soc1_1.h"

#include <QDebug>

namespace DGNB {


double DGNB::Soc1_1::score()
{	double scoreSoc1_1 = 0;

	// summing up points for Soc1.1
	if (m_soc1_1_alt.score() > 0)
		scoreSoc1_1 += m_soc1_1_alt.score();
	else
		scoreSoc1_1 += m_soc1_1_1.score() + m_soc1_1_2.score() + m_soc1_1_3.score() + m_soc1_1_4.score();

	scoreSoc1_1 += m_soc1_1_6.score();
	// capping total points for Soc1.1 at 100
	scoreSoc1_1 = std::min<double>(100, scoreSoc1_1);

	return scoreSoc1_1;
}

double DGNB::Soc1_1::scoreBonus()
{	double scoreBonusSoc1_1 = 0;

	// adding Bonus points from Agenda2030
	scoreBonusSoc1_1 += m_soc1_1_5.scoreBonus();

	return scoreBonusSoc1_1;
}	// scoreSoc1.1

}	// namespace DGNB
