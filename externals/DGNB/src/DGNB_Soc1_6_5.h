#ifndef DGNB_Soc1_6_5H
#define DGNB_Soc1_6_5H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.6.5 Quality of Stay - Outdoor Areas */
class Soc1_6_5
{
public:

	/*! Basic parameters. */
	enum para_t {
		/*! Soc1_6_5_3AlternativeInnovativeSolutions */
		P_Soc1_6_5_3AlternativeInnovativeSolutions,													// Keyword: Soc1_6_5_3AlternativeInnovativeSolutions	[-]
		/*! Soc1_6_5_4AlternativeInnovativePoints */
		P_Soc1_6_5_4AlternativeInnovativePoints,													// Keyword: Soc1_6_5_4AlternativeInnovativePoints		[-]
		NUM_P
	};

	/*! Soc1.6.5.1 Design Concept for Outdoor Areas */
	enum QS_DesignConceptForOutdoorAreas {															// max +15
		QSDCOA_DesignConceptFulfillsUserRequirementsAndFeaturesDifferentFunctions,					// Keyword: QSDCOA_DesignConceptFulfillsUserRequirementsAndFeaturesDifferentFunctions
		QSDCOA_DesignConsidersMaterialQuality,														// Keyword: QSDCOA_DesignConsidersMaterialQuality
		QSDCOA_DesignConsidersEnvironmentFriendlyAndSociallyAcceptableLighting,						// Keyword: QSDCOA_DesignConsidersEnvironmentFriendlyAndSociallyAcceptableLighting
		QSDCOA_DesignConsidersIntuitiveOrientation,													// Keyword: QSDCOA_DesignConsidersIntuitiveOrientation
		QSDCOA_DesignAvoidsPlacesOfAnxiety,															// Keyword: QSDCOA_DesignAvoidsPlacesOfAnxiety
		QSDCOA_DesignConsidersIntegrationAndGreeningOfTechnicalFacilities,							// Keyword: QSDCOA_DesignConsidersIntegrationAndGreeningOfTechnicalFacilities
		QSDCOA_AlternativeCertification_DesignGuidelinesFeatureIndividualPreferencesOfResidents,	// Keyword: QSDCOA_AlternativeCertification_DesignGuidelinesFeatureIndividualPreferencesOfResidents
		QSDCOA_Healthcare_CommonAreasNotExposedToNoiseMalodorOrSimilarConstrictions,				// Keyword: QSDCOA_Healthcare_CommonAreasNotExposedToNoiseMalodorOrSimilarConstrictions
		NUM_QSDCOA
	};

	/*! Soc1.6.5.2 Outdoor Common Areas */
	enum QS_OutdoorCommonAreas {																	// max +15
		QSOCA_MoreThan10PercentOfRooftopAtLeast5m2,													// Keyword: QSOCA_MoreThan10PercentOfRooftopAtLeast5m2
		QSOCA_CSCBSC_MoreThan1PercentOfRooftop,														// Keyword: QSOCA_CSCBSC_MoreThan1PercentOfRooftop
		QSOCA_BalconiesLoggiasWinterGardenOfAtLeast3m2PerUnit,										// Keyword: QSOCA_BalconiesLoggiasWinterGardenOfAtLeast3m2PerUnit
		QSOCA_MoreThan25PercentOfOutdoorAreaAtLeast30m2_AccordingToDIN_277,							// Keyword: QSOCA_MoreThan25PercentOfOutdoorAreaAtLeast30m2_AccordingToDIN_277
		QSOCA_Healthcare_BalconiesLoggiasWinterGardenAccessbileForMostUsers,						// Keyword: QSOCA_Healthcare_BalconiesLoggiasWinterGardenAccessbileForMostUsers
		NUM_QSOCA
	};

