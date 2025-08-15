#ifndef DGNB_Soc1_6_4H
#define DGNB_Soc1_6_4H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.6.4 Quality of Stay - Inner Allotment */
class Soc1_6_4
{
public:

	/*! Basic parameters. */
	enum para_t {
		/*! Soc1_6_4_1AlternativeInnovativeSolutions */
		P_Soc1_6_4_1AlternativeInnovativeSolutions,															// Keyword: Soc1_6_4_1AlternativeInnovativeSolutions		[-]
		NUM_P
	};

	/*! Soc1.6.4.1 Quality of Stay in Inner Allotment Areas */
	enum QS_InnerAllotmentAreas {																			// max +10
		QSIAA_WideningsGalleriesNichesStairwellsOfSufficientWidthAndAirSpaceForCrossFloorCommunication,		// Keyword: QSIAA_WideningsGalleriesNichesStairwellsOfSufficientWidthAndAirSpaceForCrossFloorCommunication
		QSIAA_DaylightAvailabilityInAllotmentAreas,															// Keyword: QSIAA_DaylightAvailabilityInAllotmentAreas
		QSIAA_DoorwayOpeningsToBalconiesRoofTerracesAtria,													// Keyword: QSIAA_DoorwayOpeningsToBalconiesRoofTerracesAtria
		QSIAA_AllotmentAreasFeatureHeightenedThermalAcousticOrSoundproofingRequirementsEnablingFlexibleUse,	// Keyword: QSIAA_AllotmentAreasFeatureHeightenedThermalAcousticOrSoundproofingRequirementsEnablingFlexibleUse
		QSIAA_InnovationRoomAlternativeCertification,														// Keyword: QSIAA_InnovationRoomAlternativeCertification
		NUM_QSIAA
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_6_4(){}

	Soc1_6_4(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag					m_flag_QSIAA[NUM_QSIAA];		// XML:E
	
	IBK::Parameter				m_para[NUM_P];					// XML:E

	Utilities::UsageType		m_usageType;

};

} // namespace DGNB

#endif // DGNB_Soc1_6_4
