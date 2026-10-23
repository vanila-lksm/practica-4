#include "red.h"

red::red() {}
red::~red(){}
bool red::existeEnrutador(char id) const
{
    return enrutadores.find(id) != enrutadores.end();
}
bool red::agregarEnrutador(char id)
{
    if (existeEnrutador(id))
        return false;
    enrutadores[id] = enrutador(id);
    return true;
}
