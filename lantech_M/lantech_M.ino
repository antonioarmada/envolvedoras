// primero con nuevo protocolo anti ruido

#include "HX711.h"
#include <SoftwareSerial.h>
#include "millisDelay.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_MCP4725.h>
#include <Keypad.h>
#include <efsm.h> // https://github.com/cubiwan/easy-finite-state-machine-arduino
#include <EEPROM.h>

// mias
#include "FDS.h"
#include "tornamesa.h"
#include "config.h" // <-- CONFIGURACION

// Declaracinnes FSM -------------------------------------------
STATES {
  reposo,  
  haciendoHome, 
  pausado, 
  subirForzado, 
  bajarForzado, 
  girarLentoForzado, 
  ayudaPelicula,
  envolviendoAbajo,  
  envolviendoMedio,
  envolviendoMedioBajando,
  envolviendoArriba,
  envolviendoArribaBajar,
  envolviendoAbajoBajando,
  cicloPausado
  };

EVENTS {
  hacerHome, 
  ponerReposo, 
  pausar, 
  reposar,
  continuar,
  btnForzarSubida,
  btnForzarBajada,
  btnAyudaPelicula,
  btnGirarLentoForzado,
  btnPausa,
  btnInicio
  };

INIT(reposo);

// -- OBJETOS y VARIABLES ASOCIADAS -------------------------
millisDelay latidoDelay;
#define OLED_RESET -1
Adafruit_SH1106 display(OLED_RESET); /* Object of class Adafruit_SSD1306 */
Adafruit_MCP4725 dac;
HX711 celdaDeCarga;
FDS miFDS= FDS (PIN_ENABLE_FDS, PIN_DOWN_FDS, PIN_SENSOR_FDS_DWN, PIN_SENSOR_FDS_UP);
Tornamesa miTornamesa= Tornamesa (PIN_SSR_TORNAMESA, PIN_SENSOR_TORNAMESA, PIN_2DAVELOC_TORNAMESA);
SoftwareSerial RS485(PIN_RS485_RX, PIN_RS485_TX ); // RX, TX para arduino mega


// -- Variables GLOBALES -------------------------
bool debugON; 
int estadoEnvolviendo;
bool bajarEnvolviendo = false;  // --------LEER DE EEPROM!!!!!!!!!!!!!!!!
bool SegundavezAbajo = false;
//comunicacion
char comandoAejecutar= 0x00; //Null
bool esperandoRespuesta= false;
long ultimoIntentoTx= millis();
char ultimoMensajeEnviado;
byte cantidadDeIntentosTx=0;


void setup() { //---------------------------------------
 
  Serial.begin(9600); 

  latidoDelay.start(latidoTiempo);

  pinMode(PIN_5V_DAC, OUTPUT);
  digitalWrite(PIN_5V_DAC,HIGH);
  pinMode(PIN_LATIDO_LED, OUTPUT);
  pinMode(PIN_LATIDO_LED_EXTRA, OUTPUT);

  pinMode(PIN_SSR_STRETCH, OUTPUT);
  digitalWrite(PIN_SSR_STRETCH, LOW);


  pinMode(PIN_cambia_RXaTX, OUTPUT);
  digitalWrite(PIN_cambia_RXaTX, LOW); // modo de RS485 (DE-RE): LOW= Rx, HIGH= Tx

  dac.begin(0x60); //0x60 para el modulo que compré
  dac.setVoltage(0, false);
 
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display(); 
  display.setRotation(2);
  display.setCursor(0,0);

  celdaDeCarga.begin(PIN_CELDA_DATA, PIN_CELDA_CLK);
  celdaDeCarga.set_scale(ESCALA_CELDA_DE_CARGA); // Establecemos la escala

  RS485.begin(9600);
  delay(2000); // espero al esclavo

  pinMode(PIN_SWITCH_DEBUG, INPUT_PULLUP); 
  // el cambio en DEBUG funciona solo al iniciar para ver todo el ciclo
  // y no perder tiempo en leer el switch en cada mensaje
  if (digitalRead(PIN_SWITCH_DEBUG)== 0) {
    debugON=true;
    Tx_Msg(MSG_DEGUG_ON);
    printDebug("SW DEBUG", "ON");
  } else {
    Tx_Msg(MSG_DEGUG_OFF);
    printDebug("SW DEBUG", "OFF");
  }
  
  pinMode(PIN_SENSOR_FDS_BANDA,INPUT_PULLUP);
  
  miFDS.inicio();
  miTornamesa.inicio();

  Serial.println("Fin Setup " + ESTA_VERSION);
  printDebug("Fin Setup", ESTA_VERSION);

  entrarEnReposo();

}

void loop() { //----------------------------------------

  static int timerMsgVuelasInicio= millis();
  static int yaEnvidadoVueltas= 0;

  latidoFuncion();
  checkBandaFDS();
  check_RS485();

  // hago esto aca y no en Setup porque espero respuesta de DEBUG
  // que envía el Slave y scolision
  if (millis()-timerMsgVuelasInicio > 600 && yaEnvidadoVueltas<1) {
    vueltasInicioUP();
    yaEnvidadoVueltas++;
    }
  // espero un tiempo mayor al de TimeOut por si estaba en esa
  if (millis()-timerMsgVuelasInicio > 1200 && yaEnvidadoVueltas<2) {
     vueltasInicioDWN();
     yaEnvidadoVueltas++;
    }

  // efsmTriggers(); si hay
  efsmExecute();

} // fin loop()
