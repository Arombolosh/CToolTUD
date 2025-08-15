#ifndef DGNB_Pro2_5_2H
#define DGNB_Pro2_5_2H

#include <IBK_Flag.h>
#include "DGNB_Utilities.h"
#include "DGNB_CodeGenMacros.h"

namespace DGNB {

class Pro2_5_2
{
public:

	/*! Pro2.5.2 Maintenance, Inspection, Operation and Service Instructions */
	enum MaintenanceInspectionOperationAndServiceInstructions {								// max +20
		MIOSI_CreationOfInstructionsAndHandoverToHiredServiceCompaniesOrConductors,			// Keyword: MIOSI_CreationOfInstructionsAndHandoverToHiredServiceCompaniesOrConductors
		MIOSI_CreationOfMaintenanceAndUpkeepPlansForHighCareElementsOfCostGroups300And400,	// Keyword: MIOSI_CreationOfMaintenanceAndUpkeepPlansForHighCareElementsOfCostGroups300And400
		MIOSI_IncorporationOfGuidelinesForSustainableBuildingOperation,						// Keyword: MIOSI_IncorporationOfGuidelinesForSustainableBuildingOperation
		NUM_MIOSI
	};
	

	// *** PUBLIC MEMBER FUNCTIONS ***

	DGNB_READWRITE

	Pro2_5_2(){}

	Pro2_5_2(const Utilities::UsageType &ut):
		m_usageType(ut)
	{}

	double score();

	// *** PUBLIC MEMBER VARIABLES ***

	/*! List of flags. */
	IBK::Flag						m_flag_MIOSI[NUM_MIOSI];								// XML:E

	Utilities::UsageType			m_usageType;


};

} // namespace DGNB

#endif // DGNB_Pro2_5_2H
