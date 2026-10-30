#include "red.h"
#include<iostream>
#include<fstream>
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
bool red::eliminarEnrutador(char id)
{
    map<char, enrutador>::iterator it = enrutadores.find(id);
    if (it == enrutadores.end())
        throw string("el enrutador no existe");

    for (std::map<char, enrutador>::iterator otro = enrutadores.begin();otro != enrutadores.end(); ++otro)
    {
        if (otro->first != id)
            otro->second.eliminarVecino(id);
    }
    enrutadores.erase(it);
    return true;
}
int red::cantidadEnrutadores() const
{
    return static_cast<int>(enrutadores.size());
}
bool red::conectar(char idA, char idB, int costo)
{
    if (idA == idB)
        throw string("no conex entre si mismo");
    if (!existeEnrutador(idA) || !existeEnrutador(idB))
        throw string("alguno de los enrutadores no existe");
    if (costo <= 0)
        throw string("el costo debe ser mayor que cero");

    enrutadores[idA].agregarVecino(idB, costo);
    enrutadores[idB].agregarVecino(idA, costo);
    return true;
}
bool red::desconectar(char idA, char idB)
{
    if (!existeEnrutador(idA) || !existeEnrutador(idB))
        throw string("alguno de los enrutadores no existe");
    if (!enrutadores[idA].esVecino(idB))
        throw std::string("el enlace no existe");
    enrutadores[idA].eliminarVecino(idB);
    enrutadores[idB].eliminarVecino(idA);
    return true;
}
//los costos
void red::calc_costosMin(char origen,
                    map<char, int> &costos,
                    map<char, char> &previos)
{
    costos.clear();
    previos.clear();
    map<char, bool> visitado;
    for (map<char, enrutador>::const_iterator it = enrutadores.begin();
         it != enrutadores.end(); ++it)
    {
        costos[it->first] = infinito;
        previos[it->first] = '\0';
        visitado[it->first] = false;
    }
    if (!existeEnrutador(origen))
        return;
    costos[origen] = 0;
    for (size_t vuelta = 0; vuelta < enrutadores.size(); ++vuelta)
    {
        // 1) Buscar el enrutador sin visitar que tenga el menor costo.
        char nodo = '\0';
        int menorCosto = infinito;

        for (map<char, int>::const_iterator c = costos.begin();c != costos.end(); ++c)
        {
            if (!visitado[c->first] && c->second < menorCosto)
            {
                menorCosto = c->second;
                nodo = c->first;
            }
        }
        if (nodo == '\0')
            break;
        visitado[nodo] = true;
        const map<char, int> &vecinos =
            enrutadores.find(nodo)->second.getVecinos();

        for (map<char, int>::const_iterator v = vecinos.begin();
             v != vecinos.end(); ++v)
        {
            char idVecino = v->first;
            int pesoEnlace = v->second;

            if (!existeEnrutador(idVecino))
                continue;

            int nuevoCosto = menorCosto + pesoEnlace;
            if (nuevoCosto < costos[idVecino])
            {
                costos[idVecino] = nuevoCosto;
                previos[idVecino] = nodo;
            }
        }
    }
}


void red::actualizarConex()
{
    for (map<char, enrutador>::iterator it = enrutadores.begin();
         it != enrutadores.end(); ++it)
    {
        map<char, int> costos;
        map<char, char> previos;
        calc_costosMin(it->first, costos, previos);

        it->second.limpiarConex();
        for (map<char, int>::const_iterator c = costos.begin();
             c != costos.end(); ++c)
        {
            int valor = (c->second == infinito) ? -1 : c->second;
            it->second.actualizarCosto(c->first, valor);
        }
    }
}

vector<char> red::encontrarCamino(char origen, char destino)
{
    vector<char> camino;

    if (!existeEnrutador(origen) || !existeEnrutador(destino))
        throw string("alguno de los enrutadores no existe");

    map<char, int> costos;
    map<char, char> previos;

    calc_costosMin(origen, costos, previos);

    if (costos[destino] == infinito)
        return camino;

    char actual = destino;
    while (actual != '\0')
    {
        camino.push_back(actual);
        if (actual == origen)
            break;
        actual = previos[actual];
    }

    for (size_t i = 0, j = camino.size() - 1; i < j; ++i, --j)
    {
        char temp = camino[i];
        camino[i] = camino[j];
        camino[j] = temp;
    }
    return camino;
}
int red::costoEntre(char origen, char destino) const
{
    map<char, enrutador>::const_iterator it = enrutadores.find(origen);
    if (it == enrutadores.end())
        return -1;
    return it->second.costoHacia(destino);
}
//imprimir...

void red::imprimirRuta(char inicio,char destino)
{
    vector<char> camino = encontrarCamino(inicio, destino);

    if (camino.empty())
    {
        cout<<inicio<<" -> "<<destino<<"   sin ruta"<<endl;
        return;
    }

    for (size_t i = 0; i < camino.size(); ++i)
    {
        cout << camino[i];
        if (i + 1 < camino.size())
            cout <<" -> ";
    }
    cout<< "   (costo " <<costoEntre(inicio, destino)<<")"<<endl;
}

void red::cargarEnru(const string& ruta)
{
    ifstream archivo(ruta.c_str());
    if (!archivo.is_open())
        throw string ("cargarDesdeArchivo: no se pudo abrir " + ruta);
    red temporal;
    string linea;
    if (!getline(archivo, linea))
        throw string("cargarDesdeArchivo: el archivo esta vacio");

    for (size_t i = 0; i < linea.size(); ++i)
    {
        if (linea[i] != ' ' && linea[i] != '\t' && linea[i] != '\r')
            temporal.agregarEnrutador(linea[i]);
    }

    if (temporal.cantidadEnrutadores() == 0)
        throw string ("cargarDesdeArchivo: no se declaro ningun enrutador");

    char origen, destino;
    int costo;
    while (archivo >> origen >> destino >> costo)
    {
        temporal.conectar(origen, destino, costo);
    }

    if (!archivo.eof())
        throw string ("cargarDesdeArchivo: datos mal formados en los enlaces");

    archivo.close();

    enrutadores = temporal.enrutadores;
}




















