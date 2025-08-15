#ifndef DGNB_Tec3_1_4H
#define DGNB_Tec3_1_4H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

/*! Tec3.1.4 Renting Systems */
class Tec3_1_4
{
public:

	/*! Basic parameters. */
	enum para_t {
		/*! NumberOfIndividualNonOverlappingMobilitySharingOffers */
		P_Tec3_1_4NumberOfIndividualNonOverlappingMobilitySharingOffers,												// Keyword: Tec3_1_4NumberOfIndividualNonOverlappingMobilitySharingOffers		[-]
		NUM_P
	};

	/*! Tec3.1.4 Mobility Sharing */
	enum RS_MobilitySharing {																							// max +10
		RSMS_ResultsSubmitted,																							// Keyword: RSMS_ResultsSubmitted
		RSMS_Alt_BuildingAndOccupantsArePartOfAQuarterMobilityConceptIncludingOrganisationAndSupportOfSharingsystems,	// Keyword: RSMS_Alt_BuildingAndOccupantsArePartOfAQuarterMobilityConceptIncludingOrganisationAndSupportOfSharingsystems
		NUM_IAFSBTEB
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Tec3_1_4(){}

	Tec3_1_4(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_IAFSBTEB[NUM_IAFSBTEB];			// XML:E
	
	IBK::Parameter					m_para[NUM_P];							// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Tec3_1_4H
