#ifndef CGDRAWEVENT_H
#define CGDRAWEVENT_H

#include "CgBase/CgBaseEvent.h"
#include <glm/glm.hpp>
#include <iostream>

class CgDrawEvent: public CgBaseEvent
{
public:
    CgDrawEvent(int i);
    ~CgDrawEvent();
    Cg::EventType getType();
    int getKoerper();
private:
    Cg::EventType m_type;
    CgBaseEvent* clone();
    int koerper;
};

#endif // CGDRAWEVENT_H
