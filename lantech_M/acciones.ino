
void latidoFuncion() {
  static bool PIN_LATIDO_LED_Estado;
  if (latidoDelay.justFinished()) {
    latidoDelay.repeat();
    PIN_LATIDO_LED_Estado = !PIN_LATIDO_LED_Estado;
    digitalWrite(PIN_LATIDO_LED, PIN_LATIDO_LED_Estado ? HIGH : LOW);
    digitalWrite(PIN_LATIDO_LED_EXTRA, PIN_LATIDO_LED_Estado ? HIGH : LOW);
  }
}

void checkBandaFDS() {
  //printDebug("ENTRANDO", "B");
  if (digitalRead(PIN_SENSOR_FDS_BANDA) == HIGH) {
      printDebug("BANDA CORTADA", "ERRORFATAL");
      Tx_Msg(MSG_ERROR_BANDA_CORTADA);
      // detener todo y colgar la placa...
      miTornamesa.detener();
      miFDS.detener();
      //cli(); //desactiva las interrupciones
      while(1); //bucle infinito
  }
}

void entrarEnReposo() {
  fncAyudaPeliculaInicializacion(); 
  if (miFDS.quePosicion()==0 && miTornamesa.quePosicion()==0) { // si esta en pos inicial 
    printDebug("REPOSO", "entrando en");
    Tx_Msg(MSG_ESTADO_REPOSO);
  } else {
    printDebug("ERROR", "NO HOME");
    Tx_Msg(MSG_ERROR_NO_HOME);
  }
}

void estoyEnReposo() {
  fcnAyudaPelicula(); 
}

void fcnSetupHome() {
  fncAyudaPeliculaInicializacion();
  Tx_Msg(MSG_ESTADO_HOME);
  if (miFDS.quePosicion()!=0){ //0-HOME_DOWN, 1-HOME_UP, 3-CAMNIO
    miFDS.bajar();
    printDebug("FDS HOME SETUP", "OK");
  } else {
    printDebug("FDS HOME SETUP", "HOME");
  }
  if (miTornamesa.quePosicion()!=0){ //0-HOME, 1-NO_HOME
    miTornamesa.girarLento();
    printDebug("TORN HOME SETUP", "OK");
  } else {
    printDebug("TORN HOME SETUP", "HOME");
  }
}

void fcnHaciendoHome() { // hice una funcion para que sean simultaneos
  static bool miFDSHome, miTornamesaHome;
  fcnAyudaPelicula();
  if (miFDSHome == false) {
    if (miFDS.quePosicion()==0){ //0-HOME_DOWN, 1-HOME_UP, 3-CAMNIO
      miFDS.detener();
      printDebug("FDS HOME", "END");
      miFDSHome= true;
    }
  }
  if (miTornamesaHome == false) {
    if (miTornamesa.quePosicion()==0){ //0-HOME, 1-NO_HOME
        miTornamesa.detener();
        printDebug("TORN HOME", "END");
        miTornamesaHome= true;
    }
  }
  if (miFDSHome && miTornamesaHome) {
      miTornamesaHome= miFDSHome = false;
      pararEnvolver(5);
      efsmEvent(continuar);
  }
}

void fcnIniciarSubida() {
  miFDS.subir();
  Tx_Msg(MSG_ESTADO_SUBIENDO_FORAZADO);
}

void fcnDetenerFDSyAvisar() {
  miFDS.detener();
  Tx_Msg(MSG_ESTADO_REPOSO);
}

void fcnIniciarBajada() {
  miFDS.bajar();
  Tx_Msg(MSG_ESTADO_BAJANDO_FORAZADO);
}

void fcnDetenerTornamesayAvisar() {
  miTornamesa.detener();
  //Tx_Msg(MSG_ESTADO_REPOSO);
   efsmEvent(reposar);
}

void fcnSubiendoForzado() {
  if (miFDS.quePosicion()==1){ //0-HOME_DOWN, 1-HOME_UP, 3-CAMNIO
    miFDS.detener();
    printDebug("FDS HOME", "UP");
    //efsmEvent(btnForzarSubida);
    //Tx_Msg(MSG_ESTADO_REPOSO);
    efsmEvent(reposar);
  }
}

void fcnBajandoForzado() {
  if (miFDS.quePosicion()==0){ //0-HOME_DOWN, 1-HOME_UP, 3-CAMNIO
    miFDS.detener();
    printDebug("FDS HOME", "DOWN");
    //efsmEvent(btnForzarBajada);
    //Tx_Msg(MSG_ESTADO_REPOSO);
    efsmEvent(reposar);
  }
}

void fncEnvolverInicializacion() { 
  if (miFDS.quePosicion()==0 && miTornamesa.quePosicion()==0) {
    printDebug("Envolver","INICIO");
    Tx_Msg(MSG_ESTADO_ENVOL_ABAJO);
    //miTornamesa.girarLento();
    miTornamesa.girarNormal();
    delay(ESPERA_PARA_DAR_FILM_ENVOLVIENDO);
    dac.setVoltage(500, false); // arranco bien despacio el stretch
    digitalWrite(PIN_SSR_STRETCH, HIGH);
  } else {
     printDebug("ERROR", "NO HOME");
     Tx_Msg(MSG_ERROR_NO_HOME);
     //delay(2000); // ------------------------------------------------------------------------
     efsmEvent(reposar);
    }
  }

