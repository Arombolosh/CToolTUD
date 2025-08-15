#ifndef DGNB_Pro2_1_1H
#define DGNB_Pro2_1_1H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

/*! Pro2.1.1 Noise Reduced Construction Site */
class Pro2_1_1
{
public:

	/*! Pro2.1.1.1 Concept */
	enum NRCS_Concept {														// max +5
		NRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts,	// Keyword: NRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts
		NUM_NRCSC
	};

	/*! Pro2.1.1.2 Instruction */
	enum NRCS_InstructionOfOperators {										// max +2.5
		NRCSIO_InstructionOrBriefungOfOperators,							// Keyword: NRCSIO_InstructionOrBriefungOfOperators
		NUM_NRCSIO
	};

	/*! Pro2.1.1.3 Examination of Implementation */
	enum NRCS_ExaminationOfImplementation {									// max +5
		NRCSEI_ExaminationOrVerificationOfImplementation,					// Keyword: NRCSEI_ExaminationOrVerificationOfImplementation
		NUM_NRCSEI
	};
	

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_1_1(){}

	Pro2_1_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_NRCSC[NUM_NRCSC];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_NRCSIO[NUM_NRCSIO];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_NRCSEI[NUM_NRCSEI];				// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro2_1_1H
