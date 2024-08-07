//Falta mejorar la opcion de ver los pedidos de los clientes


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
    int puntaje;
    int ingresos;
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
  adicional2 = {6, "PORCI�N DE PAPAS FAMILIARES", 14.90},
  adicional3 = {7, "1/2 PORCI�N DE PAPAS FAMILIARES", 9.90},
  adicional4 = {8, "ENSALADA CL�SICA", 10.00},
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
  producto6 = {"lim�n", 20000},
  producto7 = {"ma�z morado", 20000},
  producto8 = {"az�car", 10000};

bool comprobarcarac(char [], int);
void copiarLineas(string [], cliente , int , int );
int contarLineas(ifstream &);
int buscarLinea(char [], ifstream &);
void interfazClienteCompra(char []);
void interfazcarta();
void interfazClientePrincipal(char []);
void sesionUsuario();
void registroUsuario();
void interfazCliente();
void interfazTrabajador();
void sesionTrabajador();
void opcionesTrabajador();
void visualizarPedido();

//Interfaz para seleccionar si es cliente o trabajador
int main() {
    setlocale(LC_CTYPE, "Spanish");
    char identificacion[10];
    bool error = false;
    trabajador trabajadores[5] = {trabajador1, trabajador2, trabajador3, trabajador4, trabajador5};
    stock productos[9] = {producto1, producto2, producto3, producto4, producto5, producto6, producto7, producto8};

    cout << "Ingrese su identificaci�n o Salir para finalizar el programa" << endl;
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
            cout << "\nIdentificaci�n no v�lida. Int�ntelo de nuevo: \n";
        }
    } while (error);

    return 0;
}

//Interfaz para el inicio de sesi�n o el registro del cliente
void interfazCliente() {
    setlocale(LC_CTYPE, "Spanish");
    int opciones, h = 0;
    bool error = false ;
    	do{
        cout << "Seleccione una opci�n: " << endl;
        cout << "1. Iniciar Sesi�n" << endl;
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
                cout << "\nOpci�n no v�lida. Int�ntelo de nuevo: \n";
            }
        } while (error);
    	} while (h==0);
}

