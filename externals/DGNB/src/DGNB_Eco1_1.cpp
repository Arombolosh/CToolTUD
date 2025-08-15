#include "DGNB_Eco1_1.h"

namespace DGNB {

double Eco1_1::score() {
	double scoreEco1_1 = m_eco1_1_1.score() + m_eco1_1_2.score() + m_eco1_1_3.score();
	scoreEco1_1 = std::min<double>(100, scoreEco1_1);

	return scoreEco1_1;
}

double Eco1_1::scoreBonus() {
	double scoreBonusEco1_1 = 0;

	scoreBonusEco1_1 += m_eco1_1_2.scoreBonus();

	return scoreBonusEco1_1;
}	// Eco1.1

}	// namespace DGNB