	/*! Soc1.6.5.3 Outdoor Common Areas Suited to Use */
	enum QS_OutdoorCommonAreasSuitedToUse {															// max +25
		QSOCASU_AllotmentAndNetworkingFunction,														// Keyword: QSOCASU_AllotmentAndNetworkingFunction
		QSOCASU_AccessibilityToPublic,																// Keyword: QSOCASU_AccessibilityToPublic
		QSOCASU_MeetupAndCommunicationFunction,														// Keyword: QSOCASU_MeetupAndCommunicationFunction
		QSOCASU_ExerciseAndPlayFunction,															// Keyword: QSOCASU_ExerciseAndPlayFunction
		QSOCASU_WorkAndConcentrationFunction,														// Keyword: QSOCASU_WorkAndConcentrationFunction
		QSOCASU_RestAndRecuperationFunction,														// Keyword: QSOCASU_RestAndRecuperationFunction
		QSOCASU_SocialControlOfOutdoorAreasThroughBuildingExteriorRelation,							// Keyword: QSOCASU_SocialControlOfOutdoorAreasThroughBuildingExteriorRelation
		QSOCASU_EnvironmentFriendlyAndSociallyAcceptableLighting,									// Keyword: QSOCASU_EnvironmentFriendlyAndSociallyAcceptableLighting
		QSOCASU_InnovationRoomAlternativeCertification,												// Keyword: QSOCASU_InnovationRoomAlternativeCertification
		NUM_QSOCASU
	};

	/*! Soc1.6.5.4 Outdoor Common Area Comfort */
	enum QS_OutdoorCommonAreaComfort {											// max +15
		QSDCOAC_SolarisationOnDec21AtLeast1Hour,								// Keyword: QSDCOAC_SolarisationOnDec21AtLeast1Hour
		QSDCOAC_SolarisationOnDec21AtLeast3Hours,								// Keyword: QSDCOAC_SolarisationOnDec21AtLeast3Hours
		QSDCOAC_SummerSunblindThroughTreesShadingOrBuildingsOn10PercentOrMore,	// Keyword: QSDCOAC_SummerSunblindThroughTreesShadingOrBuildingsOn10PercentOrMore
		QSDCOAC_SummerSunblindThroughTreesShadingOrBuildingsOn30PercentOrMore,	// Keyword: QSDCOAC_SummerSunblindThroughTreesShadingOrBuildingsOn30PercentOrMore
		QSDCOAC_WindShieldNoNegativeEffectsOnCommonAreasOrPreventativeMeasures,	// Keyword: QSDCOAC_WindShieldNoNegativeEffectsOnCommonAreasOrPreventativeMeasures
		QSDCOAC_InnovationRoomAlternativeCertification,							// Keyword: QSDCOAC_InnovationRoomAlternativeCertification
		NUM_QSDCOAC
	};

	/*! Soc1.6.5.5 Agenda2030 Climate Protection Factor of Surface Structures and Climate Protection Optimisation of Outdoor Areas */
	enum QS_Agenda2030ClimateProtectionFactorOfSurfaceStructuresAndClimateProtectionOptimisationOfOutdoorAreas {	// max +10
		QSA2030_ClimateProtectionFactorOfSurfaceStructures,						// Keyword: QSA2030_ClimateProtectionFactorOfSurfaceStructures
		QSA2030_ClimateProtectionProtectionOptimisationOfOutdoorAreas,			// Keyword: QSA2030_ClimateProtectionProtectionOptimisationOfOutdoorAreas
		NUM_QSA2030
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_6_5(){}

	Soc1_6_5(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag					m_flag_QSDCOA[NUM_QSDCOA];		// XML:E
	/*! List of flags. */
	IBK::Flag					m_flag_QSOCA[NUM_QSOCA];		// XML:E
	/*! List of flags. */
	IBK::Flag					m_flag_QSOCASU[NUM_QSOCASU];	// XML:E
	/*! List of flags. */
	IBK::Flag					m_flag_QSDCOAC[NUM_QSDCOAC];	// XML:E
	/*! List of flags. */
	IBK::Flag					m_flag_QSA2030[NUM_QSA2030];	// XML:E
	
	IBK::Parameter				m_para[NUM_P];					// XML:E

	Utilities::UsageType		m_usageType;

};

} // namespace DGNB

#endif // DGNB_Soc1_6_5
