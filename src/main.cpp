#include "JugadorAleatorio.h"
#include "MightyWS.h"
#include "Tournament.h"
#include <iostream>
#include <memory>
#include "JugadorHumano.h"

int main() {
  Tournament t;

  t.addPlayer(
      []() { return std::make_shared<MightyWS>("Mightyws"); });
  t.addPlayer(
      []() { return std::make_shared<JugadorAleatorio>("Random_Bot"); });

  std::cout << "Starting simulation with 2 Random Players (10000 matches)..."
            << std::endl;

  t.run(10000);
  t.displayResults();

  return 0;
}
