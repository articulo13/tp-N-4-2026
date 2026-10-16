
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>   // Necesario para strcmp y strcpy
#include <iomanip>   // Necesario para setw y left

using namespace std;

//Defino los structs que voy a utilizar

struct ComandaHistorica
  {
  char  fecha[11];
  char  nombreMozo[50];
  int   codigoProducto;
  int cantidad;
  float comision;
  };

//constante
const int MAX_REGISTROS = 1000;


int main()
{
    int semana;
    int mes;
    string rutaArchivo;
    
       FILE* archivo = NULL;
       bool prueba1 = false;

       // Ciclo de validaci�n para pedir la semana y armar la ruta din�micamente
       while (prueba1 == false)
       {
           cout << "Ingrese numero de semana  : ";
           cin >> semana;
           cout << "Ingresar numero de mes: ";
           cin>> mes;

           // Armamos el nombre del archivo concatenando el texto fijo con la variable ingresada
           // Si lo guardas dentro de una carpeta "datos/", d�jalo como "datos/comandas_semana_" + semana + ".dat"
           rutaArchivo = "datos/comandas_semana_S" + to_string(semana) + "-" + to_string(mes) + ".dat";

           // Abrimos el archivo en modo lectura binaria
           archivo = fopen(rutaArchivo.c_str(), "rb");

           if (archivo == NULL)
           {
               cout << "�El archivo no existe o la ruta es incorrecta! Aseg�rese de escribir bien el c�digo (ej: s1-05).\n" << endl;
           } else
           {
               cout << "�Carga completa!\n" << endl;
               prueba1 = true;
           }
       }

       ComandaHistorica registros[MAX_REGISTROS];
       int totalregistros = 0;
       ComandaHistorica c;


       //Lectura anticipada
       int leido = fread(&c, sizeof(ComandaHistorica), 1, archivo);

       while (leido == 1 && totalregistros < MAX_REGISTROS)
       {
           registros[totalregistros] = c;
           totalregistros++;
           leido = fread(&c, sizeof(ComandaHistorica), 1, archivo);
       }

       fclose(archivo); // cerrar archivo

       if (totalregistros == 0)
       {
           cout << "El archivo est� vac�o o no se pudieron leer registros." << endl;
           return 0;
       }

       //Ordenamiento del arrego por nombreMozo Alfabeticamente. Uso Ordenamiento Burbuja
       for (int i = 0; i < totalregistros - 1; i++)
       {
           for (int j = 0; j < totalregistros - i - 1; j++)
           {
               if (strcmp(registros[j].nombreMozo, registros[j + 1].nombreMozo) > 0)
               {
                   ComandaHistorica aux = registros[j];
                   registros[j] = registros[j + 1];
                   registros[j + 1] = aux;
               }
           }
       }

       // Corte de Control
       cout << "MOZO | PROD. VENDIDOS | COMISION TOTAL" << endl;
               cout << " ---------------------------------------- " << endl;

       int i = 0;
       float totalGeneralBuffet = 0;

       while (i < totalregistros)
       {
           char mozoActual[50];
           strcpy(mozoActual, registros[i].nombreMozo);

           int totalProductosGrupo = 0;
           float totalComisionGrupo = 0;

           // Subciclo de acumulaci�n al producirse el corte. evalua que no se pase del tama�o del arreglo y luego verifica que estemos hablando del mozo
           while (i < totalregistros && strcmp(registros[i].nombreMozo, mozoActual) == 0)
           {
               totalProductosGrupo = totalProductosGrupo+registros[i].cantidad;

               totalComisionGrupo = totalComisionGrupo + registros[i].comision;

               i++;
           }

           cout << mozoActual << " | " << totalProductosGrupo << " | $ " << totalComisionGrupo << "\n";//truco de IA porque no me funcionaba el endl debido a mezcla de datos

           totalGeneralBuffet += totalComisionGrupo;
       }

       cout << "------------------------------------------------------------" << endl; // para la estetica use IA
       cout << "Total general del buffet: $" << fixed << setprecision(2) << totalGeneralBuffet << endl;




   return 0;
}
