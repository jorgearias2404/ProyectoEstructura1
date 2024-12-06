#include <string>
#include <iostream>

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

//EXISTEN VALORES FIJOSQUE NO SON ALTERABLES?
bool Rango (Cara A) {
  if(A.Profundidad_Ojos>=0.1&&A.Profundidad_Ojos<=0.5)
  {
    if (A.Distancia_Frente_Nariz<=4&&A.Distancia_Frente_Nariz>=1)
       {
        if (A.Distancia_Nariz_Labio<=0.5&&A.Distancia_Nariz_Labio>=0.1)
        {
          if (A.Distancia_Ojos<=0.5&&A.Distancia_Ojos>=0.1)
          {
            return false;//ESTA EN CAMPOS NORMALES
          }
          
        }
        
       }
  }
      
    return true; //CAMPOS ANORMALES  
  }
bool ValidarTamanio(float A)
{
  if (1<=A&&A<=20)
  {
    return true;
  }
  return false;
}
bool ValidarProfundidadOjos(float A){
if (0.1<=A&&A<=0.5)
{
  return true;
}

}
bool ValidarDistanciaOjos(float A){
  if (0.1<=A&&A<=0.5)
  {
    return true;
  }
  return false;
}
bool ValidarDistanciaNarizFrente(float A){
  if (1<=A&&A<=4)
  {
    return true;
  }
   return false;
}
bool ValidarDistanciaNarizLabio(float A){
 if (0.1<=A&&A<=0.5)
 {
  return true;
 }
 return false;
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
 