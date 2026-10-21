#include "enrutador.h"

enrutador::enrutador() : identificador('\0') {}
enrutador::enrutador(char id) : identificador(id) {}
enrutador::~enrutador() {}
//get
char enrutador::getId() const
{return identificador;}
const std::map<char, int> &enrutador::getVecinos() const
{return vecinos;}
const std::map<char, int> &enrutador::getOtras_conex() const
{return conex;}
//set
void enrutador::setId(char id)
{identificador = id;}
//funciones
void enrutador::agregarVecino(char idVecino, int costo)
{vecinos[idVecino] = costo;}

void enrutador::eliminarVecino(char idVecino)
{vecinos.erase(idVecino);}

void enrutador::actualizarCosto(char destino, int costo)
{conex[destino] = costo;}
bool enrutador::esvecino(char idVecino)
{
    return vecinos.find(idVecino) != vecinos.end();
}
int enrutador::costoEnlace(char idVecino)
{
    std::map<char, int>::const_iterator it = vecinos.find(idVecino);
    if (it == vecinos.end())
        return -1;
    return it->second;
}
void enrutador::limpiarConex()
{
    conex.clear();
}
int enrutador::costoHacia(char destino)const
{
    map<char,int>::const_iterator i = conex.find(destino);
    if(i==conex.end())
        return -1;
    return i->second;
}