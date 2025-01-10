#include <iostream>
#include <fstream>
using namespace std;

const int Cantidad_Especies = 10;
const string Especies[Cantidad_Especies] = {"Humano", "Kripsan", "Elfo", "Enano", "Goliat", "Orco", "Ubarikiwe", "Hada", "Celcoa", "Drakna'ar"};
const float Rango_Error = 0.05;

struct Cara {
    float Profundidad_Ojos;
    float Distancia_Ojos;
    float Distancia_Frente_Nariz;
    float Distancia_Nariz_Labio;

    Cara() {
        Profundidad_Ojos = 0;
        Distancia_Ojos = 0;
        Distancia_Frente_Nariz = 0;
        Distancia_Nariz_Labio = 0;
    }
};

struct Persona {
    int Id;
    string Nombre;
    string Especie;
    float Altura;
    bool Magia;
    Cara Mi_Rostro;
    bool Guardado;

    Persona() {
        Id = 0;
        Especie = "";
        Altura = 0;
        Magia = false;
        Guardado = false;
    }
};

struct Sospechoso {
    int CantidadDeRelaciones;
    Persona Origen;
    Persona* Relaciones;

    Sospechoso() {
        CantidadDeRelaciones = 0;
        Relaciones = nullptr;
    }

    ~Sospechoso() {
        delete[] Relaciones;
    }

    void AgregarRelacion(const Persona& nuevaRelacion) {
        for (int i = 0; i < CantidadDeRelaciones; i++) {
            if (Relaciones[i].Id == nuevaRelacion.Id) {
                return; // No duplicar relaciones.
            }
        }

        Persona* nuevoArreglo = new Persona[CantidadDeRelaciones + 1];
        for (int i = 0; i < CantidadDeRelaciones; i++) {
            nuevoArreglo[i] = Relaciones[i];
        }
        nuevoArreglo[CantidadDeRelaciones] = nuevaRelacion;

        delete[] Relaciones;
        Relaciones = nuevoArreglo;
        CantidadDeRelaciones++;
    }

    void ImprimirRelaciones() {
        if (CantidadDeRelaciones > 0) {
            cout << "Cambiaformas Original: " << Origen.Nombre << endl;
            for (int i = 0; i < CantidadDeRelaciones; i++) {
                cout << "   - " << Relaciones[i].Nombre << endl;
            }
        } else {
            cout << Origen.Nombre << " no tiene transformaciones." << endl;
        }
    }
};

bool EsCambiaFormas(const Persona& Base, const Persona& Clon) {
    if (Base.Magia || Clon.Magia) return false;
    if (Base.Especie == Especies[1] || Clon.Especie == Especies[1]) return false;
    if (abs(Base.Altura - Clon.Altura) > 1.0) return false;
    if (abs(Base.Mi_Rostro.Profundidad_Ojos - Clon.Mi_Rostro.Profundidad_Ojos) > Rango_Error) return false;

    return true; // Es un cambiaformas si todas las condiciones se cumplen.
}

void BackTrackingRelaciones(int index1, int index2, Sospechoso* Personas, int CantidadPersonas) {
    if (index1 >= CantidadPersonas) return;
    if (index2 >= CantidadPersonas) {
        BackTrackingRelaciones(index1 + 1, index1 + 2, Personas, CantidadPersonas);
        return;
    }

    if (index1 != index2 && EsCambiaFormas(Personas[index1].Origen, Personas[index2].Origen)) {
        Personas[index1].AgregarRelacion(Personas[index2].Origen);
    }

    BackTrackingRelaciones(index1, index2 + 1, Personas, CantidadPersonas);
}

Sospechoso* CargarElementos(int& CantidadPersonas) {
    ifstream Archivo("dataBase7.in");
    if (Archivo.fail()) {
        cout << "Error al abrir el archivo" << endl;
        return nullptr;
    }

    Archivo >> CantidadPersonas;
    Archivo.ignore(); // Ignorar el salto de línea después del número.

    Sospechoso* Personas = new Sospechoso[CantidadPersonas];
    for (int i = 0; i < CantidadPersonas; i++) {
        Personas[i].Origen.Id = i;
        getline(Archivo, Personas[i].Origen.Nombre);
        getline(Archivo, Personas[i].Origen.Especie);
        Archivo >> Personas[i].Origen.Altura;
        Archivo.ignore();
        string magia;
        getline(Archivo, magia);
        Personas[i].Origen.Magia = (magia == "Si" || magia == "si");
        Archivo >> Personas[i].Origen.Mi_Rostro.Profundidad_Ojos;
        Archivo >> Personas[i].Origen.Mi_Rostro.Distancia_Ojos;
        Archivo >> Personas[i].Origen.Mi_Rostro.Distancia_Frente_Nariz;
        Archivo >> Personas[i].Origen.Mi_Rostro.Distancia_Nariz_Labio;
        Archivo.ignore();
    }

    Archivo.close();
    return Personas;
}

int main() {
    int CantidadPersonas;
    Sospechoso* Personas = CargarElementos(CantidadPersonas);
    if (!Personas) return 1;

    BackTrackingRelaciones(0, 1, Personas, CantidadPersonas);

    for (int i = 0; i < CantidadPersonas; i++) {
        Personas[i].ImprimirRelaciones();
    }

    delete[] Personas;
    return 0;
}