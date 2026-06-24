#ifndef JUGADORVORAZ_H
#define JUGADORVORAZ_H

#include "Jugador.h"
#include <map>
#include <random>
#include <string>
#include <vector>

class JugadorVoraz : public Jugador {
public:
  JugadorVoraz(std::string nom = "MightyFGF") : Jugador(nom) {}

  int jugar(const std::map<std::string, Marcador> & /*marcadores*/,
            const std::vector<Actuacion> &actuacionesPosibles,
            const std::vector<int> & /*dados*/,
            const Anotacion & /*resultadoPrevio*/) override {

  int mejorIndice = 0;
  int maxPuntos = -1;
  int indiceLanzar = -1;
  int indiceTachar = -1;
  
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
  //si se nos da la oportunidad de asegurar 20 puntos o mas, cobramos inmediatamente
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
