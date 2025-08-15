#ifndef DGNB_UtilitiesH
#define DGNB_UtilitiesH

#include <tinyxml.h>

#include <IBK_LinearSpline.h>
#include <IBK_Parameter.h>
#include <IBK_IntPara.h>
#include <IBK_Flag.h>
#include <IBK_Time.h>
#include <IBK_messages.h>
#include <IBK_Path.h>
#include <QDebug>
#include "DGNB_CodeGenMacros.h"


extern const char * XML_READ_ERROR;
extern const char * XML_READ_UNKNOWN_ATTRIBUTE;
extern const char * XML_READ_UNKNOWN_ELEMENT;
extern const char * XML_READ_UNKNOWN_NAME;

namespace DGNB {

class Utilities
{
public:
	enum UsageType{
		UT_Office,														// Keyword: offices
		UT_Education,													// Keyword: education
		UT_Residential,													// Keyword: residential
		UT_Hotel,														// Keyword: hotel
		UT_ConvenienceStore,											// Keyword: convenienceStore
		UT_ShoppingCenter,												// Keyword: shoppingCenter
		UT_CommercialBuilding,											// Keyword: commercialBuilding
		UT_Logistics,													// Keyword: logistics
		UT_Production,													// Keyword: production
		UT_Assembly,													// Keyword: assembly
		UT_Healthcare,													// Keyword: healthcare
		NUM_UT
	};

	/*! Attempts to read an XML text, hereby and checking if
		the top-level XML tag matches the requested tag name.
	*/
	TiXmlElement * openXMLText(const std::string & xmltext,
							   const std::string & parentXmlTag, TiXmlDocument & doc);

	/*! Reads a linear spline from XML element (with proper error handling). */
	void readLinearSplineElement(const TiXmlElement * element,
								 IBK::LinearSpline & spl, std::string & name, IBK::Unit * xunit, IBK::Unit * yunit);

	/*! Writes a linear spline into XML format.
		\code
		<IBK:LinearSpline name="MySpline">
			<X unit="m">0 1 1.4 2 </X>
			<Y unit="C">1 2 3.4 5 </Y>
		</IBK:LinearSpline>
		\endcode
	*/
	void writeLinearSplineElement(TiXmlElement * parent, const std::string & name, const IBK::LinearSpline & spl, const std::string & xunit, const std::string & yunit);

	/*! Reads an IBK::Parameter from XML element (with proper error handling). */
	static void readParameterElement(const TiXmlElement * element, IBK::Parameter & p){
		FUNCID(NANDRAD::readParameterElement);
		const TiXmlAttribute* attrib = TiXmlAttribute::attributeByName(element, "name");
		if (attrib == nullptr)
			throw IBK::Exception(IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg("Missing 'name' attribute in IBK:Parameter element."), FUNC_ID);
		const std::string & namestr = attrib->ValueStr();
		attrib = TiXmlAttribute::attributeByName(element, "unit");
		if (attrib == nullptr)
			throw IBK::Exception(IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg("Missing 'unit' attribute in IBK:Parameter element."), FUNC_ID);
		const std::string & unit = attrib->ValueStr();
		IBK::Unit u;
		try {
			u.set(unit);
		} catch (...) {
			throw IBK::Exception(IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg("Unknown/invalid unit '"+unit+"' in IBK:Parameter element."), FUNC_ID);
		}
		const char * const str = element->GetText();
		try {
			double val = IBK::string2val<double>(str);
			p.set(namestr, val, u);
		} catch (...) {
			throw IBK::Exception(IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg("Cannot read value in IBK:Parameter element."), FUNC_ID);
		}
	}

	/*! Reads an IBK::IntPara from XML element (with proper error handling). */
	void readIntParaElement(const TiXmlElement * element, IBK::IntPara & p);

	/*! Reads an IBK::Flag from XML element (with proper error handling). */
	static void readFlagElement(const TiXmlElement * element, IBK::Flag & f){
		FUNCID(NANDRAD::readParameterElement);
		const TiXmlAttribute* attrib = TiXmlAttribute::attributeByName(element, "name");
		if (attrib == nullptr)
			throw IBK::Exception(IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg("Missing 'name' attribute in IBK:Parameter element."), FUNC_ID);
		const std::string & namestr = attrib->ValueStr();

		const char * const str = element->GetText();
		try {
			bool val = IBK::string2val<bool>(str);
			f.set(namestr, val);
		} catch (...) {
			throw IBK::Exception(IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg("Cannot read value in IBK:Parameter element."), FUNC_ID);
		}
	}

