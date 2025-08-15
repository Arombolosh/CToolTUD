#include "DGNB_Tec1_4.h"

namespace DGNB {

double Tec1_4::score() {
	double scoreTec1_4 = m_tec1_4_1.score() + m_tec1_4_2.score() + m_tec1_4_3.score() + m_tec1_4_4.score() + m_tec1_4_5.score();
	scoreTec1_4 = std::min<double>(100, scoreTec1_4);

	return scoreTec1_4;
}

double Tec1_4::scoreBonus() {
	double scoreBonusTec1_4 = 0;

	scoreBonusTec1_4 += m_tec1_4_4.scoreBonus();

	return scoreBonusTec1_4;
}	// Tec1.4

}	// namespace DGNB
