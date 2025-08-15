#include "DGNB_Soc1_3.h"

#include <QDebug>

#define Macro_VariableToString(Variable) (void(Variable),#Variable)

namespace DGNB {


double DGNB::Soc1_3::score() {
	double scoreSoc1_3 = 0;

	// summing up points for Soc1.3
	scoreSoc1_3 += m_soc1_3_1.score() + m_soc1_3_2.score() + m_soc1_3_3.score();
	switch (m_usageType) {
		case Utilities::UT_Residential:
			scoreSoc1_3 = std::min<double>(110, scoreSoc1_3);
			break;

		default:
			scoreSoc1_3 = std::min<double>(100, scoreSoc1_3);
			break;
	}
	return scoreSoc1_3;

}	// scoreSoc1.3

double DGNB::Soc1_3::scoreBonus() {
	double scoreBonusSoc1_3 = 0;
	
	// Bonus will only be assigned if full points were granted for Soc1.3.2 and Soc1.3.3
	switch (m_usageType) {	
		case Utilities::UT_Education:
			if (m_soc1_3_2.score() == 10 && m_soc1_3_3.score() == 60 && m_soc1_3_3.m_flag_RAHHcAEO[(Soc1_3_3::RAHHcAEO_MeasuresTakenAndVerified)].isEnabled())
			scoreBonusSoc1_3 += 10;
			break;
			
		case Utilities::UT_Hotel:
		case Utilities::UT_Assembly:
		case Utilities::UT_Healthcare:
		case Utilities::UT_Office:
			if (m_soc1_3_2.score() == 10 && m_soc1_3_3.score() == 50 && m_soc1_3_3.m_flag_RAHHcAEO[(Soc1_3_3::RAHHcAEO_MeasuresTakenAndVerified)].isEnabled())
			scoreBonusSoc1_3 += 10;
		break;
			
		default: // includes Residential
			scoreBonusSoc1_3 += 0;
			break;
	}

	return scoreBonusSoc1_3;
}	// scoreSoc1.3Bonus

}	// namespace DGNB
