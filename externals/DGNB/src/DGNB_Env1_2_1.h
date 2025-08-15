#ifndef DGNB_Env1_2_1H
#define DGNB_Env1_2_1H
#include "DGNB_Utilities.h"

namespace DGNB {
	
/*! environment-friendly materials */
class Env1_2_1 {
	public:

	/*! Basic parameters. */
	enum para_t {
		/*! EFMA2030_MeasurementsTakenForSufficientStructureNumberOfRows */
		P_EFMA2030_MeasurementsTakenForSufficientStructureNumberOfRows,	// Keyword: EFMA2030_MeasurementsTakenForSufficientStructureNumberOfRows	[-]
		/*! EFMA2030_WaivingOfUnsolveableConnectionsNumberOfRows */
		P_EFMA2030_WaivingOfUnsolveableConnectionsNumberOfRows,			// Keyword: EFMA2030_WaivingOfUnsolveableConnectionsNumberOfRows			[-]
		NUM_P
	};
	
	/*! Environment-friendly materials - part 1: all */
	// Env1.2.1.1
	enum EFM_A{
		EFMA_QS1SimplifiedDocumentation,							// Keyword: EFMA_QS1SimplifiedDocumentation
		EFMA_QS2SimplifiedDocumentation,							// Keyword: EFMA_QS2SimplifiedDocumentation
		EFMA_QS2MaterialEcologicalComponentCatalogue,				// Keyword: EFMA_QS2MaterialEcologicalComponentCatalogue
		EFMA_QS3MaterialEcologicalComponentCatalogue,				// Keyword: EFMA_QS3MaterialEcologicalComponentCatalogue
		EFMA_QS4MaterialEcologicalComponentCatalogue,				// Keyword: EFMA_QS4MaterialEcologicalComponentCatalogue
		NUM_EFMA
	};

	/*! Environment-friendly materials - part 2a: residential buildings, commercial buildings */
	// Env1.2.1.2a
	enum EFM_BResidentialCommercial{
		EFMBRC_QS1SimplifiedDocumentation,							// Keyword: EFMBRC_QS1SimplifiedDocumentation
		EFMBRC_QS2SimplifiedDocumentation,							// Keyword: EFMBRC_QS2SimplifiedDocumentation
		EFMBRC_QS2MaterialEcologicalComponentCatalogue,				// Keyword: EFMBRC_QS2MaterialEcologicalComponentCatalogue
		EFMBRC_QS3MaterialEcologicalComponentCatalogue,				// Keyword: EFMBRC_QS3MaterialEcologicalComponentCatalogue
		EFMBRC_QS4MaterialEcologicalComponentCatalogue,				// Keyword: EFMBRC_QS4MaterialEcologicalComponentCatalogue
		NUM_EFMBRC
	};

	/*! Environment-friendly materials - part 2b: shopping center */
	// Env1.2.1.2b
	enum EFM_BShoppingCenter{
		EFMBSC_QS1SimplifiedDocumentation,							// Keyword: EFMBSC_QS1SimplifiedDocumentation
		EFMBSC_QS2SimplifiedDocumentation,							// Keyword: EFMBSC_QS2SimplifiedDocumentation
		EFMBSC_QS2MaterialEcologicalComponentCatalogue,				// Keyword: EFMBSC_QS2MaterialEcologicalComponentCatalogue
		EFMBSC_QS3MaterialEcologicalComponentCatalogue,				// Keyword: EFMBSC_QS3MaterialEcologicalComponentCatalogue
		EFMBSC_QS4MaterialEcologicalComponentCatalogue,				// Keyword: EFMBSC_QS4MaterialEcologicalComponentCatalogue
		NUM_EFMBSC
	};

	// Env1.2.1.2c
	enum EFM_Agenda2030 {
		EFMA2030_1WaivingOfCrossOutCriterionQS3,					// Keyword: EFMA2030_1WaivingOfCrossOutCriterionQS3
		EFMA2030_2WaivingOfCrossOutCriterionQS4,					// Keyword: EFMA2030_2WaivingOfCrossOutCriterionQS4
		EFMA2030_MeasurementsTakenForSufficientStructure,			// Keyword: EFMA2030_MeasurementsTakenForSufficientStructure
		EFMA2030_WaivingOfUnsolveableConnections,					// Keyword: EFMA2030_WaivingOfUnsolveableConnections
		EFMA2030_AllRowsOnlyFeatureProductsOfSVHCOfMax0_1Percent,	// Keyword: EFMA2030_AllRowsOnlyFeatureProductsOfSVHCOfMax0_1Percent
		NUM_EFMA2030
	};

	/*! Extra points for realization of a cooling system that does not use halogenated of semi-halogenated cooling agents in QS 1 through 3 */
	// Env1.2.1.3
	enum EFM_ExtraPointsForQS123 {
		EFMEPQS123_RealizationOfCoolingSystemWithoutHalogenatedCoolingAgent,		// Keyword: EFMEPQS123_RealizationOfCoolingSystemWithoutHalogenatedCoolingAgent
		NUM_EFMEPQS123
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Env1_2_1(){}

	Env1_2_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();

	bool platinumRequirementsMet();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_EFMA[NUM_EFMA];						// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_EFMBRC[NUM_EFMBRC];					// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_EFMBSC[NUM_EFMBSC];					// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_EFMA2030[NUM_EFMA2030];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_EFMEPQS123[NUM_EFMEPQS123];			// XML:E

	IBK::Parameter					m_para[NUM_P];								// XML:E

	Utilities::UsageType			m_usageType;

};

} // namespace DGNB

#endif // Env1_2_1H
