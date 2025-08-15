#ifndef DGNB_Eco2_4_2H
#define DGNB_Eco2_4_2H

#include "DGNB_Utilities.h"

namespace DGNB {
/*! Eco2.4.2 Adaptability and Third Party Utilisation Suitability */
class Eco2_4_2	// max +10
{
public:

	/*! Eco2.4.2.1 & Eco2.4.2.2 Proof of Reusability for same and different usage types */
	enum ATPUS_ProofOfReusability {									// max +35
		ATPUSPR_SameUsageType,										// Keyword: ATPUSPR_SameUsageType
		ATPUSPR_DifferentUsageType,									// Keyword: ATPUSPR_DifferentUsageType
		NUM_ATPUSPR
	};

	/*! Eco2.4.2.3 */
	enum ATPUS_ProofOfAdaptabilityOfIndividualFactors {
		ATPUSPAIF_CeilingHeight,									// Keyword: ATPUSPAIF_CeilingHeight
		ATPUSPAIF_BuildingDepth,									// Keyword: ATPUSPAIF_BuildingDepth
		ATPUSPAIF_FloorAllotment,									// Keyword: ATPUSPAIF_FloorAllotment
		ATPUSPAIF_GroundPlanFlexibility,							// Keyword: ATPUSPAIF_GroundPlanFlexibility
		ATPUSPAIF_Construction,										// Keyword: ATPUSPAIF_Construction
		ATPUSPAIF_BuildingServices,									// Keyword: ATPUSPAIF_BuildingServices
		NUM_ATPUSPAIF
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco2_4_2(){}

	Eco2_4_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag			m_flag_ATPUSPR[NUM_ATPUSPR];				// XML:E
	/*! List of flags. */
	IBK::Flag			m_flag_ATPUSPAIF[NUM_ATPUSPAIF];			// XML:E

	Utilities::UsageType			m_usageType;

}; // Eco 2.4.2

} // namespace DGNB

#endif // DGNB_Eco2_4_2H
