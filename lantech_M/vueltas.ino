void vueltasInicioUP() {
    int vueltas;
    unsigned char msg_vueltas; // unsigned es importante para que vaya de 0-255
    // Vueltas Arriba
    vueltas = EEPROM.read(EE_DIRECCION_UP);
    EEPROM.update(EE_DIRECCION_UP, vueltas );
    printDebug("VUEL_UP",String(vueltas));
    msg_vueltas= (char) (148 + vueltas); // codigos ascii
    Tx_Msg(msg_vueltas);
}

void vueltasInicioDWN() {
    int vueltas;
    unsigned char msg_vueltas; // unsigned es importante para que vaya de 0-255
    //Vueltas Abajo
    vueltas = EEPROM.read(EE_DIRECCION_DWN);
    printDebug("VUEL_DWN",String(vueltas));
    msg_vueltas= (char) (48 + vueltas); // codigos ascii de numeros 1-9
    Tx_Msg(msg_vueltas);
} 

void vueltasDWN() {
    int vueltas;
    //int ascii_vueltas;
    unsigned char msg_vueltas; // unsigned es importante para que vaya de 0-255
    //EEPROM.get(EE_DIRECCION_DWN,vueltas);
    vueltas = EEPROM.read(EE_DIRECCION_DWN);
    printDebug("EE_DWN",String(vueltas));
    if (vueltas < 9) {
        vueltas++;
    } else {
        vueltas = 1;
    }
    // cuando esto ande hacer que espere 10 seg para grabar desde
    // la ultima con un static
    EEPROM.update(EE_DIRECCION_DWN, vueltas );
    printDebug("VUEL_DWN",String(vueltas));
    msg_vueltas= (char) (48 + vueltas); // codigos ascii de numeros 1-9
    Tx_Msg(msg_vueltas);
}


void vueltasUP() {
    int vueltas;
    unsigned char msg_vueltas;
    //EEPROM.get(EE_DIRECCION_UP, vueltas);
    vueltas = EEPROM.read(EE_DIRECCION_UP);
    printDebug("EE_UP",String(vueltas));
    if (vueltas < 9) {
        vueltas++;
    } else {
        vueltas = 1;
    }
    // cuando esto ande hacer que espere 10 seg para grabar desde
    // la ultima con un static
    EEPROM.update(EE_DIRECCION_UP, vueltas );
    printDebug("VUEL_UP",String(vueltas));
    msg_vueltas= (char) (148 + vueltas); // codigos ascii
    Tx_Msg(msg_vueltas);
}


