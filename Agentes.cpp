#include <string>
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

};

struct Persona
{
    int Id;
    string Nombre;
    string Especie;
    float Altura;
    bool Magia;
    Cara Mi_Rostro;

};

ifstream Archivo;
//EXISTEN VALORES FIJOSQUE NO SON ALTERABLES?
//estas funciones solo aseguran que los valores proporcionados estan en los intervalos correspondientes
bool ValidarTamanio(float A)
{
  if ((1<=A+Rango_Error && A-Rango_Error<=20)||(1<=A-Rango_Error && A+Rango_Error<=20))
  {
    return true;
  }
  return false;
}
bool ValidarProfundidadOjos(float A){
  if ((0.1<=A+Rango_Error&&A-Rango_Error<=0.5)||(0.1<=A-Rango_Error&&A+Rango_Error<=0.5))
    {
      return true;
    }
return false;
}
bool ValidarDistanciaOjos(float A){
  if ((0.1<=A+Rango_Error&&A-Rango_Error<=0.5)||(0.1<=A-Rango_Error&&A+Rango_Error<=0.5))
  {
    return true;
  }
  return false;
}
bool ValidarDistanciaNarizFrente(float A){
  if ((1<=A+Rango_Error&&A-Rango_Error<=4)||(1<=A+Rango_Error&&A-Rango_Error<=4))
  {
    return true;
  }
   return false;
}
bool ValidarDistanciaNarizLabio(float A){
 if ((0.1<=A+Rango_Error&&A-Rango_Error<=0.5)||(0.1<=A-Rango_Error&&A+Rango_Error<=0.5))
 {
  return true;
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
 
  }
  

}

void LLenarId(Persona *Personas,int N){

  for (int i = 0; i < N; i++)
  {
      Personas[i].Id=i;
  }
  

}
bool AlturaSospechosa(Persona Base,Persona Clon){
     if (ValidarTamanio(Base.Altura)&&ValidarTamanio(Clon.Altura))
     {
       if (Base.Altura<Clon.Altura||Base.Altura>Clon.Altura)
       {
        return true;
       }
     }
     return false;
     
}
bool ProfundidadOjosSospechosa(Persona Base,Persona Clon){
    if (ValidarProfundidadOjos(Base.Mi_Rostro.Profundidad_Ojos)&&ValidarProfundidadOjos(Clon.Mi_Rostro.Profundidad_Ojos))
     {
       if (Base.Mi_Rostro.Profundidad_Ojos<Clon.Mi_Rostro.Profundidad_Ojos||Base.Mi_Rostro.Profundidad_Ojos >Clon.Mi_Rostro.Profundidad_Ojos)
       {
        return true;
       }
     }
     return false;
}
bool CompartenRasgosSospechoso(Persona Base,Persona Clon){
  if (Base.Mi_Rostro.Distancia_Frente_Nariz==Clon.Mi_Rostro.Distancia_Frente_Nariz)
  {
    return true;
  }
  if (Base.Mi_Rostro.Distancia_Nariz_Labio==Clon.Mi_Rostro.Distancia_Nariz_Labio)
  {
    return true;
  }
  
  if (Base.Mi_Rostro.Distancia_Ojos==Clon.Mi_Rostro.Distancia_Ojos)
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
if (CompartenRasgosSospechoso(Base,Clon))
{
  if (ProfundidadOjosSospechosa(Base,Clon))
  {
    if (AlturaSospechosa(Base,Clon))
    {
      return true;
    }
    
  }
}
return false;
}
int main(){
int PersonasCanti;
Persona *Personas;
CantidadPersonas(PersonasCanti);//ALMACENA LA CANTIDAD PERSONAS 
Personas = CargarElementos();
LLenarId(Personas,PersonasCanti);
ImprimirLista(Personas,PersonasCanti);
cout<<EsCambiaFormas(Personas[0],Personas[2]);
return 0;
}
 