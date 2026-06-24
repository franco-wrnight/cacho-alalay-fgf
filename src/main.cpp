#include "JugadorAleatorio.h"
#include "JugadorVoraz.h"
#include "Tournament.h"
#include <iostream>
#include <memory>

int main() {
  Tournament t;

  t.addPlayer(
      []() { return std::make_shared<JugadorVoraz>("MightyFGF"); });
  t.addPlayer(
      []() { return std::make_shared<JugadorAleatorio>("Bot_Random_2"); });
  t.addPlayer(
      []() { return std::make_shared<JugadorAleatorio>("Bot_Random_3"); });

  std::cout << "Starting simulation with 3 Random Players (100 matches)..."
            << std::endl;

  t.run(100);
  t.displayResults();

  return 0;
}
