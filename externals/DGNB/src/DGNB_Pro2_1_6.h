#ifndef DGNB_Pro2_1_6H
#define DGNB_Pro2_1_6H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

/*! Pro2.1.6 Resource Conservation */
class Pro2_1_6
{
public:

	/*! Pro2.1.6.1 Water Usage */
	/*! Pro2.1.6.1.1 Water Usage: Data Transparency */
	enum RCWU_DataTransparency {											// max +5
		RCWUDT_MeasuringAndDocumentationOfWaterUsageOnConstructionSite,		// Keyword: RCWUDT_MeasuringAndDocumentationOfWaterUsageOnConstructionSite
		NUM_RCWUDT
	};
	
	/*! Pro2.1.6.1.2 Water Usage: Concept */
	enum RCWU_Concept {														// max +5
		RCWUC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts,	// Keyword: RCWUC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts
		NUM_RCWUC
	};

	/*! Pro2.1.6.1.3 Water Usage: Instruction */
	enum RCWU_InstructionOfOperators {										// max +2.5
		RCWUIO_InstructionOrBriefungOfOperators,							// Keyword: RCWUIO_InstructionOrBriefungOfOperators
		NUM_RCWUIO
	};

	/*! Pro2.1.6.1.4 Water Usage: Examination of Implementation */
	enum RCWU_ExaminationOfImplementation {									// max +5
		RCWUEI_ExaminationOrVerificationOfImplementation,					// Keyword: RCWUEI_ExaminationOrVerificationOfImplementation
		NUM_RCWUEI
	};

	/*! Pro2.1.6.2 Energy Usage */
	/*! Pro2.1.6.1.1 Energy Usage: Data Transparency */
	enum RCEU_DataTransparency {											// max +5
		RCEUDT_MeasuringAndDocumentationOfWaterUsageOnConstructionSite,		// Keyword: RCEUDT_MeasuringAndDocumentationOfWaterUsageOnConstructionSite
		NUM_RCEUDT
	};
	
	/*! Pro2.1.6.2.2 Energy Usage: Concept */
	enum RCEU_Concept {														// max +5
		RCEUC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts,	// Keyword: RCEUC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts
		NUM_RCEUC
	};

	/*! Pro2.1.6.2.3 Energy Usage: Instruction */
	enum RCEU_InstructionOfOperators {										// max +2.5
		RCEUIO_InstructionOrBriefungOfOperators,							// Keyword: RCEUIO_InstructionOrBriefungOfOperators
		NUM_RCEUIO
	};

	/*! Pro2.1.6.2.4 Energy Usage: Examination of Implementation */
	enum RCEU_ExaminationOfImplementation {									// max +5
		RCEUEI_ExaminationOrVerificationOfImplementation,					// Keyword: RCEUEI_ExaminationOrVerificationOfImplementation
		NUM_RCEUEI
	};
	

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_1_6(){}

	Pro2_1_6(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_RCWUDT[NUM_RCWUDT];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_RCWUC[NUM_RCWUC];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_RCWUIO[NUM_RCWUIO];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_RCWUEI[NUM_RCWUEI];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_RCEUDT[NUM_RCEUDT];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_RCEUC[NUM_RCEUC];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_RCEUIO[NUM_RCEUIO];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_RCEUEI[NUM_RCEUEI];				// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro2_1_6H
