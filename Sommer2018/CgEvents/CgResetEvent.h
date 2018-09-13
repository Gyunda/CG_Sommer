#ifndef CGRESETEVENT_H
#define CGRESETEVENT_H

#include "CgBase/CgBaseEvent.h"
#include <glm/glm.hpp>
#include <iostream>

class CgResetEvent: public CgBaseEvent
{

public:
    CgResetEvent();

    ~CgResetEvent();

    Cg::EventType getType();
    CgBaseEvent* clone();

    friend std::ostream& operator <<(std::ostream& os, const CgResetEvent&);

private:
    Cg::EventType m_type;
};

#endif // CGRESETEVENT_H
