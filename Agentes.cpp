#include <iostream>
#include <fstream>


using namespace std;


const int Cantidad_Especies = 10;
const string Especies[Cantidad_Especies] ={"Humano","Kripsan","Elfo","Enano","Goliat","Orco","Ubarikiwe","Hada","Celcoa","Drakna'ar" };
const float Rango_Error=0.05;

ifstream Archivo;

//CLASES PARA DATOS DE LAS PERSONAS
struct Cara
{
    float Profundidad_Ojos;
    float Distancia_Ojos;
    float Distancia_Frente_Nariz;
    float Distancia_Nariz_Labio;


 Cara(){
    Profundidad_Ojos=0;
    Distancia_Ojos=0;
    Distancia_Frente_Nariz=0;
    Distancia_Nariz_Labio=0;
 }
};

struct Persona
{
    int Id;
    string Nombre;
    string Especie;
    float Altura;
    bool Magia;
    Cara Mi_Rostro;
    bool Guardado;

 Persona(){
     Id=0;
     Especie="";
     Altura=0;
     Magia=false;
     Guardado=false;
 }
 void ImprimirPersona(){
  cout<<"ID: "<<Id<<endl;
  cout<<"Nombre: "<<Nombre<<endl;
  cout<<"Especie: "<<Especie<<endl;
 }

};

class Sospechoso
{ 
public:
 int CantidadDeRelaciones;
 Persona Origen;
 Persona* Relaciones;
 bool PoseeRelaciones;
  
  Sospechoso(){
    CantidadDeRelaciones=0;
    PoseeRelaciones=false;
    Relaciones=nullptr;
  }
  // Constructor de copia
    Sospechoso(const Sospechoso& otro) {
        CantidadDeRelaciones = otro.CantidadDeRelaciones;
        Origen = otro.Origen;
        PoseeRelaciones = otro.PoseeRelaciones;
        if (otro.Relaciones != nullptr) {
            Relaciones = new Persona[CantidadDeRelaciones];
            for (int i = 0; i < CantidadDeRelaciones ; i++) {
                Relaciones[i] = otro.Relaciones[i];
            }
        } else {
            Relaciones = nullptr;
        }
    }

    // Destructor
    ~Sospechoso() {
        delete[] Relaciones;
    }


    void ImprimirLista2() {
       for (int i = 0; i < CantidadDeRelaciones; i++)
       {
        cout<<Origen.Id<<" - "<<Relaciones[i].Nombre<<endl;
       }
       
    }
  
};


//CARGA LOS ELEMENTOS DEL ARCHIVO
Sospechoso* CargarElementos() {
    Archivo.open("dataBase.in", ios::in);
    if (Archivo.fail()) {
        cout << "Error al abrir el archivo" << endl;
        return nullptr;
    }

    string linea;
    getline(Archivo, linea);
    int cantidadPersonas = stoi(linea);
    Sospechoso* personas = new Sospechoso[cantidadPersonas];

    for (int i = 0; i < cantidadPersonas; i++) {
        Sospechoso p;
        p.Origen.Id = i;
        getline(Archivo, p.Origen.Nombre);
        getline(Archivo, p.Origen.Especie );

        getline(Archivo, linea);
        p.Origen.Altura = stof(linea);

        getline(Archivo, linea);
        p.Origen.Magia = (linea == "Si" || linea == "si" || linea == "SI");

        getline(Archivo, linea);
        p.Origen.Mi_Rostro.Profundidad_Ojos = stof(linea);

        getline(Archivo, linea);
        p.Origen.Mi_Rostro.Distancia_Ojos = stof(linea);

        getline(Archivo, linea);
        p.Origen.Mi_Rostro.Distancia_Frente_Nariz = stof(linea);

        getline(Archivo, linea);
        p.Origen.Mi_Rostro.Distancia_Nariz_Labio = stof(linea);

        personas[i] = p;
    }

    Archivo.close();
    return personas;
}