	template <typename T>
	void readVector(const TiXmlElement * element, const std::string & name, std::vector<T> & vec) {
		FUNCID(NANDRAD::readVector);
		std::string text = element->GetText();
		text = IBK::replace_string(text, ",", " ");
		try {
			IBK::string2vector(text, vec);
		} catch (IBK::Exception & ex) {
			throw IBK::Exception( ex, IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
				IBK::FormatString("Error reading vector element '%1'.").arg(name) ), FUNC_ID);
		}
	}

	/*! Special implementation for double-type vectors. */
//	template <>
//	void readVector(const TiXmlElement * element, const std::string & name, std::vector<double> & vec){
//		FUNCID(NANDRAD::readVector);
//		std::string text = element->GetText();
//		text = IBK::replace_string(text, ",", " ");
//		try {
//			IBK::string2valueVector(text, vec);
//		} catch (IBK::Exception & ex) {
//			throw IBK::Exception( ex, IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
//				IBK::FormatString("Error reading vector element '%1'.").arg(name) ), FUNC_ID);
//		}
//	}


	template <typename T>
	void writeVector(TiXmlElement * parent, const std::string & name, const std::vector<T> & vec) {
		if (!vec.empty()) {
			TiXmlElement * child = new TiXmlElement(name);
			parent->LinkEndChild(child);

			std::stringstream vals;
			for (unsigned int i=0; i<vec.size(); ++i) {
				vals << vec[i];
				if (i<vec.size()-1)  vals << ",";
			}
			TiXmlText * text = new TiXmlText( vals.str() );
			child->LinkEndChild( text );
		}
	}


	template <typename T>
	T readPODAttributeValue(const TiXmlElement * element, const TiXmlAttribute * attrib) {
		FUNCID(NANDRAD::readPODAttributeValue);
		try {
			return IBK::string2val<T>(attrib->ValueStr());
		} catch (IBK::Exception & ex) {
			throw IBK::Exception( ex, IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
				IBK::FormatString("Error reading '"+attrib->NameStr()+"' attribute.") ), FUNC_ID);
		}
	}

	template <typename T>
	T readPODElement(const TiXmlElement * element, const std::string & eName) {
		FUNCID(NANDRAD::readPODElement);
		try {
			return IBK::string2val<T>(element->GetText());
		} catch (IBK::Exception & ex) {
			throw IBK::Exception( ex, IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
				IBK::FormatString("Error reading '"+eName+"' tag.") ), FUNC_ID);
		}
	}

	/*! Read an IBK:Unit tag. */
	IBK::Unit readUnitElement(const TiXmlElement * element, const std::string & eName);
	/*! Read an IBK:Time tag. */
	IBK::Time readTimeElement(const TiXmlElement * element, const std::string & eName);


//	/*! Writes out a vector of Vector3D elements. */
//	TiXmlElement * writeVector3D(TiXmlElement * parent, const std::string & name, const std::vector<IBKMK::Vector3D> & vec);

//	/*! Reads a vector of Vector3D elements. */
//	void readVector3D(const TiXmlElement * element, const std::string & name, std::vector<IBKMK::Vector3D> & vec);


//	template <typename T>
//	void readPoint2D(const TiXmlElement * element, const std::string & name, IBK::point2D<T> & p) {
//		FUNCID(NANDRAD::readPoint2D);
//		std::string text = element->GetText();
//		try {
//			typename std::vector<T> vec;
//			IBK::string2vector(text, vec);
//			if (vec.size() != 2)
//				throw IBK::Exception("Size mismatch, expected 2 numbers separated by , .", FUNC_ID);
//			p.m_x = vec[0];
//			p.m_y = vec[1];
//		}
//		catch (IBK::Exception & ex) {
//			throw IBK::Exception( ex, IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
//				IBK::FormatString("Error reading point2D element '%1'.").arg(name) ), FUNC_ID);
//		}
//	}

//	/*! Special implementation for double-type point2D. */
//	template <>
//	void readPoint2D(const TiXmlElement * element, const std::string & name, IBK::point2D<double> & p);

//	template <typename T>
//	void writePoint2D(TiXmlElement * parent, const std::string & name, const IBK::point2D<T> & p) {
//		TiXmlElement * child = new TiXmlElement(name);
//		parent->LinkEndChild(child);

//		std::stringstream vals;
//		vals << p.m_x << " " << p.m_y;
//		TiXmlText * text = new TiXmlText( vals.str() );
//		child->LinkEndChild( text );
//	}

};

} // namespace DGNB

#endif // DGNB_UtilitiesH
