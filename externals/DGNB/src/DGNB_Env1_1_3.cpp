#include "DGNB_Env1_1_3.h"

namespace DGNB {

double DGNB::Env1_1_3::score() {
	double env1_1_3 = 0, env1_1_3_1_2 = 0;

	double refEnv1_1_3_1_1 = m_para[(P_RefEnv1_1_3_1_1)].get_value(), currentEnv1_1_3_1_1 = m_para[(P_CurrentValueEnv1_1_3_1_1)].get_value();
	double refEnv1_1_3_1_2POCP = m_para[(P_RefEnv1_1_3_1_2POCP)].get_value(), currentEnv1_1_3_1_2POCP = m_para[(P_CurrentValueEnv1_1_3_1_2POCP)].get_value();
	double refEnv1_1_3_1_1AP = m_para[(P_RefEnv1_1_3_1_2AP)].get_value(), currentEnv1_1_3_1_2AP = m_para[(P_CurrentValueEnv1_1_3_1_2AP)].get_value();
	double refEnv1_1_3_1_1EP = m_para[(P_RefEnv1_1_3_1_2EP)].get_value(), currentEnv1_1_3_1_2EP = m_para[(P_CurrentValueEnv1_1_3_1_2EP)].get_value();
	double refEnv1_1_3_1_1FW = m_para[(P_RefEnv1_1_3_1_2FW)].get_value(), currentEnv1_1_3_1_2FW = m_para[(P_CurrentValueEnv1_1_3_1_2FW)].get_value();

	/*! Comparative values of additional ecological indicators:  evaluation of additional ecological indicators */
	// ENV1.1.3.1.1
	if (m_flag_CVAEILCPEB[(CVAEILCPEB_ResultsSubmitted)].isEnabled()) {
		/*! results of life cycle primary energy balance (non-renewable) fall below target value, reference value, threshold value */
		std::vector<double> xVal_3_1_1{0.5*refEnv1_1_3_1_1, 0.75*refEnv1_1_3_1_1, refEnv1_1_3_1_1, 2.25*refEnv1_1_3_1_1};
		std::vector<double> yVal_3_1_1{10, 7.5, 5, 0};

		IBK::LinearSpline ls_3_1_1;
		ls_3_1_1.setValues(xVal_3_1_1, yVal_3_1_1);
		env1_1_3 += ls_3_1_1.value((currentEnv1_1_3_1_1));
	}

	// ENV1.1.3.1.2
	/*! weighted results of additional environmental indicators fall below target value, reference value, threshold value */

	if (m_flag_CVAEIWRAEI[(CVAEIWRAEI_ResultsSubmitted)].isEnabled()) {
		std::vector<double> xVal_3_1_2POCP{0.5*refEnv1_1_3_1_2POCP, 0.75*refEnv1_1_3_1_2POCP, refEnv1_1_3_1_2POCP, 2.25*refEnv1_1_3_1_2POCP};
		std::vector<double> xVal_3_1_2AP{0.5*refEnv1_1_3_1_1AP, 0.75*refEnv1_1_3_1_1AP, refEnv1_1_3_1_1AP, 2.25*refEnv1_1_3_1_1AP};
		std::vector<double> xVal_3_1_2EP{0.5*refEnv1_1_3_1_1EP, 0.75*refEnv1_1_3_1_1EP, refEnv1_1_3_1_1EP, 2.25*refEnv1_1_3_1_1EP};
		std::vector<double> xVal_3_1_2FW{0.5*refEnv1_1_3_1_1FW, 0.75*refEnv1_1_3_1_1FW, refEnv1_1_3_1_1FW, 2.25*refEnv1_1_3_1_1FW};
		std::vector<double> yVal_3_1_2{10, 7.5, 5, 0};

		IBK::LinearSpline ls_3_1_2;
		ls_3_1_2.setValues(xVal_3_1_2POCP, yVal_3_1_2);
		env1_1_3_1_2 += ls_3_1_2.value((currentEnv1_1_3_1_2POCP));
		ls_3_1_2.setValues(xVal_3_1_2AP, yVal_3_1_2);
		env1_1_3_1_2 += ls_3_1_2.value((currentEnv1_1_3_1_2AP));
		ls_3_1_2.setValues(xVal_3_1_2EP, yVal_3_1_2);
		env1_1_3_1_2 += ls_3_1_2.value((currentEnv1_1_3_1_2EP));
		ls_3_1_2.setValues(xVal_3_1_2FW, yVal_3_1_2);
		env1_1_3_1_2 += ls_3_1_2.value((currentEnv1_1_3_1_2FW));

		env1_1_3 += env1_1_3_1_2;
	}
	env1_1_3 = std::min<double>(20, env1_1_3);

	return env1_1_3;
}  // Env1.1.3



} // namespace DGNB
