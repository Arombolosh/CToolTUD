#ifndef DGNB_Pro2_1_2H
#define DGNB_Pro2_1_2H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

/*! Pro2.1.2 Dust-Reduced Construction Site*/
class Pro2_1_2
{
public:

	/*! Pro2.1.2.1 Concept */
	enum DRCS_Concept {														// max +5
		DRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts,	// Keyword: DRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts
		NUM_DRCSC
	};

	/*! Pro2.1.2.2 Instruction */
	enum DRCS_InstructionOfOperators {										// max +2.5
		DRCSIO_InstructionOrBriefungOfOperators,							// Keyword: DRCSIO_InstructionOrBriefungOfOperators
		NUM_DRCSIO
	};

	/*! Pro2.1.2.3 Examination of Implementation */
	enum DRCS_ExaminationOfImplementation {									// max +5
		DRCSEI_ExaminationOrVerificationOfImplementation,					// Keyword: DRCSEI_ExaminationOrVerificationOfImplementation
		NUM_DRCSEI
	};
	

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_1_2(){}

	Pro2_1_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_DRCSC[NUM_DRCSC];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_DRCSIO[NUM_DRCSIO];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_DRCSEI[NUM_DRCSEI];				// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro2_1_2H
