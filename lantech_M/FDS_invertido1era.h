#pragma onece;

#include "Arduino.h"

#define SUBIENDO 0
#define BAJANDO 1
#define DETENIDO 3
#define HOME_DOWN 0
#define HOME_UP 1
#define CAMINO 3


#define TIEMPO_FRENADO 5000

class FDS{
    
    private:
        byte _pinEnable;
        byte _pinDown;
        byte _pinSensorDwn;
        byte _pinSensorUp;  
    
    public:
        FDS ( byte pinEnable, byte pinDown, byte pinSensorDwn, byte pinSensorUp){        // Constructor
            _pinEnable = pinEnable;
            _pinDown = pinDown;
            _pinSensorDwn = pinSensorDwn;
            _pinSensorUp = pinSensorUp;
        }

        void inicio() {  
            pinMode(_pinSensorDwn, INPUT_PULLUP); // LOW = no está en home (NA) es para detenctar si desconecta
            pinMode(_pinSensorUp, INPUT_PULLUP);  // LOW = no está en home (NA) es para detenctar si desconecta
            pinMode(_pinEnable, OUTPUT); // rele HIGH Enciende el driver
            pinMode(_pinDown, OUTPUT); // rele HIGH coneta dirección hacia abajo (NA), LOW conecta dir hacia arriba (NC)
        }

        int queEstado() {
            int estado;
            if (digitalRead(_pinEnable)== HIGH && digitalRead(_pinDown)== LOW)  estado= SUBIENDO;
            if (digitalRead(_pinEnable)== HIGH && digitalRead(_pinDown)== HIGH) estado= BAJANDO;
            if (digitalRead(_pinEnable)== LOW) estado= DETENIDO;
            return estado;
        }
        int quePosicion() {
            int posicion;
            if (digitalRead(_pinSensorDwn)== HIGH) posicion= HOME_DOWN;
            if (digitalRead(_pinSensorUp)== HIGH) posicion= HOME_UP;
            if (digitalRead(_pinSensorUp)== LOW && digitalRead(_pinSensorDwn)== LOW ) posicion= CAMINO;
            return posicion;
        }
        void bajar(){
            //const char* mensajeDebug;
            if (this->quePosicion()!= HOME_DOWN) {
                if (this->queEstado() == SUBIENDO) {
                    digitalWrite(_pinEnable, LOW);
                    delay (TIEMPO_FRENADO);
                }
                digitalWrite(_pinDown, HIGH);
                digitalWrite(_pinEnable, HIGH);
                //mensajeDebug= "BAJAR";
            } else {
                digitalWrite(_pinEnable, LOW);
            }
            //return mensajeDebug;
        }
        void subir(){
            //const char* mensajeDebug;
            if (this->quePosicion()!= HOME_UP) { //HOME_UP
                if (this->queEstado() == BAJANDO) {
                    digitalWrite(_pinEnable, LOW);
                    delay (TIEMPO_FRENADO);
                }
                digitalWrite(_pinDown, LOW);
                digitalWrite(_pinEnable, HIGH);
                //mensajeDebug= "SUBIR";
            } else {
                digitalWrite(_pinEnable, LOW); 
            }
            //return mensajeDebug;
        }

        void detener(){
            //const char* mensajeDebug;
            digitalWrite(_pinDown, LOW);
            digitalWrite(_pinEnable, LOW);
            //mensajeDebug= "DETENER";
            //return mensajeDebug;
        }
  
}; // terminar clase con ;