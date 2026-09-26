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
	char password[20];  
	float TotalComision;
	
	
};

struct ComandaHistorica{               //struct del archivo binario con el mismo nombre
	
	char fecha[11];
	char nombreMozo[50];
	int codProd;  //codigo del producto
	int cantidad;
	float comision;
};

void CalcularRegistros(const char* nombre, int& x); 
void CrearArchiAux(const char* nombre);
void OrdenarArchivo(const char* nombre,int x);
void CorteDeControlArchivo();  //Corte de control con el archivo auxiliar  para generar el  archivo "Mozos.dat"
// PLANILLAS Y STOCK 
long busquedabinaria(const char* nombre, int codigo, Producto& r); //busqueda binaria para encontrar el stock (mediante las casillas fisicas)
void actualizarStock();



int main(){
	
	int cantidad_registros;
	const char nombre[] = "comandas_historicas.dat";
	
	
	//funciones
	CalcularRegistros(nombre,cantidad_registros);
	CrearArchiAux(nombre);
    OrdenarArchivo("auxiliar.dat",cantidad_registros);
	CorteDeControlArchivo();
	
	//PLANILLAS Y STOCK
	actualizarStock();
	
	
	

	return 0;
}

void CalcularRegistros(const char* nombre, int& x){
	
	FILE*f = fopen(nombre,"rb");
	
	if(f ==NULL){
		
		cout<<"No se pudo abrir el archivo"<<endl;
		return;
	}
	
	fseek(f,0,SEEK_END);
	
   long y = ftell(f)/ sizeof(ComandaHistorica);
	x=y;
	fclose(f);
}
void CrearArchiAux(const  char* nombre){
	
	ComandaHistorica m;
	
	FILE*a = fopen(nombre,"rb");
	FILE*b = fopen("auxiliar.dat","wb");
	
	if(a == NULL ){
		cout<<"No se pudo abrir el archivo"<<endl;
		return;
	}
	if(b == NULL){
		
		cout<<"No se pudo crear/abrir el archivo"<<endl;
		return;
	}
	
	while(fread(&m,sizeof(ComandaHistorica),1,a)==1){
		
		fwrite(&m,sizeof(ComandaHistorica),1,b);
	}
	
	fclose(a);
	fclose(b);
}

void OrdenarArchivo(const char* nombre,int x){
	
	FILE*a = fopen(nombre,"rb+"); //abrimos el archivo  en modo lectura y escribir
	
	if(a == NULL){
		
		cout<<"No se pudo abrir el archivo"<<endl;
		return;
	}
	
	ComandaHistorica  m,n; //declaramos variables
	
	
	for(int i=0;i<x-1;i++){
			int pos=i;    //asumimos al primero en cada vuelta del primer for como el minimo
			
		fread(&m,sizeof(ComandaHistorica),1,a); //el puntero avanza un lugar y guarda en la variable m el primer registro
		
		char minimo[50];
		strcpy(minimo,m.nombreMozo);  //copiamos en minimo el contenido del segundo parametro
        
		for(int j=i+1;j<x;j++){
			fread(&m,sizeof(ComandaHistorica),1,a); //el puntero avanza un lugar mas  y guarda en m otro valor, lo que nos permite ir comparando los nombres
			if(strcmp(minimo,m.nombreMozo)>0){ 
				
			    strcpy(minimo,m.nombreMozo);
				pos=j;
			}
		}
		
		fseek(a,pos*sizeof(ComandaHistorica),SEEK_SET); //el puntero se posiciona en el registro con  el menor valor 
		fread(&m,sizeof(ComandaHistorica),1,a);      // guardamos el valor del dato de ese registro
		
		fseek(a,i*sizeof(ComandaHistorica),SEEK_SET); //el puntero se posiciona en nuestro primer registro desordenado
		fread(&n,sizeof(ComandaHistorica),1,a);   //guardamos el valor
		
		
		 //INTERCAMBIO DE VALORES
		fseek(a,i*sizeof(ComandaHistorica),SEEK_SET);   //nos posicionamos en el primer registro desordenado
		fwrite(&m,sizeof(ComandaHistorica),1,a);    //guardamos los datos del registro con el menor valor en el primer registro desordenado
		
	    fseek(a,pos*sizeof(ComandaHistorica),SEEK_SET);   //nos posicionamos en el lugar del registro con menor valor
	    fwrite(&n,sizeof(ComandaHistorica),1,a);         // guardamos los datos del registro desordenado en esa posicion
		
		fseek(a,(i+1)*sizeof(ComandaHistorica),SEEK_SET);  // como ya intercambiamos los valores, debemos cambiar la posicion del puntero hacai el siguiente registro no ordenado
		
	}	

    fclose(a); //cerramos  el archivo
}

