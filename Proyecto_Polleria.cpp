#include<iostream>
#include<string.h>
#include<windows.h>
#include<locale.h>
#include<fstream>

using namespace std;

void interfazCliente();
void interfazTrabajador();

struct cliente{
	char nombre_Cliente[25];
	char documento_Cliente[9];
	int puntos;	
	int consumo;
};

struct menu{
	int numero;
    char descripcion[25];
    float precio;  
}
plato1={1,"1 pollo",47.00},
plato2={2,"1/2 pollo",23.00},
plato3={3,"1/4 pollo",12.00},
plato4={4,"1/8 pollo",8.00},
plato5={5,"porción de papas",15.00},
plato6={6,"1/2 porción de papas",10.00},
plato7={7,"ensalada",10.00},
bebida1={8,"gaseosa 3L",13.00},
bebida2={9,"limonada frozen 1L",15.00},
bebida3={10,"chicha 1L",15.00};

struct trabajador{
	char nombre_Trabajador[25];
	char documento_Trabajador[10];		
	char user[15];
	char contrasena[6];
	char cargo[12];	
}
trabajador1={"Pepe Quintana","32356489","pepequin","6489","gerente"},
trabajador2={"Alexandra Vargas","56236979","alexvar","6979","subgerente"},
trabajador3={"Diego Aguilar","45638679","diegoagui","8679","mozo"},
trabajador4={"Gerardo Carrillo","71556889","gerardoca","6889","mozo"},
trabajador5={"Mariana Mendoza","23132565","marianamen","2565","mozo"};

struct stock{
	char nomProducto[15];
	float cantidad;
}
producto1={"pollo",40},
producto2={"papa",30000},
producto3={"lechuga",20},
producto4={"tomate",30},
producto5={"gaseosa",25},
producto6={"limón",20000},
producto7={"maíz morado",20000},
producto8={"azúcar",10000};

int main(){
	setlocale(LC_CTYPE, "Spanish");
	char identificacion[10];
	bool error=false;
	trabajador trabajadores[5] = {trabajador1,trabajador2,trabajador3,trabajador4,trabajador5};
	stock productos[9] = {producto1,producto2,producto3,producto4,producto5,producto6,producto7,producto8};
	
	do{
	cout<<"¿Es trabajador o cliente?"<<endl;
	gets(identificacion);
    if(strcmp(identificacion, "cliente") == 0 || strcmp(identificacion, "Cliente") == 0){
    interfazCliente();	
	}
    else if(strcmp(identificacion, "trabajador") == 0 || strcmp(identificacion, "Trabajador") == 0){
    interfazTrabajador();	
	}else{
            error = true;
            cout << "Identificación no válida. Inténtelo de nuevo.\n";
	}
    }while(error);
	
		
	return 0;
}

void interfazCliente(){
	setlocale(LC_CTYPE, "Spanish");
	ofstream es("Datos_de_los_clientes.txt", ios_base::out | ios_base::app);
    if (!es.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }
    int pedido;
    char respuesta;
	cliente x;
	menu carta[10] = {plato1,plato2,plato3,plato4,plato5,plato6,plato7,bebida1,bebida2,bebida3}; 
	float cuenta=0.0;
    
    cout<<"Ingrese su nombre: ";
    cin.ignore();
    gets(x.nombre_Cliente);
    cout<<"Ingrese su documento: ";
    gets(x.documento_Cliente);
    cout << "Datos almacenados correctamente." << endl;
    cout<<"<------Bienvenido "<<x.nombre_Cliente<<"------>"<<endl;
	cout<<"Nuestra carta: "<<endl;
	cout<<"Platillos"<<"\t"<<"\t"<<"Precio\n";
	for(int i=0;i<10;i++){
		if(strlen(carta[i].descripcion)>15)
	    cout<<i+1<<"."<<carta[i].descripcion<<"\t"<<carta[i].precio<<"\n";
	    else
	    cout<<i+1<<"."<<carta[i].descripcion<<"\t"<<"\t"<<carta[i].precio<<"\n";
	}
	do{
		cout<<"¿Qué desea pedir?\n";
		cin>>pedido;
		for(int i=0;i<10;i++){
			if(carta[i].numero==pedido){
			cuenta+=carta[i].precio;	
			}
		}
        cout << "¿Desea añadir algo más? (s/n): ";
        cin >> respuesta;
	}while(respuesta == 's' || respuesta == 'S');
	cout<<"El monto total a pagar será s/."<<cuenta;
	x.consumo++;  
	es << "Nombre del cliente" << "\t" << "\t" << "Documento" << "\t" << "\t" << "N° de consumos" <<endl;	  
	es << x.nombre_Cliente <<" \t "<<" \t "<< x.documento_Cliente <<" \t "<<" \t "<< x.consumo <<endl;
    es.close();
}

void interfazTrabajador(){
	setlocale(LC_CTYPE, "Spanish");
	cout<<"Estamos trabajando...";
	
	
}





//4 trabajores fijos
//struct cliente (nombre, dni, fecha de nacimiento, puntos (ofertas))
//struct stock (nombre del producto (pollo, porción de papas (gramos), bebidas)
//struct precios 
//

