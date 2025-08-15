#ifndef CTI_SurfaceH
#define CTI_SurfaceH

#include <IBKMK_Polygon3D.h>

#include <QJsonObject>

namespace CTI {

const unsigned int INVALID_ID = std::numeric_limits<unsigned int>::max();

class Surface
{
public:

	enum Type {
		T_Wall,
		T_Ceiling,
		T_Floor,
		NUM_T
	};

	struct Layer{

		bool isValid(){
			if(m_density < 0.1)
				return false;
			if(m_specHeat < 200)
				return false;
			if(m_thickness <=0)
				return false;
			return true;
		}

		std::string m_name;
		double		m_conductivity;				// W/mK
		double		m_density;					// kg/m3
		double		m_specHeat;					// J/kgK
		double		m_thickness;				// m
	};

	struct Interface{
		double		m_heatConvectionCoeff = 0;	// W/m2K
		double		m_emissivity = 0;			// -
		double		m_shortWaveAbsorption = 0;	// -
		double		m_outsideTemperature;		// C
		bool		m_hasOutsideTemperature = false;
		int			m_type;						// 0 -> Außenluft; 1 -> Erdreich; 2 -> innen; 3 -> None
	};

	struct SubSurface{

		bool isValid();

		std::string			m_name;
		IBKMK::Polygon3D	m_polygon;
		double				m_uValue;				// W/m2K
		double				m_shgc;
		double				m_conductivityFrame;	// W/mK
		double				m_thicknessFrame;		// m
		double				m_frameFraction;
	};

	void read(const QJsonObject &data, Type type = T_Wall);

	bool isValid();

	unsigned int					m_id;
	unsigned int					m_connectedID = INVALID_ID;
	std::string						m_name;
	IBKMK::Polygon3D				m_polygon;
	std::string						m_uuid;

	Interface						m_interfaceA;
	Interface						m_interfaceB;

	std::vector<Layer>				m_layers;

	std::vector<SubSurface>			m_subSurfaces;
};

} // namespace CTI

#endif // CTI_SurfaceH
