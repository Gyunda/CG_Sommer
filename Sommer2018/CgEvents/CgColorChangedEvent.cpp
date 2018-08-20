#include "CgColorChangedEvent.h"
#include "CgBase/CgEnums.h"

CgColorChangedEvent::CgColorChangedEvent(float red, float green, float blue):
    m_type(Cg::CgColorChangedEvent)
{
    m_color = glm::vec3(red,green,blue);
}

CgColorChangedEvent::~CgColorChangedEvent(){

}

Cg::EventType CgColorChangedEvent::getType()
{
    return m_type;
}


CgBaseEvent* CgColorChangedEvent::clone()
{
    return new CgColorChangedEvent(m_color.x,m_color.y,m_color.z);
}

glm::vec3 CgColorChangedEvent::getColor()
{
    return m_color;
}

std::ostream& operator <<(std::ostream& os, const CgColorChangedEvent& e){

    os << "Rot " << e.m_color.x *255 << ",Grün " << e.m_color.y *255<< ",Blau " << e.m_color.z *255<<std::endl;
    return os;
}

