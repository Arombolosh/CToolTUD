#include "VICUS_PolyLine.h"

namespace VICUS {

PolyLine::PolyLine()
{
}

PolyLine::PolyLine(const std::vector<IBKMK::Vector3D> & newVertexes):
	m_vertexes(newVertexes)
{
}

const std::vector<IBKMK::Vector3D> & PolyLine::vertexes() const {
	return m_vertexes;
}

void PolyLine::setVertexes(const std::vector<IBKMK::Vector3D> & newVertexes) {
	m_vertexes = newVertexes;
}

void PolyLine::addVertex(const IBKMK::Vector3D & newVertex) {
	m_vertexes.push_back(newVertex);
}

void PolyLine::updateLines() const {
	m_lines.clear();
	for (unsigned int i=1; i<m_vertexes.size(); ++i)
		m_lines.push_back(NetworkLine(m_vertexes[i-1], m_vertexes[i]));
}

const std::vector<VICUS::NetworkLine>& PolyLine::lines() const {
	updateLines();
	return m_lines;
}

bool PolyLine::isValid() const{
	// the last point should not be contained by any of the currently drawn lines
	std::vector<VICUS::NetworkLine> lines;
	for (unsigned int i=1; i<m_vertexes.size() - 1; ++i)
		lines.push_back(NetworkLine(m_vertexes[i-1], m_vertexes[i]));
	for (const VICUS::NetworkLine &line: lines){
		if (line.containsPoint(m_vertexes.back()))
			return false;
	}
	return true;
}

} // namespace VICUS
