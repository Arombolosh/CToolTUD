#ifndef DGNB_Soc1_2_2H
#define DGNB_Soc1_2_2H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.2.2 Internal Hygiene - Air Change Frequency */
class Soc1_2_2
{
public:

	/*! Basic parameters. */
	enum para_t {
		/*! PercentageOfMechanicalAeration */
		P_CurrentValue_soc1_2_2_1_a_PercentageOfMechanicalAeration,		// Keyword: CurrentValue_soc1_2_2_1_a_PercentageOfMechanicalAeration		[---]		// ToDo Einheit % SO oder anders?
		/*! ZonalStreamingSimulationResult */
		P_CurrentValue_soc1_2_2_1_a_ZonalStreamingSimulationResult,		// Keyword: CurrentValue_soc1_2_2_1_a_ZonalStreamingSimulationResult		[-]			// ToDo Einheit ppm
		NUM_P
	};

	/*! Soc1.2.2.1.a Air Change Frequency Office Education Hotel Assembly Healthcare */
	enum IH_AirChangeFrequencyOfficeEducationHotelAssemblyHealthcare {				// max +50
		IHACFOEHAH_RatioSubmitted,									// Keyword: IHACFOEHAH_RatioSubmitted
		IHACFOEHAH_ZonalStreamingSimulation,						// Keyword: IHACFOEHAH_ZonalStreamingSimulation
		IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat3,					// Keyword: IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat3
		IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat2,					// Keyword: IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat2
		IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat1,					// Keyword: IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat1
		IHACFOEHAH_ManualNoCertification,							// Keyword: IHACFOEHAH_ManualNoCertification
		IHACFOEHAH_ManualObservationOfASR3_6,						// Keyword: IHACFOEHAH_ManualObservationOfASR3_6
		IHACFOEHAH_ManualObservationOfASR3_6AndSensorMonitoring,	// Keyword: IHACFOEHAH_ManualObservationOfASR3_6AndSensorMonitoring
		IHACFOEHAH_ZonalDIN_EN_16798_1_Kat4,						// Keyword: IHACFOEHAH_ZonalDIN_EN_16798_1_Kat4
		IHACFOEHAH_ZonalDIN_EN_16798_1_Kat3,						// Keyword: IHACFOEHAH_ZonalDIN_EN_16798_1_Kat3
		IHACFOEHAH_ZonalDIN_EN_16798_1_Kat1and2,					// Keyword: IHACFOEHAH_ZonalDIN_EN_16798_1_Kat1and2
		NUM_IHACFOEHAH
	};
	
	/*! Soc1.2.2.1.b Air Change Frequency ShoppingCenter CommercialBuilding ConvenienceStore */
	enum IH_AirChangeFrequencyShoppingCenterCommercialBuildingConvenienceStore {	// max +70
		IHACFSCCBCS_DIN_EN_16798_1_Kat4_CBCSandSCShops,				// Keyword: IHACFSCCBCS_DIN_EN_16798_1_Kat4_CBCSandSCShops
		IHACFSCCBCS_DIN_EN_16798_1_Kat3_CBCSandSCShops,				// Keyword: IHACFSCCBCS_DIN_EN_16798_1_Kat3_CBCSandSCShops
		IHACFSCCBCS_DIN_EN_16798_1_Kat1and2_CBCSandSCShops,			// Keyword: IHACFSCCBCS_DIN_EN_16798_1_Kat1and2_CBCSandSCShops
		IHACFSCCBCS_DIN_EN_16798_1_Kat4_SCMalls,					// Keyword: IHACFSCCBCS_DIN_EN_16798_1_Kat4_SCMalls
		IHACFSCCBCS_DIN_EN_16798_1_Kat3_SCMalls,					// Keyword: IHACFSCCBCS_DIN_EN_16798_1_Kat3_SCMalls
		IHACFSCCBCS_DIN_EN_16798_1_Kat1and2_SCMalls,				// Keyword: IHACFSCCBCS_DIN_EN_16798_1_Kat1and2_SCMalls
		NUM_IHACFSCCBCS
	};
	
	/*! Soc1.2.2.1.c Air Change Frequency Residential */
	enum IH_AirChangeFrequencyResidential {							// max +50
		IHACFR_AerationMeasuresAccordingToLevelsFL,					// Keyword: IHACFR_AerationMeasuresAccordingToLevelsFL
		IHACFR_AerationMeasuresAccordingToLevelsRL,					// Keyword: IHACFR_AerationMeasuresAccordingToLevelsRL
		IHACFR_AerationMeasuresAccordingToLevelsNL,					// Keyword: IHACFR_AerationMeasuresAccordingToLevelsNL
		NUM_IHACFR
	};
	
	/*! Soc1.2.2.1.d Air Change Frequency Logicstics and Production */
	enum IH_AirChangeLogisticsAndProduction {						// max +50
		IHACFLP_NoCertification,									// Keyword: IHACFLP_NoCertification
		IHACFLP_ObservationOfASR3_6,								// Keyword: IHACFLP_ObservationOfASR3_6
		IHACFLP_NeedbasedAeration,									// Keyword: IHACFLP_NeedbasedAeration
		IHACFLP_AerationExceedsMinimumRateByAtLeast20Percent,		// Keyword: IHACFLP_AerationExceedsMinimumRateByAtLeast20Percent
		NUM_IHACFLP
	};
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_2_2(){}

	Soc1_2_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag					m_flag_IHACFOEHAH[NUM_IHACFOEHAH];					// XML:E
	/*! List of flags. */
	IBK::Flag					m_flag_IHACFSCCBCS[NUM_IHACFSCCBCS];				// XML:E
	/*! List of flags. */
	IBK::Flag					m_flag_IHACFR[NUM_IHACFR];							// XML:E
	/*! List of flags. */
	IBK::Flag					m_flag_IHACFLP[NUM_IHACFLP];						// XML:E

	IBK::Parameter				m_para[NUM_P];										// XML:E
	
	Utilities::UsageType		m_usageType;

};

} // namespace DGNB

#endif // DGNB_Soc1_2_2H
