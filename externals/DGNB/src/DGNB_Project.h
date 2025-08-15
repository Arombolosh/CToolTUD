#ifndef DGNB_ProjectH
#define DGNB_ProjectH

#include "DGNB_Environment.h"
#include "DGNB_Economy.h"
#include "DGNB_Socioculture.h"
#include "DGNB_Technology.h"
#include "DGNB_Process.h"
#include "DGNB_Site.h"
// #include "DGNB_Chart.h"

#include <NANDRAD_Utilities.h>
#include <IBK_StringUtils.h>

namespace DGNB {

class Project
{
public:
	Project();

	DGNB_READWRITE

	/*! Reads the project data from an XML file.
		\param filename  The full path to the project file.
	*/

	void readXML(const IBK::Path & filename);

	/*! Writes the project file to an XML file.
		\param filename  The full path to the project file.
	*/
	void writeXML(const IBK::Path & filename) const;

	void setValuesTest01();
	void totalProcess();

	void score();

	// double totalScore();
	int grading();

	Environment				m_environment;					// XML:E
	Economy					m_economy;						// XML:E
	Socioculture			m_socioculture;					// XML:E
	Technology				m_technology;					// XML:E
	Process					m_process;						// XML:E
	Site					m_site;							// XML:E

	Utilities::UsageType	m_usageType;

	// DGNB_Chart				*m_chart;
};

} // namespace DGNB

#endif // DGNB_ProjectH
