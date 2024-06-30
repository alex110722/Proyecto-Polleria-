//Falta la interfaz del trabajador y la interfaz de compra del cliente



#include <iostream>
#include <string>
#include <cstring>
#include <windows.h>
#include <locale.h>
#include <fstream>
#include <cctype>
#include <iomanip>

using namespace std;


bool comprobarcarac(char [], int);
void interfazcarta();
void interfazClientePrincipal(char []);
void sesionUsuario();
void registroUsuario();
void interfazCliente();
void interfazTrabajador();

struct cliente {
    char nombre_Cliente[30];
    char apellidos_Cliente[30];
    char documento_Cliente[9];
    char usuario_Cliente[11];
    char contrasena_Cliente[9];
    int puntos;
    int consumo;
};

struct menu {
    int numero;
    char descripcion[75];
    float precio;
} plato1 = {1, "1 POLLO + PAPAS FAMILIARES + ENSALADA FAMILIAR + GASEOSA 1.5L", 53.90},
  plato2 = {2, "1/2 POLLO + PAPAS MEDIANAS + ENSALADA MEDIANA + 2 GASEOSAS PERSONALES", 35.90},
  plato3 = {3, "1/4 DE POLLO + PAPAS PERSONALES + ENSALADA PERSONAL + GASEOSA PERSONAL", 15.90},
  plato4 = {4, "1/8 DE POLLO + PAPAS PERSONALES + ENSALADA PERSONAL", 8.90},
  adicional1 = {5, "1/4 DE POLLO", 15.90},
  adicional2 = {6, "PORCIÓN DE PAPAS FAMILIARES", 14.90},
  adicional3 = {7, "1/2 PORCIÓN DE PAPAS FAMILIARES", 9.90},
  adicional4 = {8, "ENSALADA CLÁSICA", 10.00},
  adicional5 = {9, "ENSALADA DE PALTA", 10.00},
  bebida1 = {10, "GASEOSA 3L", 13.00},
  bebida2 = {11, "LIMONADA FROZEN 1L", 15.00},
  bebida3 = {12, "CHICHA MORADA 1L", 15.00};

struct trabajador {
    char nombre_Trabajador[25];
    char documento_Trabajador[10];
    char user[15];
    char contrasena[6];
    char cargo[12];
    
} trabajador1 = {"Pepe Quintana", "32356489", "pepequin", "6489", "gerente"},
  trabajador2 = {"Alexandra Vargas", "56236979", "alexvar", "6979", "subgerente"},
  trabajador3 = {"Diego Aguilar", "45638679", "diegoagui", "8679", "mozo"},
  trabajador4 = {"Gerardo Carrillo", "71556889", "gerardoca", "6889", "mozo"},
  trabajador5 = {"Mariana Mendoza", "23132565", "marianamen", "2565", "mozo"};

struct stock {
    char nomProducto[15];
    float cantidad;
} producto1 = {"pollo", 40},
  producto2 = {"papa", 30000},
  producto3 = {"lechuga", 20},
  producto4 = {"tomate", 30},
  producto5 = {"gaseosa", 25},
  producto6 = {"limón", 20000},
  producto7 = {"maíz morado", 20000},
  producto8 = {"azúcar", 10000};

//Interfaz para seleccionar si es cliente o trabajador
int main() {
    setlocale(LC_CTYPE, "Spanish");
    char identificacion[10];
    bool error = false;
    trabajador trabajadores[5] = {trabajador1, trabajador2, trabajador3, trabajador4, trabajador5};
    stock productos[9] = {producto1, producto2, producto3, producto4, producto5, producto6, producto7, producto8};

    cout << "Ingrese su identificación o Salir para finalizar el programa" << endl;
    cout << "- Cliente" << endl;
    cout << "- Trabajador" << endl;
    do {
        gets(identificacion);
        for (int i = 0; i < 10; i++) {
            identificacion[i] = toupper(identificacion[i]);
        }

        if (strcmp(identificacion, "CLIENTE") == 0) {
            system("cls");
            interfazCliente();
            error = false;
        } else if (strcmp(identificacion, "TRABAJADOR") == 0) {
            interfazTrabajador();
            error = false;
        } else if (strcmp(identificacion, "SALIR") == 0) {
            cout << "Gracias por su preferencia." << endl;
            error = false;
        } else {
            error = true;
            cout << "\nIdentificación no válida. Inténtelo de nuevo: \n";
        }
    } while (error);

    return 0;
}

