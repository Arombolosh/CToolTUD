#include "DGNB_Env1_3_1.h"

namespace DGNB {

double DGNB::Env1_3_1::score() {
	double rurpeSCDCounter = 0, rurpeRURPCounter = 0, rurpeRUREDCounter = 0;
	double env1_3_1 = 0;		// max 20

	/*! responsible usage of resources in planning and execution */
	for(unsigned int i=0; i<NUM_RURPESCD; ++i)
		rurpeSCDCounter += (m_flag_RURPESCD[(RURPE_SupplyChainDiligence)i].isEnabled() ? 1 : 0);

	/*! responsible usage of resources in planning and execution */
	for(unsigned int i=0; i<NUM_RURPERURP; ++i)
		rurpeRURPCounter += (m_flag_RURPERURP[(RURPE_ResponsibleUsageOfResourcesInPlanning)i].isEnabled() ? 1 : 0);

	/*! responsible usage of resources in planning and execution */
	for(unsigned int i=0; i<NUM_RURPERURED; ++i)
		rurpeRUREDCounter += (m_flag_RURPERURED[(RURPE_ResponsibleUsageOfResourcesInExecutionAndDocumentation)i].isEnabled() ? 1 : 0);


	// summing up points for Env1_3_1
	if (rurpeSCDCounter > 0)
		env1_3_1 += 5;

	if (rurpeRURPCounter > 0)
		env1_3_1 += 5;

	if (rurpeRUREDCounter > 0)
		env1_3_1 += 10;
	// points can not exceed cap of 20

	return env1_3_1;
}  // Env1.3.1



} // namespace DGNB
