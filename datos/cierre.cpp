#include <iostream> 
#include <cstring>
#include <cstdio> 
#include <filesystem>
using namespace std; 

#define MAX_MOZOS 53 
#define DIAS_SEMANA 7
#define MAX_REGISTROS 1000 


struct comanda
{
    char fecha[11]; //dd/mm/aa
    char mozo[53]; //Nombre Apellido
    int codprod; //num de 3 digitos 
    int cantidad; 
    int comision; //cantidad ganada en el dia 
};




int main(){

const char* nombresArchi[DIAS_SEMANA] = {
"lunes.dat", "martes.dat", "miercoles.dat", "jueves.dat", "viernes.dat", "sabado.dat", "domingo.dat" 
//Enumera y guarda cada archivo que entra, poniendo el lunes como 0 y domingo como 6 en el array DIAS_SEMANA.
}; 

comanda registros[MAX_REGISTROS]; 
int totalregistros = 0; 

char mozos[MAX_MOZOS][53]; 
int totalmozos = 0; //inicializamos la cantidad de mozos en 0 para enumerarlos al momento
                    // (no sabemos cuantos pueden llegar a venir).



//Lectura de los 7 archivos. 
for (int dia = 0; dia < DIAS_SEMANA; dia++)
{
   FILE* archivo =fopen(nombresArchi[dia], "rb");  //Abrimos en modo lectura para que lea los archvivos guardados.

    if (archivo == NULL)
    {
     cout << "No se pudo abrir el archivo: "<< nombresArchi[dia] << "/n"; 
    continue; //sigue con el resto de dias si flata uno.
    }
    
   comanda c; 
    while (fread(&c, sizeof(comanda),1, archivo) ==1) 
{
    //Guarda el registro.
    registros[totalregistros] = c; 
    totalregistros++; 
    
    //Empieza a almacenar los que se repiten.
    int existe = 0; 
    for (int j = 0; j < totalmozos; j++)
    {
       if (strcmp(mozos[j], c.mozo)== 0)
       {
        existe = 1; 
        break; 
       }
       
    }
    
    //Agrega a los que nuevos (los que no aparecieron anteriormente).
    if (!existe)
    {
        strcpy(mozos[totalmozos], c.mozo);
        totalmozos++; 
    }
    
}

fclose(archivo); 

}



}
