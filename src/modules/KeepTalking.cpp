#include "KeepTalking.hpp"

/*
GAME 01
- STATE: LED blika cervena, zelena, zelena
- INTERACTION: na zasunuti konektoru zahraje nejaky nastroj
- ANSWER: je nutne zadat trojmistne cislo 

GAME 02:
- STATE: LED blika cervena, modra, modra
- INTERACTION: na zasunuti konektoru zahraje zvuk zvirete
- ANSWER: podle barvy diody je nutne zahrat za sebou zvuky tri zvirat pri zasunutem libovolnem jacku

GAME 03:
- STATE: LED blika cervena, zelena, modra
- INTERACTION: na zasunuti konektoru zahraje muziku
- ANSWER: podle barvy diody je nutne zahrat za sebou zvuky tri zvirat pri zasunutem libovolnem jacku

GAME 04:
- STATE: LED blika zelena, modra, modra
- INTERACTION: na zasunuti konektoru ukaze symbol
- ANSWER: podle symbolu je nutne zadat cislo

GAME 05:
- STATE: LED blika cervena, cervena, modra
- INTERACTION: na zasunuti konektoru ukaze symbol
- ANSWER: podle cisla musi zastrcit jack a 10 vterin se nehybat
*/

KeepTalking::KeepTalking(Context context) : context_(context) {
}

void KeepTalking::setup() {
}

void KeepTalking::loop() {
  switch (gameIndex_) {
    case 0:
      handleGame01();
  }
}

void KeepTalking::handleGame01() {

}
