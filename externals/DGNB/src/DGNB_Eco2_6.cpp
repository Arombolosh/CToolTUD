#include "DGNB_Eco2_6.h"

namespace DGNB {

double Eco2_6::score() {
	double scoreEco2_6 = m_eco2_6_1.score() + m_eco2_6_2.score() + m_eco2_6_3.score();
	scoreEco2_6 = std::min<double>(100, scoreEco2_6);

	return scoreEco2_6;
}

double Eco2_6::scoreBonus() {
	double scoreEco2_6 = m_eco2_6_1.scoreBonus() + m_eco2_6_2.scoreBonus();
	return scoreEco2_6;
}

} // namespace DGNB
