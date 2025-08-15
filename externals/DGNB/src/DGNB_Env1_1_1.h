#ifndef DGNB_Env1_1_1H
#define DGNB_Env1_1_1H

#include "DGNB_Utilities.h"

namespace DGNB {
	
/*! Integration of life cycle CO2 balance into the planning process */
class Env1_1_1 {			
	public:
	// max +10 pts
	/*! early stage: operating evaluation */
	enum CO2EarlyStage_OperatingEvaluation{							// evaluation of 2+ variants: +5
		CO2ESOE_HighEnergyStandard,									// Keyword: CO2ESOE_HighEnergyStandard
		CO2ESOE_CO2NeutralOperation,								// Keyword: CO2ESOE_CO2NeutralOperation
		CO2ESOE_PreparedCO2NeutralOperation,						// Keyword: CO2ESOE_PreparedCO2NeutralOperation
		CO2ESOE_SufficiencyStandard,								// Keyword: CO2ESOE_SufficiencyStandard
		NUM_CO2ESOE
	};


	/*! early stage: further variants */
	enum CO2EarlyStage_FurtherVariants{								// evaluation of 3+ variants: +5
		CO2ESFV_MaterialOptimization,								// Keyword: CO2ESFV_MaterialOptimization
		CO2ESFV_CO2ReducedMaterials,								// Keyword: CO2ESFV_CO2ReducedMaterials
		CO2ESFV_LowTech,											// Keyword: CO2ESFV_LowTech
		CO2ESFV_CircularDesign,										// Keyword: CO2ESFV_CircularDesign
		CO2ESFV_Longevity,											// Keyword: CO2ESFV_Longevity
		NUM_CO2ESFV
	};


	/*! planning stage: operating evaluation */
	enum CO2PlanningStage_OperatingEvaluation{						// evaluation of 2+ variants: +5
		CO2PSOE_ElevatedEnergeticStandard,							// Keyword: CO2PSOE_ElevatedEnergeticStandard
		CO2PSOE_NettoGreenhouseGasNeutralOperation,					// Keyword: CO2PSOE_NettoGreenhouseGasNeutralOperation
		CO2PSOE_SufficiencyStandard,								// Keyword: CO2PSOE_SufficiencyStandard
		NUM_CO2PSOE
	};


	/*! planning stage: further variants */
	enum CO2PlanningStage_FurtherVariants{							// evaluation of 3+ variants: +5
		CO2PSFV_MaterialOptimization,								// Keyword: CO2PSFV_MaterialOptimization
		CO2PSFV_CO2ReducedMaterials,								// Keyword: CO2PSFV_CO2ReducedMaterials
		CO2PSFV_LowTech,											// Keyword: CO2PSFV_LowTech
		CO2PSFV_CircularDesign,										// Keyword: CO2PSFV_CircularDesign
		CO2PSFV_Longevity,											// Keyword: CO2PSFV_Longevity
		NUM_CO2PSFV
	};


	/*! planning stage: emission optimization */
	enum CO2PlanningStage_EmissionOptimization{						// evaluation: +2.5
		CO2PSEO_LogisticsAndSiteOperationsOptimizedForEmission,		// Keyword: CO2PSEO_LogisticsAndSiteOperationsOptimizedForEmission
		NUM_CO2PSEO
	};



	/*! Climate Protection through integration of a preexisting building for 50+% of new buildings floor area */
	enum CO2Agenda2030_IntegrationOfPreexistingBuilding {
		CO2A2030IPB_IntegrationOfPreexistingBuilding,				// Keyword: CO2A2030IPB_IntegrationOfPreexistingBuilding
		NUM_CO2A2030IPB
	};

	/*! Optimization of Mobility for Emission, Submission of calculation results */
	enum CO2Agenda2030MobilityOptimization {
		CO2A2030MO_ForEmission,										// Keyword: CO2A2030MO_ForEmission
		NUM_CO2A2030MO
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env1_1_1(){}

	Env1_1_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	/*! Current points of this single criteria. */
	double score();
	double scoreBonus();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_ESOE[NUM_CO2ESOE];					// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_ESFV[NUM_CO2ESFV];					// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_PSOE[NUM_CO2PSOE];					// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_PSFV[NUM_CO2PSFV];					// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_PSEO[NUM_CO2PSEO];					// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_A2030IPB[NUM_CO2A2030IPB];			// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_A2030MO[NUM_CO2A2030MO];				// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // Env1_1_1H
