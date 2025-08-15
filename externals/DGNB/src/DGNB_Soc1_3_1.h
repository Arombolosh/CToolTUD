#ifndef DGNB_Soc1_3_1H
#define DGNB_Soc1_3_1H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.3.1 Building Acoustics - Observation of DIN 4109 and VDI 2569 */
class Soc1_3_1
{
public:

	/*! Soc1.3.1.1a Observation of Raised Soundproofing Requirements - Healthcare Assembly Hotel */
	enum ORSR_HealthcareHotelAssembly {								// max +10
		ORSRHcHA_DIN_4109_5_RaisedSoundproofingMet,					// Keyword: ORSRHcHA_DIN_4109_5_RaisedSoundproofingMet
		NUM_ORSRHcHA
	};

	/*! Soc1.3.1.1b Observation of Raised Soundproofing Requirements - Office */
	enum ORSR_Office {												// max +10
		ORSRO_ObservationOfVDI_2569_ClassAorBRequirements,			// Keyword: ORSRO_ObservationOfVDI_2569_ClassAorBRequirements
		NUM_ORSRO
	};

	/*! Soc1.3.1.1c Observation of Raised Soundproofing Requirements - Residential */
	enum ORSR_Residential {											// max +40
		ORSRR_DIN_4109_5_RequirementsMet,							// Keyword: ORSRR_DIN_4109_5_RequirementsMet
		ORSRR_SoundproofingPassClassCOrBetter,						// Keyword: ORSRR_SoundproofingPassClassCOrBetter
		NUM_ORSRR
	};

	/*! Soc1.3.1.2 Building Acoustic Measuring - Office Education Hotel Assembly Healthcare Residential */
	enum BAM_OfficeEducationHotelAssemblyHealthcareResidential {	// max +30 / +50 depending on usageType
		BAMOEHAHcR_ConfirmationThroughMeasuring,					// Keyword: BAMOEHAHcR_ConfirmationThroughMeasuring
		NUM_BAMOEHAHcR
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_3_1(){}

	Soc1_3_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag					m_flag_ORSRHcHA[NUM_ORSRHcHA];						// XML:E
	/*! List of flags. */
	IBK::Flag					m_flag_ORSRO[NUM_ORSRO];							// XML:E
	/*! List of flags. */
	IBK::Flag					m_flag_ORSRR[NUM_ORSRR];							// XML:E
	/*! List of flags. */
	IBK::Flag					m_flag_BAMOEHAHcR[NUM_BAMOEHAHcR];					// XML:E

	Utilities::UsageType		m_usageType;

};

} // namespace DGNB

#endif // DGNB_Soc1_3_1