void fncEnvolverAbajo() {  
    static int nroVueltasInferior = EEPROM.read(EE_DIRECCION_DWN);
    static int contadorVueltas;
    //static long debunceVueltaAnterior;
    static bool bajoElSensorTornamesa;
    if (miTornamesa.quePosicion()!=0) {
      bajoElSensorTornamesa = true; 
    }
//      if (contadorVueltas==1) {
//            miTornamesa.girarNormal();
//      }
       miTornamesa.girarNormal(); // sacar si descomentamos lo anterior
      if (contadorVueltas < nroVueltasInferior) {
        fcnEnvolviendo();
        if (miTornamesa.quePosicion()==0 && bajoElSensorTornamesa){ //0-HOME, 1-NO_HOME
          contadorVueltas++;
          bajoElSensorTornamesa = false;
          printDebug("contadorV" , String(contadorVueltas));
          //debunceVueltaAnterior = millis();
        }
      } else {
        contadorVueltas=0;
        miTornamesa.girarNormal(); // por si era una sola vuelta y quedaba lento
        miFDS.subir();
        efsmEvent(continuar);
      } 
}  

void fncEnvolverMedio() { // subiendo
    if (miFDS.quePosicion()!=1){ //0-HOME_DOWN, 1-HOME_UP, 3-CAMNIO 
      fcnEnvolviendo();
    } else {
      miFDS.detener();
      if (!bajarEnvolviendo) {
        changeState(envolviendoArriba);
      } else {
        changeState(envolviendoArribaBajar);
      }
    }   
} 

void fncEnvolverArriba() { 
    static int nroVueltasSuperior = EEPROM.read(EE_DIRECCION_UP);
    static int contadorVueltas;
    //static long debunceVueltaAnterior;
    static bool bajoElSensorTornamesa; // es para un debunce.. digo "sube" el sensor cuando esta en home, y baja cuando no, pasaba que si esta lengo suma mas vueltas por eso.. 
    static bool tornamesaGirandoLento;
    if (miTornamesa.quePosicion()!=0) {
      bajoElSensorTornamesa = true; 
    }
    if (miFDS.quePosicion()==1){ //0-HOME_DOWN, 1-HOME_UP, 3-CAMNIO 
      if (contadorVueltas < nroVueltasSuperior) {
          tornamesaGirandoLento = false;
          if (contadorVueltas>=(nroVueltasSuperior-1)){
             miTornamesa.girarLento();
             tornamesaGirandoLento= true;
          }
          if (!tornamesaGirandoLento) { // cuando giraba lento la funcion envolviendo tira mucho film por eso cambio a ayuda pelicula
            fcnEnvolviendo();
          } else {
            fcnAyudaPelicula(); 
          }
          if (miTornamesa.quePosicion()==0 && bajoElSensorTornamesa){ //0-HOME, 1-NO_HOME //&& (millis()- debunceVueltaAnterior) > DEBOUNCE_VUELTA)
              contadorVueltas++;
              bajoElSensorTornamesa=false;
          }
      } else if (miTornamesa.quePosicion()==0){ // para asegurarme que pare en home
          contadorVueltas=0;
          pararEnvolver(0); // reinicia la variable global estadoEnvolviendo
          delay(ESPERA_AL_TERMINAR_ARRIBA);
          efsmEvent(continuar);
      } 
    } else {
      printDebug("ERROR", "NO UP");
    } 
} 

void fncEnvolverArribaBajar() { 
    static int nroVueltasSuperior = EEPROM.read(EE_DIRECCION_UP); // EEPROM.read(EE_DIRECCION_UP)leer de EEPROM -------------------------- HARCODEADOOOOO
    static int contadorVueltas;
    static bool bajoElSensorTornamesa;
    if (miTornamesa.quePosicion()!=0) {
      bajoElSensorTornamesa = true; 
    }
    if (miFDS.quePosicion()==1){ //0-HOME_DOWN, 1-HOME_UP, 3-CAMNIO 
      if (contadorVueltas <= nroVueltasSuperior) {
        fcnEnvolviendo();
        if (miTornamesa.quePosicion()==0 && bajoElSensorTornamesa){ //0-HOME, 1-NO_HOME
          contadorVueltas++;
          bajoElSensorTornamesa= false;
        }
      } else { // para asegurarme que pare en home
        contadorVueltas=0;
        miFDS.bajar();
        efsmEvent(continuar);
      } 
    } else {
      printDebug("ERROR", "NO UP");
    } 
} 

void fncEnvolverMedioBajando() {  
    if (miFDS.quePosicion()!=0){ //0-HOME_DOWN, 1-HOME_UP, 3-CAMNIO 
      fcnEnvolviendo();
    } else {
      miFDS.detener();
      efsmEvent(continuar);
    }   
} 

