//  clase boton
#pragma once
#include <Arduino.h>

class Boton {
    private:
        uint32_t holdDuration;
        uint32_t debunceDuration;
        unsigned long timerHold;
        unsigned long timerDebounce;
        bool isHolding;
        bool isDebouncing;
        byte pin;

    public:
        Boton (byte _pin, bool internalPullUp, uint32_t _holdDuration, uint32_t _debunceDuration)  {
            // donde:
            // _pin : de la entrada
            // internalPullUp : bool que indica si se habilita pullup interno o no
            // _holdDuration : cuanto hay que tener apretado para que de click
            // _debunceDuration : cuanto espera para el proximo click, anti rebote
            holdDuration = _holdDuration;
            debunceDuration = _debunceDuration;
            pin = _pin;
            if (internalPullUp) {
                pinMode(pin, INPUT_PULLUP);
            } else {
                pinMode(pin, INPUT);
            }
        }

    bool click() {
        bool btnState = digitalRead(pin); // presionado es false (GND)
        bool returnClick;
        if (!btnState && !isHolding && millis()-timerDebounce >= debunceDuration) {
            isHolding = true;
            timerHold = millis();
            returnClick = false;
        }
        if (!btnState && isHolding && millis()-timerHold >= holdDuration){
            isHolding = false;
            timerDebounce = millis();
            returnClick = true;
        }
        if (btnState) {
            isHolding = false;
            returnClick = false;
        }
        return returnClick;
    }
};
