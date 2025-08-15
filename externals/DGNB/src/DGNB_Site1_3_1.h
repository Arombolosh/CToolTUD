#ifndef DGNB_Site1_3_1H
#define DGNB_Site1_3_1H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"

namespace DGNB {

/*! Site1.3.1 Motorised Individual Transport */
class Site1_3_1
{
public:

	/*! Site 1.3.1.1 Surroundings */
	enum MIT_Surroundings {																															// max +10
		MITS_ConnectionToBundesstrasseA_Road,																										// Keyword: MITS_ConnectionToBundesstrasseA_Road
		MITS_ConnectionToFreeway,																													// Keyword: MITS_ConnectionToFreeway
		MITS_ConnectionToMainStreet,																												// Keyword: MITS_ConnectionToMainStreet
		NUM_MITS
	};

	/*! Site 1.3.1.2 Relation To Building */
	enum MIT_RelationToBuilding {																													// max +10
		MITRB_BuildingParkingSpacesAreIntegratedIntoSuperordinateParkingConceptOfParkingAreasUsedMostlyByUserGroupsOfSeveralBuildingsInTheQuarter,	// Keyword: MITRB_BuildingParkingSpacesAreIntegratedIntoSuperordinateParkingConceptOfParkingAreasUsedMostlyByUserGroupsOfSeveralBuildingsInTheQuarter
		NUM_MITRB
	};
	
	
	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Site1_3_1(){}

	Site1_3_1(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_MITS[NUM_MITS];			// XML:E
	/*! List of flags. */
	IBK::Flag						m_flag_MITRB[NUM_MITRB];		// XML:E

	Utilities::UsageType			m_usageType;
};

} // namespace DGNB

#endif // DGNB_Site1_3_1H
