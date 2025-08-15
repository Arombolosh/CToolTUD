#ifndef DGNB_Eco2_4_3H
#define DGNB_Eco2_4_3H

#include "DGNB_Utilities.h"

namespace DGNB {
/*! Eco2.4.3 Degree of Use or Tenancy at Time of Completion */
class Eco2_4_3	// max +10
{
public:
	/*! Basic parameters. */
	enum para_t {
		/*! DegreeOfUseOrTenancy */
		P_CurrentValue_eco2_4_3DegreeOfUseOrTenancy,					// Keyword: CurrentValue_eco2_4_3DegreeOfUseOrTenancy		[---]	// ToDo Einheit % SO oder anders?
		NUM_P
	};

	/*! Eco2.4.3.1 Degree of Use or Tenancy */
	enum DUTTC_DegreeOfUseOrTenancy {									// not for HC: max +10
		DUTTCDUT_ResultsSubmitted,										// Keyword: DUTTCDUT_ResultsSubmitted
		NUM_DUTTCDUT
	};

	/*! Eco2.4.3.2 Circular Economy Bonus - Users and Tenants */
	enum DUTTC_CircularEconomyUsersAndTenants {							// max +10
		DUTTCCEUT_AtLeastOneUserOrTenantContributesToCircularEconomy,	// Keyword: DUTTCCEUT_AtLeastOneUserOrTenantContributesToCircularEconomy
		NUM_DUTTCCEUT
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco2_4_3(){}

	Eco2_4_3(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();
	double scoreBonus();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_DUTTCDUT[NUM_DUTTCDUT];		// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_DUTTCCEUT[NUM_DUTTCCEUT];	// XML:E

	IBK::Parameter					m_para[NUM_P];						// XML:E

	Utilities::UsageType			m_usageType;

}; // Eco 2.4.3

} // namespace DGNB

#endif // DGNB_Eco2_4_3H
