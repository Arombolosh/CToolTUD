#include "DGNB_Env2_3_1.h"

namespace DGNB {

double DGNB::Env2_3_1::score(){
	double env2_3_1 = 0;
	int adDCFlag = 0;

	for(unsigned int i=0; i<NUM_ADDC; ++i)
		adDCFlag = (m_flag_ADDC[(AD_DegreeOfConversion)i].isEnabled() ? i : adDCFlag);

	switch (adDCFlag){
		case 0:			 // case outlying development area
			env2_3_1 += 0;  // assigning 0 points
		break;
		case 1:			 // case internal development area
			env2_3_1 += 40; // assigning 40 points
		break;
		case 2:			 // case development area has been in prior structural or infrastructural use
			env2_3_1 += 70; // assigning 70 points
		break;
	}

	return env2_3_1;
}   // Env2.3.1



} // namespace DGNB
