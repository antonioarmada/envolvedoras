// CONFIGURACION DE LA MAQUINA DE ESTADOS FINITOS
// en el main hice las declaraciones de estados y eventos

START_TRANSITIONS
    TRANSITION(hacerHome, reposo, haciendoHome,fcnSetupHome()); //(evento, estadoInicial, estadoFinal, ejecutarAntesdePasara)
    TRANSITION(continuar, haciendoHome, reposo, entrarEnReposo());  
    TRANSITION(reposar, ANY_STATE, reposo, entrarEnReposo());

    TRANSITION(btnForzarSubida, reposo, subirForzado, fcnIniciarSubida()); 
    TRANSITION(btnForzarSubida, subirForzado, reposo, fcnDetenerFDSyAvisar());
    TRANSITION(btnForzarBajada, reposo, bajarForzado, fcnIniciarBajada()); 
    TRANSITION(btnForzarBajada, bajarForzado, reposo, fcnDetenerFDSyAvisar());

    TRANSITION(btnGirarLentoForzado, reposo, girarLentoForzado, miTornamesa.girarLento()); 
    TRANSITION(btnGirarLentoForzado, girarLentoForzado, reposo, fcnDetenerTornamesayAvisar()); 

    TRANSITION(btnAyudaPelicula, reposo, ayudaPelicula, fncAyudaPeliculaInicializacion());
    TRANSITION(btnAyudaPelicula, ayudaPelicula, reposo, pararEnvolver(5));

    TRANSITION(btnInicio, reposo, envolviendoAbajo, fncEnvolverInicializacion());
    TRANSITION(btnInicio, cicloPausado, ANY_STATE, retomarEnvolver(estadoEnvolviendo));


    TRANSITION(continuar, envolviendoAbajo, envolviendoMedio, Tx_Msg(MSG_ESTADO_ENVOL_MEDIO)); 
    TRANSITION(continuar, envolviendoMedio, envolviendoArriba, Tx_Msg(MSG_ESTADO_ENVOL_ARRIBA)); 
    TRANSITION(continuar, envolviendoArriba, haciendoHome, fcnSetupHome()); 
    TRANSITION(continuar, envolviendoArribaBajar, envolviendoMedioBajando, Tx_Msg(MSG_ESTADO_ENVOL_MEDIO)); 
    TRANSITION(continuar, envolviendoMedioBajando, envolviendoAbajoBajando, Tx_Msg(MSG_ESTADO_ENVOL_ABAJO)); 
    TRANSITION(continuar, envolviendoAbajoBajando, reposo, entrarEnReposo()); 

    TRANSITION(btnPausa, envolviendoAbajo, cicloPausado, pararEnvolver(1));
    TRANSITION(btnPausa, envolviendoMedio, cicloPausado, pararEnvolver(2)); 
    TRANSITION(btnPausa, envolviendoArriba, cicloPausado, pararEnvolver(3));
    TRANSITION(btnPausa, envolviendoMedioBajando, cicloPausado, pararEnvolver(4)); 
    TRANSITION(btnPausa, cicloPausado, ANY_STATE, retomarEnvolver(estadoEnvolviendo)); 

    //TRANSITION(hacerHome, envolviendoAbajo, haciendoHome, fcnSetupHome()); // SALE DEL ERROR DE NO HOME
    //TRANSITION(ANY_EVENT,ANY_STATE,ANY_STATE,Serial.println("FAIL!!!")) //in any other case
END_TRANSITIONS

START_EXECUTIONS
    EXECUTION(reposo,estoyEnReposo());
    EXECUTION(haciendoHome,fcnHaciendoHome()); //se ejecuta cuando isState(haciendoHome) es true
    EXECUTION(subirForzado,fcnSubiendoForzado()); 
    EXECUTION(bajarForzado,fcnBajandoForzado()); 
    EXECUTION(ayudaPelicula,fcnAyudaPelicula()); 
    EXECUTION(envolviendoAbajo,fncEnvolverAbajo());
    EXECUTION(envolviendoMedio,fncEnvolverMedio());
    EXECUTION(envolviendoMedioBajando,fncEnvolverMedioBajando());
    EXECUTION(envolviendoArriba,fncEnvolverArriba());
    EXECUTION(envolviendoArribaBajar,fncEnvolverArribaBajar());
    EXECUTION(envolviendoAbajoBajando,fncEnvolverAbajoBajando());
    //EXECUTION(terminandoEnHome,fcnHaciendoHome());
END_EXECUTIONS

/*
START_TRIGGERS
Serial.println("Triggers");
COUNTER(start,5,next); //State start wait 5 iterations and launch event next
TIMER(step1,2000,next); //State step1 wait 2 sg and launch event next
//CONDITIONAL(start, digitalRead(buttonPin) == HIGH, restart); //State finish wait until push button an launch event restart
END_TRIGGERS
*/
