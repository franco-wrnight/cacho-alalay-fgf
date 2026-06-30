#ifndef MIGHTYWS_H
#define MIGHTYWS_H

#include "Jugador.h"
#include <map>
#include <random>
#include <string>
#include <vector>
#include <climits>
#include <iostream>

class MightyWS : public Jugador {
  private:
    const std::vector<double> esperanzas = {0.00, 0.1667, 0.3333, 0.5000, 0.6667, 0.8333};
    std::string nombreEstudiante;

public:
    MightyWS(std::string nom = "Mightyws") 
        : Jugador(nom), nombreEstudiante("Franco Tomas Gonzalez Fuentes") {}

    int jugar(const std::map<std::string, Marcador> & /*marcadores*/,
              const std::vector<Actuacion> &actuacionesPosibles,
              const std::vector<int>&dados,  /*dados*/
              const Anotacion & /*resultadoPrevio*/) override {
        
      int mejorIndice = 0;
      int maxPuntos = -1;
      int indiceLanzar = -1;
      int indiceTachar = -1;
      // prints de cada jugada de mi jugador mightyws esto es mas que nada para debuggear cada turno de mi jugador IGNORAR
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
          std::cout << "-----------------------" << std::endl;
      }

      for(size_t i = 0 ; i < actuacionesPosibles.size(); i++){
        const Actuacion& opt = actuacionesPosibles[i];
        
        // si tenemos dormida automaticamente win
        if(opt.accion == "dormida"){
          return i;
        }

        // evaluar opciones por puntaje
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
      // parte fundamental de mi resolución viene ahora
      std::vector<int> count(7,0);
      for(auto v : dados){
        count[v]++;
      }
      int vecesDadoMax = 0;
      int caraDadoMax = 0;
      for(size_t i = 1; i<=6; i++){
        if(count[i] > vecesDadoMax){
          vecesDadoMax = count[i];
          caraDadoMax = i;
        }
      }
      // ahora se ve cual es el dado maximo y cuantas veces sale y luego eso se aplica a la formula de esperanza, sacar n dados libres
      int dadosLibres = 5 - vecesDadoMax;
      // ptje proyectado por esperanza e(x) = np
      double puntajeProyectado = maxPuntos + (esperanzas[dadosLibres] * caraDadoMax);
      // si la mano actual es debil, menor que 20, y el ptje proyectado es mayor que los puntos sacados
      // binomial: toma el riesgo al proyectarse
      // voraz si la mano es mayor a 20 y si la proyeccion es mala con pocos dados
      if(indiceLanzar != -1 && maxPuntos < 20 && puntajeProyectado > maxPuntos){
        return indiceLanzar;
      }
      if(maxPuntos > 0){
        return mejorIndice;
      }
      // si todas las jugadas fueron malas, aceptar cualquier cosa
      return indiceTachar;
    }
    std::string getNombreEstudiante() const {
        return nombreEstudiante;
    }
  
};
#endif