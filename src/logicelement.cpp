#include "wire.h"
#include "module.h"
#include "logicelement.h"

LogicElement::LogicElement() {}

LogicElement::LogicElement(QString _name, const Module* _type)
{
    name = _name;
    type = _type;
}

LogicElement::~LogicElement() {}
