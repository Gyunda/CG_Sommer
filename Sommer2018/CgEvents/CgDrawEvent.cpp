#include "CgDrawEvent.h"
#include "CgBase/CgEnums.h"

CgDrawEvent::CgDrawEvent(int i): m_type(Cg::CgDrawEvent)
{
    koerper = i;
}

CgBaseEvent* CgDrawEvent::clone()
{
    return new CgDrawEvent(koerper);
}

CgDrawEvent::~CgDrawEvent(){

}

Cg::EventType CgDrawEvent::getType()
{
    return m_type;
}

int CgDrawEvent::getKoerper() {
    return koerper;
}

