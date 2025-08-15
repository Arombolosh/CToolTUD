#ifndef DGNB_Pro2_1_5H
#define DGNB_Pro2_1_5H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

/*! Pro2.1.5 Communication */
class Pro2_1_5
{
public:

	/*! Pro2.1.5.1 Communication: External */
	/*! Pro2.1.5.1.1 Communication: External - Signage and Information */
	enum C_ExternalSignageAndInformation {												// max +5
		CESI_NotificationOfNearbyResidentsOnProjectAndSite,								// Keyword: CESI_NotificationOfNearbyResidentsOnProjectAndSite
		NUM_CESI
	};
	
	/*! Pro2.1.5.1.2 Communication: External - Communication with Residents */
	enum C_ExternalCommunicationWithResidents {											// max +5
		CECR_DetailsOnHowResidentsAreInformedOnAndIncludedInProjectAsideFromSignage,	// Keyword: CECR_DetailsOnHowResidentsAreInformedOnAndIncludedInProjectAsideFromSignage
		NUM_CECR
	};
	
	/*! Pro2.1.5.2 Communication: Internal - Sharing of Information */
	enum C_InternalSharingOfInformation {												// max +5
		CISI_ParticipantsInProjectProvidedWithAllRelevantInformation,					// Keyword: CISI_ParticipantsInProjectProvidedWithAllRelevantInformation
		CISI_GuaranteeOfFixedInformationFlowBetweenPlannersAndSite,						// Keyword: CISI_GuaranteeOfFixedInformationFlowBetweenPlannersAndSite
		CISI_ContinuousCommunicationOfRelevantInformationOnConstructionProgress,		// Keyword: CISI_ContinuousCommunicationOfRelevantInformationOnConstructionProgress
		CISI_AvailabilityOfCompleteAndUpToDateListsOfProvidersPlannersAndConstructors,	// Keyword: CISI_AvailabilityOfCompleteAndUpToDateListsOfProvidersPlannersAndConstructors
		CISI_OnlineAvailabilityOfAllInformation,										// Keyword: CISI_OnlineAvailabilityOfAllInformation
		NUM_CISI
	};
	

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_1_5(){}

	Pro2_1_5(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_CESI[NUM_CESI];								// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CECR[NUM_CECR];								// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_CISI[NUM_CISI];								// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro2_1_5H
