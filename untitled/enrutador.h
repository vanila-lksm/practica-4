#ifndef ENRUTADOR_H
#define ENRUTADOR_H
#include <map>
using namespace std;
class enrutador
{
private:
    char identificador;
    map<char,int> vecinos;
    map<char,int> conex;

public:
    enrutador();
    enrutador(char id);
    ~enrutador();
    //get
    char getId() const;
    const map<char, int> &getVecinos() const;
    const map<char, int> &getOtras_conex() const;
    //set
    void setId(char id);
    //funciones
    void agregarVecino(char id,int costo);
    void eliminarVecino(char id);
    void actualizarCosto(char destino, int costo);
    bool esVecino(char id);
    int costoEnlace(char id);
    void limpiarConex();
    int costoHacia(char destino)const;

};

#endif // ENRUTADOR_H
