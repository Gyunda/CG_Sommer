#include "CgPolyline.h"

#include "CgBase/CgEnums.h"

unsigned int CgPolyline::total_ids = 1000;

CgPolyline::CgPolyline(glm::vec3 start, glm::vec3 end, glm::vec3 color, unsigned int lineWidth):
    m_type(Cg::Polyline),
    m_id(total_ids++)
{
    m_verticies.push_back(start);
    m_verticies.push_back(end);
    m_color = color;
    m_lineWidth = lineWidth;
}

CgPolyline::CgPolyline(std::vector<glm::vec3> verticies, unsigned int lineWidth): //unendliche Linie Konstruktor
    m_type(Cg::Polyline),
    m_id(total_ids++)
{

    m_verticies = verticies;
    m_lineWidth = lineWidth;
    m_color = glm::vec3(0,0,1);
}

CgPolyline::~CgPolyline(){
    m_verticies.clear();
}

const std::vector<glm::vec3>& CgPolyline::getVertices() const{
    return m_verticies;
}

glm::vec3 CgPolyline::getColor() const{
    return m_color;
}

unsigned int CgPolyline::getLineWidth() const{
    return m_lineWidth;
}

void CgPolyline::setColor(glm::vec3 color){
    m_color = color;
}