//Interfaz para el inicio de sesión o el registro del cliente
void interfazCliente() {
    setlocale(LC_CTYPE, "Spanish");
    int opciones;
    bool error = false;
        cout << "Seleccione una opción: " << endl;
        cout << "1. Iniciar Sesión" << endl;
        cout << "2. Registrarse" << endl;
        cout << "3. Salir" << endl;
        do {
            cin >> opciones;
            if (opciones == 1) {
            	system("cls");
            	sesionUsuario();
            	error = false;
            } else if (opciones == 2) {
                system("cls");
                registroUsuario();
                system("cls");
                error = false;
            } else if (opciones == 3) {
                cout << "Gracias por su preferencia." << endl;
                error = false;
            } else {
                error = true;
                cout << "\nOpción no válida. Inténtelo de nuevo: \n";
            }
        } while (error);
}

//Interfaz para el inicio de sesión
void sesionUsuario() {
    cliente y;
    int h = 0;
    string us;
    char usc[11];
    char con[9];
    bool correcto = false;
    ifstream sm("Datos_de_los_clientes.txt", ios_base::in);
    if (!sm.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }
    else{
	    cin.ignore();
	    while (!correcto) {
	        h = 0; // Reiniciar el indicador de usuario encontrado
	        cout << "Ingrese su usuario (10 caracteres): ";
	        gets(y.usuario_Cliente);
	        while (comprobarcarac(y.usuario_Cliente, 10) == false) {
	            cout << "\nUsuario no válido (solo 10 caracteres, no espacios ni el caracter | ). Inténtelo de nuevo: \n";
	            gets(y.usuario_Cliente);
	        }
	        sm.clear();
	        sm.seekg(0);
	        while (!sm.eof() && h == 0) {
	            getline(sm, us, '|');
	            strcpy(usc, us.c_str());
	            if (strcmp(usc, y.usuario_Cliente) == 0) {
	                h++;
	                getline(sm, us, '|'); // Leer la contraseña
	                strcpy(con, us.c_str()); // Almacenar la contraseña leída
	                getline(sm, us); // Leer el resto de la línea
	            } else {
	                getline(sm, us); // Leer el resto de la línea si el usuario no coincide
	            }
	        }
	        if (h == 0) {
	            cout << "No existe el usuario\n";
	            continue;
	        }
	        
	        cout << "Ingrese su contraseña (8 caracteres): ";
	        gets(y.contrasena_Cliente);
	        while (comprobarcarac(y.contrasena_Cliente, 8) == false) {
	            cout << "\nContraseña no válida (solo 8 caracteres, no espacios ni el caracter | ). Inténtelo de nuevo: \n";
	            gets(y.contrasena_Cliente);
	            cout << "\n";
	        }
	        
	        if (strcmp(con, y.contrasena_Cliente) == 0) {
	            cout << "Inicio de sesión exitoso.\n";
	             system("pause");
	            system("cls");
	            interfazClientePrincipal(usc);
	            correcto = true;
	        } else {
	            cout << "Contraseña incorrecta.\n";
	            correcto = false;
	        }
	    }
	    sm.close();
	}
}

