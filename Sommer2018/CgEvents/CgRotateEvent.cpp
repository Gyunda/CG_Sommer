#include "CgRotateEvent.h"
#include <stdio.h>
#include <CgBase/CgEnums.h>

CgRotateEvent::CgRotateEvent(int newAufloesung): m_type(Cg::CgRotateEvent)
{
    aufloesung = newAufloesung;
}

CgBaseEvent* CgRotateEvent::clone()
{

    return new CgRotateEvent(aufloesung);
}

CgRotateEvent::~CgRotateEvent(){

}

Cg::EventType CgRotateEvent::getType()
{
    return m_type;
}

int CgRotateEvent::getAufloesung() {
    return aufloesung;
}

