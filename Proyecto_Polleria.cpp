#include<iostream>
#include<string.h>
#include<locale.h>

void interfazCliente();
void interfazTrabajador();

struct cliente{
	char nombre_Cliente[30];
	char documento_Cliente[10];
	int puntos;	
	int consumo;
}
cliente1,
cliente2,
cliente3,
cliente4,
cliente5,
cliente6,
cliente7,
cliente8,
cliente9,
cliente10;

struct menu{
    char descripcion[20];
    float precio;  
}
plato1={"1 pollo",47.00},
plato2={"1/2 pollo",23.00},
plato3={"1/4 pollo",12.00},
plato4={"1/8 pollo",8.00},
plato5={"porción de papas",15.00},
plato6={"1/2 porción de papas",10.00},
plato7={"ensalada",10.00},
bebida1={"gaseosa 3L",13.00},
bebida2={"limonada 1L",15.00},
bebida3={"chicha 1L",15.00};

struct trabajador{
	char nombre_Trabajador[30];
	char documento_Trabajador[10];		
	char user[20];
	char contraseña[4];
	char cargo[15];	
}
trabajador1={"Pepe Quintana","32356489","pepequin","6489","gerente"},
trabajador2={"Alexandra Vargas","56236979","alexvar","6979","subgerente"},
trabajador3={"Diego Aguilar","45638679","diegoagui","8679","mozo"},
trabajador4={"Gerardo Carrillo","71556889","gerardoca","6889","mozo"},
trabajador5={"Mariana Mendoza","23132565","marianamen","2565","mozo"};

struct stock{
	float 
	float
	float	
};

int main(){
	char identificacion[10];
	bool error=false;
	cliente clientes[10] = {cliente1,cliente2,cliente3,cliente4,cliente5,cliente6,cliente7,cliente8,cliente9,cliente10};
	menu carta[10] = {plato1,plato2,plato3,plato4,plato5,plato6,plato7,bebida1,bebida2,bebida3}; 
	trabajador trabajadores[5] = {trabajador1,trabajador2,trabajador3,trabajador4,trabajador5};
	
	do{
	cout<<"¿Es trabajador o cliente?"<<endl;
	gets(identificacion);
    if(strcmp(identificacion, "cliente") == 0 || strcmp(identificacion, "Cliente") == 0){
    interfazCliente();	
	}
    else if(strcmp(identificacion, "trabajador") == 0 || strcmp(identificacion, "Trabajador") == 0){
    	
	}else{
            error = true;
            cout << "Identificación no válida. Inténtelo de nuevo.\n";
	}
    }while(error);
	
		
	return 0;
}

void interfazCliente(){
	bool error=false;
	do{
    cout<<"Por favor ingrese su nombre: "
	}while(error);

	cout<<"Nuestra carta es: "<<endl;
	cout<<"Platillos"<<"\t"<<"Precio\n";
	for(int i=0;i<10;i++){
	cout<<carta[i].descripcion<<"\t"<<carta[i].precio<<"\n";
	}
}

void interfazTrabajador(){
	
	
	
}



//4 trabajores fijos
//struct cliente (nombre, dni, fecha de nacimiento, puntos (ofertas))
//struct stock (nombre del producto (pollo, porción de papas (gramos), bebidas)
//struct precios 
//

