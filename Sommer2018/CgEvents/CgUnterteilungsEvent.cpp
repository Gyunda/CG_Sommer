#include "CgUnterteilungsEvent.h"
#include "CgBase/CgEnums.h"

CgUnterteilungsEvent::CgUnterteilungsEvent(int newAufloesung):
m_type(Cg::CgUnterteilungsEvent)
{
    aufloesung = newAufloesung;
}

CgUnterteilungsEvent::~CgUnterteilungsEvent(){

}

Cg::EventType CgUnterteilungsEvent::getType()
{
    return m_type;
}

CgBaseEvent* CgUnterteilungsEvent::clone()
{
    return new CgUnterteilungsEvent(aufloesung);
}

int CgUnterteilungsEvent::getAufloesung() {
    return aufloesung;
}

std::ostream& operator <<(std::ostream& os, const CgUnterteilungsEvent&){

    os << "4-Punkt Schema Mittelungsschritt durchgeführt" << std::endl;
    return os;
}

