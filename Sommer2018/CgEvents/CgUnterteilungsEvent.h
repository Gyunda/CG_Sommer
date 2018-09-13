#ifndef CGUNTERTEILUNGSEVENT_H
#define CGUNTERTEILUNGSEVENT_H

#include "CgBase/CgBaseEvent.h"
#include <glm/glm.hpp>
#include <iostream>


class CgUnterteilungsEvent: public CgBaseEvent
{

public:
    CgUnterteilungsEvent(int newAufloesung);


    ~CgUnterteilungsEvent();

    Cg::EventType getType();
    CgBaseEvent* clone();
    int getAufloesung();
    friend std::ostream& operator <<(std::ostream& os, const CgUnterteilungsEvent&);

private:
    Cg::EventType m_type;
    int aufloesung;

};

#endif // CGUNTERTEILUNGSEVENT_H
