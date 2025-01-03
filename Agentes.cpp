#include <iostream>
#include <fstream>

using namespace std;


const int Cantidad_Especies = 10;
const string Especies[Cantidad_Especies] ={"Humano","Kripsan","Elfo","Enano","Goliat","Orco","Ubarikiwe","Hada","Celcoa","Drakna'ar" };
const float Rango_Error=0.05;

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

ifstream Archivo;

//estas funciones solo aseguran que los valores proporcionados estan en los intervalos correspondientes
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

Persona* CargarElementos() {
    Archivo.open("dataBase.in", ios::in);
    if (Archivo.fail()) {
        cout << "Error al abrir el archivo" << endl;
        return nullptr;
    }

    string linea;
    getline(Archivo, linea);
    int cantidadPersonas = stoi(linea);
    Persona* personas = new Persona[cantidadPersonas];

    for (int i = 0; i < cantidadPersonas; i++) {
        Persona p;
        p.Id = i;
        getline(Archivo, p.Nombre);
        getline(Archivo, p.Especie);

        getline(Archivo, linea);
        p.Altura = stof(linea);

        getline(Archivo, linea);
        p.Magia = (linea == "Si" || linea == "si" || linea == "SI");

        getline(Archivo, linea);
        p.Mi_Rostro.Profundidad_Ojos = stof(linea);

        getline(Archivo, linea);
        p.Mi_Rostro.Distancia_Ojos = stof(linea);

        getline(Archivo, linea);
        p.Mi_Rostro.Distancia_Frente_Nariz = stof(linea);

        getline(Archivo, linea);
        p.Mi_Rostro.Distancia_Nariz_Labio = stof(linea);

        personas[i] = p;
    }

    Archivo.close();
    return personas;
}


void ImprimirLista(Persona *Personas,int N){

  for (int i = 0; i < N; i++)
  {
    cout<<"--------------"<<endl;
    cout<<"Persona "<<Personas[i].Id<<endl;
    cout<<"Nombre: "<<Personas[i].Nombre<<endl;
    cout<<"Especie: "<<Personas[i].Especie<<endl;
    cout<<"Altura: "<<Personas[i].Altura<<endl;
    cout<<"Magia: "<<Personas[i].Magia<<endl;
    cout<<"Profundidad ojos: "<<Personas[i].Mi_Rostro.Profundidad_Ojos<<endl;
    cout<<"Distancia ojos: "<<Personas[i].Mi_Rostro.Distancia_Ojos<<endl;
    cout<<"Distancia frente nariz: "<<Personas[i].Mi_Rostro.Distancia_Frente_Nariz<<endl;
    cout<<"Distancia nariz labio: "<<Personas[i].Mi_Rostro.Distancia_Nariz_Labio<<endl;
 
  }
  

}

void LLenarId(Persona *Personas,int N){

  for (int i = 0; i < N; i++)
  {
      Personas[i].Id=i;
  }
  

}

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
bool GrupoSospechoso(Persona Base,Persona A,Persona B){
int coincidencia=0;
//VALIDAMOS FRENTE NARIZ
  if (Base.Mi_Rostro.Distancia_Frente_Nariz==A.Mi_Rostro.Distancia_Frente_Nariz&&Base.Mi_Rostro.Distancia_Frente_Nariz==B.Mi_Rostro.Distancia_Frente_Nariz)
  {
    coincidencia++;
  }
  //VALIDAMOS NARIZ LABIO
  if (Base.Mi_Rostro.Distancia_Nariz_Labio == A.Mi_Rostro.Distancia_Nariz_Labio && Base.Mi_Rostro.Distancia_Nariz_Labio==B.Mi_Rostro.Distancia_Nariz_Labio)
  {
    coincidencia++;
  }
  //VALIDAMOS DISTANCIA OJOS
   if (Base.Mi_Rostro.Distancia_Ojos == A.Mi_Rostro.Distancia_Ojos&& Base.Mi_Rostro.Distancia_Ojos==B.Mi_Rostro.Distancia_Ojos)
  {
    coincidencia++;
  }
  
  if (coincidencia>2)
  {
    return true;
  }
  return false;
  
}


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

