#ifndef DGNB_Eco2_4_7H
#define DGNB_Eco2_4_7H

#include "DGNB_Utilities.h"

namespace DGNB {

/*! Eco2.4.7 Agenda 2030 Bonuses */
class Eco2_4_7 {

public:

	/*! Eco2.4.7.1 Expandability */
	enum A2030_Expandability {										// max +5
		A2030E_Concept,												// Keyword: A2030E_Concept
		NUM_BRLCCC
	};

	/*! Eco2.4.7.2 Impulse/Attractor */
	enum A2030_ImpulsAttractor {
		A2030IA_AddressEffect,										// Keyword: A2030IA_AddressEffect
		NUM_A2030IA
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Eco2_4_7(){}

	Eco2_4_7(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double scoreBonus();


	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag			m_flag_A2030E[NUM_BRLCCC];					// XML:E
	/*! List of flags. */
	IBK::Flag			m_flag_A2030IA[NUM_A2030IA];				// XML:E

	Utilities::UsageType			m_usageType;

}; // Eco 2.4.7

} // namespace DGNB

#endif // DGNB_Eco2_4_7H
