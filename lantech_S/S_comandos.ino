
void ejecutarComando(char msg) {
    unsigned char u_msg; //pasa
    u_msg = reinterpret_cast<unsigned char&>(msg); //pasa
    int int_msg;
        switch (msg) {
            case MSG_DEGUG_ON: 
                printDebug(F("MSG DEBUG"),F("ON"));
                debugON= true; 
                break;
            case MSG_DEGUG_OFF: 
                printDebug(F("MSG DEBUG"),F("OFF"));
                if (FORZAR_DEBUG == false) debugON= false; 
                break; 
            case MSG_ESTADO_REPOSO: 
                printDebug(F("ESTADO"),F("Reposo"));
                printReposo();
                break;
            case MSG_ESTADO_HOME: 
                printDebug(F("ESTADO"),F("H.Home"));
                printMesajeComun(F("IR A POS."), F("INICIAL"));
                break;
            case MSG_ESTADO_ENVOL_ABAJO: 
                printDebug("ESTADO","En.DWN");
                //printEnvolviendo("> ABAJO");
                break;
            case MSG_ESTADO_ENVOL_MEDIO: 
                printDebug("ESTADO","EN.MED");
                //printEnvolviendo("> MEDIO");
                break;
            case MSG_ESTADO_ENVOL_ARRIBA: 
                printDebug("ESTADO","En.UP");
                //printEnvolviendo("> ARRIBA");
                break;
            case MSG_ESTADO_PAUSADO:
                printDebug("ESTADO","Pausado");
                printMesajeComun("CICLO", "PAUSADO");
                break;
            case MSG_ESTADO_SUBIENDO_FORAZADO: 
                printDebug("ESTADO","FDS UP");
                printMesajeComun("SUBIENDO","FDS");
                break;
            case MSG_ESTADO_BAJANDO_FORAZADO: 
                printDebug("ESTADO","FDS DWN");
                printMesajeComun("BAJANDO","FDS");
                break;
            case MSG_ESTADO_GIRAR_LENTO: 
                printDebug("ESTADO","Girar");
                printMesajeComun("AVANCE","LENTO");
                break;
            case MSG_ESTADO_AYUDA_PELICULA: 
                printDebug("ESTADO","A.Peli");
                printMesajeComun("AYUDA","FILM");
                break;
            case MSG_SETED_BAJAR_ENVOLVIENDO_TRUE: 
                printDebug("BajarEnvo","ON");
                subirYbajar = true;
                printReposo();
                break;
            case MSG_SETED_BAJAR_ENVOLVIENDO_FALSE: 
                printDebug("BajarEnvo","OFF");
                subirYbajar = false;
                printReposo();
                break;
            case MSG_ERROR_FILM_CORTADO: 
                printDebug("Error Film","CORTADO");
                printError("FILM CORTADO");
                break;
            case MSG_ERROR_NO_HOME: 
                printDebug("Error HOME","NO");
                printError("IR A POS. INICIAL");
                break;
            default:                
                int u_int_msg= int (u_msg); //funciona           
                int_msg= int (msg); // funciona
                if (u_int_msg>48 && u_int_msg<58) {
                    vueltasDWN= u_int_msg - 48;
                    printReposo();
                    printDebug("vueltasDWN",String(vueltasDWN));
                } else if (u_int_msg>148 && u_int_msg<158){
                    vueltasUP= u_int_msg - 148;
                    printReposo();
                    printDebug("VueltasUP",String(vueltasUP));
                } else {
                   printDebug("RTA RARA",String(msg));
                }
        }
    }