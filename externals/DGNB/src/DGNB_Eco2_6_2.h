#ifndef DGNB_Eco2_6_2H
#define DGNB_Eco2_6_2H

#include "DGNB_Utilities.h"

namespace DGNB {

/*! Eco2.6.2 Adaptation to Climate Change */
class Eco2_6_2 {

public:

	/*! Eco2.6.2.1 Quantitative Evaluation of Measures to adapt to climate change and risk reduction */
	enum ACC_QuantitativeEvaluationOfMeasures {										// max +30
		ACCQEM_RecommendedMeasuresToReduceClimateRisksImplemented,					// Keyword: ACCQEM_RecommendedMeasuresToReduceClimateRisksImplemented
		//platin req:
		ACCQEM_MeasuresImproveResilienceAndInlcudeReductionOfAllHighRiskFactors,	// Keyword: ACCQEM_MeasuresImproveResilienceAndInlcudeReductionOfAllHighRiskFactors
		ACCQEM_MeasuresFurtherIncludeReductionOfAllModerateRiskFactors,				// Keyword: ACCQEM_MeasuresFurtherIncludeReductionOfAllModerateRiskFactors
		ACCQEM_MeasuresReduceProbableFutureRisksOnSite,								// Keyword: ACCQEM_MeasuresReduceProbableFutureRisksOnSite
		NUM_ACCQEM
	};

	/*! Eco2.6.2.2 Details on Quality of implemented adaptation measures */
	enum ACC_QualityOfImplementedAdaptationMeasures {				// max +15 (5,5,3,5)
		ACCQIAM_PreferentialUseOfNaturalAndPassiveSolutions,		// Keyword: ACCQIAM_PreferentialUseOfNaturalAndPassiveSolutions
		ACCQIAM_MeasuresInAccordanceWithLocalRegionalPlans,			// Keyword: ACCQIAM_MeasuresInAccordanceWithLocalRegionalPlans
		ACCQIAM_MeasuresInAccordanceWithNationalStrategy,			// Keyword: ACCQIAM_MeasuresInAccordanceWithNationalStrategy
		ACCQIAM_SurveillanceOfImplementedOrPreparedMeasures,		// Keyword: ACCQIAM_SurveillanceOfImplementedOrPreparedMeasures
		ACCQIAM_RegulationOfRemedialMeasures,						// Keyword: ACCQIAM_RegulationOfRemedialMeasures
		NUM_ACCQIAM
	};

	/*! Eco2.6.2.3 general resilience to elemental damages */
	enum ACC_GeneralResilienceToElementalDamages {					// max +15
		//min req:
		ACCGRED_EssentialMeasuresTaken,								// Keyword: ACCGRED_EssentialMeasuresTaken
		ACCGRED_GeneralResilienceExists,							// Keyword: ACCGRED_GeneralResilienceExists
		NUM_ACCGRED
	};

	/*! Eco2.6.2.4 Agenda 2030 Bonus Heat Load */
	enum ACC_Agenda2030HeadLoad {									// max +5
		ACCA2030HL_ProbableHighHeatLoad,							// Keyword: ACCA2030HL_ProbableHighHeatLoad
		ACCA2030HL_MeasuresTakenToReduceHeatLoadRisksToHealth,		// Keyword: ACCA2030HL_MeasuresTakenToReduceHeatLoadRisksToHealth
		NUM_ACCA2030HL
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco2_6_2(){}

	Eco2_6_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();

	bool minimumRequirementsMet();
	bool platinumRequirementsMet();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_ACCQEM[NUM_ACCQEM];					// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_ACCQIAM[NUM_ACCQIAM];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_ACCGRED[NUM_ACCGRED];				// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_ACCA2030HL[NUM_ACCA2030HL];			// XML:E

	Utilities::UsageType			m_usageType;

}; // Eco 2.6.2

} // namespace DGNB

#endif // DGNB_Eco2_6_2H