//Interfaz para el registro
void registroUsuario() {
    ofstream es("Datos_de_los_clientes.txt", ios_base::app);
    if (!es.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }
    ifstream ms("Datos_de_los_clientes.txt", ios_base::in);
    if (!ms.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }
    cliente x;
    int r = 0, i = 0, h;
    x.consumo = 0;
    x.puntos = 0;
    string us;
    cout << "Ingrese sus nombres: ";
    cin.ignore();
    gets(x.nombre_Cliente);
    while (comprobarcarac(x.nombre_Cliente, 30) == false) {
        cout << "\nNombre no válido (No debe contener el caracter | y ser menor a 30 caracteres). Inténtelo de nuevo: \n";
        gets(x.nombre_Cliente);
    }
    cout << "Ingrese sus apellidos: ";
    gets(x.apellidos_Cliente);
    while (comprobarcarac(x.apellidos_Cliente, 30) == false) {
        cout << "\nApellidos no válidos (No debe contener el caracter | y ser menor a 30 caracteres). Inténtelo de nuevo: \n";
        gets(x.apellidos_Cliente);
    }
    cout << "Ingrese su documento de DNI: ";
    gets(x.documento_Cliente);
    while (strlen(x.documento_Cliente) != 8 || strspn(x.documento_Cliente, "0123456789") != 8) {
        cout << "\nDocumento no válido. Inténtelo de nuevo: \n";
        gets(x.documento_Cliente);
    }
    do {
        h = 1;
        cout << "Ingrese su usuario (10 caracteres): ";
        gets(x.usuario_Cliente);
        while (comprobarcarac(x.usuario_Cliente, 10) == false) {
            cout << "\nUsuario no válido (solo 10 caracteres, no espacios ni el caracter | ). Inténtelo de nuevo: \n";
            gets(x.usuario_Cliente);
        }
        ms.clear();
        ms.seekg(0);
        while (!ms.eof() && h == 1) {
            getline(ms, us, '|');
            if (strcmp(us.c_str(), x.usuario_Cliente) == 0) {
                h = 0;
            }
            getline(ms, us); // Leer el resto de la línea
        }
        if (h == 0) {
        	cout<<endl;
            cout << "Ya existe el usuario "<<endl;
            cout<<endl;
        }
    } while (h == 0);
    cout << "Ingrese su contraseña (8 caracteres): ";
    gets(x.contrasena_Cliente);
    while (comprobarcarac(x.contrasena_Cliente, 8) == false) {
        cout << "\nContraseña no válida (solo 8 caracteres, no espacios ni el caracter | ). Inténtelo de nuevo: \n";
        gets(x.contrasena_Cliente);
    }
    
    cout << "Usuario Registrado\n";
    system("pause");
    es << x.usuario_Cliente << "|" << x.contrasena_Cliente << "|" << x.nombre_Cliente << "|" << x.apellidos_Cliente << "|" << x.documento_Cliente << "|" << x.puntos << "|" << x.consumo << "|" << endl;
    es.close();
    ms.close();
}

//Interfaz para el cliente despues de inciar sesión
void interfazClientePrincipal(char x[]) {
    cliente y;
    string aux;
    int opciones, h=0;
    bool encontrado = false, error;
    ifstream dat("Datos_de_los_clientes.txt", ios_base::in);
    if (!dat.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return;
    } else {
        while (!dat.eof() && !encontrado) {
            getline(dat, aux, '|');
            if (strcmp(aux.c_str(), x) == 0) {
                encontrado = true;
                // Leer el resto de los datos del cliente
                getline(dat, aux, '|'); // Leer la contraseña
                getline(dat, aux, '|'); // Leer el nombre
                strcpy(y.nombre_Cliente, aux.c_str());
                getline(dat, aux, '|'); // Leer los apellidos
                strcpy(y.apellidos_Cliente, aux.c_str());
                getline(dat, aux, '|'); // Leer el documento
                strcpy(y.documento_Cliente, aux.c_str());
                getline(dat, aux, '|'); // Leer los puntos
                y.puntos = atoi(aux.c_str());
                getline(dat, aux, '|'); // Leer el consumo
                y.consumo = atoi(aux.c_str());
            } else {
                getline(dat, aux); // Leer el resto de la línea si el usuario no coincide
            }
        }
        if (encontrado) {
        	do {
        	cout << "Bienvenido " << y.nombre_Cliente << endl;
        	cout << "Elija la opción que desee: "<< endl;
        	cout << "1. Carta: " << endl;
            cout << "2. Comprar: " << endl;
            cout << "3. Información del usuario: " << endl;
        	cout << "4. Salir: " << endl;
	        	do {
	            cin >> opciones;
	            if (opciones == 1) {
		            	system("cls");
		            	interfazcarta();
		            	system("cls");
		            	error = false;
		            } else if (opciones == 2) {
		                system("cls");
		                //registroUsuario();
		                system("cls");
		                error = false;
		            } else if (opciones == 3) {
		            	system("cls");
		                cout << "Nombre: " << y.nombre_Cliente << endl;
		            	cout << "Apellidos: " << y.apellidos_Cliente << endl;
		            	cout << "Documento: " << y.documento_Cliente << endl;
		            	cout << "Puntos: " << y.puntos << endl;
		            	cout << "Consumo: " << y.consumo << endl;
		            	system("pause");
		            	system("cls");
		                error = false;
		            } else if (opciones == 4) {
		                cout << "Gracias por su preferencia." << endl;
		                error = false;
		                h++;
		            } else {
		                error = true;
		                cout << "\nOpción no válida. Inténtelo de nuevo: \n";
		            }
	        	} while (error);
	        } while (h==0);
        } 
		else
            cout << "Usuario no encontrado." << endl;
    }
    dat.close();
}

