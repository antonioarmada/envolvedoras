void hayError(int _nroError) { // no usar el nombre "error" porque es interno
    static int nroError = _nroError;
    switch (nroError) {
        case 0: // Time Out
            printDebug("ERROR","T.OUT");
            esperandoRespuesta = MSG_RECIBIDO; // ya no espero mas respuesta 
            printError("TIME OUT");
            break;
        case 1: // Esperando una respuesta entro otra
            printDebug("ERROR","OTRA.RTA");
            printError("RTA. EXTRAÑA");
            break;
    }
}