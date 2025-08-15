#ifndef DGNB_Soc2_1_1H
#define DGNB_Soc2_1_1H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Accessibility Quality Stages */
class Soc2_1_1
{
public:

	/*! Basic parameters. */
	enum para_t {
		/*! Soc2_1_1Qualitystage */
		P_Soc2_1_1Qualitystage,									// Keyword: Soc2_1_1Qualitystage		[-]
		NUM_P
	};


	/*! Soc2.1.1  */
	enum AQS_TotalQualityStage {								// max +10
		AQST_ResultsSubmitted,									// Keyword: AQST_ResultsSubmitted
		AQST_Residential_StudentHostelBoardingHouses,			// Keyword: AQST_Residential_StudentHostelBoardingHouses
		AQST_Residential_NursingHomesHospicesDisabledElderly,	// Keyword: AQST_Residential_NursingHomesHospicesDisabledElderly
		NUM_AQST
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc2_1_1(){}

	Soc2_1_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	bool minimumRequirementsMet();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag					m_flag_AQST[NUM_AQST];			// XML:E
	
	IBK::Parameter				m_para[NUM_P];					// XML:E

	Utilities::UsageType		m_usageType;

};

} // namespace DGNB

#endif // DGNB_Soc2_1_1
