#include <iostream>

using namespace std;

#include "red.h"
#include <iostream>

int main()
{
    red red;

    // La carga inicial sí aborta el programa si falla: sin red no hay nada que hacer.
    try
    {
        red.cargarEnru("red.txt");
        red.actualizarConex();
        cout << "Red cargada"<<endl;
    }
    catch (const string &mensaje)
    {
        cout << "Error al cargar: " << mensaje <<endl;
        return 1;
    }
    int opcion = -1;
    while (opcion != 0)
    {
        cout<< endl<<"--------------------------------"<<endl;
        cout<< " 1. Agregar enrutador"<<endl;
        cout<< " 2. Eliminar enrutador"<<endl;
        cout<< " 3. Conectar dos enrutadores"<<endl;
        cout<< " 4. Desconectar dos enrutadores"<<endl;
        cout<< " 5. Ver ruta entre dos enrutadores"<<endl;
        cout<< " 0. Salir"<<endl;
        cout<< "--------------------------------"<<endl;
        cout<< "Opcion: ";

        if (!(cin >> opcion))
        {
            cout << "Entrada invalida"<<endl;
            return 1;
        }
        try
        {
            if (opcion == 1)
            {
                char id;
                cout << "Id del nuevo enrutador: ";
                cin >> id;
                if (red.agregarEnrutador(id))
                {
                    red.actualizarConex();
                    cout << "Enrutador " << id << " agregado"<<endl;
                }
                else
                {
                    cout <<"mala entrada mon ami"<<endl;
                }
            }
            else if (opcion == 2)
            {
                char id;
                cout << "id del enrutador a eliminar: ";
                cin >> id;
                red.eliminarEnrutador(id);
                red.actualizarConex();
                cout <<"Enrutador "<< id<< " eliminado"<<endl;
            }
            else if (opcion == 3)
            {
                char a, b;
                int costo;
                cout << "Enrutador origen: ";
                cin >> a;
                cout << "Enrutador destino: ";
                cin >> b;
                cout << "Costo del enlace: ";
                cin >> costo;

                red.conectar(a, b, costo);
                red.actualizarConex();
                cout << "todo exitoso merci"<<endl;
            }
            else if (opcion == 4)
            {
                char a, b;
                cout << "Enrutador origen: ";
                cin >> a;
                cout << "Enrutador destino: ";
                cin >> b;

                red.desconectar(a, b);
                red.actualizarConex();
                cout << "Enlace eliminado"<<endl;
            }
            else if (opcion == 5)
            {
                char inicio, destino;
                cout << "Enrutador origen: ";
                cin >> inicio;
                cout << "Enrutador destino: ";
                cin >> destino;

                red.imprimirRuta(inicio, destino);
            }
            else if (opcion != 0)
            {
                cout << "Opcion no valida.\n";
            }
        }
        catch (const string &mensaje)
        {
            cout << "Error: " << mensaje << "\n";
        }
    }

    cout << "Fin del programa.\n";
    return 0;
}
