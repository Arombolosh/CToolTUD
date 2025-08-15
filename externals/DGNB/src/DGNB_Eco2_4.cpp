#include "DGNB_Eco2_4.h"

namespace DGNB {

double Eco2_4::score() {
	double scoreEco2_4 = m_eco2_4_1.score() + m_eco2_4_2.score() + m_eco2_4_3.score() + m_eco2_4_4.score() + m_eco2_4_5.score();

	scoreEco2_4 = std::min<double>(100, scoreEco2_4);

	return scoreEco2_4;
}

double Eco2_4::scoreBonus() {
	double scoreEco2_4 = m_eco2_4_3.scoreBonus() + m_eco2_4_4.scoreBonus() + m_eco2_4_6.scoreBonus() + m_eco2_4_7.scoreBonus();
	return scoreEco2_4;
}

} // namespace DGNB
