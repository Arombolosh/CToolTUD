#include "DGNB_Site1_1_3.h"

namespace DGNB {
	
double DGNB::Site1_1_3::score() {
	double site1_1_3 = 0;

	// assigning points for Site1.1.3.1
	if (m_flag_EEISN[(EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan55dB)].isEnabled())
		site1_1_3 += 10;
	else if (m_flag_EEISN[(EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan65dB)].isEnabled())
		site1_1_3 += 5;
	else if (m_flag_EEISN[(EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan75dB)].isEnabled())
		site1_1_3 += 2;

	// assigning points for Site1.1.3.2
	if (m_flag_EEIAQ[(EEIAQ_PM10NeverExceedsLimit)].isEnabled())
		site1_1_3 += 5;
	else if (m_flag_EEIAQ[(EEIAQ_PM10ExceedsLimitOnNoMoreThan35DaysAnnually)].isEnabled())
		site1_1_3 += 2;
	site1_1_3 += (m_flag_EEIAQ[(EEIAQ_PM10ExceedsLimitOnNoMoreThan35DaysAnnually)].isEnabled() ? 5 : 0);
	if (m_flag_EEIAQ[(EEIAQ_NO2NeverExceedsExceedsLimit)].isEnabled())
		site1_1_3 += 5;
	else if (m_flag_EEIAQ[(EEIAQ_NO2ExceedsLimitOnNoMoreThan18IntervalsOf3HoursBeyondThe1HourDailyLimitAnnually)].isEnabled())
		site1_1_3 += 2;

	// assigning points for Site1.1.3.3
	if (m_flag_EEIR[(EEIR_ConclusionThatSiteIsNotInARadonPreventionZoneBasedOnZonePassOrGovernmentalInformation)].isEnabled())
		site1_1_3 += 5;
	else if (m_flag_EEIR[(EEIR_ExaminationIfSiteIsInARadonPreventionZoneBasedOnZonePassOrGovernmentalInformation)].isEnabled())
		site1_1_3 += 2;
	if (m_flag_EEIR[(EEIR_ReferenceValueMeasuredOrExpectedInLessThan75PercentOfAdministrationUnitZoneOrNoMoreThan10PercentOfBuildings)].isEnabled())
		site1_1_3 += 5;
	else if (m_flag_EEIR[(EEIR_RadonConcentrationOfCompartmentOrBasementAirMeasured)].isEnabled())
		site1_1_3 += 2;

	return site1_1_3;
} // Site1.1.3

} // namespace DGNB
