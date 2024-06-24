#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <windows.h>
#include <locale.h>

using namespace std;

struct cliente {
    char nombre_Cliente[25];
    char documento_Cliente[9];
    int puntos;
    int consumo;
};

struct menu {
    int numero;
    char descripcion[25];
    float precio;  
};

menu plato1={1,"1: 1 pollo",47.00},
     plato2={2,"2: 1/2 pollo",23.00},
     plato3={3,"3: 1/4 pollo",12.00},
     plato4={4,"4: 1/8 pollo",8.00},
     plato5={5,"5: porción de papas",15.00},
     plato6={6,"6: 1/2 porción de papas",10.00},
     plato7={7,"7: ensalada",10.00},
     bebida1={8,"8: gaseosa 3L",13.00},
     bebida2={9,"9: limonada frozen 1L",15.00},
     bebida3={10,"10: chicha 1L",15.00};

void interfazCliente() {
    setlocale(LC_CTYPE, "Spanish");
    ofstream es("Datos_de_los_clientes.txt", ios_base::out | ios_base::app);
    if (!es.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    cliente x;
    menu carta[10] = {plato1, plato2, plato3, plato4, plato5, plato6, plato7, bebida1, bebida2, bebida3};
    float cuenta = 0.0;
    int pedido;
    char respuesta;

    cout << "Ingrese su nombre: ";
    cin.ignore();
    cin.getline(x.nombre_Cliente, 25);
    cout << "Ingrese su documento: ";
    cin.getline(x.documento_Cliente, 9);
    x.consumo = 0;

    cout << "Datos almacenados correctamente." << endl;
    cout << "<------Bienvenido " << x.nombre_Cliente << "------>" << endl;
    cout << "Nuestra carta: " << endl;
    cout << left << setw(25) << "Platillos" << right << setw(10) << "Precio" << endl;

    for(int i = 0; i < 10; i++) {
        cout << left << setw(25) << carta[i].descripcion << right << setw(10) << carta[i].precio << endl;
    }

    do {
        cout << "¿Qué desea pedir?(ingrese el número del platillo o bebida)\n";
        cin >> pedido;

        for(int i = 0; i < 10; i++) {
            if(carta[i].numero == pedido) {
                cuenta += carta[i].precio;
                x.consumo++;
            }
        }

        cout << "¿Desea añadir algo más? (s/n): ";
        cin >> respuesta;
    } while (respuesta == 's' || respuesta == 'S');

    cout << "El monto total a pagar será S/." << cuenta << endl;

    if (es.tellp() == 0) {
        es << left << setw(25) << "Nombre del cliente" << setw(15) << "Documento" << setw(15) << "N° de consumos" << endl;
    }

    es << left << setw(25) << x.nombre_Cliente << setw(15) << x.documento_Cliente << setw(15) << x.consumo << endl;
    es.close();
}

void interfazTrabajador() {
    setlocale(LC_CTYPE, "Spanish");
    cout << "Estamos trabajando...";
}

int main() {
    setlocale(LC_CTYPE, "Spanish");
    char identificacion[10];
    bool error;

    do {
        error = false;
        cout << "¿Es trabajador o cliente?" << endl;
        cin >> identificacion;

        if (strcmp(identificacion, "cliente") == 0 || strcmp(identificacion, "Cliente") == 0) {
            interfazCliente();
        }
        else if (strcmp(identificacion, "trabajador") == 0 || strcmp(identificacion, "Trabajador") == 0) {
            interfazTrabajador();
        }
        else {
            error = true;
            cout << "Identificación no válida. Inténtelo de nuevo.\n";
        }
    } while (error);

    return 0;
}





//4 trabajores fijos
//struct cliente (nombre, dni, fecha de nacimiento, puntos (ofertas))
//struct stock (nombre del producto (pollo, porción de papas (gramos), bebidas)
//struct precios 
//

