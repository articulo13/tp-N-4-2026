#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const float TASA_COMISION = 0.10f;
const int MAX_MOZOS = 100;
const int MAX_PRODUCTOS = 100;

struct Mozo {
    int idMozo;
    char nombre[50];
    char password[20];
    float totalComision;
};

struct Producto {
    int codigo;
    char descripcion[50];
    float precio;
    int stockActual;
};

struct Comanda {
    int idMozo;
    int codigoProducto;
    int cantidad;
    float comision;
};

int cargarMozo(Mozo lista[]) {
    FILE* archivoMozo = fopen("mozos.dat", "rb");
    if(archivoMozo == NULL) {
        cout << "Error al abrir mozos.dat" << endl;
        return 1;
    }

    int cantidadMozo = 0;

    while(cantidadMozo < MAX_MOZOS && fread (&lista[cantidadMozo], sizeof(Mozo), 1, archivoMozo)) {
        cantidadMozo++;
    }

    fclose (archivoMozo);
    return cantidadMozo;
}

int cargarProducto(Producto lista[]) {
    FILE* archivoProducto = fopen("Inventario.dat", "rb");
    if(archivoProducto == NULL) {
        cout << "Error al abrir Inventario.dat" << endl;
        return 1;
    }

    int cantidadProducto = 0;

    while(cantidadProducto < MAX_PRODUCTOS && fread(&lista[cantidadProducto], sizeof(Producto), 1, archivoProducto)) {
        cantidadProducto++;
    }

    fclose(archivoProducto);
    return cantidadProducto;
}