#ifndef DGNB_Env2_3_1H
#define DGNB_Env2_3_1H
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Env2_3_1 degree of conversion */
class Env2_3_1 {
	public:

	/*! Env2_3_1_1 degree of conversion */
	enum AD_DegreeOfConversion {									// max +70 (0, 40, 70)
		ADDC_OutlyingDevelopmentArea,								// Keyword: ADDC_OutlyingDevelopmentArea
		ADDC_InternalDevelopmentArea,								// Keyword: ADDC_InternalDevelopmentArea
		ADDC_DevelopmentAreaInPriorStructuralOrInfrastructuralUse,	// Keyword: ADDC_DevelopmentAreaInPriorStructuralOrInfrastructuralUse
		NUM_ADDC
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env2_3_1(){}

	Env2_3_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_ADDC[NUM_ADDC];						// XML:E

	Utilities::UsageType			m_usageType;

};

} // namespace DGNB

#endif // Env2_3_1H
