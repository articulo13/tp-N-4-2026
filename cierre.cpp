#include <iostream> 
#include <cstring>
#include <cstdio> 
using namespace std; 

struct comanda
{
    char fecha[11]; 
    char mozo[53]; 
    int codprod;
    int cantidad; 
    int comision; 
};




int main(){

FILE* archivo = fopen ("comandas_historicas.dat", "rb");
if (archivo == NULL)
{
    cout << "No es posible abrir el archivo" << endl; 
    return 0; 
}

comanda comandas[1000]; 
int cantidad = 0; 
while (fread (&comandas [cantidad], sizeof (comanda),1 , archivo) ==1)
{
    cantidad++;
}
fclose(archivo); 




}
