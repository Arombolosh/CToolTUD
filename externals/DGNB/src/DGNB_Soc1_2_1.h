#ifndef DGNB_Soc1_2_1H
#define DGNB_Soc1_2_1H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.2.1 Interior Hygiene - volatile organic components */
class Soc1_2_1
{
public:

	/*! Basic parameters. */
	enum para_t {
		/*! Soc1_2_TVOC */
		P_CurrentValue_soc1_2_TVOC,							// Keyword: CurrentValue_soc1_2_TVOC							[kg/m3]		// TODO Einheit µg
		/*! Soc1_2_Formaldehyde */
		P_CurrentValue_soc1_2_Formaldehyde,					// Keyword: CurrentValue_soc1_2_Formaldehyde					[kg/m3]		// TODO Einheit µg
		/*! Soc1_2_TVOCRenterPromise */
		P_CurrentValue_soc1_2_TVOCRenterPromise,			// Keyword: CurrentValue_soc1_2_TVOCRenterPromise				[kg/m3]		// TODO Einheit µg
		/*! Soc1_2_FormaldehydeRenterPromise */
		P_CurrentValue_soc1_2_FormaldehydeRenterPromise,	// Keyword: CurrentValue_soc1_2_FormaldehydeRenterPromise		[kg/m3]		// TODO Einheit µg
		NUM_P
	};

	/*! Soc1.2.1.1 Measuring of TVOC */
	enum IHTVOC_Measuring_OfficeEducationHotelAssemblyHealthcareResidentialLogisticsProduction {	// max +50 / +70 depending on usageType
		IHTVOCM_TVOCResultsSubmitted,												// Keyword: IHTVOCM_TVOCResultsSubmitted
		IHTVOCM_FormaldehydeResultsSubmitted,										// Keyword: IHTVOCM_FormaldehydeResultsSubmitted
		IHTVOCM_AlternativeCertification,											// Keyword: IHTVOCM_AlternativeCertification
		IHTVOCM_ResidentialDegreeOfRentExtensionHigherThan80Percent,				// Keyword: IHTVOCM_ResidentialDegreeOfRentExtensionHigherThan80Percent
		IHTVOCM_LP_DeclarationAndVerificationOfProductsForFloors,					// Keyword: IHTVOCM_LP_DeclarationAndVerificationOfProductsForFloors
		IHTVOCM_LP_DeclarationAndVerificationOfProductsForAllInteriorSurfaces,		// Keyword: IHTVOCM_LP_DeclarationAndVerificationOfProductsForAllInteriorSurfaces
		NUM_IHTVOCM
	};
	
	enum IHTVOC_ShoppingCenterCommercialBuildingConvenienceStore {
		IHTVOCSCCBCS_OnlyLowEmissionMaterialsUsed,									// Keyword: IHTVOCSCCBCS_OnlyLowEmissionMaterialsUsed
		IHTVOCSCCBCS_RentersHoldUpEnv1_2QS3In50PercentOfSpaces,						// Keyword: IHTVOCSCCBCS_RentersHoldUpEnv1_2QS3In50PercentOfSpaces
		IHTVOCSCCBCS_RentersHoldUpEnv1_2QS3In80PercentOfSpaces,						// Keyword: IHTVOCSCCBCS_RentersHoldUpEnv1_2QS3In80PercentOfSpaces
		NUM_IHTVOCSCCBCS
	};
	
	/*! Soc1.2.1.2 Agenda 2030 Bonus - Interior Air Toxic Matter Reduction, Health and Comfort */
	enum IHTVOC_Agenda2030InteriorAirToxicMatterReductionHealthAndComfort {
		IHTVOCA2030IATMRHC_NonSmokerProtection,										// Keyword: IHTVOCA2030IATMRHC_NonSmokerProtection
		IHTVOCA2030IATMRHC_RespirableDustPrevention,								// Keyword: IHTVOCA2030IATMRHC_RespirableDustPrevention
		NUM_IHTVOCA2030IATMRHC
	};
	
	/*! Soc1.2.1.3 Woodwork Bonus Points */
	enum IHTVOC_WoodworkBonus {
		IHTVOCWWB_WoodworkApplicable,												// Keyword: IHTVOCWWB_WoodworkApplicable
		IHTVOCWWB_LimoneneBelowNOW,													// Keyword: IHTVOCWWB_LimoneneBelowNOW
		IHTVOCWWB_AlphaPineneBelowNOW,												// Keyword: IHTVOCWWB_AlphaPineneBelowNOW
		NUM_IHTVOCWWB
	};
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_2_1(){}

	Soc1_2_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();
	bool minimumRequirementsMet();
	bool platinumRequirementsMet();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag					m_flag_IHTVOCM[NUM_IHTVOCM];							// XML:E
	/*! List of flags. */
	IBK::Flag					m_flag_IHTVOCSCCBCS[NUM_IHTVOCSCCBCS];				// XML:E
	/*! List of flags. */
	IBK::Flag					m_flag_IHTVOCA2030IATMRHC[NUM_IHTVOCA2030IATMRHC];	// XML:E
	/*! List of flags. */
	IBK::Flag					m_flag_IHTVOCWWB[NUM_IHTVOCWWB];					// XML:E

	IBK::Parameter				m_para[NUM_P];										// XML:E
	
	Utilities::UsageType		m_usageType;

};

} // namespace DGNB

#endif // DGNB_Soc1_2_1
