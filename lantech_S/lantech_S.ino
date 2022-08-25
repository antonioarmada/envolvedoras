
#include <SoftwareSerial.h>
#include "millisDelay.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Keypad.h>

// mias
#include "boton.h"
#include "config.h" // <-- CONFIGURACION


// -- OBJETOS y VARIABLES ASOCIADAS -------------------------
millisDelay latidoDelay;
#define OLED_RESET -1
Adafruit_SH1106 display(OLED_RESET); /* Object of class Adafruit_SSD1306 */
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
Boton btnIniciar = Boton(PIN_BOTON_INICIO, true, 500, 500); //(byte _pin, bool internalPullUp, uint32_t _holdDuration, uint32_t _debunceDuration)

SoftwareSerial RS485(PIN_RS485_RX, PIN_RS485_TX); // RX, TX 
//SoftwareSerial RS485(A8, A9);


// -- Benditas Variables GLOBALES -------------------------
bool debugON; 
unsigned long tiempoEsperandoRespuesta;
int vueltasUP;
int vueltasDWN;
bool subirYbajar;
//comunicacion
char comandoAejecutar= 0x00; //Null
bool esperandoRespuesta= false;
long ultimoIntentoTx= millis();
char ultimoMensajeEnviado;
byte cantidadDeIntentosTx=0;

 

void setup() { //---------------------------------------
 
  // inicio debuON como esta en config.h
  // ver que en S_RS485 se cambia si llega mensaje MSG_DEGUG_ON
  debugON = FORZAR_DEBUG; 
  
  pinMode(PIN_LATIDO_LED_EXTRA, OUTPUT);
  latidoDelay.start(latidoTiempo);

  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display(); 
  display.setRotation(2);
  display.setCursor(0,0);
  
  pinMode(PIN_cambia_RXaTX, OUTPUT);
  digitalWrite(PIN_cambia_RXaTX, LOW); // Transceiver en modo recepción
  RS485.begin(9600); // Inicializa el puerto SoftwareSerial
  delay(50);

  customKeypad.setDebounceTime(500);
  customKeypad.setHoldTime(HOLD_TIME_KEYPAD);
  customKeypad.addEventListener(keypadEvent); //agrego listener para usar HOLD (por ruido)
  
  
  Serial.begin(9600);
  Serial.println("Fin Setup " + ESTA_VERSION);
  printDebug("Fin Setup", ESTA_VERSION); 
}

void latidoFuncion() { //---------------------------------------
  static bool PIN_LATIDO_LED_Estado;
  if (latidoDelay.justFinished()) {
    latidoDelay.repeat();
    PIN_LATIDO_LED_Estado = !PIN_LATIDO_LED_Estado;
    digitalWrite(PIN_LATIDO_LED_EXTRA, PIN_LATIDO_LED_Estado ? HIGH : LOW);
  }
}

void loop() { //----------------------------------------
  
  static bool paso_primer_vuelta;

  latidoFuncion();
  
  char customKey = customKeypad.getKey(); // esto es para que se ejecute el listener del keypad
 
  //KeyState state = customKeypad.getState();

  check_RS485();

  if (btnIniciar.click()){
    printDebug("Boton INICIO", "ON");
    Tx_Msg(MSG_BOTON_INICIAR);
  } 

  // hago esto aca y no en Setup porque espero respuesta y estado de DEBUG
  // que envía el Master
  if (paso_primer_vuelta == false) {
    printLogo();
    printReposo();
    printDebug("1erVuelta","PASS");
    }
  paso_primer_vuelta = true;  

} // fin loop()