Persona Clonar(Persona B){
     Persona A;
    A.Guardado = B.Guardado;
    A.Id = B.Id; // Asegúrate de copiar el Id
    A.Nombre = B.Nombre;
    A.Especie = B.Especie;
    A.Altura = B.Altura;
    A.Magia = B.Magia;
    A.Mi_Rostro.Profundidad_Ojos = B.Mi_Rostro.Profundidad_Ojos;
    A.Mi_Rostro.Distancia_Ojos = B.Mi_Rostro.Distancia_Ojos;
    A.Mi_Rostro.Distancia_Frente_Nariz = B.Mi_Rostro.Distancia_Frente_Nariz; // Corregir este campo
    A.Mi_Rostro.Distancia_Nariz_Labio = B.Mi_Rostro.Distancia_Nariz_Labio;
     return A;
}

Persona* CargarRelaciones(Persona* Arreglo, int Tamanio, Persona Origen, int &CantidadDeRelaciones, bool &PoseeRelaciones) {
    // Primero, contamos cuántas relaciones hay
    int contador = 0;
    for (int i = 0; i < Tamanio; i++) {
        if (Origen.Id != Arreglo[i].Id && EsCambiaFormas(Origen, Arreglo[i])) {
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
        if (Origen.Id != Arreglo[i].Id && EsCambiaFormas(Origen, Arreglo[i])) {
            Relaciones[CantidadDeRelaciones] = Clonar(Arreglo[i]);
            CantidadDeRelaciones++;
        }
    }

    PoseeRelaciones = true;

    
    return Relaciones;
}


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

    void ImprimirLista() {
        if (CantidadDeRelaciones > 0) {
            cout << "Cambia formas Original: " << Origen.Nombre << endl;
        } else {
            cout << "Persona Sospechosa: " << Origen.Nombre << endl;
        }

        for (int i = 0; i < CantidadDeRelaciones; i++) {
            cout << "--------------" << endl;
            cout << "Persona " << Relaciones[i].Id << endl;
            cout << "Nombre: " << Relaciones[i].Nombre << endl;
            cout << "--------------" << endl;
            cout<<endl;
        }
    }
  
};



void CorregirErrorDeCarga(Persona* Arreglo, int Tamanio, Sospechoso& Sospechoso) {
    for (int i = 0; i < Tamanio; i++) {
        if (Sospechoso.Origen.Nombre == Arreglo[i].Nombre) {
            Sospechoso.Origen.Id = Arreglo[i].Id;
        }
    }

    for (int i = 0; i < Tamanio; i++) {
        for (int j = 0; j < Sospechoso.CantidadDeRelaciones; j++) {
            if (Sospechoso.Relaciones[j].Nombre == Arreglo[i].Nombre) {
                Sospechoso.Relaciones[j].Id = Arreglo[i].Id;
            }
        }
    }
}
//TERMINAR FUNCION DE CONTENCION
bool ContenidoEn(Sospechoso A, Sospechoso B) {
 
       if (A.CantidadDeRelaciones<B.CantidadDeRelaciones)
       {  

         bool OrigenEnArreglo =false;

                  for (int i = 0; i < B.CantidadDeRelaciones; i++)
                  {
                    if (A.Origen.Id == B.Relaciones[i].Id)
                    {
                      OrigenEnArreglo = true;
                    }
                  }

                  if (OrigenEnArreglo==true && A.CantidadDeRelaciones==0)
                  {
                    return true;
                  }
                  
                  if ( OrigenEnArreglo == false)
                  {
                      return false;
                  }
                  

          for (int i = 0; i < A.CantidadDeRelaciones; i++)
              {
                bool Encontrado =false;
                for (int j = 0; j < B.CantidadDeRelaciones; j++)
                {
                
                  
                  if (A.Relaciones[i].Id == B.Relaciones[j].Id)
                  {
                    Encontrado =true;
                  }
                  
                }
                if (Encontrado ==false)
                {
                  return false;
                }
                
                
              }
        }
        else{
        bool OrigenEnArreglo =false;

            for (int i = 0; i < A.CantidadDeRelaciones; i++)
                  {
                    if (B.Origen.Id == A.Relaciones[i].Id)
                    {
                      OrigenEnArreglo = true;
                    }
                  }

                  if (OrigenEnArreglo==true && B.CantidadDeRelaciones==0)
                  {
                    return true;
                  }
                  
                  if ( OrigenEnArreglo == false)
                  {
                      return false;
                  }
           
           for (int i = 0; i < B .CantidadDeRelaciones; i++)
              {
                bool Encontrado =false;
                for (int j = 0; j < A.CantidadDeRelaciones; j++)
                {
              
                  
                  if (B.Relaciones[i].Id == A.Relaciones[j].Id)
                  {
                    Encontrado =true;
                  }
                  
                }
                if (Encontrado ==false)
                {
                  return false;
                }
                
                
              }
        }
      
       
       
    return true; // Si todas las relaciones de A están en B, retornar true
}

