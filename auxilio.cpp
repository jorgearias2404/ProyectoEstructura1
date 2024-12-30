#include <iostream>
#include <string>

const int MAX_PERSONAS = 1000; // Máximo número de personas según el enunciado
const int MAX_GRUPO = 10;      // Tamaño máximo razonable para un grupo de cambiaformas

// Estructura para almacenar los datos de cada persona
struct Persona {
    std::string nombre;
    std::string especie;
    double altura;
    bool capacidadMagica;
    double profundidadOjos;
    double distanciaEntreOjos;
    double frenteANariz;
    double narizALabio;
};

class DetectorCambiaformas {
private:
    Persona personas[MAX_PERSONAS];
    int gruposEncontrados[MAX_PERSONAS][MAX_GRUPO];  // Almacena los índices de las personas en cada grupo
    int tamanoGrupos[MAX_PERSONAS];                  // Almacena el tamaño de cada grupo
    bool usado[MAX_PERSONAS];
    int numPersonas;
    int numGrupos;
    const double ERROR_MEDICION = 0.05;
    
    bool puedeSerCambiaforma(const Persona& p1, const Persona& p2) {
        // Regla 1: Diferencia de altura
        if (std::abs(p1.altura - p2.altura) > 1.0)
            return false;
            
        // Regla 2: Kripsans
        if (p1.especie == "Kripsan" || p2.especie == "Kripsan")
            return false;
            
        // Regla 3: Capacidad mágica
        if (p1.capacidadMagica && p2.capacidadMagica)
            return false;
            
        // Contar medidas faciales coincidentes
        int medidasCoincidentes = 0;
        
        if (std::abs(p1.profundidadOjos - p2.profundidadOjos) <= ERROR_MEDICION)
            medidasCoincidentes++;
        if (std::abs(p1.distanciaEntreOjos - p2.distanciaEntreOjos) <= ERROR_MEDICION)
            medidasCoincidentes++;
        if (std::abs(p1.frenteANariz - p2.frenteANariz) <= ERROR_MEDICION)
            medidasCoincidentes++;
        if (std::abs(p1.narizALabio - p2.narizALabio) <= ERROR_MEDICION)
            medidasCoincidentes++;
            
        return medidasCoincidentes >= 3;
    }
    
    bool validarGrupoActual(int grupo[], int tamano) {
        // Verificar coincidencias entre tres personas
        for (int i = 0; i < tamano - 2; i++) {
            for (int j = i + 1; j < tamano - 1; j++) {
                for (int k = j + 1; k < tamano; k++) {
                    int coincidencias = 0;
                    
                    if (std::abs(personas[grupo[i]].profundidadOjos - personas[grupo[j]].profundidadOjos) <= ERROR_MEDICION &&
                        std::abs(personas[grupo[i]].profundidadOjos - personas[grupo[k]].profundidadOjos) <= ERROR_MEDICION)
                        coincidencias++;
                        
                    if (std::abs(personas[grupo[i]].distanciaEntreOjos - personas[grupo[j]].distanciaEntreOjos) <= ERROR_MEDICION &&
                        std::abs(personas[grupo[i]].distanciaEntreOjos - personas[grupo[k]].distanciaEntreOjos) <= ERROR_MEDICION)
                        coincidencias++;
                        
                    if (std::abs(personas[grupo[i]].frenteANariz - personas[grupo[j]].frenteANariz) <= ERROR_MEDICION &&
                        std::abs(personas[grupo[i]].frenteANariz - personas[grupo[k]].frenteANariz) <= ERROR_MEDICION)
                        coincidencias++;
                        
                    if (std::abs(personas[grupo[i]].narizALabio - personas[grupo[j]].narizALabio) <= ERROR_MEDICION &&
                        std::abs(personas[grupo[i]].narizALabio - personas[grupo[k]].narizALabio) <= ERROR_MEDICION)
                        coincidencias++;
                        
                    if (coincidencias > 2)
                        return true;
                }
            }
        }
        return false;
    }
    
    void backtracking(int personaActual, int grupoActual[], int& tamanoGrupoActual) {
        if (tamanoGrupoActual > 1 && validarGrupoActual(grupoActual, tamanoGrupoActual)) {
            // Guardar grupo encontrado
            for (int i = 0; i < tamanoGrupoActual; i++) {
                gruposEncontrados[numGrupos][i] = grupoActual[i];
            }
            tamanoGrupos[numGrupos] = tamanoGrupoActual;
            numGrupos++;
            return;
        }
        
        for (int i = personaActual; i < numPersonas; i++) {
            if (!usado[i]) {
                if (tamanoGrupoActual == 0 || puedeSerCambiaforma(personas[grupoActual[0]], personas[i])) {
                    usado[i] = true;
                    grupoActual[tamanoGrupoActual] = i;
                    tamanoGrupoActual++;
                    backtracking(i + 1, grupoActual, tamanoGrupoActual);
                    tamanoGrupoActual--;
                    usado[i] = false;
                }
            }
        }
    }

public:
    DetectorCambiaformas(int n) : numPersonas(n), numGrupos(0) {
        for (int i = 0; i < MAX_PERSONAS; i++) {
            usado[i] = false;
            tamanoGrupos[i] = 0;
        }
    }
    
    void agregarPersona(int indice, const Persona& p) {
        personas[indice] = p;
    }
    
    void detectar() {
        int grupoActual[MAX_GRUPO];
        int tamanoGrupoActual = 0;
        backtracking(0, grupoActual, tamanoGrupoActual);
        
        // Imprimir resultados
        std::cout << numGrupos << std::endl;
        for (int i = 0; i < numGrupos; i++) {
            for (int j = 0; j < tamanoGrupos[i]; j++) {
                std::cout << (i + 1) << " - " << personas[gruposEncontrados[i][j]].nombre;
                if (j == 0) std::cout << " (O)";
                std::cout << std::endl;
            }
        }
    }
};

int main() {
    int N;
    std::cin >> N;
    
    DetectorCambiaformas detector(N);
    
    for (int i = 0; i < N; i++) {
        Persona p;
        std::cin.ignore();
        std::getline(std::cin, p.nombre);
        std::getline(std::cin, p.especie);
        std::cin >> p.altura;
        std::string magia;
        std::cin.ignore();
        std::getline(std::cin, magia);
        p.capacidadMagica = (magia == "Si");
        std::cin >> p.profundidadOjos;
        std::cin >> p.distanciaEntreOjos;
        std::cin >> p.frenteANariz;
        std::cin >> p.narizALabio;
        
        detector.agregarPersona(i, p);
    }
    
    detector.detectar();
    
    return 0;
}
