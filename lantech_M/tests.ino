void testFuerzaCelda() {  // no borrar prueba solo celda de carga
    static long medAnterior;
    printDebug ("Fuerza",String(celdaDeCarga.get_units(20)));
    if ((millis() - medAnterior)>500) {
        printDebug ("Fuerza",String(celdaDeCarga.get_units(20)));
        //Serial.print(celdaDeCarga.get_units(20),3);
        //printDebug ("Fuerza",String(medAnterior));
        medAnterior = millis();
    }
}

void testPote() { // no borrar prueba solo pote de fuerza
    static long medAnterior;
    if ((millis() - medAnterior)>500) {
        int lecturaPote;
        lecturaPote= analogRead(PIN_ENTRADA_POTE_FUERZA);
        printDebug ("Pote",String(lecturaPote));
        medAnterior = millis();
    }
}

void testStretch() { // no borrar prueba driver stretch con pote
    uint32_t voltajeDAC;
    static long medAnterior;
    int lecturaPote;
    if ((millis() - medAnterior)>100) {
        lecturaPote= analogRead(PIN_ENTRADA_POTE_FUERZA);
        voltajeDAC= map(lecturaPote, 0, 1024, 0, 4000); //10bit entrada y 12bit DAC, ambos 0-5v
        //voltajeDAC=4000;
        dac.setVoltage(voltajeDAC, false);
        digitalWrite(PIN_SSR_STRETCH, HIGH);
        printDebug ("DAC seted",String(voltajeDAC));
        medAnterior = millis();
    }
}

void testAjuste() {  // SI BORRAR CUANDO ESTE EL DEFINITIVO
    static uint32_t voltajeDAC;
    static long medAnterior;
    const int Vmax= 4000;//int(3*4096/5);
    const int Fmax= 20; //kg
    float b= Vmax/Fmax;
    int lecturaPote = analogRead(PIN_ENTRADA_POTE_FUERZA);
    float Fpote= map(lecturaPote, 0, 1023, 0, Fmax);
    float Fcelda= celdaDeCarga.get_units(20);
    float dF= Fcelda - Fpote; 
    //dF = constrain (dF, 0 , 100); // o Fmax? tiene que ser negativo
    voltajeDAC = voltajeDAC + int(dF*b);
    voltajeDAC = constrain (voltajeDAC, 0 , Vmax);
    if (voltajeDAC > 0) {
        digitalWrite(PIN_SSR_STRETCH, HIGH);
    } else {
        digitalWrite(PIN_SSR_STRETCH, LOW);
    }
    if ((millis() - medAnterior)>500) {
        dac.setVoltage(voltajeDAC, false);
        printDebug ("dF",String(dF));
        medAnterior = millis();
    }
}  
 

/* void testEnvolver1() { // SI BORRAR CUANDO ESTE EL DEFINITIVO
    static uint32_t voltajeDAC;
    static long medAnterior;
    const int Vmax= 4000;//int(3*4096/5);
    const int Fmax= 20; //kg
    int lecturaPote = analogRead(PIN_ENTRADA_POTE_FUERZA);
    float Fpote= map(lecturaPote, 0, 1023, 0, Fmax);
    float Fcelda= celdaDeCarga.get_units(20);
    //float dF= Fcelda - Fpote; 
    if (Fcelda>=Fpote) {
        voltajeDAC= Vmax;
    }
    if (Fcelda<Fpote && Fcelda>(3/4*Fpote)) {
        voltajeDAC= 3/4*Vmax;
    }
    if (Fcelda<Fpote && Fcelda>(1/2*Fpote)) {
        voltajeDAC= 1/2*Vmax;
    }
    if (Fcelda<Fpote && Fcelda>(1/4*Fpote)) {
        voltajeDAC= 1/3*Vmax;
    }
    voltajeDAC = constrain (voltajeDAC, 0 , Vmax);
    miTornamesa.girarNormal();
    if (voltajeDAC > 10) {
        digitalWrite(PIN_SSR_STRETCH, HIGH);
    } else {
        digitalWrite(PIN_SSR_STRETCH, LOW);
    }
    if ((millis() - medAnterior)>500) {
        dac.setVoltage(voltajeDAC, false);
        printDebug ("dF",String(dF));
        medAnterior = millis();
    }
}   */


void testFinEnvolver() { // BORRAR
    miTornamesa.detener();
    digitalWrite(PIN_SSR_STRETCH, LOW);
}