void fncEnvolverAbajoBajando() {  
    static int nroVueltasInferior = EEPROM.read(EE_DIRECCION_DWN); // EEPROM.read(EE_DIRECCION_DWN); leer de EEPROM -------------------------- HARCODEADOOOOO
    static int contadorVueltas;
    bool bajoElSensorTornamesa;
    if (miTornamesa.quePosicion()!=0) {
      bajoElSensorTornamesa = true; 
    }
    if (contadorVueltas==(nroVueltasInferior-1)){
          miTornamesa.girarLento();
      }
    if (contadorVueltas <= nroVueltasInferior) {
        fcnEnvolviendo();
        if (miTornamesa.quePosicion()==0 && bajoElSensorTornamesa){ //0-HOME, 1-NO_HOME
          contadorVueltas++;
          printDebug("contadorV",String(contadorVueltas));
          bajoElSensorTornamesa= false;
      }
      } else {
        contadorVueltas=0;
        pararEnvolver(0);
        efsmEvent(continuar);
      } 
}  


void fcnEnvolviendo() {
  static uint32_t voltajeDAC;
  static long medAnterior;
  const int Vmax= 3000;//int(3*4096/5);
  const int Fmax= 7; //kg
  float b = Vmax/Fmax;
  static int cuantos0fuerza; // nro de iteraciones que dio 0 la fuerza
  int lecturaPote = lecturaPote = analogRead(PIN_ENTRADA_POTE_FUERZA);
  float Fpote = map(lecturaPote, 0, 1023, 0, Fmax);
  float Fcelda = celdaDeCarga.get_units(10); 
  float dF = Fcelda - Fpote; 
  voltajeDAC = voltajeDAC + int(dF*b);
  voltajeDAC = constrain (voltajeDAC, 0 , Vmax);
  dac.setVoltage(voltajeDAC, false);
  if (Fcelda < LIMITE_ERROR_FUERZA_FILM) { 
    cuantos0fuerza++;
  } else {
    cuantos0fuerza=0;
  }
  if (cuantos0fuerza > LIMITE_ERROR_CICLOS_FILM) { 
    printDebug("ERROR", "F.CORTADO");
    //pararEnvolver(0);
    Tx_Msg(MSG_ERROR_FILM_CORTADO);
    miTornamesa.detener(); // porque seguia girando cuando estaba lento, asi me aseguro que pare aca
    efsmEvent(btnPausa); //cambie reposar por btnPausa para que pueda continuar.
  } 
}

void pararEnvolver(int _estadoEnvolviendo) {
    estadoEnvolviendo = _estadoEnvolviendo; // int global
    miFDS.detener(); 
    miTornamesa.detener();
    digitalWrite(PIN_SSR_STRETCH, LOW);
}

void retomarEnvolver(int _estadoEnvolviendo) {
    printDebug("Envolver","INICIO");
    miTornamesa.girarNormal();
    delay(1000);// espero que arranque la tornamesa
    dac.setVoltage(500, false); // arranco bien despacio el stretch
    digitalWrite(PIN_SSR_STRETCH, HIGH);
    switch (_estadoEnvolviendo){ // porque el estado es cicloPausado, asi lo retoma
      case 1:
        changeState(envolviendoAbajo);
        break;
      case 2:
        miFDS.subir(); 
        changeState(envolviendoMedio);
        break;
      case 3:
        changeState(envolviendoArriba);
        break;
      case 4:
        miFDS.bajar();
        changeState(envolviendoMedioBajando);
        break;
      default:
      changeState(reposo);
      Tx_Msg(MSG_ESTADO_REPOSO);
        break;
    }
}

void fncAyudaPeliculaInicializacion() {
    printDebug("Ayuda Pel","INICIO");
    dac.setVoltage(0, false); // arranco bien despacio el stretch
    //digitalWrite(PIN_SSR_STRETCH, HIGH);
    //delay(100);
    float Fcelda = celdaDeCarga.get_units(10); // sacar
    //printDebug("Fuerza",String(Fcelda)); // sacar
  }

int fcnAyudaPelicula() {
  static uint32_t voltajeDAC;
  static unsigned long ultimaAyuda;
  const int Vmax= 1500; //1500 org
  const int Vmin= 0;
  float Fcelda = celdaDeCarga.get_units(10); 
  if (Fcelda >= LIMITE_FUERZA_AYUDA_PELICULA) { //LIMITE_FUERZA_AYUDA_PELICULA
      digitalWrite(PIN_SSR_STRETCH, HIGH);
      ultimaAyuda = millis();
      if (Fcelda < LIMITE_FUERZA_AYUDA_PELICULA * 2 ){ // hice dos grados de ayuda.. para que no tire tanto.
        dac.setVoltage(Vmax/2, false);
      } else {
        dac.setVoltage(Vmax, false);
      } 
  } else {
    dac.setVoltage(Vmin, false);
    if ((millis() - ultimaAyuda) > TEMPORIZADOR_HIGH_AYUDA_PELICULA){   
      digitalWrite(PIN_SSR_STRETCH, LOW);
    }
  }
}
