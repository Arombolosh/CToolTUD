#include "DGNB_Eco2_7.h"

namespace DGNB {

double Eco2_7::score() {
	double scoreEco2_7 = 0;

	// alternative certification in effect?
	if (m_eco2_7_alt.score() != 0) {
		scoreEco2_7 = m_eco2_7_alt.score();
	} else {
		scoreEco2_7 = m_eco2_7_1.score() + m_eco2_7_2.score() + m_eco2_7_3.score() + m_eco2_7_4.score() + m_eco2_7_5.score();
		scoreEco2_7 = std::min<double>(100, scoreEco2_7);
	}

	return scoreEco2_7;
}

double Eco2_7::scoreBonus() {
	double scoreEco2_7Bonus = m_eco2_7_1.scoreBonus() + m_eco2_7_3.scoreBonus() + m_eco2_7_4.scoreBonus();

	return scoreEco2_7Bonus;
}

} // namespace DGNB
