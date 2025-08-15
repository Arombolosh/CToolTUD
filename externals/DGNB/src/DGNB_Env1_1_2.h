#ifndef DGNB_Env1_1_2H
#define DGNB_Env1_1_2H
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Reference Values of life cycle CO2 balance */
class Env1_1_2 {													//max +100 pts
	public:

	/*! Basic parameters. */
	enum para_t {
		/*! RefEnv1_1_2_2_1 */
		P_RefEnv1_1_2_2_1,					// Keyword: RefEnv1_1_2_2_1				[-]		// ToDo Einheit kg/m2a	[kg pro m² und Jahr]
		/*! CurrentValueEnv1_1_2_2_1 */
		P_CurrentValueEnv1_1_2_2_1,			// Keyword: CurrentValueEnv1_1_2_2_1	[-]		// ToDo Einheit kg/m2a	[kg pro m² und Jahr]
		/*! RefEnv1_1_2_5_1 */
		P_RefEnv1_1_2_5_1,					// Keyword: RefEnv1_1_2_5_1				[-]		// ToDo Einheit kg/m2a	[kg pro m² und Jahr]
		/*! CurrentValueEnv1_1_2_5_1 */
		P_CurrentValueEnv1_1_2_5_1,			// Keyword: CurrentValueEnv1_1_2_5_1	[-]		// ToDo Einheit kg/m2a	[kg pro m² und Jahr]
		NUM_P
	};

	/*! Disclosure of Life Cycle Balances for CO2 and non-renewable primary energy */
	// ENV1.1.2.1.1
	enum LCCO2_DisclosureOfLifeCycleBalances{						// evaluation +5
		LCCO2Disc_GreenHouseGasBalance,								// Keyword: LCCO2Disc_GreenHouseGasBalance
		LCCO2Disc_NonRenewablePrimaryEnergyBalance,					// Keyword: LCCO2Disc_NonRenewablePrimaryEnergyBalance
		NUM_LCCO2DISC
	};

	/*! Life cycle balance framework: evaluation of life cycle CO2 balance of the finished building */
	// ENV1.1.2.2.1
	enum LCCO2_InterpolationOfEvaluationResultBasedOnReferenceValue{
		LCCO2IER_ResultsSubmitted,									// Keyword: LCCO2IER_ResultsSubmitted
		NUM_LCCO2IER
	};

	/*! Agenda2030 Bonus lowest life cycle CO2 balance, life cycle climate protection agenda, and climate protection through sufficiency */
	/*! Balance Framework - lowest life cycle CO2 balance */
	// ENV1.1.2.3.1 -> all necessary data already provided in ENV1.1 2.2.1

	/*! Life cycle climate protection agenda - climate neutral building*/
	// ENV1.1.2.3.2
	enum LCCO2Agenda2030_LifeCycleClimateProtectionAgenda {
		// Agenda is a package, contains calculations to prove achieving CO2 neutral balance by year 2045 as well as accumulated GHG value of 0kg
		LCCO2A2030LCCPA_AgendaSubmitted,							// Keyword: LCCO2A2030LCCPA_AgendaSubmitted
		NUM_LCCO2A2030LCCPA
	};

	/*! climate protection through sufficiency */
	// ENV1.1.2.3.3
	enum LCCO2Agenda2030_ClimateProtectionThroughSufficiency {
		// Agenda contains quantified data to both measures taken and resulting reductions, measures taken must not overlap with other indicators within the criterion
		LCCO2A2030CPTS_AgendaSubmitted,								// Keyword: LCCO2A2030CPTS_AgendaSubmitted
		NUM_LCCO2A2030CPTS
	};

	/*! balance framework operation: climate protection agenda and net neutral greenhouse gas operation */
	// ENV1.1.2.4.1-3
	enum LCCO2BalanceFrameworkOperation_ClimateProtectionAgendaClimateNeutralOperation {	// max +15
		LCCO2BFO_ClimateProtectionAgendaClimateNeutralOperation,				// Keyword: LCCO2BFO_ClimateProtectionAgendaClimateNeutralOperation
		LCCO2BFO_AmbitiousClimateProtectionAgenda,								// Keyword: LCCO2BFO_AmbitiousClimateProtectionAgenda
		LCCO2BFO_NetGreenhouseHeutrallyClimateNeutrallyOperatedBuilding,		// Keyword: LCCO2BFO_NetGreenhouseHeutrallyClimateNeutrallyOperatedBuilding
		NUM_LCCO2BFO
	};

	/*! balance framework structure: CO2 reduced structure -> CO2 reduced construction phase */
	// ENV1.1.2.5.1
	enum LCCO2BalanceFrameworkStructure_CO2ReducedConstructionPhase {			// GWPFossil < specification values of building type
		LCCO2BFSCO2RCP_ResultsSubmitted,										// Keyword: LCCO2BFSCO2RCP_ResultsSubmitted
		NUM_LCCO2BFSCO2RCP
	};

	/*! Agenda 2030 Bonus - lowest CO2 emission during construction */
	// ENV1.1 2.5.2 -> all necessary data already provided in ENV1.1 2.5.1



	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env1_1_2(){}

	Env1_1_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	/*! Current points of this single criteria. */
	double score();
	double scoreBonus();
	bool minimumRequirementsMet();
	bool platinumRequirementsMet();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_LCCO2DISC[NUM_LCCO2DISC];							// XML:E

	/*! List of flags. */
	IBK::Flag						m_flag_LCCO2IER[NUM_LCCO2IER];								// XML:E

	/*! List of flags. */
	IBK::Flag						m_flag_LCCO2A2030LCCPA[NUM_LCCO2A2030LCCPA];				// XML:E

	/*! List of flags. */
	IBK::Flag						m_flag_LCCO2A2030CPTS[NUM_LCCO2A2030CPTS];					// XML:E

	/*! List of flags. */
	IBK::Flag						m_flag_LCCO2BFO[NUM_LCCO2BFO];								// XML:E

	/*! List of flags. */
	IBK::Flag						m_flag_LCCO2BFSCO2RCP[NUM_LCCO2BFSCO2RCP];					// XML:E

	IBK::Parameter					m_para[NUM_P];												// XML:E

	Utilities::UsageType			m_usageType;

};

} // namespace DGNB

#endif // Env1_1_2H