//Interfaz para el inicio de sesi�n
void sesionUsuario() {
    cliente y;
    int h = 0;
    string us;
    char usc[11];
    char con[9];
    bool correcto = false;
    ifstream sm("Datos_de_los_clientes.txt", ios_base::in);
    if (!sm.is_open()) {
        cout << "Primero reg�strese." << endl;
        return;
    }
    else{
	    cin.ignore();
	    while (!correcto) {
	        h = 0; // Reiniciar el indicador de usuario encontrado
	        cout << "Ingrese su usuario (10 caracteres): ";
	        gets(y.usuario_Cliente);
	        while (comprobarcarac(y.usuario_Cliente, 10) == false) {
	            cout << "\nUsuario no v�lido (solo 10 caracteres, no espacios ni el caracter | ). Int�ntelo de nuevo: \n";
	            gets(y.usuario_Cliente);
	        }
	        sm.clear();
	        sm.seekg(0);
	        while (!sm.eof() && h == 0) {
	            getline(sm, us, '|');
	            strcpy(usc, us.c_str());
	            if (strcmp(usc, y.usuario_Cliente) == 0) {
	                h++;
	                getline(sm, us, '|'); // Leer la contrase�a
	                strcpy(con, us.c_str()); // Almacenar la contrase�a le�da
	                getline(sm, us); // Leer el resto de la l�nea
	            } else {
	                getline(sm, us); // Leer el resto de la l�nea si el usuario no coincide
	            }
	        }
	        if (h == 0) {
	            cout << "No existe el usuario\n";
	            continue;
	        }
	        
	        cout << "Ingrese su contrase�a (8 caracteres): ";
	        gets(y.contrasena_Cliente);
	        while (comprobarcarac(y.contrasena_Cliente, 8) == false) {
	            cout << "\nContrase�a no v�lida (solo 8 caracteres, no espacios ni el caracter | ). Int�ntelo de nuevo: \n";
	            gets(y.contrasena_Cliente);
	            cout << "\n";
	        }
	        
	        if (strcmp(con, y.contrasena_Cliente) == 0) {
	            cout << "Inicio de sesi�n exitoso.\n";
	             system("pause");
	            system("cls");
	            interfazClientePrincipal(usc);
	            correcto = true;
	        } else {
	            cout << "Contrase�a incorrecta.\n";
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
        cout << "\nNombre no v�lido (No debe contener el caracter | y ser menor a 30 caracteres). Int�ntelo de nuevo: \n";
        gets(x.nombre_Cliente);
    }
    cout << "Ingrese sus apellidos: ";
    gets(x.apellidos_Cliente);
    while (comprobarcarac(x.apellidos_Cliente, 30) == false) {
        cout << "\nApellidos no v�lidos (No debe contener el caracter | y ser menor a 30 caracteres). Int�ntelo de nuevo: \n";
        gets(x.apellidos_Cliente);
    }
    cout << "Ingrese su documento de DNI: ";
    gets(x.documento_Cliente);
    while (strlen(x.documento_Cliente) != 8 || strspn(x.documento_Cliente, "0123456789") != 8) {
        cout << "\nDocumento no v�lido. Int�ntelo de nuevo: \n";
        gets(x.documento_Cliente);
    }
    do {
        h = 1;
        cout << "Ingrese su usuario (10 caracteres): ";
        gets(x.usuario_Cliente);
        while (comprobarcarac(x.usuario_Cliente, 10) == false) {
            cout << "\nUsuario no v�lido (solo 10 caracteres, no espacios ni el caracter | ). Int�ntelo de nuevo: \n";
            gets(x.usuario_Cliente);
        }
        ms.clear();
        ms.seekg(0);
        while (!ms.eof() && h == 1) {
            getline(ms, us, '|');
            if (strcmp(us.c_str(), x.usuario_Cliente) == 0) {
                h = 0;
            }
            getline(ms, us); // Leer el resto de la l�nea
        }
        if (h == 0) {
        	cout<<endl;
            cout << "Ya existe el usuario "<<endl;
            cout<<endl;
        }
    } while (h == 0);
    cout << "Ingrese su contrase�a (8 caracteres): ";
    gets(x.contrasena_Cliente);
    while (comprobarcarac(x.contrasena_Cliente, 8) == false) {
        cout << "\nContrase�a no v�lida (solo 8 caracteres, no espacios ni el caracter | ). Int�ntelo de nuevo: \n";
        gets(x.contrasena_Cliente);
    }
    
    cout << "Usuario Registrado\n";
    system("pause");
    es <<"USUARIO "<< "|" <<" CONTRASE�A "<< "|" <<" NOMBRES " << "|" << " APELLIDOS "<< "|" << " DOCUMENTO " << "|" << " PUNTOS " <<"|" << " CONSUMO " <<"|" << endl;
    es << x.usuario_Cliente << "|" << x.contrasena_Cliente << "|" << x.nombre_Cliente << "|" << x.apellidos_Cliente << "|" << x.documento_Cliente << "|" << x.puntos << "|" << x.consumo << "|" << endl;
    es.close();
    ms.close();
}

//Interfaz para el cliente despues de inciar sesi�n
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
                getline(dat, aux, '|'); // Leer la contrase�a
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
                getline(dat, aux); // Leer el resto de la l�nea si el usuario no coincide
            }
        }
        if (encontrado) {
        	do {
        	cout << "Bienvenido " << y.nombre_Cliente << endl;
        	cout << "Elija la opci�n que desee: "<< endl;
        	cout << "1. Carta: " << endl;
            cout << "2. Comprar: " << endl;
            cout << "3. Informaci�n del usuario: " << endl;
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
		                cout << "\nOpci�n no v�lida. Int�ntelo de nuevo: \n";
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
    cout << setw(85) << setfill('-') << "" << endl; // L�nea divisoria
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
    cout << setw(85) << setfill('-') << "" << endl; // L�nea divisoria
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
    cout << setw(85) << setfill('-') << "" << endl; // L�nea divisoria
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
        getline(dat, aux[(nl/2)-1], '|'); // Leer la contrase�a
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
        ofstream pedido("pedido_cliente.txt", ios_base::out | ios_base::app);

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
			cout << "\nOpci�n no v�lida. Int�ntelo de nuevo: \n";
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
					cout << "\nOpci�n no v�lida. Int�ntelo de nuevo: \n";
					cin>>opciones;
					cout << "\n";
					}
	    			cout << "Elija la cantidad: "; cin>>cant;
	    			while (cant<1){
						cout << "\nOpci�n no v�lida. Int�ntelo de nuevo: \n";
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
			        cout << "\nOpci�n no v�lida. Int�ntelo de nuevo: \n";
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
		    cout << "�Desea alg�n adicional? (s/n): ";
		    else
		    cout << "�Desea alg�n adicional extra? (s/n): ";
		    do {
		        cin>>s_n;;
		        if ('S' == toupper(s_n)) {
		        	x2=1;
		        	cout << "Seleccione el adicional a comprar: "<< endl;
		        	cin>>opciones;
		        	while (opciones<1 || opciones>5){
						cout << "\nOpci�n no v�lida. Int�ntelo de nuevo: \n";
						cin>>opciones;
						cout << "\n";
					}
	    			cout << "Elija la cantidad: "; cin>>cant;
	    			while (cant<1){
						cout << "\nOpci�n no v�lida. Int�ntelo de nuevo: \n";
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
			        cout << "\nOpci�n no v�lida. Int�ntelo de nuevo: \n";
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
		    cout << "�Desea alguna bebida? (s/n): ";
		    else
		    cout << "�Desea alguna bebida adicional? (s/n): ";
		    do {
		        cin>>s_n;;
		        if ('S' == toupper(s_n)) {
		        	x2=1;
		        	cout << "Seleccione la bebidad a comprar: "<< endl;
		        	cin>>opciones;
		        	while (opciones<1 || opciones>3){
						cout << "\nOpci�n no v�lida. Int�ntelo de nuevo: \n";
						cin>>opciones;
						cout << "\n";
					}
	    			cout << "Elija la cantidad: "; cin>>cant;
	    			while (cant<1){
						cout << "\nOpci�n no v�lida. Int�ntelo de nuevo: \n";
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
			        cout << "\nOpci�n no v�lida. Int�ntelo de nuevo: \n";
			    }
		    } while (error);
		} while (error2);
		cout << "El total es de: S/."<< fixed << setprecision(2) << total << endl;
        pedido << "Total: S/." << fixed << setprecision(2) << total << endl;
        pedido.close();
		if (total>=75)
		y.puntos++;
		y.consumo++;
		cout << "�Desea calificarnos? (s/n): ";
		    do {
		        cin>>s_n;;
		        if ('S' == toupper(s_n)) {
		        	x2=1;
		        	cout << "Ingrese una puntuaci�n del 1 al 5: "<< endl;
		        	cin>>opciones;
		        		while (opciones<1 || opciones>5){
						cout << "\nOpci�n no v�lida. Int�ntelo de nuevo: \n";
						cin>>opciones;
						cout << "\n";
					}
			    	error = false;
			    } else if ('N' == toupper(s_n)) {
			        cout << endl;
			        error = false;
			    } else {
			        error = true;
			        cout << "\nOpci�n no v�lida. Int�ntelo de nuevo: \n";
			    }
		    } while (error);
		    copiarLineas(aux, y, nl/2, nt/2);
    }
    dat.close();
    cout << "Compra realizada con �xito \n";
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

void copiarLineas(string aux[], cliente y, int nl, int nt){
	ofstream newdat("Datos_de_los_clientes.txt", ios_base::trunc);
    if (!newdat.is_open()) {
        cout << "Error al abrir el archivo." << endl;
    } else {
    	for (int i = 0; i < nl-1; i++) {
    		newdat <<"USUARIO "<< "|" <<" CONTRASE�A "<< "|" <<" NOMBRES " << "|" << " APELLIDOS "<< "|" << " DOCUMENTO " << "|" << " PUNTOS " <<"|" << " CONSUMO " <<"|" << endl;
            newdat << aux[i] << endl;
        }
        
        newdat <<"USUARIO "<< "|" <<" CONTRASE�A "<< "|" <<" NOMBRES " << "|" << " APELLIDOS "<< "|" << " DOCUMENTO " << "|" << " PUNTOS " <<"|" << " CONSUMO " <<"|" << endl;
        newdat << y.usuario_Cliente << "|" << y.contrasena_Cliente << "|" << y.nombre_Cliente << "|" << y.apellidos_Cliente << "|" << y.documento_Cliente << "|" << y.puntos << "|" << y.consumo << "|" << endl;
        
		for (int i = nl; i < nt; i++) {
        	newdat <<"USUARIO "<< "|" <<" CONTRASE�A "<< "|" <<" NOMBRES " << "|" << " APELLIDOS "<< "|" << " DOCUMENTO " << "|" << " PUNTOS " <<"|" << " CONSUMO " <<"|" << endl;
            newdat << aux[i] << endl;
    	}
}
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
    return -1; // Devuelve -1 si no se encontr� la l�nea
}

//Funci�n para comprobar la longitud y el uso de algunos caracteres
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

//Interfaz para el trabajador
void interfazTrabajador() {
    setlocale(LC_CTYPE, "Spanish");
    int opciones;
    bool error = false;
        cout << "Seleccione una opci�n: " << endl;
        cout << "1. Iniciar Sesi�n" << endl;
        cout << "2. Salir" << endl;
        do {
            cin >> opciones;
            if (opciones == 1) {
            	system("cls");
            	sesionTrabajador();
            	error = false;
            } else if (opciones == 2) {
                cout << "Saliendo..." << endl;
                error = false;
            } else {
                error = true;
                cout << "\nOpci�n no v�lida. Int�ntelo de nuevo: \n";
            }
        } while (error);
}
//Verficacion del usuario
void sesionTrabajador() {
    string nomUsua;
    string contra;
    bool error;

    do {
        cout << "Ingrese el usuario: ";
        cin >> nomUsua;

        if (nomUsua == trabajador1.user || nomUsua == trabajador2.user) {
            cout << "Ingrese su contrase�a: ";
            cin >> contra;

            if ((nomUsua == trabajador1.user && contra == trabajador1.contrasena) || 
                (nomUsua == trabajador2.user && contra == trabajador2.contrasena)) {
                cout << "Ingresando..." << endl;
                cout << "Presione cualquier tecla para continuar..." << endl;
                cin.ignore();
                cin.get();
                system("cls");
                opcionesTrabajador();
                error = false;
            } else {
                cout << "Contrase�a incorrecta. Por favor, intente de nuevo." << endl;
                error = true;
            }
        } else {
            cout << "Usuario no encontrado. Por favor, intente de nuevo." << endl;
            error = true;
        }
    } while (error);
}

//Ver los pedidos de los clientes
void visualizarPedido() {
    ifstream pedido("pedido_cliente.txt");
    if (!pedido.is_open()) {
        cout << "Error al abrir el archivo de pedidos." << endl;
        return;
    }
    string linea;
    cout << "Pedidos realizados:" << endl;
    while (getline(pedido, linea)) {
        cout << linea << endl;
    }
    pedido.close();
}

//Opciones disponibles para el trabajador
void opcionesTrabajador() {
    int opcion = 0;
    while (opcion != 3) {
        cout << "Men� del Trabajador" << endl;
        cout << "1. Ver �rdenes" << endl;
        cout << "2. Ver stock" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opci�n: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
            	system("cls");
                cout << "\nMostrando �rdenes..." << endl;
                visualizarPedido();
                cout<<"\nPresione una tecla para volver... ";
                cin.ignore();
                cin.get();
                system("cls");
                break;
            case 2:
            	system("cls");
                cout << "\nMostrando stock...\n" << endl;
                cout<<producto1.nomProducto<<" = "<<producto1.cantidad<<endl ;
                cout<<producto2.nomProducto<<" = "<<producto2.cantidad<<endl ;
                cout<<producto3.nomProducto<<" = "<<producto3.cantidad<<endl ;
                cout<<producto4.nomProducto<<" = "<<producto4.cantidad<<endl ;
                cout<<producto5.nomProducto<<" = "<<producto5.cantidad<<endl ;
                cout<<producto6.nomProducto<<" = "<<producto6.cantidad<<endl ;
                cout<<producto7.nomProducto<<" = "<<producto7.cantidad<<endl ;
                cout<<producto8.nomProducto<<" = "<<producto8.cantidad<<endl ;
                cout<<"\nPresione una tecla para volver... ";
                cin.ignore();
                cin.get();
                system("cls");
                break;
            case 3:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opci�n inv�lida. Por favor, intente de nuevo." << endl;
                break;
        }
        cout << endl;
    }
}