//PROBAR
bool ExisteAlMenosUnoEnOtro(Sospechoso A, Sospechoso B){

//VALIDAMOS SI EL ORIGEN ESTA CONTEDNIDO EN ELOTRO ARREGLO
if (A.CantidadDeRelaciones<B.CantidadDeRelaciones)
{
       for (int i = 0; i < B.CantidadDeRelaciones; i++)
                  {
                    if (A.Origen.Id == B.Relaciones[i].Id)
                    {
                      return true;
                    }
                  }


       for (int i = 0; i < A.CantidadDeRelaciones; i++)
       {
        for (int j = 0; i < B.CantidadDeRelaciones; i++)
        {
          if (A.Relaciones[i].Id == B.Relaciones[j].Id )
          {
            return true;
          }
        }
        
       }
                  
   
} else {

        for (int i = 0; i < A.CantidadDeRelaciones; i++)
                  {
                    if (B.Origen.Id == A.Relaciones[i].Id)
                    {
                      return true;
                    }
                  }
    
        for (int i = 0; i < B.CantidadDeRelaciones; i++)
       {
        for (int j = 0; i < A.CantidadDeRelaciones; i++)
        {
          if (B.Relaciones[i].Id == A.Relaciones[j].Id )
          {
            return true;
          }
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

void ImprimirSospechosos(Sospechoso *Arreglo,int Tamanio){
  for (int i = 0; i < Tamanio; i++)
  {
    Arreglo[i].ImprimirLista();
    cout<<"---------- "<< i <<"  --------"<<endl;
  }
  
}

Sospechoso* cargarSospechosos(Persona* Personas, int PersonasCanti) {
    // Crear un arreglo de Sospechoso con el tamaño de PersonasCanti
    Sospechoso* ArregloSospechosos = new Sospechoso[PersonasCanti];
    

    // Recorrer todas las personas para cargar sus relaciones
    for (int i = 0; i < PersonasCanti; i++) {
        Sospechoso sospechoso;
        sospechoso.Origen = Personas[i]; // Asignar la persona como origen
        sospechoso.Relaciones = CargarRelaciones(Personas, PersonasCanti, sospechoso.Origen, sospechoso.CantidadDeRelaciones, sospechoso.PoseeRelaciones);  
        ArregloSospechosos[i] = sospechoso;
      
    }

    return ArregloSospechosos;
}
//LUEGO DE ARREGLAR LA FUNCION DE ARRIBA BUSCAR PROBAR ESTA
int NumeroDeCambiaFormas(Sospechoso *Arreglo, int CantidadPersonas) {
    int CantidadCambiaFormas = 0;

    // Recorremos cada sospechoso en el arreglo
    for (int i = 0; i < CantidadPersonas; i++) {
        bool tieneRelacion = false;

        // Comparamos con todos los demás sospechosos
        for (int j = 0; j < CantidadPersonas; j++) {
            if (i == j) continue; // No comparar consigo mismo

            // Verificamos si las relaciones de Arreglo[i] están contenidas en Arreglo[j]
            // o si al menos una relación existe en Arreglo[j]
            if (ContenidoEn(Arreglo[i], Arreglo[j]) || ExisteAlMenosUnoEnOtro(Arreglo[i], Arreglo[j])) {
                tieneRelacion = true;
                break; // Si tiene relación, salimos del bucle interno
            }
        }

        // Si no tiene relación con ningún otro sospechoso, incrementamos el contador
        if (tieneRelacion==false) {
            CantidadCambiaFormas++;
        }
    }

    return CantidadCambiaFormas;
}
int main(){

int PersonasCanti;
    Persona* Personas;
    CantidadPersonas(PersonasCanti);
    Personas = CargarElementos();
    if (Personas == nullptr) {
        return 1; // Manejo de error si no se cargan personas
    }

Sospechoso *Arreglo = cargarSospechosos( Personas, PersonasCanti);

for (int i = 0; i < PersonasCanti; i++)//ordenamos y cargamos la informacion en arreglos de sospechosos
{
   CorregirErrorDeCarga(Personas,PersonasCanti,Arreglo[i]);
   OrdenarRelaciones(Arreglo[i]);
   Arreglo[i].ImprimirLista();//temporal
}


cout<<"Numero de cambia formas: "<<NumeroDeCambiaFormas(Arreglo,PersonasCanti)<<endl;
delete[] Arreglo;
delete[] Personas;
return 0; 
}
 