#ifndef DGNB_Pro2_1_3H
#define DGNB_Pro2_1_3H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

/*! Pro2.1.3 Soil and Groundwater Protection On Construction Site */
class Pro2_1_3
{
public:

	/*! Pro2.1.3.1 Concept */
	enum SGPCS_Concept {													// max +5
		SGPCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts,	// Keyword: SGPCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts
		NUM_SGPCSC
	};

	/*! Pro2.1.3.2 Instruction */
	enum SGPCS_InstructionOfOperators {										// max +2.5
		SGPCSIO_InstructionOrBriefungOfOperators,							// Keyword: SGPCSIO_InstructionOrBriefungOfOperators
		NUM_SGPCSIO
	};

	/*! Pro2.1.3.3 Examination of Implementation */
	enum SGPCS_ExaminationOfImplementation {								// max +5
		SGPCSEI_ExaminationOrVerificationOfImplementation,					// Keyword: SGPCSEI_ExaminationOrVerificationOfImplementation
		NUM_SGPCSEI
	};
	

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_1_3(){}

	Pro2_1_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_SGPCSC[NUM_SGPCSC];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_SGPCSIO[NUM_SGPCSIO];			// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_SGPCSEI[NUM_SGPCSEI];			// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro2_1_3H
