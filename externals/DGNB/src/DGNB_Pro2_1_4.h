#ifndef DGNB_Pro2_1_4H
#define DGNB_Pro2_1_4H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

/*! Pro2.1.4 Waste Reduced Construction Site */
class Pro2_1_4
{
public:

	/*! Pro2.1.4.1 Concept */
	enum WRCS_Concept {																	// max +5
		WRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts,				// Keyword: WRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts
		NUM_WRCSC
	};

	/*! Pro2.1.4.2 Instruction */
	enum WRCS_InstructionOfOperators {													// max +2.5
		WRCSIO_InstructionOrBriefungOfOperators,										// Keyword: WRCSIO_InstructionOrBriefungOfOperators
		NUM_WRCSIO
	};

	/*! Pro2.1.4.3 Examination of Implementation */
	enum WRCS_ExaminationOfImplementation {												// max +5
		WRCSEI_ExaminationOrVerificationOfImplementation,								// Keyword: WRCSEI_ExaminationOrVerificationOfImplementation
		NUM_WRCSEI
	};

	/*! Pro2.1.4.4 Circular Economy Bonus - Waste Prevention On The Construction Site */
	enum WRCS_CircularEconomyWastePrevention {											// max +10 bonus
		WRCSCEWP_UseOfNovelAndLargelyWastePreventiveConceptsMethodsAndTechnologies,		// Keyword: WRCSCEWP_UseOfNovelAndLargelyWastePreventiveConceptsMethodsAndTechnologies
		NUM_WRCSCEWP
	};
	

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_1_4(){}

	Pro2_1_4(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_WRCSC[NUM_WRCSC];							// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_WRCSIO[NUM_WRCSIO];							// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_WRCSEI[NUM_WRCSEI];							// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_WRCSCEWP[NUM_WRCSCEWP];						// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro2_1_4H
