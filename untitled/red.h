#ifndef RED_H
#define RED_H
#include "enrutador.h"
#include <map>
class red
{
private:
    map<char,enrutador> enrutadores;
public:
    red();
    ~red();
    bool existeEnrutador(char id) const;
    bool agregarEnrutador(char id);
    bool eliminarEnrutador(char id);
};

#endif // RED_H
