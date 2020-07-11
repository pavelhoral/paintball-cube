#include "KeepTalking.hpp"

/*

nahodne rezimy, zafixovani stavu hodnoty, indikace svetelna a zvukova
display muze ukazovat paznaky
projiti alespon 5 stavy, chyba uzamkne krabicku na 10s...

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
