#pragma onece;

#include "Arduino.h"

#define DETENIDA 0
#define GIRANDO_LENTO 1
#define GIRANDO_NORMAL 1
#define NO_HOME 1
#define HOME 0

class Tornamesa{
    
    private:
        byte _pinSSR;
        byte _pinSensor;
        byte _pin2daVelocidad;
  
    public:
        Tornamesa ( byte pinSSR, byte pinSensor, byte pin2daVelocidad){        // Constructor
            _pinSSR = pinSSR;
            _pinSensor = pinSensor;
            _pin2daVelocidad = pin2daVelocidad;
        }

    void inicio() {  
        pinMode(_pinSensor, INPUT_PULLUP); // HIGH = no está en home (NC)
        pinMode(_pinSSR, OUTPUT); // SSR HIGH Enciende el driver
        pinMode(_pin2daVelocidad, OUTPUT); // rele interno HIGH conecta pote preset en nuestra placa
    }

    int queEstado() {
        int estado;
        if (digitalRead(_pinSSR)== LOW) estado = DETENIDA;
        if (digitalRead(_pinSSR)== HIGH && digitalRead(_pin2daVelocidad)== HIGH ) estado = GIRANDO_LENTO;
        if (digitalRead(_pinSSR)== HIGH && digitalRead(_pin2daVelocidad)== LOW ) estado = GIRANDO_NORMAL;
        return estado;
    }
    int quePosicion() {
        int posicion;
        if (digitalRead(_pinSensor)== LOW) { 
            posicion= HOME;
        } else {
            posicion= NO_HOME;
        }
        return posicion;
    }
    void girarLento(){
        //const char* mensajeDebug;
        digitalWrite(_pin2daVelocidad, HIGH);
        digitalWrite(_pinSSR, HIGH);
        //mensajeDebug = "GIRAR_LENTO";
        //return mensajeDebug;
    }
    void girarNormal(){
        //const char* mensajeDebug;
        digitalWrite(_pin2daVelocidad, LOW);
        digitalWrite(_pinSSR, HIGH);
        //mensajeDebug = "GIRAR_LENTO";
        //return mensajeDebug;
    }
    
    void detener(){
        //const char* mensajeDebug;
        digitalWrite(_pin2daVelocidad, LOW);
        digitalWrite(_pinSSR, LOW);
        //mensajeDebug= "DETENER";
        //return mensajeDebug;
    }
  
}; // terminar clase con ;