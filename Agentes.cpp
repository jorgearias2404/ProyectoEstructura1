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

Persona* CargarElementos(){
     Archivo.open("dataBase.in", ios::in); // se abre el archivo en modo lectura


    if (Archivo.fail())
    {
        cout << "Error al abrir el archivo" << endl;
        return NULL;
    }

    string linea;
    getline(Archivo, linea);
    int cantidadPersonas = stoi(linea); // Leer la cantidad de personas
  Persona* personas = new Persona[cantidadPersonas];
    for (int i = 0; i < cantidadPersonas; i++)
    {
        Persona p;
        p.Id = i; // Asignar un ID único
        getline(Archivo, p.Nombre); // Leer nombre
        getline(Archivo, p.Especie); // Leer especie

        // Leer altura y validar
        getline(Archivo, linea);
        p.Altura = stof(linea);

        // Leer capacidad mágica y convertir a booleano
        getline(Archivo, linea);
        if (linea=="Si"||linea=="si"||linea=="SI")
        {
          p.Magia = true;
        }
        else
        {
          p.Magia = false;
        }
        
       

        // Leer medidas de la cara
        getline(Archivo, linea);
        p.Mi_Rostro.Profundidad_Ojos = stof(linea);

        getline(Archivo, linea);
        p.Mi_Rostro.Distancia_Ojos = stof(linea);

        getline(Archivo, linea);
        p.Mi_Rostro.Distancia_Frente_Nariz = stof(linea);

        getline(Archivo, linea);
        p.Mi_Rostro.Distancia_Nariz_Labio = stof(linea);

        // Almacenar la persona en el arreglo
        personas[i] = p;
    }
    Persona *Arreglo = personas;
    delete[] personas; // Liberar memoria del arreglo temporal 
    Archivo.close(); // Cerrar el archivo
    return Arreglo;
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

  void ImprimirLista(){

if (CantidadDeRelaciones>0)
{
  cout<<"Cambia formas Original: "<<Origen.Nombre<<endl;
}
else{
    cout<<"Persona Sospechosa: "<<Origen.Nombre<<endl;
}

    
     

  for (int i = 0; i < CantidadDeRelaciones; i++)
  {
    cout<<"--------------"<<endl;
    cout<<"Persona "<<Relaciones[i].Id<<endl;
    cout<<"Nombre: "<<Relaciones[i].Nombre<<endl;
  }
  

}
  
};

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


int main(){

int PersonasCanti;
Persona *Personas;
CantidadPersonas(PersonasCanti);//ALMACENA LA CANTIDAD PERSONAS 
Personas = CargarElementos();
LLenarId(Personas,PersonasCanti);
// ImprimirLista(Personas,PersonasCanti);
// cout<<EsCambiaFormas(Personas[0],Personas[4]);


//SE INICIA COMPROVACION PARA EL SISTEMA DE CARGAS DE LOS CAMBIA FORMAS
Sospechoso Persona,Persona2;
Persona.Origen = Personas[0];
Persona2.Origen = Personas[1];

Persona.Relaciones = CargarRelaciones(Personas,PersonasCanti,Persona.Origen,Persona.CantidadDeRelaciones,Persona.PoseeRelaciones);
Persona2.Relaciones = CargarRelaciones(Personas,PersonasCanti,Persona2.Origen,Persona2.CantidadDeRelaciones,Persona2.PoseeRelaciones);

OrdenarRelaciones(Persona);
OrdenarRelaciones(Persona2);

Persona.ImprimirLista();
cout<<"==///==///==///==///==///==///==///==///==///"<<endl;
Persona2.ImprimirLista();
cout<<"==///==///==///==///==///==///==///==///==///"<<endl;
cout<<endl;
cout<<ContenidoEn(Persona2,Persona);
//implementar funcion recursiva para determinara cuantos cambia formas



return 0; 
}
 