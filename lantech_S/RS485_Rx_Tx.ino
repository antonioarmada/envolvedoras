void check_RS485(){
  check_Rx();
  checkTxTimeOut();

  if (comandoAejecutar == MSG_RECIBIDO){
    esperandoRespuesta= false;
    cantidadDeIntentosTx= 0;
    //Serial.println("-- transaccion OK --");
    comandoAejecutar= 0x00;
  } 
  
  if (comandoAejecutar != 0x00 && comandoAejecutar != MSG_RECIBIDO){ //distinto de NULL
    Tx_Msg(MSG_RECIBIDO);
    char comandoAejecutar_=comandoAejecutar; 
    comandoAejecutar= 0x00; // lo habilito antes de mandarlo por si tarda mucho ejecutarComando
    ejecutarComando(comandoAejecutar_);
  }
 }

void check_Rx() {
  static int idx;
  static char buffer_rx[tamanoBuffer_rx];
  // tener en cuenta que se van a recibir los caracteres de la trama más x03 (ETX) al final
  // es decir si la trama tiene 3 caracteres se reciben 4 contando el ETX
  if (RS485.available() > 0) {
    delay(100); //allows all serial sent to be received together
    while(RS485.available()) { 
      buffer_rx[idx] = RS485.read();
      //printDebug("->RxLl:  " , String(idx) + "-"+  String(buffer_rx[idx]));
      idx++;
      //esto que viene parece redundante pero uno de los arduino me metia el ETX en el lugar del head cuando respondia OK
      if (idx==1 && buffer_rx[0]!=MSG_HEAD){
        idx=0;
      }
    }
    // Termine de recibir la trama
    Serial.println(String (buffer_rx));
    if (checkData(buffer_rx)){
       printDebug(">RX", String(buffer_rx[1]));
       comandoAejecutar = buffer_rx[1];
    } else {
      //Serial.println("MSG ERROR"); 
    }
    idx=0;
    //memset(buffer_rx, 0, sizeof(buffer_rx));
  }
 }

bool checkData(char data_rx[tamanoBuffer_rx]){
  // aca puede ser mas complejo con un checksum o algo asi)
  if (data_rx[0]== MSG_HEAD && data_rx[2]== MSG_TAIL){
    return true; 
  } else {
    return false;
  }
}
 
// aca deberia chequear colisiones, pero para eso tengo que hacer
 // un buffer de mensajes a enviar, mucho laburo por lo poco probable
 // Mejor que no entre el mensaje que
 // se estaba recibiendo (cambia estado RxaTx) lo va a volver enviar checkTimeOut
void Tx_Msg(char _msg) {
    char msg = _msg;
    char trama[3];
    trama[0] = MSG_HEAD;
    trama[1] = msg;
    trama[2] = MSG_TAIL;
    //byte ckecksum = stringChecksum(trama);
    //Serial.println("CKS: " + String(ckecksum));
    digitalWrite(PIN_cambia_RXaTX, HIGH); // modo tx
    RS485.write(trama, 3);
    // esperar que todos los bytes se envien
    RS485.flush();
    printDebug("<-TX: " , String(msg));            
    digitalWrite(PIN_cambia_RXaTX, LOW); // modo rx
    if (msg != MSG_RECIBIDO) { // si no estoy mandando una confirmacion de recibido
      esperandoRespuesta= true;
      ultimoIntentoTx= millis();
      ultimoMensajeEnviado = msg;
      cantidadDeIntentosTx++;
    }
}

/* byte stringChecksum(char *s)
{
    byte c = 0;
    while(*s != '\0')
        c ^= *s++; 
    return c;
} */


void checkTxTimeOut() {
    if (esperandoRespuesta && (millis()-ultimoIntentoTx) > 500) { //cuantoTiempoEsperoRespuesta
        if (cantidadDeIntentosTx < CANTIDAD_INTENTO_TIMEOUT) {
          printDebug("ERR","renviando..");
          Tx_Msg(ultimoMensajeEnviado);
        } else {
          printDebug("ERR","TIME OUT");
          esperandoRespuesta = false;
          cantidadDeIntentosTx= 0;
        }
      }
}
