
//Falta las funciones de los trabajadores dependiendo del cargo




#include <iostream>
#include <string>
#include <cstring>
#include <windows.h>
#include <locale.h>
#include <fstream>
#include <cctype>
#include <iomanip>

using namespace std;

struct cliente {
    char nombre_Cliente[30];
    char apellidos_Cliente[30];
    char documento_Cliente[9];
    char usuario_Cliente[11];
    char contrasena_Cliente[9];
    int puntos;
    int consumo;
};

struct polleria {
	float ingresos;
	float puntaje;
    int cantpuntaje;
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
    char nombre_Trabajador[30];
    char apellidos_Trabajador[30];
    char documento_Trabajador[9];
    char usuario_Trabajador[11];
    char contrasena_Trabajador[9];
    char cargo[16];
    
} trabajador1 = {"Luis Alfredo","Paredes Quintana", "32356489", "Luisparqui", "12345670", "Gerente"},
  trabajador2 = {"Claudia Elisa","Vargas Lopez", "56236979", "Clauvarlop", "12345671", "Subgerente"};

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

bool comprobarcarac(char [], int);
void puntosD(cliente &, float &);
bool actualizardatosP(polleria, char);
void copiarLineas(string [], cliente , int , int );
int contarLineas(ifstream &);
int buscarLinea(char [], ifstream &);
void interfazClienteCompra(char []);
void interfazcarta();
void interfazClientePrincipal(char []);
void sesionUsuario();
void registroUsuario();
void interfazCliente();
bool existeArchivo();
void interfazTrabajador();
void interfazsesionTrabajador();


