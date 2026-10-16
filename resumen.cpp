
#include <iostream>
#include <cstdio>
#include <iomanip>

using namespace std;

struct Comanda {
    int idMozo;
    int codigoProducto;
    int cantidad;
    float comision;
};

int main() {
    int semana = 0;
    int mes = 0;
    char rutaArchivo[100];
    FILE* archivo = NULL;

    // Pedimos semana y mes hasta que se pueda abrir el archivo correspondiente
    while (archivo == NULL) {
        cout << "Ingrese numero de semana (ej: 1): ";
        cin >> semana;
        cout << "Ingrese numero de mes (1 a 12): ";
        cin >> mes;

        // Formato pedido por la consigna: comandas_semana_sX-mm.dat (ej: s1-06)
        // Nota: Si el grupo guarda todo en la carpeta "datos/", dejar "datos/comandas_semana_s%d-%02d.dat"
        snprintf(rutaArchivo, sizeof(rutaArchivo), "datos/comandas_semana_s%d-%02d.dat", semana, mes);

        archivo = fopen(rutaArchivo, "rb");

        if (archivo == NULL) {
            cout << "No se pudo abrir el archivo: " << rutaArchivo << "\n" << endl;
        }
    }

    cout << "\n=======================================================" << endl;
    cout << left << setw(12) << "ID MOZO"
         << setw(20) << "PROD. VENDIDOS"
         << setw(15) << "COMISION TOTAL" << endl;
    cout << "-------------------------------------------------------" << endl;

    Comanda reg;
    int totalProductosBuffet = 0;
    float totalComisionesBuffet = 0.0f;

    // Lectura para Corte de Control directo sobre el archivo (ya ordenado por idMozo)
    int leido = fread(&reg, sizeof(Comanda), 1, archivo);

    if (leido != 1) {
        cout << "El archivo esta vacio." << endl;
        fclose(archivo);
        return 0;
    }

    while (leido == 1) {
        int mozoActual = reg.idMozo;
        int cantProductosMozo = 0;
        float comisionMozo = 0.0f;

        // Mientras sea el mismo mozo y no se termine el archivo, acumulamos
        while (leido == 1 && reg.idMozo == mozoActual) {
            cantProductosMozo += reg.cantidad;
            comisionMozo += reg.comision;

            leido = fread(&reg, sizeof(Comanda), 1, archivo);
        }

        // Mostramos el resumen del mozo actual
        cout << left << setw(12) << mozoActual
             << setw(20) << cantProductosMozo
             << "$ " << fixed << setprecision(2) << comisionMozo << endl;

        // Acumulamos al total general de la semana
        totalProductosBuffet += cantProductosMozo;
        totalComisionesBuffet += comisionMozo;
    }

    cout << "=======================================================" << endl;
    cout << "Total de productos vendidos por el buffet en la semana: " << totalProductosBuffet << endl;
    cout << "Total general de comisiones a pagar: $ " << fixed << setprecision(2) << totalComisionesBuffet << endl;

    fclose(archivo);
    return 0;
}