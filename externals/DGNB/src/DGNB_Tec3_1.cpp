#include "DGNB_Tec3_1.h"

namespace DGNB {

double Tec3_1::score() {
	double scoreTec3_1 = m_tec3_1_1.score() + m_tec3_1_2.score() + m_tec3_1_3.score() + m_tec3_1_4.score() + m_tec3_1_5.score();

	scoreTec3_1 = std::min<double>(100, scoreTec3_1);

	return scoreTec3_1;
}

double Tec3_1::scoreBonus() {
	double scoreTec3_1 = 0;

	scoreTec3_1 += m_tec3_1_2.scoreBonus() + m_tec3_1_3.scoreBonus();

	return scoreTec3_1;
}	// Tec3.1

}	// namespace DGNB
