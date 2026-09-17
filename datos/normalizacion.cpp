#include<iostream>
#include<cstdio>
#include<cstring>


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
	char nombreMozo[50];
	int codProd;  //codigo del producto
	int cantidad;
	float comision;
};



void CargaDatosArchivo(ComandaHistorica aux[],const char* nombre);  //pasar los registros del archivo a un arreglo auxiliar
void Ordenar(ComandaHistorica aux[]);        //ordenar por seleccion 
void PasarDatosArchivo(ComandaHistorica aux[]);    //creamos un archivo auxiliar temporal, luego se borrara
void CorteDeControlArchivo();  //Corte de control con el archivo auxiliar  para generar el  archivo "Mozos.dat"



int main(){
	
	ComandaHistorica aux[30]={}; //arreglo auxiliar para ordenar los registros del archivo comanda_historica por nombre
	const char nombre[] = "comandas_historicas.dat";
	
	//funciones
    CargaDatosArchivo(aux,nombre);
	Ordenar(aux);
	PasarDatosArchivo(aux);
	

	return 0;
}






void CargaDatosArchivo(ComandaHistorica aux[], const char* nombre){
	
	FILE* f = fopen(nombre,"rb");   //abrimos el archivo en modo lectura
	if(f == NULL){
		
		cout<<"No  se pudo abrir el archivo"<<endl;
		return;
	}
	
		int i=0;
	
	while(fread(&aux[i],sizeof(ComandaHistorica),1,f)==1){
		i++;
	}
	
	fclose(f);
}

void Ordenar(ComandaHistorica aux[]){    //ordenamos los datos del arreglo auxiliar por nombre
	
	ComandaHistorica caux; // struct auxiliar para  que no se pierdan datos
	
	for(int i=0;i<29;i++){
		
		int min=i;
		for(int j=i+1;j<30;j++){
			
			if( strcmp(aux[min].nombreMozo,aux[j].nombreMozo)>0){    //comparamos los nombres de cada  mozo para ordenarlos
				min=j;	
			}
		}
		caux=aux[i];     //intercambiamos los datos de los registros
		aux[i]=aux[min];
		aux[min]=caux;
	}
	

}


void PasarDatosArchivo(ComandaHistorica aux[]){          //pasamos los datos del arreglo a un archivo auxiliar
	
	FILE*f = fopen("auxiliar.dat","wb");
	
	if(f == NULL){
		
		cout<<"El archivo no pudo ser creado"<<endl;
		return;
	};
	
	for(int i=0;i<30;i++){
	
	fwrite(&aux[i],sizeof(ComandaHistorica),1,f);
	}
	
	fclose(f);
}
