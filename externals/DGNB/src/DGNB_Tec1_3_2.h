#ifndef DGNB_Tec1_3_2H
#define DGNB_Tec1_3_2H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Tec1_3_2
{
public:

	/*! Tec1.3.2.1 Quality Of Building Envelope: Transmission Over Envelope Surface - Envelope Parts */
	enum  TOES_EnvelopeParts {																			// max +10
		TOESEP_NominalRoomTemperature19Degrees,															// Keyword: TOESEP_NominalRoomTemperature19Degrees
		TOESEP_19Degrees_OpaqueExteriorBuildingElementsHTCLessThan0_18,									// Keyword: TOESEP_19Degrees_OpaqueExteriorBuildingElementsHTCLessThan0_18
		TOESEP_19Degrees_TransparentExteriorBuildingElementsAndFrontsHTCLessThan1_0,					// Keyword: TOESEP_19Degrees_TransparentExteriorBuildingElementsAndFrontsHTCLessThan1_0
		TOESEP_19Degrees_OtherTransparentElementsLikeGlassRoofsLightBandsLightDomesHTCLessThan1_6,		// Keyword: TOESEP_19Degrees_OtherTransparentElementsLikeGlassRoofsLightBandsLightDomesHTCLessThan1_6
		TOESEP_NominalRoomTemperatureBetween12And19Degrees,												// Keyword: TOESEP_NominalRoomTemperatureBetween12And19Degrees
		TOESEP_12to19Degrees_OpaqueExteriorBuildingElementsHTCLessThan0_24,								// Keyword: TOESEP_12to19Degrees_OpaqueExteriorBuildingElementsHTCLessThan0_24
		TOESEP_12to19Degrees_TransparentExteriorBuildingElementsAndFrontsHTCLessThan1_3,				// Keyword: TOESEP_12to19Degrees_TransparentExteriorBuildingElementsAndFrontsHTCLessThan1_3
		TOESEP_12to19Degrees_OtherTransparentElementsLikeGlassRoofsLightBandsLightDomesHTCLessThan2_0,	// Keyword: TOESEP_12to19Degrees_OtherTransparentElementsLikeGlassRoofsLightBandsLightDomesHTCLessThan2_0
		TOESEP_Residential_TransmissionOverHullSurfaceComparedToReferenceBuildingLessThan55Percent,		// Keyword: TOESEP_Residential_TransmissionOverHullSurfaceComparedToReferenceBuildingLessThan55Percent
		NUM_TOESEP
	};
	
	/*! Tec1.3.2.2 Quality Of Building Envelope: Transmission Over Envelope Surface - Thermal Bridge Bonus */
	enum  TOES_ThermalBridgeSurcharge {		// max +10
		TOESTBS_EvaluationImpossible,		// Keyword: TOESTBS_EvaluationImpossible
		TOESTBS_SurchargeLessThan0_05,		// Keyword: TOESTBS_SurchargeLessThan0_05
		TOESTBS_SurchargeLessThan0_01,		// Keyword: TOESTBS_SurchargeLessThan0_01
		NUM_TOESTBS
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Tec1_3_2(){}

	Tec1_3_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_TOESEP[NUM_TOESEP];					// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_TOESTBS[NUM_TOESTBS];				// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Tec1_3_2H
