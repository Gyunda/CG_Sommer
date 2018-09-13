#ifndef CGSMOOTHLINEEVENT_H
#define CGSMOOTHLINEEVENT_H

#include "CgBase/CgBaseEvent.h"
#include <glm/glm.hpp>
#include <iostream>

class CgRotateEvent: public CgBaseEvent
{
public:
    CgRotateEvent(int newAufloesung);
    ~CgRotateEvent();
    Cg::EventType getType();
    int getAufloesung();
private:
    Cg::EventType m_type;
    CgBaseEvent* clone();
    int aufloesung;
};

#endif // CGSMOOTHLINEEVENT_H
