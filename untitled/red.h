#ifndef RED_H
#define RED_H
#include "enrutador.h"
#include <map>
#include<vector>
#include<string>
class red
{
private:
    map<char,enrutador> enrutadores;
    static const int infinito=1999999999;
    void calc_costosMin(char origen,
                    std::map<char, int> &costos,
                        std::map<char, char> &previos);
public:
    red();
    ~red();
    bool existeEnrutador(char id) const;
    bool agregarEnrutador(char id);
    bool eliminarEnrutador(char id);
    int cantidadEnrutadores() const;
    //cosas ya de coneciones
    bool conectar(char id1,char id2,int costo);
    bool desconectar(char idA, char idB);
    //costos
    void actualizarConex();
    vector<char> encontrarCamino(char origen, char destino);
    int costoEntre(char origen, char destino) const;
};


#endif // RED_H
