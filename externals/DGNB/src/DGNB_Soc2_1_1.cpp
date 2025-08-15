#include "DGNB_Soc2_1_1.h"

namespace DGNB {
	
double DGNB::Soc2_1_1::score() {
	double soc2_1_1 = 0;
	bool invalidQSEntered = false;
	int soc2_1_1QualityStage = m_para[(P_Soc2_1_1Qualitystage)].get_value();

	// assigning points for Soc2.1.1 according to QS and usage type
	if (m_flag_AQST[(AQST_ResultsSubmitted)].isEnabled()) {
		switch (m_usageType) {
			case Utilities::UT_Office:
				if (soc2_1_1QualityStage == 6)
					soc2_1_1 += 100;
				else if (soc2_1_1QualityStage == 5)
					soc2_1_1 += 80;
				else if (soc2_1_1QualityStage == 4)
					soc2_1_1 += 55;
				else if (soc2_1_1QualityStage == 3)
					soc2_1_1 += 30;
				else if (soc2_1_1QualityStage == 2)
					soc2_1_1 += 10;
				else if (soc2_1_1QualityStage == 1)
					soc2_1_1 += 0;
				break;

			case Utilities::UT_Education:
				if (soc2_1_1QualityStage == 6)
					soc2_1_1 += 100;
				else if (soc2_1_1QualityStage == 5)
					soc2_1_1 += 75;
				else if (soc2_1_1QualityStage == 4)
					soc2_1_1 += 50;
				else if (soc2_1_1QualityStage == 3)
					soc2_1_1 += 25;
				else if (soc2_1_1QualityStage == 2)
					soc2_1_1 += 10;
				else if (soc2_1_1QualityStage == 1)
					soc2_1_1 += 0;
				break;

			case Utilities::UT_Residential:
				// Student Hostels and Boarding Houses
				if (m_flag_AQST[(AQS_TotalQualityStage)1].isEnabled()) {
					if (soc2_1_1QualityStage == 6)
						soc2_1_1 += 100;
					else if (soc2_1_1QualityStage == 5)
						soc2_1_1 += 100;
					else if (soc2_1_1QualityStage == 4)
						soc2_1_1 += 75;
					else if (soc2_1_1QualityStage == 3)
						soc2_1_1 += 50;
					else if (soc2_1_1QualityStage == 2)
						soc2_1_1 += 10;
					else if (soc2_1_1QualityStage == 1)
						soc2_1_1 += 0;
				} else if (m_flag_AQST[(AQS_TotalQualityStage)2].isEnabled()) {
					if (soc2_1_1QualityStage == 6)
						soc2_1_1 += 100;
					else if (soc2_1_1QualityStage == 5)
						soc2_1_1 += 80;
					else if (soc2_1_1QualityStage == 4)
						soc2_1_1 += 70;
					else if (soc2_1_1QualityStage == 3)
						soc2_1_1 += 60;
					else if (soc2_1_1QualityStage == 2)
						soc2_1_1 += 50;
					else if (soc2_1_1QualityStage == 1)
						soc2_1_1 += 30;
				}
				break;

			case Utilities::UT_Hotel:
				if (soc2_1_1QualityStage == 6)
					soc2_1_1 += 100;
				else if (soc2_1_1QualityStage == 5)
					soc2_1_1 += 75;
				else if (soc2_1_1QualityStage == 4)
					soc2_1_1 += 50;
				else if (soc2_1_1QualityStage == 3)
					soc2_1_1 += 25;
				else if (soc2_1_1QualityStage == 2)
					soc2_1_1 += 10;
				else if (soc2_1_1QualityStage == 1)
					soc2_1_1 += 0;
				break;

			case Utilities::UT_ConvenienceStore:
				if (soc2_1_1QualityStage == 6)
					soc2_1_1 += 100;
				else if (soc2_1_1QualityStage == 5)
					soc2_1_1 += 75;
				else if (soc2_1_1QualityStage == 4)
					soc2_1_1 += 50;
				else if (soc2_1_1QualityStage == 3)
					soc2_1_1 += 25;
				else if (soc2_1_1QualityStage == 2)
					soc2_1_1 += 10;
				else if (soc2_1_1QualityStage == 1)
					soc2_1_1 += 10;
				break;

			case Utilities::UT_ShoppingCenter:
				if (soc2_1_1QualityStage == 6)
					soc2_1_1 += 100;
				else if (soc2_1_1QualityStage == 5)
					soc2_1_1 += 75;
				else if (soc2_1_1QualityStage == 4)
					soc2_1_1 += 50;
				else if (soc2_1_1QualityStage == 3)
					soc2_1_1 += 25;
				else if (soc2_1_1QualityStage == 2)
					soc2_1_1 += 10;
				else if (soc2_1_1QualityStage == 1)
					soc2_1_1 += 0;
				break;

			case Utilities::UT_CommercialBuilding:
				if (soc2_1_1QualityStage == 6)
					soc2_1_1 += 100;
				else if (soc2_1_1QualityStage == 5)
					soc2_1_1 += 75;
				else if (soc2_1_1QualityStage == 4)
					soc2_1_1 += 50;
				else if (soc2_1_1QualityStage == 3)
					soc2_1_1 += 25;
				else if (soc2_1_1QualityStage == 2)
					soc2_1_1 += 10;
				else if (soc2_1_1QualityStage == 1)
					soc2_1_1 += 10;
				break;

			case Utilities::UT_Logistics:
				if (soc2_1_1QualityStage == 6)
					soc2_1_1 += 100;
				else if (soc2_1_1QualityStage == 5)
					soc2_1_1 += 80;
				else if (soc2_1_1QualityStage == 4)
					soc2_1_1 += 55;
				else if (soc2_1_1QualityStage == 3)
					soc2_1_1 += 30;
				else if (soc2_1_1QualityStage == 2)
					soc2_1_1 += 10;
				else if (soc2_1_1QualityStage == 1)
					soc2_1_1 += 0;
				break;

			case Utilities::UT_Production:
				if (soc2_1_1QualityStage == 6)
					soc2_1_1 += 100;
				else if (soc2_1_1QualityStage == 5)
					soc2_1_1 += 80;
				else if (soc2_1_1QualityStage == 4)
					soc2_1_1 += 55;
				else if (soc2_1_1QualityStage == 3)
					soc2_1_1 += 30;
				else if (soc2_1_1QualityStage == 2)
					soc2_1_1 += 10;
				else if (soc2_1_1QualityStage == 1)
					soc2_1_1 += 0;
				break;

			case Utilities::UT_Healthcare:
				if (soc2_1_1QualityStage == 6)
					soc2_1_1 += 100;
				else if (soc2_1_1QualityStage == 5) {
					soc2_1_1 += 0;
					invalidQSEntered = true;
				} else if (soc2_1_1QualityStage == 4) {
					soc2_1_1 += 0;
					invalidQSEntered = true;
				} else if (soc2_1_1QualityStage == 3) {
					soc2_1_1 += 0;
					invalidQSEntered = true;
				} else if (soc2_1_1QualityStage == 2)
					soc2_1_1 += 10;
				else if (soc2_1_1QualityStage == 1)
					soc2_1_1 += 0;
				break;

			case Utilities::UT_Assembly:
				if (soc2_1_1QualityStage == 6)
					soc2_1_1 += 100;
				else if (soc2_1_1QualityStage == 5) {
					soc2_1_1 += 0;
					invalidQSEntered = true;
				} else if (soc2_1_1QualityStage == 4) {
					soc2_1_1 += 0;
					invalidQSEntered =true;
				} else if (soc2_1_1QualityStage == 3) {
					soc2_1_1 += 0;
					invalidQSEntered = true;
				} else if (soc2_1_1QualityStage == 2)
					soc2_1_1 += 50;
				else if (soc2_1_1QualityStage == 1)
					soc2_1_1 += 30;
				break;

			default:
				break;
		}
	}
	if (invalidQSEntered) {
		soc2_1_1 = 0;
		qDebug() << "Quality Stage entered is invalid for selected usage type. No points will be granted.";
	}

	return soc2_1_1;
} // Soc2.1.1

bool DGNB::Soc2_1_1::minimumRequirementsMet() {
	bool minReqMet = false;

	if (m_para[P_Soc2_1_1Qualitystage].get_value() > 0)
		minReqMet = true;

	return minReqMet;
}
} // namespace DGNB
