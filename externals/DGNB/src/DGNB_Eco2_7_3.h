#ifndef DGNB_Eco2_7_3H
#define DGNB_Eco2_7_3H

#include "DGNB_Utilities.h"

namespace DGNB {

/*! Eco2.7.3 Planning Phase With BIM */
class Eco2_7_3 {

public:

	/*! Eco2.7.3.1 Preparation of Planning with BIM */
	enum PPBIM_Preparation {										// max +0/10
		PPBIMP_CalculationByBGFSmallerThan5000m2Method,				// Keyword: PPBIMP_CalculationByBGFSmallerThan5000m2Method
		PPBIMP_UseOfSharedDataEnvironment,							// Keyword: PPBIMP_UseOfSharedDataEnvironment
		PPBIMP_NecessaryBasicDocuments,								// Keyword: PPBIMP_NecessaryBasicDocuments
		PPBIMP_BIMCoordinatorSurveilingModelQuality,				// Keyword: PPBIMP_BIMCoordinatorSurveilingModelQuality
		// BAP / BEP: BIM Execution Plan
		PPBIMP_CompetenceCheckAndCoordinationOfBEP,					// Keyword: PPBIMP_CompetenceCheckAndCoordinationOfBEP
		PPBIMP_BIMInformationRequirementsAndGoalsCommunicated,		// Keyword: PPBIMP_BIMInformationRequirementsAndGoalsCommunicated
		NUM_PPBIMP
	};

	/*! Eco2.7.3.2 Creation of Planning with BIM */
	enum PPBIM_Creation {											// max +0/+6
		PPBIMC_CalculationByBGFSmallerThan5000m2Method,				// Keyword: PPBIMC_CalculationByBGFSmallerThan5000m2Method
		PPBIMC_Level0to1_CAD3D,										// Keyword: PPBIMC_Level0to1_CAD3D
		PPBIMC_Level2_BIM4to5D,										// Keyword: PPBIMC_Level2_BIM4to5D
		PPBIMC_Level3_IntegratedBIM6to7D,							// Keyword: PPBIMC_Level3_IntegratedBIM6to7D
		NUM_PPBIMC
	};

	/*! Eco2.7.3.3 Sustanability Optimisation with BIM */
	enum PPBIM_SustainabilityOptimisationWithBIM {					// max +0/+2
		PPBIMSO_CalculationByBGFSmallerThan5000m2Method,			// Keyword: PPBIMSO_CalculationByBGFSmallerThan5000m2Method
		PPBIMSO_VariantsCalculatedAndDocumented,					// Keyword: PPBIMSO_VariantsCalculatedAndDocumented
		NUM_PPBIMSO
	};

	/*! Eco2.7.3.4 Circular Economy Bonus BIM2FM Operator Concept */
	enum PPBIM_CircularEconomyBIM2FMOperatorConcept {				// max +0/10
		PPBIMCEBIM2FMOC_SustainableOperatorConcept,					// Keyword: PPBIMCEBIM2FMOC_SustainableOperatorConcept
		NUM_PPBIMCEBIM2FMOC
	};

	/*! Eco2.7.3.5 Agenda 2030 Bonus Sustainability Check */
	enum PPBIM_Agenda2030SustainabilityCheck {						// max +0/10
		PPBIMA2030SC_ModelBasedBuildingSustainabilityCheckConducted,// Keyword: PPBIMA2030SC_ModelBasedBuildingSustainabilityCheckConducted
		NUM_PPBIMA2030SC
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco2_7_3(){}

	Eco2_7_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag			m_flag_PPBIMP[NUM_PPBIMP];					// XML:E
	/*! List of flags. */
	IBK::Flag			m_flag_PPBIMC[NUM_PPBIMC];					// XML:E
	/*! List of flags. */
	IBK::Flag			m_flag_PPBIMSO[NUM_PPBIMSO];				// XML:E
	/*! List of flags. */
	IBK::Flag			m_flag_PPBIMCEBIM2FMOC[NUM_PPBIMCEBIM2FMOC];// XML:E
	/*! List of flags. */
	IBK::Flag			m_flag_PPBIMA2030SC[NUM_PPBIMA2030SC];		// XML:E

	Utilities::UsageType			m_usageType;

}; // Eco 2.7.3

} // namespace DGNB

#endif // DGNB_Eco2_7_3H
