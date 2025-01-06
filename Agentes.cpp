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



bool ContenidoEn(Sospechoso A, Sospechoso B) {
 
    
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
        
      
       
       
    return true; // Si todas las relaciones de A están en B, retornar true
}
bool ExisteAlMenosUnoEnOtro(Sospechoso A, Sospechoso B){


if (A.CantidadDeRelaciones = 0)
{
  for (int i = 0; i < B.CantidadDeRelaciones; i++)
  {
    if (A.Origen.Id == B.Relaciones[i].Id)
    {
      return true;
    }
    
  }
  return false;
}
if (B.CantidadDeRelaciones = 0)
{
  for (int i = 0; i < A.CantidadDeRelaciones; i++)
  {
    if (B.Origen.Id == A.Relaciones[i].Id)
    {
      return true;
    }
    
  }
  return false;
}

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
void ImprimirSospechosos(Sospechoso *Personas,int Tamanio){
  for (int i = 0; i < Tamanio; i++)
  {
     cout<<"--------------"<<endl;
    cout<<"Persona "<<Personas[i].Origen.Id<<endl;
    cout<<"Nombre: "<<Personas[i].Origen.Nombre<<endl;
    cout<<"Especie: "<<Personas[i].Origen.Especie<<endl;
    cout<<"Altura: "<<Personas[i].Origen.Altura<<endl;
    cout<<"Magia: "<<Personas[i].Origen.Magia<<endl;
    cout<<"Profundidad ojos: "<<Personas[i].Origen.Mi_Rostro.Profundidad_Ojos<<endl;
    cout<<"Distancia ojos: "<<Personas[i].Origen.Mi_Rostro.Distancia_Ojos<<endl;
    cout<<"Distancia frente nariz: "<<Personas[i].Origen.Mi_Rostro.Distancia_Frente_Nariz<<endl;
    cout<<"Distancia nariz labio: "<<Personas[i].Origen.Mi_Rostro.Distancia_Nariz_Labio<<endl;

    cout<<"---------- "<< i <<"  --------"<<endl;
  }
  
}


int CantidadDeElementosRepetidos(Sospechoso &sospechoso1, Sospechoso &sospechoso2) {
    int cantidadRepetidos = 0;


    // Verificar si el origen de sospechoso2 está en el arreglo de sospechoso1
    for (int i = 0; i < sospechoso1.CantidadDeRelaciones; i++) {
        if (sospechoso2.Origen.Id == sospechoso1.Relaciones[i].Id) {
            cantidadRepetidos++;
            break;
        }
    }

    // Verificar si hay elementos repetidos en los arreglos de ambos sospechosos
    for (int i = 0; i < sospechoso1.CantidadDeRelaciones; i++) {
        for (int j = 0; j < sospechoso2.CantidadDeRelaciones; j++) {
            if (sospechoso1.Relaciones[i].Id == sospechoso2.Relaciones[j].Id) {
                cantidadRepetidos++;
                break;
            }
        }
    }

    return cantidadRepetidos;
}
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

//funciones de simplificacion ARREGLAR
bool OrigenEnArreglo(Sospechoso A,Sospechoso B){
   for (int i = 0; i < A.CantidadDeRelaciones; i++)
   {
    if (B.Origen.Id == A.Relaciones[i].Id)
    {
      return true;
    }
    
   }
   return false;
}

void Copia(Sospechoso A,Sospechoso B)
{
 if (OrigenEnArreglo(A,B))
 {
    int tamanio = A.CantidadDeRelaciones + B.CantidadDeRelaciones - CantidadDeElementosRepetidos(A,B);
    Persona *Lista = new Persona[tamanio];
    int Almacenados = 0;
    for (int i = 0; i < A.CantidadDeRelaciones; i++)
    {
      Lista[i] = A.Relaciones[i];
      Almacenados++;
    }
    
       for (int i = 0; i < B.CantidadDeRelaciones; i++)
           {
             bool Duplicado = false;
               for (int j = 0; j < Almacenados; j++){
                 if (B.Relaciones[i].Id == Lista[j].Id)
                 {
                   Duplicado = true;
                    break;
                 }
               }
                if (!Duplicado) {
                    Lista[Almacenados] = B.Relaciones[i];
                    Almacenados++;
                }
           }

           A.CantidadDeRelaciones = Almacenados;
           delete[] A.Relaciones;
           A.Relaciones = Lista;
    
 }
 
 if (!OrigenEnArreglo(A,B))
 {
   int tamanio = 1 + A.CantidadDeRelaciones + B.CantidadDeRelaciones - CantidadDeElementosRepetidos(A,B);
    Persona *Lista = new Persona[tamanio];
    int Almacenados = 0;
    for (int i = 0; i < A.CantidadDeRelaciones; i++)
    {
      Lista[i] = A.Relaciones[i];
      Almacenados++;
    }
      Lista[Almacenados] = B.Origen;
      Almacenados++;
       for (int i = 0; i < B.CantidadDeRelaciones; i++)
           {
             bool Duplicado = false;
               for (int j = 0; j < Almacenados; j++){
                 if (B.Relaciones[i].Id == Lista[j].Id)
                 {
                   Duplicado = true;
                    break;
                 }
               }
                if (!Duplicado) {
                    Lista[Almacenados] = B.Relaciones[i];
                    Almacenados++;
                }
           }

           A.CantidadDeRelaciones = Almacenados;
           delete[] A.Relaciones;
           A.Relaciones = Lista;
 }
 
}

void Final(Sospechoso A,Sospechoso B){
  if (A.CantidadDeRelaciones > B.CantidadDeRelaciones)
  {
    Copia(A,B);
  }
  else
  {
    Copia(B,A);
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
    for (int i = 0; i < PersonasCanti; i++)
    {
      Personas[i].Relaciones = CargarRelaciones(Personas[i].Origen,Personas,PersonasCanti,Personas[i].CantidadDeRelaciones,Personas[i].PoseeRelaciones);
    
    }

//  implementando simplificacion AQUI PASAN COSAS LOCAS REQUIERE VALIDACION

  for (int i = 0; i < PersonasCanti ; i++)
  {
   for (int j = 1; j < PersonasCanti; j++)
   {
      if (ContenidoEn(Personas[i],Personas[j]))
      {
        break;
      }
      if (!ExisteAlMenosUnoEnOtro(Personas[i],Personas[j]))
      {
        break;
      }
      // I > J
      if (Personas[i].CantidadDeRelaciones > Personas[j].CantidadDeRelaciones)
      { 
        
        bool ContenidoEnOtro =false;
        for (int k = 0; k < Personas[j].CantidadDeRelaciones; k++)
        {
          if (Personas[j].Origen.Id == Personas[i].Relaciones[k].Id)
          {
            ContenidoEnOtro = true;
          }
          
        }
        
        
        if (ContenidoEnOtro){
          int tamanio = Personas[i].CantidadDeRelaciones + Personas[j].CantidadDeRelaciones - CantidadDeElementosRepetidos(Personas[i],Personas[j]);
           Persona *Lista = new Persona[tamanio];
           int Cargados =0;
           for (int k = 0; i < Personas[i].CantidadDeRelaciones; k++)
           {
            Lista[k] = Personas[i].Relaciones[k];
            Cargados++;
           }

           for (int k = 0; k < Personas[j].CantidadDeRelaciones; k++)
           {
             bool Duplicado = false;
               for (int l = 0; l < Cargados; l++){
                 if (Personas[j].Relaciones[k].Id == Lista[l].Id)
                 {
                   Duplicado = true;
                    break;
                 }
               }
                if (!Duplicado) {
                    Lista[Cargados] = Personas[j].Relaciones[i];
                    Cargados++;
                }
           }
           
           
           Personas[i].CantidadDeRelaciones = Cargados;
           delete[] Personas[i].Relaciones;
           Personas[i].Relaciones = Lista;
          
        }

         if (!ContenidoEnOtro){
          int tamanio = 1 + Personas[i].CantidadDeRelaciones + Personas[j].CantidadDeRelaciones - CantidadDeElementosRepetidos(Personas[i],Personas[j]);
           Persona *Lista = new Persona[tamanio];
           int Cargados =0;
           for (int k = 0; i < Personas[i].CantidadDeRelaciones; k++)
           {
            Lista[k] = Personas[i].Relaciones[k];
            Cargados++;
           }
           Lista[Cargados] = Personas[j].Origen;
           Cargados++;

           for (int k = 0; k < Personas[j].CantidadDeRelaciones; k++)
           {
             bool Duplicado = false;
               for (int l = 0; l < Cargados; l++){
                 if (Personas[j].Relaciones[k].Id == Lista[l].Id)
                 {
                   Duplicado = true;
                    break;
                 }
               }
                if (!Duplicado) {
                    Lista[Cargados] = Personas[j].Relaciones[i];
                       Cargados++;
                }
           }
           
          Personas[i].CantidadDeRelaciones = Cargados;
           delete[] Personas[i].Relaciones;
           Personas[i].Relaciones = Lista;
          
           
        }
        
      } else{
        //J >= I
        bool ContenidoEnOtro =false;
          for (int k = 0; k < Personas[i].CantidadDeRelaciones; i++)
        {
          if (Personas[i].Origen.Id == Personas[j].Relaciones[k].Id)
          {
            ContenidoEnOtro = true;
          }
          
        }

           if (ContenidoEnOtro){
          int tamanio = Personas[i].CantidadDeRelaciones + Personas[j].CantidadDeRelaciones - CantidadDeElementosRepetidos(Personas[i],Personas[j]);
           Persona *Lista = new Persona[tamanio];
           int Cargados =0;
           for (int k = 0; i < Personas[j].CantidadDeRelaciones; k++)
           {
            Lista[k] = Personas[j].Relaciones[k];
            Cargados++;
           }

           for (int k = 0; k < Personas[i].CantidadDeRelaciones; k++)
           {
             bool Duplicado = false;
               for (int l = 0; l < Cargados; l++){
                 if (Personas[i].Relaciones[k].Id == Lista[l].Id)
                 {
                   Duplicado = true;
                    break;
                 }
               }
                if (!Duplicado) {
                    Lista[Cargados] = Personas[i].Relaciones[i];
                     Cargados++;
                }
           }
           
          Personas[j].CantidadDeRelaciones = Cargados;
           delete[] Personas[j].Relaciones;
           Personas[j].Relaciones = Lista;
          
           
        }

         if (!ContenidoEnOtro){
          int tamanio = Personas[i].CantidadDeRelaciones + Personas[j].CantidadDeRelaciones - CantidadDeElementosRepetidos(Personas[i],Personas[j]);
           Persona *Lista = new Persona[tamanio];
           int Cargados =0;
           for (int k = 0; i < Personas[j].CantidadDeRelaciones; k++)
           {
            Lista[k] = Personas[j].Relaciones[k];
            Cargados++;
           }
           Lista[Cargados] = Personas[i].Origen;
           Cargados++;
           for (int k = 0; k < Personas[i].CantidadDeRelaciones; k++)
           {
             bool Duplicado = false;
               for (int l = 0; l < Cargados; l++){
                 if (Personas[i].Relaciones[k].Id == Lista[l].Id)
                 {
                   Duplicado = true;
                    break;
                 }
               }
                if (!Duplicado) {
                    Lista[Cargados] = Personas[i].Relaciones[i];
                    Cargados++;
                }
           }
           
           Personas[j].CantidadDeRelaciones = Cargados;
           delete[] Personas[j].Relaciones;
           Personas[j].Relaciones = Lista;
          
           
        }
      }
      
      
   }
   
  }
  



for (int i = 0; i < PersonasCanti; i++)
{
  for (int j = 1; j < PersonasCanti; j++)
  {
    if (ContenidoEn(Personas[i],Personas[j])){
           Personas[j] = Sospechoso();
    }
  }
  
}

for (int i = 0; i < PersonasCanti; i++)
{
  OrdenarRelaciones(Personas[i]);
  Personas[i].ImprimirLista();
}


// delete[] Lista;
delete[] Personas;
return 0; 
}
 