#ifndef DGNB_Site1_1_3H
#define DGNB_Site1_1_3H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Site1.1.3 Evaluation of External Influences */
class Site1_1_3
{
public:

	/*! Site 1.1.3.1 Surrounding Noise */
	enum EEI_SurroundingNoise {																								// max +10
		EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan75dB,					// Keyword: EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan75dB
		EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan65dB,					// Keyword: EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan65dB
		EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan55dB,					// Keyword: EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan55dB
		NUM_EEISN
	};

	/*! Site 1.1.3.2 Air Quality */
	enum EEI_AirQuality {																									// max +15
		EEIAQ_PM10ExceedsLimitOnNoMoreThan35DaysAnnually,																	// Keyword: EEIAQ_PM10ExceedsLimitOnNoMoreThan35DaysAnnually
		EEIAQ_PM10NeverExceedsLimit,																						// Keyword: EEIAQ_PM10NeverExceedsLimit
		EEIAQ_PM2_5NeverExceedsLimit,																						// Keyword: EEIAQ_PM2_5NeverExceedsLimit
		EEIAQ_NO2ExceedsLimitOnNoMoreThan18IntervalsOf3HoursBeyondThe1HourDailyLimitAnnually,								// Keyword: EEIAQ_NO2ExceedsLimitOnNoMoreThan18IntervalsOf3HoursBeyondThe1HourDailyLimitAnnually
		EEIAQ_NO2NeverExceedsExceedsLimit,																					// Keyword: EEIAQ_NO2NeverExceedsExceedsLimit
		NUM_EEIAQ
	};

	/*! Site 1.1.3.3 Radon */
	enum EEI_Radon {																										// max +10
		EEIR_ExaminationIfSiteIsInARadonPreventionZoneBasedOnZonePassOrGovernmentalInformation,								// Keyword: EEIR_ExaminationIfSiteIsInARadonPreventionZoneBasedOnZonePassOrGovernmentalInformation
		EEIR_ConclusionThatSiteIsNotInARadonPreventionZoneBasedOnZonePassOrGovernmentalInformation,							// Keyword: EEIR_ConclusionThatSiteIsNotInARadonPreventionZoneBasedOnZonePassOrGovernmentalInformation
		EEIR_RadonConcentrationOfCompartmentOrBasementAirMeasured,															// Keyword: EEIR_RadonConcentrationOfCompartmentOrBasementAirMeasured
		EEIR_ReferenceValueMeasuredOrExpectedInLessThan75PercentOfAdministrationUnitZoneOrNoMoreThan10PercentOfBuildings,	// Keyword: EEIR_ReferenceValueMeasuredOrExpectedInLessThan75PercentOfAdministrationUnitZoneOrNoMoreThan10PercentOfBuildings
		NUM_EEIR
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Site1_1_3(){}

	Site1_1_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_EEISN[NUM_EEISN];												// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_EEIAQ[NUM_EEIAQ];												// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_EEIR[NUM_EEIR];													// XML:E

	Utilities::UsageType			m_usageType;
};

} // namespace DGNB

#endif // DGNB_Site1_1_3H
