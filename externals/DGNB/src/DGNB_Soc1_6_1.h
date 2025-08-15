#ifndef DGNB_Soc1_6_1H
#define DGNB_Soc1_6_1H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.6.1 Communication-supporting Offers */
class Soc1_6_1
{
public:

	/*! Basic parameters. */
	enum para_t {
		/*! AlternativeInnovativeCommunicationConstellations */
		P_AlternativeInnovativeCommunicationConstellations,		// Keyword: AlternativeInnovativeCommunicationConstellations		[-]
		NUM_P
	};

	/*! Soc1.6.1.1 communication zone main usage */
	enum CSO_CommunicationZoneMainUsage {						// max +15
		CSOCZMU_DifferentCommunicationZones,					// Keyword: CSOCZMU_DifferentCommunicationZones
		CSOCZMU_CommunicationSupportingRoomDesign,				// Keyword: CSOCZMU_CommunicationSupportingRoomDesign
		CSOCZMU_InnovationRoomAlternativeCertification,			// Keyword: CSOCZMU_InnovationRoomAlternativeCertification
		NUM_CSOCZMU
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_6_1(){}

	Soc1_6_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag					m_flag_CSOCZMU[NUM_CSOCZMU];	// XML:E
	
	IBK::Parameter				m_para[NUM_P];					// XML:E
	
	Utilities::UsageType		m_usageType;

};

} // namespace DGNB

#endif // DGNB_Soc1_6_1
