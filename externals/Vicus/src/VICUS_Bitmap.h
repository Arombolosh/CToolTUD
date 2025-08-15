#ifndef VICUS_BitmapH
#define VICUS_BitmapH

#include "VICUS_CodeGenMacros.h"
#include "VICUS_Object.h"
#include "VICUS_Polygon3D.h"

#include <IBK_Path.h>

#include <QImage>
#include <QOpenGLTexture>
#include <QVector3D>
#include <memory>


namespace VICUS{

/*!  This class holds images (bitmaps) that can be mapped on a rectangle in the scene.
	 Only the filename and rectangle are stored in the XML, the image and texture will be loaded during run-time.
*/
class Bitmap: public Object {

public:

	VICUS_READWRITE

	Bitmap() {}

	/*! Return the pointer to the texture, stored on the heap.
		Texture will be genereted uppon first request and deleted automatically
		by the shared pointer.
	*/
	const QOpenGLTexture * texture() const {
		if (m_texture == nullptr)
			m_texture = std::make_shared<QOpenGLTexture>(m_image.mirrored());
		return m_texture.get();
	}

	/*! Returns the rectangle points as QVector3D. */
	const std::vector<QVector3D> points() const{
		std::vector<QVector3D> vec;
		for (const IBKMK::Vector3D &v: m_rectangle.vertexes()) {
			QVector3D qv(v.m_x, v.m_y, v.m_z);
			vec.push_back(qv);
		}
		return vec;
	}

	/*! Type-info string. */
	const char * typeinfo() const override {
		return "Bitmap";
	}

	//:inherited	unsigned int		m_id = INVALID_ID;			// XML:A:required
	//:inherited	QString				m_displayName;				// XML:A
	//:inherited	bool				m_visible = true;			// XML:A

	/*! Rectangle the image shall be mapped to. */
	Polygon3D				m_rectangle;		// XML:E

	/*! Filename of bitmap, can be any support suffix (png, jpeg, ...) */
	IBK::Path				m_fileName;			// XML:E

	// *** Run time variables ***

	/*! Image will be loaded when project is read. */
	QImage					m_image;

private:
	/*! The texture nedded rendering on the texture shader. */
	mutable std::shared_ptr<QOpenGLTexture> m_texture = nullptr;

};


} // namespace VICUS

#endif // VICUS_BitmapH
