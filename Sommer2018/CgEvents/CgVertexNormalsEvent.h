#ifndef CGVERTEXNORMALSEVENT_H
#define CGVERTEXNORMALSEVENT_H

#include "CgBase/CgBaseEvent.h"
#include <glm/glm.hpp>
#include <iostream>

class CgVertexNormalsEvent : public CgBaseEvent
{
public:
    CgVertexNormalsEvent(bool checked);
    ~CgVertexNormalsEvent();

    Cg::EventType getType();
    CgBaseEvent* clone();
    bool getChecked();
private:
    bool draw;
    Cg::EventType m_type;
};

#endif // CGVERTEXNORMALSEVENT_H