//Interfaz para la carta
void interfazcarta() {
    menu carta[12] = {plato1, plato2, plato3, plato4, adicional1, adicional2, adicional3, adicional4, adicional5, bebida1, bebida2, bebida3};
    cout << "PLATOS PRINCIPALES:" << endl;
    cout << setw(85) << setfill('-') << "" << endl; // Línea divisoria
    cout << left << setw(75) << "Platillos:" << right << setw(10) << "Precio:" << endl;
    cout << "\n";
    for (int i = 0; i < 4; i++) {
        cout << "Platillo " << i + 1 << ":" << endl;
        cout << left << setw(75) << setfill(' ') << carta[i].descripcion 
             << right << setw(7) << "S/." 
             << setw(4) << fixed << setprecision(2) << carta[i].precio << endl;
        cout << "\n";
    }
    cout << "\n";
    cout << "PLATOS ADICIONALES :" << endl;
    cout << setw(85) << setfill('-') << "" << endl; // Línea divisoria
    cout << left << setw(75) << "Platillos:" << right << setw(10) << "Precio:" << endl;
    cout << "\n";
    for (int i = 4; i < 9; i++) {
        cout << "Platillo " << i << ":" << endl;
        cout << left << setw(75) << setfill(' ') << carta[i].descripcion 
             << right << setw(7) << "S/." 
             << setw(4) << fixed << setprecision(2) << carta[i].precio << endl;
        cout << "\n";
    }
     cout << "\n";
    cout << "BEBIDAS :" << endl;
    cout << setw(85) << setfill('-') << "" << endl; // Línea divisoria
    cout << left << setw(75) << "Platillos:" << right << setw(10) << "Precio:" << endl;
    cout << "\n";
    for (int i = 4; i < 9; i++) {
        cout << "Platillo " << i << ":" << endl;
        cout << left << setw(75) << setfill(' ') << carta[i].descripcion 
             << right << setw(7) << "S/." 
             << setw(4) << fixed << setprecision(2) << carta[i].precio << endl;
        cout << "\n";
    }
    system("pause");
}

//Función para comprobar la longitud y el uso de algunos caracteres
bool comprobarcarac(char x[], int n) {
    int r = 0, i = 0, h = 0;
    if (n<20){
	    if (strlen(x) != n) {
	        r++;
	    }
	}
    if (r == 0) {
        while (i < n && h == 0) {
        	if (n<20){
	            if (x[i] == ' ')
	                h++;
        	}
            if (x[i] == '|')
            	h++;
            i++;
        }
    }
    if (h != 0) {
        r++;
    }
    if (r == 0) {
        return true;
    } else {
        return false;
    }
}


void interfazTrabajador() {
    cout << "Estamos trabajando..." << endl;
}
