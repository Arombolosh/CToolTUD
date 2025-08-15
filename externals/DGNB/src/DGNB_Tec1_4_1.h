#ifndef DGNB_Tec1_4_1H
#define DGNB_Tec1_4_1H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {
/* Passive Systems */
class Tec1_4_1
{
public:

	/*! Tec1.4.1 Passive Systems: Planning */
	enum  PS_Planning {															// max +15
		PSP_HighCompactness,													// Keyword: PSP_HighCompactness
		PSP_BalancedWindowAreaRatioUnderConsiderationOfShading,					// Keyword: PSP_BalancedWindowAreaRatioUnderConsiderationOfShading
		PSP_ConstructionalSunblindToPreventDirectSunlightOnWindowsDuringSummer,	// Keyword: PSP_ConstructionalSunblindToPreventDirectSunlightOnWindowsDuringSummer
		PSP_AsManyNaturallyLightedRoomsAsPossible,								// Keyword: PSP_AsManyNaturallyLightedRoomsAsPossible
		PSP_UseOfHighMassElementsForHeatStorage,								// Keyword: PSP_UseOfHighMassElementsForHeatStorage
		PSP_PassiveCooling,														// Keyword: PSP_PassiveCooling
		PSP_EffectiveNaturalAeration,											// Keyword: PSP_EffectiveNaturalAeration
		NUM_PSP
	};

	/*! Tec1.4.2 Passive Systems: Implementation */
	enum  PS_Implementation {													// max +15
		PSI_HighCompactness,													// Keyword: PSI_HighCompactness
		PSI_BalancedWindowAreaRatioUnderConsiderationOfShading,					// Keyword: PSI_BalancedWindowAreaRatioUnderConsiderationOfShading
		PSI_ConstructionalSunblindToPreventDirectSunlightOnWindowsDuringSummer,	// Keyword: PSI_ConstructionalSunblindToPreventDirectSunlightOnWindowsDuringSummer
		PSI_AsManyNaturallyLightedRoomsAsPossible,								// Keyword: PSI_AsManyNaturallyLightedRoomsAsPossible
		PSI_UseOfHighMassElementsForHeatStorage,								// Keyword: PSI_UseOfHighMassElementsForHeatStorage
		PSI_PassiveCooling,														// Keyword: PSI_PassiveCooling
		PSI_EffectiveNaturalAeration,											// Keyword: PSI_EffectiveNaturalAeration
		NUM_PSI
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Tec1_4_1(){}

	Tec1_4_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_PSP[NUM_PSP];		// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_PSI[NUM_PSI];		// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Tec1_4_1H
