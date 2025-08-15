#ifndef DGNB_Tec1_3_5H
#define DGNB_Tec1_3_5H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Tec1_3_5
{
public:

	/*! Tec1.3.5 Quality Assurance: Measuring Quality Control */
	enum QA_MeasuringQualityControl {										// max +20
		QAMQC_BlowerDoorTest,												// Keyword: QAMQC_BlowerDoorTest
		QAMQC_BuildingThermographyDuringBuildingPhase,						// Keyword: QAMQC_BuildingThermographyDuringBuildingPhase
		QAMQC_OtherRelevantMeasurements,									// Keyword: QAMQC_OtherRelevantMeasurements
		NUM_QAMQC
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Tec1_3_5(){}

	Tec1_3_5(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_QAMQC[NUM_QAMQC];				// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Tec1_3_5H
