#include "CgSmoothLineEvent.h"
#include <stdio.h>
#include <CgBase/CgEnums.h>

CgSmoothLineEvent::CgSmoothLineEvent(): m_type(Cg::CgSmoothLineEvent)
{
    //printf("neues glättungsevent\n");
}

CgBaseEvent* CgSmoothLineEvent::clone()
{

    return new CgSmoothLineEvent();
}

CgSmoothLineEvent::~CgSmoothLineEvent(){

}

Cg::EventType CgSmoothLineEvent::getType()
{
    return m_type;
}

