#include "CgResetEvent.h"
#include "CgBase/CgEnums.h"

CgResetEvent::CgResetEvent():
m_type(Cg::CgResetEvent)
{

}

CgResetEvent::~CgResetEvent(){

}

Cg::EventType CgResetEvent::getType()
{
    return m_type;
}

CgBaseEvent* CgResetEvent::clone()
{
    return new CgResetEvent();
}

std::ostream& operator <<(std::ostream& os, const CgResetEvent&){

    os << "Reset durchgeführt" << std::endl;
    return os;

}
