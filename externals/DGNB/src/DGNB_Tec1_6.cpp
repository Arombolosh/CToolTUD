#include "DGNB_Tec1_6.h"

namespace DGNB {

double Tec1_6::score() {
	double scoreTec1_6 = m_tec1_6_1.score() + m_tec1_6_2.score() + m_tec1_6_3.score();
	scoreTec1_6 = std::min<double>(100, scoreTec1_6);

	return scoreTec1_6;
}

double Tec1_6::scoreBonus() {
	double scoreBonusTec1_6 = 0;

	scoreBonusTec1_6 += m_tec1_6_1.scoreBonus() + m_tec1_6_3.scoreBonus();

	return scoreBonusTec1_6;
}	// Tec1.6

} // namespace DGNB
