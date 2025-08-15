#include "DGNB_Tec1_3.h"

namespace DGNB {

double Tec1_3::score() {
	double scoreTec1_3 = m_tec1_3_1.score() + m_tec1_3_2.score() + m_tec1_3_3.score() + m_tec1_3_4.score() + m_tec1_3_5.score();
	scoreTec1_3 = std::min<double>(100, scoreTec1_3);

	return scoreTec1_3;
}   // Tec1.3

} // namespace DGNB
