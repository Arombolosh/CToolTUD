#ifndef DGNB_Soc1_4_1H
#define DGNB_Soc1_4_1H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Soc1.4.1 Daylight Availability Entire Building */
class Soc1_4_1
{
public:

	/*! Basic parameters. */
	enum para_t {
		/*! Soc1_4_1ET */
		P_CurrentValue_soc1_4_1ET,												// Keyword: CurrentValue_soc1_4_1ET									[-]						// ToDo Einheit lx
		/*! Soc1_4_1D */
		P_CurrentValue_soc1_4_1D,												// Keyword: CurrentValue_soc1_4_1D									[---]					// ToDo Einheit % SO oder anders?
		/*! Soc1_4_1LitAreaPercentageOfUsableArea */
		P_CurrentValue_soc1_4_1LitAreaPercentageOfUsableArea,					// Keyword: CurrentValue_soc1_4_1LitAreaPercentageOfUsableArea		[---]					// ToDo Einheit % SO oder anders?
		NUM_P
	};

	/*! Soc1.4.1a Daylight Supply - Office, Education, Assembly, Residential, Hotel, Healthcare, Production */
	enum DS_OfficeEducationAssemblyResidentialHotelHealthcareProduction {		// max +20 / +40 depending on usage Type
		DSOEARHHcP_ResultsSubmitted,											// Keyword: DSOEARHHcP_ResultsSubmitted
		DSOEARHHcP_HotelAlternativeCertification,								// Keyword: DSOEARHHcP_HotelAlternativeCertification
		NUM_DSOEARHHcP
	};

	/*! Soc1.4.1a Daylight Supply - ConvenienceStore ShoppingCenter CommercialBuilding */
	enum DS_ConvenienceStoreShoppingCenterCommercialBuilding {					// max +20 / +40 depending on usage Type
		DSOCSSCCB_ResultsSubmitted,												// Keyword: DSOCSSCCB_ResultsSubmitted
		DSOCSSCCB_ConvenienceStoreEqualDistributionOfCeilingLight,				// Keyword: DSOCSSCCB_ConvenienceStoreEqualDistributionOfCeilingLight
		NUM_DSOCSSCCB
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Soc1_4_1(){}

	Soc1_4_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag					m_flag_DSOEARHHcP[NUM_DSOEARHHcP];						// XML:E
	/*! List of flags. */
	IBK::Flag					m_flag_DSOCSSCCB[NUM_DSOCSSCCB];						// XML:E

	IBK::Parameter				m_para[NUM_P];											// XML:E
	
	Utilities::UsageType		m_usageType;
	
};

} // namespace DGNB

#endif // DGNB_Soc1_4_1
