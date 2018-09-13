#include "CgTranslationEvent.h"
#include "CgBase/CgEnums.h"

CgTranslationEvent::CgTranslationEvent(float x, float y, float z):
    m_type(Cg::CgTranslationEvent)
{
    m_vektor = glm::vec3(x,y,z);
}

CgTranslationEvent::~CgTranslationEvent(){

}

Cg::EventType CgTranslationEvent::getType()
{
    return m_type;
}


CgBaseEvent* CgTranslationEvent::clone()
{
    return new CgTranslationEvent(m_vektor.x,m_vektor.y,m_vektor.z);
}

glm::vec3 CgTranslationEvent::getVektorTranslation(){

    return m_vektor;

}

std::ostream& operator <<(std::ostream& os, const CgTranslationEvent& e){

    os << "X: " << e.m_vektor.x << ",Y: " << e.m_vektor.y << ",Z: " << e.m_vektor.z <<std::endl;
    return os;
}
