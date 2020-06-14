#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include "GameModule.hpp";
#include "TM1637Display.h";

/**
 * Countdown clock module.
 */
class Countdown : public GameModule {
public:
    Countdown(TM1637Display display);
    void setup();
    void loop();
    void teardown();
};

#endif