//Interfaz para seleccionar si es cliente o trabajador
int main() {
    setlocale(LC_CTYPE, "Spanish");
    char identificacion[10];
    bool error = false;
    
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
        	system("cls");
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
    int opciones, h = 0;
    bool error = false ;
    	do{
        cout << "Seleccione una opción: " << endl;
        cout << "1. Iniciar Sesión" << endl;
        cout << "2. Registrarse" << endl;
        cout << "3. Salir" << endl;
        do {
            cin >> opciones;
            if (opciones == 1) {
            	h++;
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
                h++;
                error = false;
            } else {
                error = true;
                cout << "\nOpción no válida. Inténtelo de nuevo: \n";
            }
        } while (error);
    	} while (h==0);
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
        cout << "Primero regístrese." << endl;
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
    es <<" USUARIO "<< "|" <<" CONTRASEÑA "<< "|" <<" NOMBRES " << "|" << " APELLIDOS "<< "|" << " DOCUMENTO " << "|" << " PUNTOS " <<"|" << " CONSUMO " <<"|" << endl;
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
                strcpy(y.usuario_Cliente, x);
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
		                interfazClienteCompra(y.usuario_Cliente);
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

//Interfaz para la compra
void interfazClienteCompra(char x[]){
	cliente y;
    polleria p;
    menu carta[12] = {plato1, plato2, plato3, plato4, adicional1, adicional2, adicional3, adicional4, adicional5, bebida1, bebida2, bebida3};
    int opciones, cant, nt, nl, x2;
    float total = 0;
    char s_n;
    bool error, error2;
    ifstream dat("Datos_de_los_clientes.txt", ios_base::in);

    if (!dat.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return;
    } else {
        nt = contarLineas(dat);
        string aux[nt];
        nl = buscarLinea(x, dat);
        dat.clear();
        dat.seekg(0);

        for (int i = 0; i < (nl/2)-1; i++) {
            getline(dat, aux[i]);
            getline(dat, aux[i]);
        }
		getline(dat, aux[(nl/2)-1]);
        getline(dat, aux[(nl/2)-1], '|');
        strcpy(y.usuario_Cliente, aux[(nl/2)-1].c_str());
        getline(dat, aux[(nl/2)-1], '|'); // Leer la contraseña
        strcpy(y.contrasena_Cliente, aux[(nl/2)-1].c_str());
        getline(dat, aux[(nl/2)-1], '|'); // Leer el nombre
        strcpy(y.nombre_Cliente, aux[(nl/2)-1].c_str());
        getline(dat, aux[(nl/2)-1], '|'); // Leer los apellidos
        strcpy(y.apellidos_Cliente, aux[(nl/2)-1].c_str());
        getline(dat, aux[(nl/2)-1], '|'); // Leer el documento
        strcpy(y.documento_Cliente, aux[(nl/2)-1].c_str());
        getline(dat, aux[(nl/2)-1], '|'); // Leer los puntos
        y.puntos = atoi(aux[(nl/2)-1].c_str());
        getline(dat, aux[(nl/2)-1], '|'); // Leer el consumo
        y.consumo = atoi(aux[(nl/2)-1].c_str());
        getline(dat, aux[(nl/2)-1]);
		

        for (int i = (nl/2); i < (nt/2); i++) {
            getline(dat, aux[i]);
            getline(dat, aux[i]);
        }

		cout << left << setw(75) << "Platillos:" << right << setw(10) << "Precio:" << endl;
	    cout << "\n";
	    for (int j = 0; j < 4; j++) {
	        cout << "Platillo " << j + 1 << ":" << endl;
	        cout << left << setw(75) << setfill(' ') << carta[j].descripcion 
	            << right << setw(7) << "S/." 
	            << setw(4) << fixed << setprecision(2) << carta[j].precio << endl;
	        cout << "\n";    
	    }
	    cout << "Seleccione el plato a comprar (1-4): "; 
		cin>>opciones;
		while (opciones<1 || opciones>4){
			cout << "\nOpción no válida. Inténtelo de nuevo: \n";
			cin>>opciones;
			cout << "\n";
		}
	    cout << "Elija la cantidad: "; cin>>cant;
	    total=carta[opciones-1].precio*cant;
	    do {
		    cout << "Desea otro platillo (s/n): ";
		    do {
		        cin>>s_n;;
		        if ('S' == toupper(s_n)) {
		        	cout << "Seleccione el plato a comprar: "<< endl;
		        	cin>>opciones;
		        	while (opciones<1 || opciones>4){
					cout << "\nOpción no válida. Inténtelo de nuevo: \n";
					cin>>opciones;
					cout << "\n";
					}
	    			cout << "Elija la cantidad: "; cin>>cant;
	    			while (cant<1){
						cout << "\nOpción no válida. Inténtelo de nuevo: \n";
						cin>>cant;
						cout << "\n";
					}
	   				total=carta[opciones-1].precio*cant + total;
			    	error = false;
			    	error2 = true;
			    } else if ('N' == toupper(s_n)) {
			        cout << endl;
			        cout << endl;
			        error = false;
			        error2 = false;
			    } else {
			        error = true;
			        cout << "\nOpción no válida. Inténtelo de nuevo: \n";
			    }
		    } while (error);
		} while (error2);
		
		x2=0;
		cout << left << setw(75) << "Adicional:" << right << setw(10) << "Precio:" << endl;
	    cout << "\n";
	    for (int j = 0; j < 5; j++) {
	        cout << "Adicional " << j + 1 << ":" << endl;
	        cout << left << setw(75) << setfill(' ') << carta[j+4].descripcion 
	             << right << setw(7) << "S/." 
	             << setw(4) << fixed << setprecision(2) << carta[j+4].precio << endl;
	        cout << "\n";    
	    }
		do {
			if(x2==0)
		    cout << "¿Desea algún adicional? (s/n): ";
		    else
		    cout << "¿Desea algún adicional extra? (s/n): ";
		    do {
		        cin>>s_n;;
		        if ('S' == toupper(s_n)) {
		        	x2=1;
		        	cout << "Seleccione el adicional a comprar: "<< endl;
		        	cin>>opciones;
		        	while (opciones<1 || opciones>5){
						cout << "\nOpción no válida. Inténtelo de nuevo: \n";
						cin>>opciones;
						cout << "\n";
					}
	    			cout << "Elija la cantidad: "; cin>>cant;
	    			while (cant<1){
						cout << "\nOpción no válida. Inténtelo de nuevo: \n";
						cin>>cant;
						cout << "\n";
					}
	   				total=carta[opciones+3].precio*cant + total;
			    	error = false;
			    	error2 = true;
			    } else if ('N' == toupper(s_n)) {
			        cout << endl;
			        error = false;
			        error2 = false;
			    } else {
			        error = true;
			        cout << "\nOpción no válida. Inténtelo de nuevo: \n";
			    }
		    } while (error);
		} while (error2);
	    
	    x2=0;
	    cout << left << setw(75) << "Bebidas:" << right << setw(10) << "Precio:" << endl;
	    cout << "\n";
	    for (int j = 0; j < 3; j++) {
	        cout << "Bebida " << j + 1 << ":" << endl;
	        cout << left << setw(75) << setfill(' ') << carta[j+9].descripcion 
	            << right << setw(7) << "S/." 
	            << setw(4) << fixed << setprecision(2) << carta[j+9].precio << endl;
	        cout << "\n";    
	    }
		do {
		    if(x2==0)
		    cout << "¿Desea alguna bebida? (s/n): ";
		    else
		    cout << "¿Desea alguna bebida adicional? (s/n): ";
		    do {
		        cin>>s_n;;
		        if ('S' == toupper(s_n)) {
		        	x2=1;
		        	cout << "Seleccione la bebidad a comprar: "<< endl;
		        	cin>>opciones;
		        	while (opciones<1 || opciones>3){
						cout << "\nOpción no válida. Inténtelo de nuevo: \n";
						cin>>opciones;
						cout << "\n";
					}
	    			cout << "Elija la cantidad: "; cin>>cant;
	    			while (cant<1){
						cout << "\nOpción no válida. Inténtelo de nuevo: \n";
						cin>>cant;
						cout << "\n";
					}
	   				total=carta[opciones+8].precio*cant + total;
			    	error = false;
			    	error2 = true;
			    } else if ('N' == toupper(s_n)) {
			        cout << endl;
			        error = false;
			        error2 = false;
			    } else {
			        error = true;
			        cout << "\nOpción no válida. Inténtelo de nuevo: \n";
			    }
		    } while (error);
		} while (error2);
		cout << "El total es de: S/."<< fixed << setprecision(2) << total << endl;
		if (total>=75)
			y.puntos++;
		y.consumo++;
		if (y.puntos>=5)
			puntosD(y, total);
		p.ingresos=total;
		cout << "¿Desea calificarnos? (s/n): ";
		    do {
		        cin>>s_n;;
		        if ('S' == toupper(s_n)) {
		        	x2=1;
		        	cout << "Ingrese una puntuación del 1 al 5: "<< endl;
		        	cin>>p.puntaje;
		        	while (p.puntaje<1 || p.puntaje>5){
						cout << "\nOpción no válida. Inténtelo de nuevo: \n";
						cin>>p.puntaje;
						cout << "\n";
					}
					while (actualizardatosP(p, s_n) == false){
					}
			    	error = false;
			    } else if ('N' == toupper(s_n)) {
			    	while (actualizardatosP(p, s_n) == false){
						}
					cout << "\n";
			        cout << endl;
			        error = false;
			    } else {
			        error = true;
			        cout << "\nOpción no válida. Inténtelo de nuevo: \n";
			    }
		    } while (error);
		    copiarLineas(aux, y, nl/2, nt/2);
    }
    dat.close();
    cout << "Compra realizada con éxito \n";
    system("pause");
}	

int contarLineas(ifstream &y){
	int lineas = 0;
	string aux;
	while (!y.eof()){
            getline(y, aux);
            lineas ++;
        }
	return lineas-1;
}

bool actualizardatosP(polleria p, char s){
	string aux;
	polleria paux;
	bool existe;
	ifstream datp("Datos_de_la_polleria.txt", ios_base::in);
    if (!datp.is_open()) {
        ofstream es("Datos_de_la_polleria.txt", ios_base::app);
        if (!es.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        datp.close();
        return true;
    	}
    	es <<" GANANCIAS "<< "|" <<" PUNTUACIÓN "<< "|" <<" N° PUNTUACIONES " <<"|" << endl;
        es << "0|0|0|" << endl;
        es.close();
        return false;
    } else {
    	getline(datp, aux);
        getline(datp, aux, '|');
    	paux.ingresos = atof(aux.c_str());
    	getline(datp, aux, '|');
    	paux.puntaje = atof(aux.c_str());
    	getline(datp, aux, '|');
    	paux.cantpuntaje = atoi(aux.c_str());
    	getline(datp, aux);
    	paux.ingresos = paux.ingresos + p.ingresos;
    	if ('S'== toupper(s)){
			paux.cantpuntaje++;
			paux.puntaje=(paux.puntaje*(paux.cantpuntaje-1)+p.puntaje)/paux.cantpuntaje;
			ofstream es("Datos_de_la_polleria.txt", ios_base::trunc);
			 if (!es.is_open()) {
	        	cout << "Error al abrir y editar el archivo ." << endl;
	    	} else {
	    		es <<" GANANCIAS "<< "|" <<" PUNTUACIÓN "<< "|" <<" N° PUNTUACIONES " <<"|" << endl;
	    		es <<paux.ingresos<< "|" << fixed << setprecision(2) << paux.puntaje<< "|" <<paux.cantpuntaje<<"|" << endl;
	    		es.close();
			}
			datp.close();
			cout << "Gracias por su valoración" << endl;
		}
		else if ('N'== toupper(s)){
			ofstream es("Datos_de_la_polleria.txt", ios_base::trunc);
			 if (!es.is_open()) {
	        	cout << "Error al abrir y editar el archivo ." << endl;
	    	} else {
	    		es <<" GANANCIAS "<< "|" <<" PUNTUACIÓN "<< "|" <<" N° PUNTUACIONES " <<"|" << endl;
	    		es <<paux.ingresos<< "|" << fixed << setprecision(2) << paux.puntaje<< "|" <<paux.cantpuntaje<<"|" << endl;
	    		es.close();
			}
			datp.close();
			cout << "Gracias por su compra." << endl;
		}
		return true;
	}
}


void copiarLineas(string aux[], cliente y, int nl, int nt){
	ofstream newdat("Datos_de_los_clientes.txt", ios_base::trunc);
    if (!newdat.is_open()) {
        cout << "Error al abrir el archivo." << endl;
    } else {
    	for (int i = 0; i < nl-1; i++) {
    		newdat <<" USUARIO "<< "|" <<" CONTRASEÑA "<< "|" <<" NOMBRES " << "|" << " APELLIDOS "<< "|" << " DOCUMENTO " << "|" << " PUNTOS " <<"|" << " CONSUMO " <<"|" << endl;
            newdat << aux[i] << endl;
        }
        
        newdat <<" USUARIO "<< "|" <<" CONTRASEÑA "<< "|" <<" NOMBRES " << "|" << " APELLIDOS "<< "|" << " DOCUMENTO " << "|" << " PUNTOS " <<"|" << " CONSUMO " <<"|" << endl;
        newdat << y.usuario_Cliente << "|" << y.contrasena_Cliente << "|" << y.nombre_Cliente << "|" << y.apellidos_Cliente << "|" << y.documento_Cliente << "|" << y.puntos << "|" << y.consumo << "|" << endl;
        
		for (int i = nl; i < nt; i++) {
        	newdat <<" USUARIO "<< "|" <<" CONTRASEÑA "<< "|" <<" NOMBRES " << "|" << " APELLIDOS "<< "|" << " DOCUMENTO " << "|" << " PUNTOS " <<"|" << " CONSUMO " <<"|" << endl;
            newdat << aux[i] << endl;
    	}
}
newdat.close();
}

int buscarLinea(char x[], ifstream &y) {
    int lineas = 0;
    string aux;
    bool encontrado = false;
    y.clear(); // Resetea las flags de eofbit, failbit y badbit
    y.seekg(0); // Vuelve al inicio del archivo
    while (!y.eof() && !encontrado) {
        getline(y, aux, '|');
        if (strcmp(aux.c_str(), x) == 0) {
            encontrado = true;
        } else {
            getline(y, aux);
        }
        lineas++;
    }
    if (encontrado = true)
    return lineas;
    else
    return -1; // Devuelve -1 si no se encontró la línea
}

void puntosD(cliente &x, float &total) {
	bool error;
	int aux, op;
	char s_n;
	cout << "¿Desea usar sus puntos para un descuento? (s/n): ";
		do {
		    cin>>s_n;;
		    if ('S' == toupper(s_n)) {
				aux=x.puntos/5;
				if (aux>6)
					aux=6;
				cout << "\nTiene "<<x.puntos<<" puntos\n";
				for (int i = 1; i <= aux; i++) {
				cout <<i<<". "<<i*5<< left << setw(15) <<" puntos"<<i*10<<"% de descuento"<<endl;
        		}
        		if (aux==1)
        		cout << "Escoja el descuento ("<<aux<<"): ";
        		else 
        		cout << "Escoja el descuento (1 - "<<aux<<"): ";
        		cin>>op;
		        while (op<1 || op>aux){
					cout << "\nOpción no válida. Inténtelo de nuevo: \n";
					cin>>op;
					cout << "\n";
				}
				x.puntos=x.puntos-op*5;
				total=total-(total*op*0.10);
				cout << "\nEl descuento se aplicó correctamente: \n";
				cout << "El nuevo precio es de: S/."<< fixed << setprecision(2) <<total<<endl;
				cout << "Sus puntos ahora son: "<<x.puntos<<endl;
			    error = false;
			} else if ('N' == toupper(s_n)) {
			    cout << endl;
			    error = false;
			} else {
			    error = true;
			    cout << "\nOpción no válida. Inténtelo de nuevo: \n";
			    }
		    } while (error);
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


bool existeArchivo(){
	trabajador y[2] = {trabajador1 , trabajador2};
	ifstream datp("Datos_de_los_trabajadores.txt", ios_base::in);
    if (!datp.is_open()) {
        ofstream es("Datos_de_los_trabajadores.txt", ios_base::app);
        if (!es.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        datp.close();
        return true;
    	}
    	for (int i =0;  i<=1; i++){
	    	es <<" USUARIO "<< "|" <<" CONTRASEÑA "<< "|" <<" NOMBRES " << "|" << " APELLIDOS "<< "|" << " DOCUMENTO " << "|" << " CARGO " <<"|" << endl;
	        es << y[i].usuario_Trabajador<< "|" << y[i].contrasena_Trabajador << "|" << y[i].nombre_Trabajador << "|" << y[i].apellidos_Trabajador << "|" << y[i].documento_Trabajador << "|" << y[i].cargo << "|" << endl;
		}
		es.close();
        return false;
    } else {
    	datp.close();
    	return true;
	}  
}

void interfazTrabajador() {
    setlocale(LC_CTYPE, "Spanish");
    int opciones;
    bool error = false;
        cout << "Seleccione una opción: " << endl;
        cout << "1. Iniciar Sesión" << endl;
        cout << "2. Salir" << endl;
        do {
            cin >> opciones;
            if (opciones == 1) {
            	system("cls");
            	interfazsesionTrabajador();
            	error = false;
            } else if (opciones == 2) {
                cout << "Saliendo..." << endl;
                error = false;
            } else {
                error = true;
                cout << "\nOpción no válida. Inténtelo de nuevo: \n";
            }
        } while (error);
}

void interfazsesionTrabajador(){
	trabajador y;
    int h = 0;
    string us;
    char usc[11];
    char con[9];
    bool correcto = false;
    while (existeArchivo() == false){
	}
    ifstream sm("Datos_de_los_trabajadores.txt", ios_base::in);
    if (!sm.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }
    else{
	    cin.ignore();
	    while (!correcto) {
	        h = 0; // Reiniciar el indicador de usuario encontrado
	        cout << "Ingrese su usuario (10 caracteres): ";
	        gets(y.usuario_Trabajador);
	        while (comprobarcarac(y.usuario_Trabajador, 10) == false) {
	            cout << "\nUsuario no válido (solo 10 caracteres, no espacios ni el caracter | ). Inténtelo de nuevo: \n";
	            gets(y.usuario_Trabajador);
	        }
	        sm.clear();
	        sm.seekg(0);
	        while (!sm.eof() && h == 0) {
	            getline(sm, us, '|');
	            strcpy(usc, us.c_str());
	            if (strcmp(usc, y.usuario_Trabajador) == 0) {
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
	        gets(y.contrasena_Trabajador);
	        while (comprobarcarac(y.contrasena_Trabajador, 8) == false) {
	            cout << "\nContraseña no válida (solo 8 caracteres, no espacios ni el caracter | ). Inténtelo de nuevo: \n";
	            gets(y.contrasena_Trabajador);
	            cout << "\n";
	        }
	        
	        if (strcmp(con, y.contrasena_Trabajador) == 0) {
	            cout << "Inicio de sesión exitoso.\n";
	             system("pause");
	            system("cls");
	            //interfazClientePrincipal(usc);
	            cout << "falta las opciones.\n";
	            correcto = true;
	        } else {
	            cout << "Contraseña incorrecta.\n";
	            correcto = false;
	        }
	    }
	    sm.close();
	}
}
