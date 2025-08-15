#include "DGNB_Soc1_6_5.h"

namespace DGNB {
	
double DGNB::Soc1_6_5::score() {
	double soc1_6_5 = 0, soc1_6_5_4 = 0;
	int qsdcoaCounter = 0, qsocasuCounter = 0;

	// assigning points for Soc1.6.5.1
	switch (m_usageType) {
		case Utilities::UT_Healthcare:
			for (unsigned int i = 0; i < NUM_QSDCOA; ++i)
				qsdcoaCounter += (m_flag_QSDCOA[(QS_DesignConceptForOutdoorAreas)i].isEnabled() ? 1 : 0);
			soc1_6_5 += ((qsdcoaCounter > 7) ? 15 : 0);
			break;

		default:
			for (unsigned int i = 0; i < (NUM_QSDCOA-1); ++i)
				qsdcoaCounter += (m_flag_QSDCOA[(QS_DesignConceptForOutdoorAreas)i].isEnabled() ? 1 : 0);
			soc1_6_5 += ((qsdcoaCounter > 6) ? 15 : 0);
			break;
	}

	// assigning points for Soc1.6.5.2
	switch (m_usageType) {
		case Utilities::UT_Healthcare:
				soc1_6_5 += ((m_flag_QSOCA[(QS_OutdoorCommonAreas)0].isEnabled() || m_flag_QSOCA[(QS_OutdoorCommonAreas)1].isEnabled() || (m_flag_QSOCA[(QS_OutdoorCommonAreas)2].isEnabled() && m_flag_QSOCA[(QS_OutdoorCommonAreas)4].isEnabled()) || m_flag_QSOCA[(QS_OutdoorCommonAreas)3].isEnabled()) ? 15 : 0);
			break;

		default:
			soc1_6_5 += ((m_flag_QSOCA[(QS_OutdoorCommonAreas)0].isEnabled() || m_flag_QSOCA[(QS_OutdoorCommonAreas)1].isEnabled() || m_flag_QSOCA[(QS_OutdoorCommonAreas)2].isEnabled() || m_flag_QSOCA[(QS_OutdoorCommonAreas)3].isEnabled()) ? 15 : 0);
			break;
	}

	// assigning points for Soc1.6.5.3
	for (unsigned int i = 0; i < (NUM_QSOCASU-1); ++i)
		qsocasuCounter += (m_flag_QSOCASU[(QS_OutdoorCommonAreasSuitedToUse)i].isEnabled() ? 1 : 0);

	// ToDo DGNB: additional alternative point assignments possible for indicators Soc1.6.5.1 and 2
	qsocasuCounter += (m_flag_QSOCASU[(QS_OutdoorCommonAreasSuitedToUse)8].isEnabled() ? m_para[(P_Soc1_6_5_3AlternativeInnovativeSolutions)].get_value() : 0);

	soc1_6_5 += std::min<double>(25, 5*qsocasuCounter);

	// assigning points for Soc1.6.5.4
	if (m_flag_QSDCOAC[(QS_OutdoorCommonAreaComfort)1].isEnabled()) {
		soc1_6_5_4 += 5;
	} else if (m_flag_QSDCOAC[(QS_OutdoorCommonAreaComfort)0].isEnabled()) {
		soc1_6_5_4 += 2;
	}
	if (m_flag_QSDCOAC[(QS_OutdoorCommonAreaComfort)3].isEnabled()) {
		soc1_6_5_4 += 5;
	} else if (m_flag_QSDCOAC[(QS_OutdoorCommonAreaComfort)2].isEnabled()) {
		soc1_6_5_4 += 2;
	}
	if (m_flag_QSDCOAC[(QS_OutdoorCommonAreaComfort)4].isEnabled()) {
		soc1_6_5_4 += 5;
	}
	if (m_flag_QSDCOAC[(QS_OutdoorCommonAreaComfort)5].isEnabled()) {
		soc1_6_5_4 += m_para[(P_Soc1_6_5_4AlternativeInnovativePoints)].get_value();
	}

	soc1_6_5 += std::min<double>(15, soc1_6_5_4);

	return soc1_6_5;
} // Soc1.6.5

double DGNB::Soc1_6_5::scoreBonus() {
	double soc1_6_5Bonus = 0;

	soc1_6_5Bonus += (m_flag_QSA2030[(QS_Agenda2030ClimateProtectionFactorOfSurfaceStructuresAndClimateProtectionOptimisationOfOutdoorAreas)0].isEnabled() ? 5 : 0);
	soc1_6_5Bonus += (m_flag_QSA2030[(QS_Agenda2030ClimateProtectionFactorOfSurfaceStructuresAndClimateProtectionOptimisationOfOutdoorAreas)1].isEnabled() ? 5 : 0);

	return soc1_6_5Bonus;
}
} // namespace DGNB
