/* IMPORTANTE: la máquina 1 tiene un rele para FDS con logica normal mientras
que las otras dos tienen invertidas. Este archivo espara las maquinas 2 y 3
en la 1 renombrar el archivo "FDS_invertido1era.h" a "FDS.h" y reemplazar este 
ACA: LOW -> ACTIVO, HIGH ->DESACTIVO */

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
            pinMode(_pinEnable, OUTPUT); // rele HIGH Enciende el driver en maquina 1 resto LOW
            pinMode(_pinDown, OUTPUT); // rele HIGH coneta dirección hacia abajo (NA), LOW conecta dir hacia arriba (NC)
            // ojo que lo de arriba esta invertido en maquina 2 y 3
            digitalWrite(_pinEnable, HIGH);
        }

        int queEstado() {
            int estado;
            if (digitalRead(_pinEnable)== LOW && digitalRead(_pinDown)== HIGH)  estado= SUBIENDO;
            if (digitalRead(_pinEnable)== LOW && digitalRead(_pinDown)== LOW) estado= BAJANDO;
            if (digitalRead(_pinEnable)== HIGH) estado= DETENIDO;
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
                    digitalWrite(_pinEnable, HIGH);
                    delay (TIEMPO_FRENADO);
                }
                digitalWrite(_pinDown, LOW);
                digitalWrite(_pinEnable, LOW);
                //mensajeDebug= "BAJAR";
            } else {
                digitalWrite(_pinEnable, HIGH);
            }
            //return mensajeDebug;
        }
        void subir(){
            //const char* mensajeDebug;
            if (this->quePosicion()!= HOME_UP) { //HOME_UP
                if (this->queEstado() == BAJANDO) {
                    digitalWrite(_pinEnable, HIGH);
                    delay (TIEMPO_FRENADO);
                }
                digitalWrite(_pinDown, HIGH);
                digitalWrite(_pinEnable, LOW);
                //mensajeDebug= "SUBIR";
            } else {
                digitalWrite(_pinEnable, HIGH); 
            }
            //return mensajeDebug;
        }

        void detener(){
            //const char* mensajeDebug;
            digitalWrite(_pinDown, HIGH);
            digitalWrite(_pinEnable, HIGH);
            //mensajeDebug= "DETENER";
            //return mensajeDebug;
        }
  
}; // terminar clase con ;