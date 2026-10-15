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




int main(int argc, char* argv[]){

comanda registros[MAX_REGISTROS]; 
int totalregistros = 0; 
 
int idmozos[MAX_MOZOS];  
int totalmozos = 0; //inicializamos la cantidad de mozos en 0 para enumerarlos al momento
                    //(no sabemos cuantos pueden llegar a venir).
 
vector<comanda> matriz[MAX_MOZOS]; 
 
 
if (argc < 2)
{
    cout << "No llegaron archivos para procesar." << endl;
    return 1;
}
 
if (argc - 1 > DIAS_SEMANA)
{
    cout << "Llegaron " << argc - 1 << " archivos, solo se procesan los primeros " << DIAS_SEMANA << "." << endl;
}
 
//_______Lectura de los archivos que llegan (en orden de llegada) y ubicacion de los mozos_______
//Se procesa cada archivo que llega, sin importar como se llame.
for (int i = 1; i < argc && i <= DIAS_SEMANA; i++)
{
   FILE* archivo =fopen(argv[i], "rb");  //Abrimos en modo lectura el archivo que llego.
 
    if (archivo == NULL)
    {
     cout << "No se pudo abrir el archivo: "<< argv[i] << endl; 
    continue; //sigue con el resto de archivos si falla uno.
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
 

//________________________________________________CREACION DE ARCHIVO _______________________________________
//Guarda la misma planilla de arriba, con todas las comandas agrupadas por mozo.
FILE* salida = fopen("planilla_semanal.dat", "wb");  //Abrimos en modo escritura binaria para crear el archivo.
 
if (salida == NULL)
{
    cout << "No se pudo crear el archivo de la planilla." << endl;
    return 1;
}
 
for (int m = 0; m < totalmozos; m++) {
    for (int col = 0; col < (int)matriz[m].size(); col++) {
        fwrite(&matriz[m][col], sizeof(comanda), 1, salida);  //escribe una comanda por vez, en el mismo orden de la planilla.
    }
}
 
fclose(salida);
 
    return 0;
}
