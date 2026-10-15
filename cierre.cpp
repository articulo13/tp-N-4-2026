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
    int idmozo; //id del mozo 
    int codprod; //num de 3 digitos 
    int cantidad;//cantidad de comandas
    float comision; //cantidad ganada
};




int main(){//En nuestras computadoras no funciono de manera automatica, 
                                //ingresen el archivo a utilizar de manera manual en la terminal 

comanda registros[MAX_REGISTROS]; 
int totalregistros = 0; 
 
int idmozos[MAX_MOZOS];  
int totalmozos = 0; //inicializamos la cantidad de mozos en 0 para enumerarlos al momento
                    //(no sabemos cuantos pueden llegar a venir).
 
vector<comanda> matriz[MAX_MOZOS]; 
 
    // ---------------------------------------------------------
    // INGRESO DEL NOMBRE DEL ARCHIVO
    // ---------------------------------------------------------


  int dia, mesArchivo, anio;

cout << "Ingrese el dia: ";
cin >> dia;

cout << "Ingrese el mes: ";
cin >> mesArchivo;

cout << "Ingrese el anio: ";
cin >> anio;

// Verificar que los valores sean validos
if (dia < 1 || dia > 31 ||
    mesArchivo < 1 || mesArchivo > 12 ||
    anio < 1)
{
    cout << "La fecha ingresada no es valida." << endl;
    return 1;
}

// Crear automaticamente el nombre del archivo
string nombrearchivo = "comandas_"
                       + to_string(dia) + "-"
                       + to_string(mesArchivo) + "-"
                       + to_string(anio) + ".dat";

cout << "\nAbriendo archivo: "
     << nombrearchivo << endl;

FILE* archivo = fopen(nombrearchivo.c_str(), "rb");

if (archivo == NULL)
{
    cout << "No se pudo abrir el archivo: "
         << nombrearchivo << endl;
    cout << "Verifique que exista en la carpeta de trabajo."
         << endl;
    return 1;
}
   // ---------------------------------------------------------
    // LECTURA DEL ARCHIVO Y UBICACION DE LOS MOZOS
    // ---------------------------------------------------------

    comanda c;
    bool limiteAlcanzado = false;

    while (fread(&c, sizeof(comanda), 1, archivo) == 1)
    {
        // Evitar superar el limite de registros
        if (totalregistros >= MAX_REGISTROS)
        {
            cout << "Se alcanzo el limite de "
                 << MAX_REGISTROS << " registros." << endl;
            limiteAlcanzado = true;
            break;
        }

        // Buscar si el mozo ya fue registrado
        int fmozo = -1;

        for (int j = 0; j < totalmozos; j++)
        {
            if (idmozos[j] == c.idmozo)
            {
                fmozo = j;
                break;
            }
        }

        // Agregar el mozo si es nuevo
        if (fmozo == -1)
        {
            if (totalmozos >= MAX_MOZOS)
            {
                cout << "Se alcanzo el limite de "
                     << MAX_MOZOS << " mozos." << endl;
                limiteAlcanzado = true;
                break;
            }

            idmozos[totalmozos] = c.idmozo;
            fmozo = totalmozos;
            totalmozos++;
        }

        // Guardar el registro
        registros[totalregistros] = c;
        totalregistros++;

        // Agregar la comanda al vector de ese mozo
        matriz[fmozo].push_back(c);
    }

    fclose(archivo);



//____________________________________________________________PLANILLA DE LOS MOZOS______________________________________________________________




cout << left << setw(12) << "MOZO" << setw(10) << "CODPROD" << setw(10) << "CANTIDAD" << setw(10) << "COMISION" << "\n"; 

for (int m = 0; m < totalmozos; m++) {
        for (int col = 0; col < (int)matriz[m].size(); col++) {
            comanda c = matriz[m][col];


            cout << left << setw(12) << c.  idmozo
                 << setw(10) << c.codprod
                 << setw(10) << c.cantidad
                 << fixed << setprecision(2) << setw(10) << c.comision
                 << "\n";
        }
    }
 

//________________________________________________CREACION DE ARCHIVO _______________________________________
//Guarda la misma planilla de arriba, con todas las comandas agrupadas por mozo.

int semana = 0; 
int mes = 0; 
cout << "Numero de mes: ";
cin >> mes;
cout << "Numero de semana: ";
cin >> semana;
string nombre = "comandas_semana_S" + to_string(semana) + "_" + to_string( mes); 


FILE* salida = fopen(nombre.c_str(), "wb");  //Abrimos en modo escritura binaria para crear el archivo.
 
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