#include <iostream> 
#include <cstring>
#include <cstdio> 
#include <iomanip>
#include <vector>
using namespace std; 

#define MAX_MOZOS 53 
#define DIAS_SEMANA 7
#define MAX_REGISTROS 1000 


struct comanda
{
    char fecha[11]; //dd/mm/aa
    char mozo[53]; //Nombre Apellido
    int idmozo; //id del mozo 
    int codprod; //num de 3 digitos 
    int cantidad;//cantidad de comandas
    float comision; //cantidad ganada
};




int main(){

const char* nombresArchi[DIAS_SEMANA] = {
"lunes.dat", "martes.dat", "miercoles.dat", "jueves.dat", "viernes.dat", "sabado.dat", "domingo.dat" 
//Enumera y guarda cada archivo que entra, poniendo el lunes como 0 y domingo como 6 en el array DIAS_SEMANA.
}; 

comanda registros[MAX_REGISTROS]; 
int totalregistros = 0; 

int idmozos[MAX_MOZOS];  
int totalmozos = 0; //inicializamos la cantidad de mozos en 0 para enumerarlos al momento
                    //(no sabemos cuantos pueden llegar a venir).

vector<comanda> matriz[MAX_MOZOS]; 


//_______Lectura de los 7 archivos y ubicacion de los mozos_______
for (int dia = 0; dia < DIAS_SEMANA; dia++)
{
   FILE* archivo =fopen(nombresArchi[dia], "rb");  //Abrimos en modo lectura para que lea los archvivos guardados.

    if (archivo == NULL)
    {
     cout << "No se pudo abrir el archivo: "<< nombresArchi[dia] << endl; 
    continue; //sigue con el resto de dias si flata uno.
    }
    
   comanda c; 
    while (fread(&c, sizeof(comanda),1, archivo) ==1) 
{
    //Guarda el registro.
    registros[totalregistros] = c; 
    totalregistros++; 
    
    //Empieza a almacenar los que se repiten.
    int fmozo = -1; 
    for (int j = 0; j < totalmozos; j++)
    {
       if ((idmozos[j] == c.idmozo))
       {
        fmozo = j; 
        break; 
       }
       
    }
    
    //Agrega a los que nuevos (los que no aparecieron anteriormente).
    if (fmozo == -1)
    {
        idmozos[totalmozos] = c.idmozo;
        fmozo = totalmozos; 
        totalmozos++; 
    }
    
    //agrega la comanda al final del vector de ese mozo
    matriz[fmozo].push_back(c); 
}

fclose(archivo); 

}
//____________________________________________________________PLANILLA DE LOS MOZOS______________________________________________________________
cout << left << setw(12) << "FECHA" << setw(20) << "MOZO" << setw(10) << "CODPROD" << setw(10) << "CANTIDAD" << setw(10) << "COMISION" << "\n"; 

for (int m = 0; m < totalmozos; m++) {
        for (int col = 0; col < (int)matriz[m].size(); col++) {
            comanda c = matriz[m][col];
            cout << left << setw(12) << c.fecha
                 << setw(20) << c.mozo
                 << setw(10) << c.codprod
                 << setw(10) << c.cantidad
                 << fixed << setprecision(2) << setw(10) << c.comision
                 << "\n";
        }
    }
 
    return 0;
}
