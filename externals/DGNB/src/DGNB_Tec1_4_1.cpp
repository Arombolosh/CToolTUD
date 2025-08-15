#include "DGNB_Tec1_4_1.h"

namespace DGNB {
	
double DGNB::Tec1_4_1::score() {
	double tec1_4_1 = 0, tec1_4_1_1 = 0, tec1_4_1_2 = 0;

	for (unsigned int i = 0; i<NUM_PSP; ++i)
		tec1_4_1_1 += (m_flag_PSP[(PS_Planning)i].isEnabled() ? 3 : 0);
	
	tec1_4_1_1 = std::min<double>(15, tec1_4_1_1);

	for (unsigned int i = 0; i<NUM_PSI; ++i)
		tec1_4_1_2 += (m_flag_PSI[(PS_Implementation)i].isEnabled() ? 5 : 0);
	
	tec1_4_1_2 = std::min<double>(25, tec1_4_1_2);

	tec1_4_1 += tec1_4_1_1 + tec1_4_1_2;

	return tec1_4_1;
} // Tec1.4.1

} // namespace DGNB
