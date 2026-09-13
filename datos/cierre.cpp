#include <iostream> 
#include <cstring>
#include <cstdio> 
using namespace std; 

#define MAX_MOZOS 53 
#define DIAS_SEMANA 7


struct comanda
{
    char fecha[11]; //dd/mm/aa
    char mozo[53]; //Nombre Apellido
    int codprod; 
    int cantidad; 
    int comision; 
};




int main(){

const char* nombresArchi[DIAS_SEMANA] = {
"lunes.dat", "martes.dat", "miercoles.dat", "jueves.dat", "viernes.dat", "sabado.dat", "domingo.dat" 
//Enumera y guarda cada archivo que entra, poniendo el lunes como 0 y domingo como 6 en el array DIAS_SEMANA  
}; 

const char* nombresDias[DIAS_SEMANA] = {
"Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo "
//En el anterior array guardamos los dias, aca les ponemos nombres en base entran para mostrarlos al final
}; 

char mozos[MAX_MOZOS][53]; 
float matriz[MAX_MOZOS][DIAS_SEMANA] ={0}; //creamos la matriz para la planilla 
int totalmozos = 0; //inicializamos la cantidad de mozos en 0 para enumerarlos al momento
                    // (no sabemos cuantos pueden llegar a venir)

for (int dia = 0; dia < DIAS_SEMANA; dia++)
{
   FILE* archivo =fopen(nombresArchi[dia], "rb");  //Abrimos en modo lectura para que lea los archvivos  guardados

   if (archivo == NULL)
   {
   cout << "No se pudo abrir el archivo: "<< nombresArchi[dia] << "/n"; 
   continue; 
   }
   
}


}
