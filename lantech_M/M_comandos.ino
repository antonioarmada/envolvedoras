
void ejecutarComando(char msg){
      switch (msg) {
        case MSG_BOTON_GIRAR_LENTO: 
          efsmEvent(btnGirarLentoForzado);
          printDebug("Teclado","TOR Lento");
          Tx_Msg(MSG_ESTADO_GIRAR_LENTO);
          break;
        case MSG_BOTON_SUBIR_FORAZADO: 
          efsmEvent(btnForzarSubida);
          printDebug("Teclado","FDS UP");
          break;
        case MSG_BOTON_BAJANDO_FORAZADO: 
          efsmEvent(btnForzarBajada);
          printDebug("Teclado","FDS DWN");
          break;
        case MSG_BOTON_AYUDA_PELICULA: 
          efsmEvent(btnAyudaPelicula);
          printDebug("Teclado","AyudaPel");
          Tx_Msg(MSG_ESTADO_AYUDA_PELICULA);
          break;
        case MSG_BOTON_POSICION_INICIAL: 
          efsmEvent(hacerHome);
          printDebug("Teclado","PosInicial");
          Tx_Msg(MSG_ESTADO_HOME);
          break;
        case MSG_BOTON_INICIAR:
          efsmEvent(btnInicio);
          printDebug("Boton","INICIAR");
          Tx_Msg(MSG_ESTADO_ENVOL_ABAJO); 
          break;
        case MSG_BOTON_PAUSA: 
          efsmEvent(btnPausa);
          printDebug("Boton","Pausa");
          Tx_Msg(MSG_ESTADO_PAUSADO); 
          break;
        case MSG_BOTON_VUELTAS_ARRIBA: 
          //efsmEvent(btnPausa);
          printDebug("VUELTAS","UP");
          vueltasUP(); 
          break;
        case MSG_BOTON_VUELTAS_ABAJO: 
          //efsmEvent(btnPausa);
          printDebug("VUELTAS","DWN");
          vueltasDWN();
          break;
        case MSG_BOTON_REESTAURAR: 
          printDebug("REESTARUAR","VAL.");
          EEPROM.update(EE_DIRECCION_DWN, 1 );
          EEPROM.update(EE_DIRECCION_UP, 1 );
          EEPROM.update(EE_DIRECCION_BAJAR_ENVOLVIENDO, 0 );
          //rearmo la secuencia de inicio para que mande ordenado el nro de vuelas
          timerMsgVuelasInicio= millis();
          secuenciaInicio= 0;
          break;
        case MSG_BOTON_BAJAR_ENVOLVIENDO: 
          printDebug("Boton","BajarEnv");
          bajarEnvolviendo=!bajarEnvolviendo;
          if (bajarEnvolviendo) { //aca aviso al esclavo que realmente se cambio la configuracion
            EEPROM.update(EE_DIRECCION_BAJAR_ENVOLVIENDO, 1 );
            Tx_Msg(MSG_SETED_BAJAR_ENVOLVIENDO_TRUE);
          } else {
            EEPROM.update(EE_DIRECCION_BAJAR_ENVOLVIENDO, 0 );
            Tx_Msg(MSG_SETED_BAJAR_ENVOLVIENDO_FALSE);
          }
          break;
        default:
          printDebug("Otra Rtta",String(msg));
          //Tx_Msg(msg);
          break;
      }
}



