#ifndef CGSMOOTHLINEEVENT_H
#define CGSMOOTHLINEEVENT_H

#include "CgBase/CgBaseEvent.h"
#include <glm/glm.hpp>
#include <iostream>

class CgSmoothLineEvent: public CgBaseEvent
{
public:
    CgSmoothLineEvent();
    ~CgSmoothLineEvent();
    Cg::EventType getType();
private:
    Cg::EventType m_type;
    CgBaseEvent* clone();
};

#endif // CGSMOOTHLINEEVENT_H
