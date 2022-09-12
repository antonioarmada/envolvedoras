// -- CONFIGURACIONES ----------------------------------
const String ESTA_VERSION="S_v5.4a";
const bool FORZAR_DEBUG= false;
const int latidoTiempo = 500;
const int HOLD_TIME_KEYPAD = 50;
const int cuantoTiempoEsperoRespuesta = 500; //millis
const int tamanoBuffer_rx = 3; //tiene que ser const
const byte CANTIDAD_INTENTO_TIMEOUT= 2;

// -- MENSAJES -------------------------------------
const char MSG_HEAD = '{';
const char MSG_TAIL = '}';
const char MSG_RECIBIDO= 'Z';
const char MSG_DEGUG_ON= '@';
const char MSG_DEGUG_OFF= '#';
const char MSG_SETED_BAJAR_ENVOLVIENDO_TRUE = '$';
const char MSG_SETED_BAJAR_ENVOLVIENDO_FALSE = '%';
// ascii 49-57 (numeros de 1-9) reservados para vuelta_DOWN
// ascii 149-157 reservados para vuelta_UP 

const char MSG_ESTADO_REPOSO = 'a';
const char MSG_ESTADO_HOME = 'b';
const char MSG_ESTADO_ENVOL_ABAJO = 'c';
const char MSG_ESTADO_ENVOL_MEDIO = 'd';
const char MSG_ESTADO_ENVOL_ARRIBA = 'e';
const char MSG_ESTADO_PAUSADO = 'f';
const char MSG_ESTADO_SUBIENDO_FORAZADO = 'g';
const char MSG_ESTADO_BAJANDO_FORAZADO = 'h';
const char MSG_ESTADO_GIRAR_LENTO = 'i';
const char MSG_ESTADO_AYUDA_PELICULA = 'j';

const char MSG_ERROR_FILM_CORTADO = 'y';
const char MSG_ERROR_NO_HOME = 'z';
 
const char MSG_BOTON_GIRAR_LENTO = 'A';
const char MSG_BOTON_SUBIR_FORAZADO = 'C';
const char MSG_BOTON_BAJANDO_FORAZADO = 'F';
const char MSG_BOTON_AYUDA_PELICULA = 'K';
const char MSG_BOTON_POSICION_INICIAL = 'D';
const char MSG_BOTON_PAUSA = 'N';
const char MSG_BOTON_VUELTAS_ARRIBA = 'B';
const char MSG_BOTON_VUELTAS_ABAJO = 'E';
const char MSG_BOTON_BAJAR_ENVOLVIENDO = 'H';
const char MSG_BOTON_REESTAURAR = 'I';  


const char MSG_BOTON_INICIAR = 'X';


// -- TECLADO -------------------------------------
#define ROWS  3 // teclado de 7 filas
#define COLS  3 // teclado de 3 columnas
const char hexaKeys[ROWS][COLS] = {
  {MSG_BOTON_GIRAR_LENTO,MSG_BOTON_VUELTAS_ARRIBA,MSG_BOTON_SUBIR_FORAZADO},
  {MSG_BOTON_BAJAR_ENVOLVIENDO,MSG_BOTON_VUELTAS_ABAJO,MSG_BOTON_BAJANDO_FORAZADO},
  {MSG_BOTON_POSICION_INICIAL,MSG_BOTON_PAUSA,'I'} 
};

// -- PINES ENTRADAS ------------------------------------
const int PIN_BOTON_INICIO = A11;
byte rowPins[ROWS] = {31, 33, 35}; 
byte colPins[COLS] = {37, 39, 41}; 


// -- PINES SALIDAS -------------------------------------
const byte PIN_LATIDO_LED_EXTRA = 13;
const int PIN_cambia_RXaTX = A10; //DE/RE 
const int PIN_RS485_RX= A8; // RO 
const int PIN_RS485_TX= A9; // D1
