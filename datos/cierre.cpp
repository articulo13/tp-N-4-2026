#include <iostream> 
#include <cstring>
#include <cstdio> 
using namespace std; 

#define MAX_MOZOS 53 
#define DIAS_SEMANA 7


struct comanda
{
    char fecha[11]; 
    char mozo[53]; 
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



}
