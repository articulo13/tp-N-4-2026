#include<iostream>
#include<cstdio>

using namespace std;

struct Producto {    // estructura del stock 
	int   codigo;   
	char descripcion[50];   
	float precio;   
	int stockActual; 
};


struct mozo{
	
	int id;
	char nombre[50];
	char password[50];  
	float TotalComision;
	
	
};

struct ComandaHistorica{               //struct del archivo binario con el mismo nombre
	
	char fecha[11];
	char nombreMozo[53];
	int codProd;  //codigo del producto
	int cantidad;
	float comision;
};

int main(){
	
	
	
	
	
	
	
	
	return 0;
}
