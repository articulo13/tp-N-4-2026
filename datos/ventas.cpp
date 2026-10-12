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
        return -1;
    }

    int MozosCargados = 0;

    while(MozosCargados < MAX_MOZOS && fread (&lista[MozosCargados], sizeof(Mozo), 1, archivoMozo)== 1) {
        MozosCargados++;
    }

    fclose (archivoMozo);
    return MozosCargados;
}

int cargarProducto(Producto lista[]) {
    FILE* archivoProducto = fopen("inventario.dat", "rb");
    if(archivoProducto == NULL) {
        cout << "Error al abrir inventario.dat" << endl;
        return -1;
    }

    int ProductosCargados = 0;

    while(ProductosCargados < MAX_PRODUCTOS && fread(&lista[ProductosCargados], sizeof(Producto), 1, archivoProducto) == 1) {
        ProductosCargados++;
    }

    fclose(archivoProducto);
    return ProductosCargados;
}

bool comprobandoFecha (char fecha[]) {
    if (strlen(fecha) != 10) {
        return false;
    }
    if (fecha[2] != '-' ) {
        return false;
    }
    if (fecha [5] != '-') {
        return false;
    }
    return true;
}

int main () {
    Mozo listaMozos[MAX_MOZOS];
    Producto listaProductos[MAX_PRODUCTOS];

    int cantidadMozos = cargarMozo(listaMozos);
    if (cantidadMozos == -1) {
        return 1;
    }

    int cantidadProductos = cargarProducto(listaProductos);
    if (cantidadProductos == -1) {
        return 1;
    }

    cout << "Se cargaron: " << cantidadMozos << " Mozos y " << cantidadProductos << " Productos." << endl;
 
    char fecha[11];

    cout << "Ingrese la fecha de hoy (DD-MM-AAAA)" << endl;
    cin >> fecha;

    while (!comprobandoFecha(fecha)) {
        cout << "Fecha incorrecta, compruebe que coincida con lo puesto entre parentesis ()." << endl;
        cout << "Ingrese la fecha de hoy (DD-MM-AAAA)" << endl;
        cin >> fecha;
    }

    char nombreArchivo[30];
    strcpy(nombreArchivo, "comandas_");
    strcat(nombreArchivo, fecha);
    strcat(nombreArchivo, ".dat");
    
}