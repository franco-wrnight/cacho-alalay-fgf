#ifndef MIGHTYWS_H
#define MIGHTYWS_H

#include "Jugador.h"
#include <map>
#include <random>
#include <string>
#include <vector>

class MightyWS : public Jugador {
public:
  MightyWS(std::string nom = "Mightyws") : Jugador(nom) {}

  int jugar(const std::map<std::string, Marcador> & /*marcadores*/,
            const std::vector<Actuacion> &actuacionesPosibles,
            const std::vector<int>&dados  /*dados*/,
            const Anotacion & /*resultadoPrevio*/) override {
  int mejorIndice = 0;
  int maxPuntos = -1;
  int indiceLanzar = -1;
  int indiceTachar = -1;

  //prints de cada jugada de mi jugador mightyws esto es mas que nada para debuggear cada turno de mi jugador
  bool printsjugadas = false;
  if (printsjugadas) {
      std::cout << "\n turno de " << this->nombre << " " << std::endl;
      std::cout << "dados tirados: [ ";
      for (auto v : dados) {
          std::cout << v << " ";
      }
      std::cout << "]" << std::endl;

      std::cout << "opciones posibles de Mightyws:" << std::endl;
      for (size_t i = 0; i < actuacionesPosibles.size(); ++i) {
          actuacionesPosibles[i].displayCompacto(i); 
      }
      std::cout << "-------------" << std::endl;
  }


  for(size_t i = 0 ; i < actuacionesPosibles.size(); i++){
    const Actuacion& opt = actuacionesPosibles[i];
    //si tenemos dormida automaticamente win
    if(opt.accion == "dormida"){
      return i;
    }

//luego

    //evaluar opciones por puntaje
    if(opt.accion == "anotar" || opt.accion == "sobre"){
      if(opt.anotacion.puntos > maxPuntos){
        maxPuntos = opt.anotacion.puntos;
        mejorIndice = i;
      }
      if(opt.anotacion.puntos == 0){
        indiceTachar = i;
      }
    }

    if(opt.accion == "lanzar"){
      indiceLanzar = i;
    }
  }
  
  //parte fundamental de mi resolución: algoritmo voraz
  //este primer if es equivalente a cortar la distribucion X ¬(5,1/6) en valores de X mayores a 4
  if(maxPuntos >= 20){
    return mejorIndice;
  }
  //si la mesa da pocos puntos 
  if(indiceLanzar != -1){
    return indiceLanzar;
  }
  //si ya se hizo el 2do intento y no mejoramos cobramos lo poco q sacamos
  if(maxPuntos > 0){
    return mejorIndice;
  }
  //si todas las jugadas fueron malas, retirarse
  return indiceTachar;
  
  }
};


#endif 