void IncripitarClave(mozo& m){
	
	int espacios;
		
		do{	
		    espacios=0;
			cout<<"Ingrese una clave para el MOZO con la ID "<<m.id<<" (la clave debe ser sin espacios): "<<endl; //pedimos al usuario que ingrese una clave
		    cin.getline(m.password,20);
			
			
			for(int i=0;m.password[i]!='\0';i++){        //verificamos ue la calve no  tenga espacios
				
				if(m.password[i]==' '){	
					espacios++;
					cout<<"\nLa clave no debe tener  espacios"<<endl<<endl;
					break;
				}
				
			}
		}while(espacios>0);
		
		for(int j=0; m.password[j]!='\0';j++){    //realizamos la encriptacion de la clave, para que no se guarde tal cual en  el archivo mozos.dat
			
			m.password[j]=m.password[j]+3;
		};

}


void CorteDeControlArchivo(){
	
	
	ComandaHistorica ch;
	mozo m;
	
	FILE* a= fopen("auxiliar.dat","rb");
	FILE* b= fopen("mozos.dat","wb");
	
	if(a == NULL){
		
		cout<<"No se pudo abrir el archivo"<<endl;
		return;
	}
	if(b == NULL){
		
		cout<<"No se pudo crear el archivo"<<endl;
		return;
	}
	
	
	int leido = fread(&ch,sizeof(ComandaHistorica),1,a);
	int contador_id=1;
	
	
	while(leido==1){
		
		float cont_comision_mozo=0;
		char campo_clave[50];
		strcpy(campo_clave, ch.nombreMozo);
		
	    strcpy(m.nombre, ch.nombreMozo);
		m.id=contador_id;
		contador_id++;
		
		//Incriptacion de Clave
	
	
		IncripitarClave(m);
		
		
		///
		
		while(leido==1 && strcmp(campo_clave, ch.nombreMozo) == 0){
			
	        cont_comision_mozo=ch.comision+cont_comision_mozo;
	        
	        leido=fread(&ch,sizeof(ComandaHistorica),1,a);
			
		}
		m.TotalComision=cont_comision_mozo;
		
		fwrite(&m,sizeof(mozo),1,b);
		
		
	}
	
	

	fclose(a);
	fclose(b);
	remove("auxiliar.dat");
	
	
}



long busquedabinaria(const char* nombre, int codigo, Producto& r){ //busqieda de la posicion del producto
	FILE* f = fopen(nombre, "rb");
    if (f == NULL) return -1;

    fseek(f, 0, SEEK_END);
    long n = ftell(f) / sizeof(Producto); // Cantidad total de registros
    long pri = 0, ult = n - 1, pos = -1;

    while (pri <= ult && pos == -1) {
        long med = (pri + ult) / 2;
        fseek(f, med * sizeof(Producto), SEEK_SET);
        fread(&r, sizeof(Producto), 1, f);

        if (r.codigo == codigo) {
            pos = med;
        } else if (codigo > r.codigo) {
            pri = med + 1;
        } else {
            ult = med - 1;
        }
    }

    fclose(f);
    return pos;

}

void actualizarStock(){ // se actualiza el numero de stock del producto
	FILE* fCom = fopen("comandas_historicas.dat", "rb");
	FILE* fInv = fopen("inventario.dat", "rb+");
	if (fCom == NULL || fInv == NULL) {
		cout << "Niguno de los archivos se puso abrir"<< endl;
		if (fCom != NULL) fclose(fCom);
		if (fInv != NULL) fclose(fInv);
		return;
	}

	ComandaHistorica comanda;
	Producto prod;
	while (fread(&comanda, sizeof(ComandaHistorica), 1, fCom) == 1){ // bucle de lectura
		long pos = busquedabinaria( "inventario.dat", comanda.codProd, prod);
			if (pos != -1){
			prod.stockActual -= comanda.cantidad;
			fseek(fInv, pos * sizeof(Producto), SEEK_SET); // descuenta del archivo inventario
			fwrite(&prod, sizeof(Producto), 1, fInv);
		}else{
			cout <<"No se encontro el prodcuto para descontar el stock" <<endl;
		}
		
	}

	fclose(fCom);
	fclose(fInv);



}