//ESTAS FUNCIONES SE ENCARGAN DE LA LOGICA PARA DETERMINAR SI SUS VALORES SON SOSPECHOSOS
bool ValidarRangoError(float Base,float Clon)
{
   if (Base>Clon)
   {
    if (Base-Clon>Rango_Error)
    {
      return true;
    }
   }
   else
   {
    if (Clon-Base>Rango_Error)
    {
      return true;
    }
   }
   
  return false;
}
bool EnRangoAltura(Persona Base,Persona Clon){
 if (Base.Altura>Clon.Altura)
 {
     if (Base.Altura-Clon.Altura<=1)
     {
      return true;
     }
 }
 else
 {
     if (Clon.Altura-Base.Altura<=1)
     {
      return true;
     }
 }
 

 return false;
  
}
void CantidadPersonas(int& numero){
   Archivo.open("dataBase.in", ios::in); // se abre el archivo en modo lectura
   
    if (Archivo.fail())
    {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
   string linea;

   getline(Archivo,linea);
    
   numero = stoi(linea);
Archivo.close();
}


//ESTAS FUNCIONES SOLO PARA LA FUNCION DE CAMBIAFORMAS
bool AlturaSospechosa(Persona Base,Persona Clon){
     if (ValidarRangoError(Base.Altura,Clon.Altura))
     {
       if (EnRangoAltura(Base,Clon))
       {
         return true;
       }
       
     }
     return false;
     
}
bool ProfundidadOjosSospechosa(Persona Base,Persona Clon){
  
       if (Base.Mi_Rostro.Profundidad_Ojos<Clon.Mi_Rostro.Profundidad_Ojos)
       {
        return true;
       }
       if (Base.Mi_Rostro.Profundidad_Ojos==Clon.Mi_Rostro.Profundidad_Ojos)
       {
        return false;
       }
     
     return false;
}
bool CompartenRasgosSospechoso(Persona Base,Persona Clon){
 if (ValidarRangoError(Base.Mi_Rostro.Distancia_Frente_Nariz,Clon.Mi_Rostro.Distancia_Frente_Nariz)==false)//es decir esta dentro del rango de error
 {
   return true;
 }
//nariz labio
 if (ValidarRangoError(Base.Mi_Rostro.Distancia_Nariz_Labio,Clon.Mi_Rostro.Distancia_Nariz_Labio)==false)//es decir esta dentro del rango de error
 {
    return true;
 }
//distancia ojos
  if (ValidarRangoError(Base.Mi_Rostro.Distancia_Ojos,Clon.Mi_Rostro.Distancia_Ojos)==false)//es decir esta dentro del rango de error
 {
    return true;
 }
  return false;

}


//FUNCION QUE DTERMINA SI DOS PERSONAS ENTRE SI SON CAMBIAFORMAS
bool EsCambiaFormas(Persona Base,Persona Clon){

if (Clon.Magia!=true&&Base.Magia!=true)
{
    if (Clon.Especie!=Especies[1] && Base.Especie!=Especies[1])
      {
       if (CompartenRasgosSospechoso(Base,Clon))
        {
        
          if (ProfundidadOjosSospechosa(Base,Clon))
          {
            if (AlturaSospechosa(Base,Clon))
            {
              if (Clon.Guardado==false)
              {
                return true;
              }
              
            }
            
          }
        } 
      }
}
return false;
}

//ESTAS FUNCIONES ADMINISTRAN LAS LISTAS DE PERSONAS RELACIONADAS ENTRE SI Y UNA COPIA EFICIENTE PARA EVITAR FLUJOS DE MEMORIA
void Copiar(Sospechoso& Base, Persona* Relaciones, int CantidadRelaciones) {
    // Liberar la memoria previa si existe
    if (Base.Relaciones != nullptr) {
        delete[] Base.Relaciones;
    }

    // Asignar la cantidad de relaciones
    Base.CantidadDeRelaciones = CantidadRelaciones;

    // Asignar memoria para las nuevas relaciones
    Base.Relaciones = new Persona[CantidadRelaciones];

    // Copiar cada persona del arreglo Relaciones a Base.Relaciones
    for (int i = 0; i < CantidadRelaciones; i++) {
        Base.Relaciones[i] = Relaciones[i];
    }

    // Indicar que Base tiene relaciones
    Base.PoseeRelaciones = (CantidadRelaciones > 0);
}
Persona* CargarRelaciones(  Persona Origen, Sospechoso* Arreglo, int Tamanio, int &CantidadDeRelaciones, bool &PoseeRelaciones) {
    // Primero, contamos cuántas relaciones hay
    int contador = 0;
    for (int i = 0; i < Tamanio; i++) {
        if (Origen.Id != Arreglo[i].Origen.Id && EsCambiaFormas(Origen, Arreglo[i].Origen)) {
            contador++;
        }
    }

    // Si no hay relaciones, devolvemos nullptr
    if (contador == 0) {
        PoseeRelaciones = false;
        return nullptr;
    }

    // Asignamos memoria dinámica para almacenar las relaciones
    Persona* Relaciones = new Persona[contador];
    CantidadDeRelaciones = 0;

    // Llenamos el arreglo con las relaciones
    for (int i = 0; i < Tamanio; i++) {
        if (Origen.Id != Arreglo[i].Origen.Id && EsCambiaFormas(Origen, Arreglo[i].Origen)) {
            Relaciones[CantidadDeRelaciones] = Arreglo[i].Origen;
            CantidadDeRelaciones++;
        }
    }

    PoseeRelaciones = true;

  
    return Relaciones;
}


//ESTAS FUNCIONES SE ENCARGAN DE VALIDAR EL COMPORTAMINETO DE LOS CONJUNTOS
bool ContenidoEn(Sospechoso A, Sospechoso B) {
    // Verificar si el origen de B está contenido en las relaciones de A
    bool OrigenEnArreglo = false;
    if (A.CantidadDeRelaciones == 0)
    {
        return false;
    }
    
    for (int i = 0; i < A.CantidadDeRelaciones; i++) {
        if (B.Origen.Id == A.Relaciones[i].Id || B.Origen.Id == A.Origen.Id) {
            OrigenEnArreglo = true;
            break;
        }
    }

    // Si el origen de B no está contenido en A, retorna falso
    if (!OrigenEnArreglo) {
        return false;
    }

    // Verificar si todas las relaciones de B están contenidas en A
    for (int i = 0; i < B.CantidadDeRelaciones; i++) {
        bool RelacionEncontrada = false;
        for (int j = 0; j < A.CantidadDeRelaciones; j++) {
            if (B.Relaciones[i].Id == A.Relaciones[j].Id) {
                RelacionEncontrada = true;
                break;
            }
        }
        // Si alguna relación de B no está en A, no está contenido
        if (!RelacionEncontrada) {
            return false;
        }
    }

    // Si todas las relaciones y el origen de B están contenidas en A, retorna verdadero
    return true;
}
bool ExisteAlMenosUnoEnOtro(Sospechoso A, Sospechoso B){

//VALIDAMOS SI EL ORIGEN ESTA CONTEDNIDO EN EL OTRO ARREGLO
  for (int i = 0; i < A.CantidadDeRelaciones; i++)
  {
    if (B.Origen.Id == A.Relaciones[i].Id)
    {
      return true;
    }
    
  }
  for (int i = 0; i < A.CantidadDeRelaciones; i++)
  {
    for (int j = 0;j < B.CantidadDeRelaciones; j++)
    {
         if (B.Origen.Id == A.Relaciones[i].Id)
        {
          return true;
        } 
    }
    
  }
  
  
 return false;
}
void OrdenarRelaciones(Sospechoso& BASE) {

  for (int i = 0; i < BASE.CantidadDeRelaciones; i++)
  {
    if (BASE.Origen.Mi_Rostro.Profundidad_Ojos>BASE.Relaciones[i].Mi_Rostro.Profundidad_Ojos)
    {
        Persona temp = BASE.Origen;
            BASE.Origen = BASE.Relaciones[i];
            BASE.Relaciones[i] = temp;
    }
    
  }
  
    for (int i = 0; i < BASE.CantidadDeRelaciones - 1; i++) {
        int indiceMenor = i;
        for (int j = i + 1; j < BASE.CantidadDeRelaciones; j++) {
            if (BASE.Relaciones[j].Mi_Rostro.Profundidad_Ojos < BASE.Relaciones[indiceMenor].Mi_Rostro.Profundidad_Ojos) {
                indiceMenor = j;
            }
        }
        // Intercambiar las relaciones
        if (indiceMenor != i) {
            Persona temp = BASE.Relaciones[i];
            BASE.Relaciones[i] = BASE.Relaciones[indiceMenor];
            BASE.Relaciones[indiceMenor] = temp;
        }
    }
}
int CantidadDeElementosRepetidos(Sospechoso &sospechoso1, Sospechoso &sospechoso2) {
    int cantidadRepetidos = 0;

    // Verificar si hay elementos repetidos en los arreglos de ambos sospechosos
    for (int i = 0; i < sospechoso1.CantidadDeRelaciones; i++) {
        for (int j = 0; j < sospechoso2.CantidadDeRelaciones; j++) {
            if (sospechoso1.Relaciones[i].Id == sospechoso2.Relaciones[j].Id) {
                cantidadRepetidos++;
                break;
            }
        }
    }

    // Verificar si el origen de sospechoso2 está en el arreglo de sospechoso1
    bool origenRepetido = false;
    for (int i = 0; i < sospechoso1.CantidadDeRelaciones; i++) {
        if (sospechoso2.Origen.Id == sospechoso1.Relaciones[i].Id) {
            origenRepetido = true;
            break;
        }
    }
    if (origenRepetido) {
        cantidadRepetidos++;
    }

    return cantidadRepetidos;
}
//ESTAS FUNCIONES UNEN LOS CONJUNTOS DEPENDIENDO DE ALGUNOS CASOS ESPECIFICOS
void FusionarRelaciones(Sospechoso& destino, Sospechoso& fuente) {
    int tamanio = destino.CantidadDeRelaciones + fuente.CantidadDeRelaciones - CantidadDeElementosRepetidos(destino, fuente);
    Persona* Lista = new Persona[tamanio];
    int Cargados = 0;

    for (int k = 0; k < destino.CantidadDeRelaciones; k++) {
        bool Duplicado = false;
        for (int l = 0; l < Cargados; l++) {
            if (destino.Relaciones[k].Id == Lista[l].Id) {
                Duplicado = true;
                break;
            }
        }
        if (!Duplicado) {
            Lista[Cargados++] = destino.Relaciones[k];
        }
    }

    for (int k = 0; k < fuente.CantidadDeRelaciones; k++) {
        bool Duplicado = false;
        for (int l = 0; l < Cargados; l++) {
            if (fuente.Relaciones[k].Id == Lista[l].Id) {
                Duplicado = true;
                break;
            }
        }
        if (!Duplicado) {
            Lista[Cargados++] = fuente.Relaciones[k];
        }
    }


    Copiar(destino,Lista,Cargados);
    delete[] Lista;
}
void FusionarRelacionesIncluyendoOrigen(Sospechoso& destino, Sospechoso& fuente) {
    int tamanio = 1 + destino.CantidadDeRelaciones + fuente.CantidadDeRelaciones - CantidadDeElementosRepetidos(destino, fuente);
    Persona* Lista = new Persona[tamanio];
    int Cargados = 0;

    for (int k = 0; k < destino.CantidadDeRelaciones; k++) {
        if (destino.Relaciones[k].Id != destino.Origen.Id) {
            Lista[Cargados++] = destino.Relaciones[k];
        }
    }

    if (fuente.Origen.Id != destino.Origen.Id) {
        Lista[Cargados++] = fuente.Origen;
    }

    for (int k = 0; k < fuente.CantidadDeRelaciones; k++) {
        bool Duplicado = false;
        for (int l = 0; l < Cargados; l++) {
            if (fuente.Relaciones[k].Id == Lista[l].Id) {
                Duplicado = true;
                break;
            }
        }
        if (!Duplicado && fuente.Relaciones[k].Id != destino.Origen.Id) {
            Lista[Cargados++] = fuente.Relaciones[k];
        }
    }
    Copiar(destino,Lista,Cargados);
    delete[] Lista;
}
bool ContieneOrigen(Sospechoso& sospechoso, int origenId) {
    for (int i = 0; i < sospechoso.CantidadDeRelaciones; i++) {
        if (sospechoso.Relaciones[i].Id == origenId) {
            return true;
        }
    }
    return false;
}
//SE ENCARGA DE GENERAR NUEVOS CONJUNTOS DE RELACIONES 
void ProcesarRelaciones(Sospechoso* Personas, int PersonasCanti) {
    for (int i = 0; i < PersonasCanti; i++) {
        for (int j = 1; j < PersonasCanti; j++) {
            if (ContenidoEn(Personas[i], Personas[j])) {
                break;
            }
            if (!ExisteAlMenosUnoEnOtro(Personas[i], Personas[j])) {
                break;
            }

            if (Personas[i].CantidadDeRelaciones > Personas[j].CantidadDeRelaciones) {
                bool ContenidoEnOtro = false;
                for (int k = 0; k < Personas[j].CantidadDeRelaciones; k++) {
                    if (Personas[j].Origen.Id == Personas[i].Relaciones[k].Id) {
                        ContenidoEnOtro = true;
                    }
                }

                if (ContenidoEnOtro) {
                    FusionarRelaciones(Personas[i], Personas[j]);
                } else {
                    FusionarRelacionesIncluyendoOrigen(Personas[i], Personas[j]);
                }
            } else {
                bool ContenidoEnOtro = false;
                for (int k = 0; k < Personas[i].CantidadDeRelaciones; k++) {
                    if (Personas[i].Origen.Id == Personas[j].Relaciones[k].Id) {
                        ContenidoEnOtro = true;
                    }
                }

                if (ContenidoEnOtro) {
                    FusionarRelaciones(Personas[j], Personas[i]);
                } else {
                    FusionarRelacionesIncluyendoOrigen(Personas[j], Personas[i]);
                }
            }
        }
    }
}


//se encarga de cargar las relaciones de los sospechosos
void Backtracking(int index, Sospechoso* Personas, int PersonasCanti) {
    // Condición base: si el índice supera la cantidad de personas, termina.
    if (index >= PersonasCanti) {
        return;
    }

    // Evaluar relaciones para la persona actual.
    if (!Personas[index].PoseeRelaciones) {
        Personas[index].Relaciones = CargarRelaciones(
            Personas[index].Origen, Personas, PersonasCanti, 
            Personas[index].CantidadDeRelaciones, Personas[index].PoseeRelaciones
        );
    }

    

    // Llamada recursiva para la siguiente persona.
    Backtracking(index + 1, Personas, PersonasCanti);
}
//se encarga de simplificar conjuntos contenidos en otros
void BacktrackingReiniciar(int index, Sospechoso* Personas, int PersonasCanti) {
    // Condición base: si el índice supera la cantidad de personas, termina.
    if (index >= PersonasCanti) {
        return;
    }

    // Llamada recursiva para la siguiente persona.
    BacktrackingReiniciar(index + 1, Personas, PersonasCanti);

    // Verificar si la persona actual está contenida en alguna otra persona.
    for (int j = 0; j < PersonasCanti; j++) {
        if (index != j) {
            // Si la persona actual está contenida en la persona j, reiniciar la persona actual.
            if (ContenidoEn(Personas[j], Personas[index])) {
                Personas[index] = Sospechoso();
                 return;
            }
        }
    }
   
}

void SalidaFinal(Sospechoso *Personas,int PersonasCanti){
    int CantidadCambiaformas = 0;
for (int i = 0; i < PersonasCanti; i++)
{
  if (Personas[i].CantidadDeRelaciones > 0)
  {
    CantidadCambiaformas++;
  }
  
}

cout<<CantidadCambiaformas<<endl;

int Index=1;
for (int i = 0; i < PersonasCanti; i++)
{
  if (Personas[i].CantidadDeRelaciones > 0)
  {

    Personas[i].Origen.Id = Index;
    cout<<Index<<" - "<< Personas[i].Origen.Nombre << " (O) "<<endl;
    Personas[i].ImprimirLista2();
    Index++;
  }
}


}

int main(){

int PersonasCanti;
    Sospechoso* Personas;
    CantidadPersonas(PersonasCanti);
    Personas = CargarElementos();
    if (Personas == nullptr) {
        return 1; // Manejo de error si no se cargan personas
    }
    

Backtracking(0, Personas, PersonasCanti);
ProcesarRelaciones(Personas,PersonasCanti);

for (int i = 0; i < PersonasCanti; i++)
{
    OrdenarRelaciones(Personas[i]);
}

BacktrackingReiniciar(0,Personas,PersonasCanti);

SalidaFinal(Personas,PersonasCanti);
delete[] Personas;

    return 0;
}


