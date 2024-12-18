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

Persona* CargarElementos(){
    Archivo.open("dataBase.in", ios::in); // se abre el archivo en modo lectura

    if (Archivo.fail())
    {
        cout << "Error al abrir el archivo" << endl;
        return;
    }

    string linea;
    getline(Archivo, linea);
    int cantidadPersonas = stoi(linea); // Leer la cantidad de personas
  Persona* personas = new Persona[cantidadPersonas];
    for (int i = 0; i < cantidadPersonas; i++)
    {
        Persona p;
        p.Id = i + 1; // Asignar un ID único

        getline(Archivo, p.Nombre); // Leer nombre
        getline(Archivo, p.Especie); // Leer especie

        // Leer altura y validar
        getline(Archivo, linea);
        p.Altura = stof(linea);

        // Leer capacidad mágica y convertir a booleano
        getline(Archivo, linea);
        p.Magia = (linea == "true");

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
bool Validar_Cara(Cara A,Cara B){
  
  bool Rasgos_Coincidentes = false;
  int Cont =0;
  if (A.Distancia_Frente_Nariz==B.Distancia_Frente_Nariz)
  {
    Cont++;
  }
  if (A.Distancia_Nariz_Labio==B.Distancia_Nariz_Labio)
  {
    Cont++;
  }
  if (A.Distancia_Ojos==B.Distancia_Ojos)
  {
    Cont++;
  }
  bool Ojos =false;
  if (A.Profundidad_Ojos<B.Profundidad_Ojos)
  {
    
    Ojos=true;
  }
  
    if (Cont>=2&&Ojos)
    {Rasgos_Coincidentes= true;
        return Rasgos_Coincidentes;
    }
return Rasgos_Coincidentes;

}

bool Sospechoso(Persona A){//Validamossi es un posible sospechoso
 if (A.Especie==Especies[1])//Si es un kripsan esta fera de sospechas
 {
  return false;
 }
  if (A.Magia==true)//Si tiene magia estaffuera de sospechas
 {
  return false;
 }
return true;
 
}

bool TamanioSospechoso(Persona A, Persona B){//Validamossi existe un cambioen su tamanio que pueda ser motivo de sospecha

if (A.Altura<B.Altura+Rango_Error||A.Altura<B.Altura-Rango_Error)
{
  return true;
}

}

bool EsCambiaFormas(Persona A, Persona B)//Validamos si hay cambios en las formas de las personas  
{
  if (Sospechoso(A)&&Sospechoso(B))//Validamos si ambos son sospechosos
  {
    
    
  }
  
}
int main(){
Persona Jan;
Jan.Altura=10.55;
Jan.Especie="Humano";
Jan.Id=1;
Jan.Nombre= "Jan Marco";
Jan.Magia=true;
Jan.Mi_Rostro.Profundidad_Ojos=0.12;
Jan.Mi_Rostro.Distancia_Ojos=0.2;
Jan.Mi_Rostro.Distancia_Frente_Nariz=1.25;
Jan.Mi_Rostro.Distancia_Nariz_Labio=0.238;
Persona Jorge;
Jorge.Altura=10.2;
Jorge.Especie="Elfo";
Jorge.Id=2;
Jorge.Nombre= "Jorge Arias";
Jorge.Magia=false;
Jorge.Mi_Rostro.Profundidad_Ojos=0.13;
Jorge.Mi_Rostro.Distancia_Ojos=0.2;
Jorge.Mi_Rostro.Distancia_Frente_Nariz=2.1;
Jorge.Mi_Rostro.Distancia_Nariz_Labio=0.239;
Persona Sergio;
Sergio.Altura=10.55;
Sergio.Especie="Humano";
Sergio.Id=3;
Sergio.Nombre= "Sergio Lopez";
Sergio.Magia=false;
Sergio.Mi_Rostro.Profundidad_Ojos=0.12;
Sergio.Mi_Rostro.Distancia_Ojos=0.2;
Sergio.Mi_Rostro.Distancia_Frente_Nariz=1.25;
Sergio.Mi_Rostro.Distancia_Nariz_Labio=0.238;
    
cout<<EsCambiaFormas(Sergio,Jan);

return 0;
}
 