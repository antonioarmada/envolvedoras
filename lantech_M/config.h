// -- CONFIGURACIONES ----------------------------------
const String ESTA_VERSION="M_v6.1";
const bool FORZAR_DEBUG= false;
unsigned long latidoTiempo = 500;
const float ESCALA_CELDA_DE_CARGA = 75666.66;
const float LIMITE_ERROR_FUERZA_FILM = 0.3; //0.3 en #1 / 1.0 en #2 / 0.3 en #3
const int LIMITE_ERROR_CICLOS_FILM = 8; // Iteraciones antes de error corte film
const float LIMITE_FUERZA_AYUDA_PELICULA= 0.9; //
const int TEMPORIZADOR_HIGH_AYUDA_PELICULA = 30*1000; //cto esta activo el SSR del A.P. hasta que se apaga solo
const int ESPERA_PARA_DAR_FILM_ENVOLVIENDO = 2*1000; // al iniciar a envolver espera esto para largar para que se tense el film
//const int DEBOUNCE_VUELTA= 2000; // para que no cuente varias veces la vuelta de tornamesa
const int ESPERA_AL_TERMINAR_ARRIBA= 10*1000; // tiempo para que corte el film antes de hacer HOME al terminar

// -- COMUNICACION --------------------------------------
const int cuantoTiempoEsperoRespuesta = 500; 
const int tamanoBuffer_rx = 3; //tiene que ser const
const byte CANTIDAD_INTENTO_TIMEOUT= 2;

// -- PINES ENTRADAS ------------------------------------
const int PIN_SENSOR_TORNAMESA = 23;
const int PIN_SENSOR_FDS_UP = 25;
const int PIN_SENSOR_FDS_DWN = 39;
const int PIN_SENSOR_FDS_BANDA = 41;
const int PIN_SENSOR_INFRARROJO= 49;
const int PIN_CELDA_DATA= 15;
const int PIN_CELDA_CLK= 16;
const int PIN_ENTRADA_POTE_FUERZA =A0;
const int PIN_SWITCH_DEBUG = A12;

// -- PINES SALIDAS -------------------------------------
const int PIN_2DAVELOC_TORNAMESA= 14;
const int PIN_SSR_TORNAMESA= 2;
const int PIN_ENABLE_FDS= A1;
const int PIN_DOWN_FDS= A2;
const int PIN_SSR_STRETCH=17;
const int PIN_LATIDO_LED = 53;
const int PIN_LATIDO_LED_EXTRA = 13;
const int PIN_5V_DAC= 19;
const int PIN_cambia_RXaTX = A10; //expansion
const int PIN_RS485_RX= A11; //expansion A8 estaba roto en la placa
const int PIN_RS485_TX= A9; //expansion

// -- EEPROM y DEFAULT ----------------------------------
const int EE_DIRECCION_UP = 10;
const int EE_DIRECCION_DWN = 20;
const int EE_DIRECCION_BAJAR_ENVOLVIENDO = 2;
const int VUELTAS_UP_DEFAULT = 4;
const int VUELTAS_DWN_DEFAULT = 4;
const int BAJAR_ENVOLVIENDO_DEFAULT = 0; // 0 NO BAJA, 1 SI BAJA ENVOLVIENDO

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

const char MSG_ERROR_BANDA_CORTADA = 'w';
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

const char MSG_BOTON_INICIAR = 'X';
