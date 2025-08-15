#include "DGNB_Env2_2_1.h"

namespace DGNB {

double DGNB::Env2_2_1::score() {
	double env2_2_1 = 0;
	double dwdwwvSCWUCounter = 0, dwdwwvUSCCounter = 0;

	/*! Env2_2_1_1: concept for water usage - superordinate concept */
	for(unsigned int i=0; i<NUM_DWDWWVSCWU; ++i)
		dwdwwvSCWUCounter += (m_flag_DWDWWVSCWU[(DWDWWV_SuperordinateConceptForWaterUsage)i].isEnabled() ? 1 : 0);

	/*! Env2_2_1_2: concept for water usage - providing updates to superordinate concept */
	for(unsigned int i=0; i<NUM_DWDWWVUSC; ++i)
		dwdwwvUSCCounter += (m_flag_DWDWWVUSC[(DWDWWV_UpdatesToSuperordinateConcept)i].isEnabled() ? 1 : 0);

	// summing up points
	if (dwdwwvSCWUCounter > 5)		  // including admission during early planning stage as condition
		env2_2_1 += 7;

	if (dwdwwvUSCCounter > 1)		   // including continuous updates as condition
		env2_2_1 += 3;

	return env2_2_1;
}   // Env2.2.1



} // namespace DGNB
