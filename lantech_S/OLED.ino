
int anchoPantalla= 21;
int lineaDebug=0;
String mensajesDebug[8] = {"0","1","2","3","4","5","6","7"};
String mensajeAnterior ="";
int repeticionMensaje=1;

void printDebug(String mensajeNuevo, String valor){ //uso string para valor porque lo preformateo antes cualquiera sea el tipo  
  if (debugON){     //debugON ||      
   if (mensajeNuevo!= mensajeAnterior){ //no uso el guardado en el array porque voy a formatearalo
    //corro los mensajes una línea 
    for (int i=7; i>=0; i--) {
     mensajesDebug[i] = mensajesDebug[i-1];
     }
    mensajeAnterior= mensajeNuevo;
    repeticionMensaje=1;
    } else { // si es igual al anterior
      repeticionMensaje++;
    }
    mensajeNuevo=String(repeticionMensaje)+"x["+valor+"] "+mensajeNuevo;
    mensajeNuevo=mensajeNuevo.substring(0, min(mensajeNuevo.length(), anchoPantalla));
    mensajesDebug[0]= mensajeNuevo;

    display.clearDisplay();
    display.fillRect(0, 0, display.width(),9, WHITE);
    display.setCursor(1,1);
    display.setTextSize(1);
    display.setTextColor(BLACK,WHITE);
    display.println(mensajesDebug[0]);
    display.setTextColor(WHITE);
    
    for (int linea = 1; linea < 8; linea++) {
     display.println(mensajesDebug[linea]);
    }  
    display.display();    
  }
 }

void printAyudaPelicula(){
  if (!debugON){ 
    display.clearDisplay();
    display.fillRect(0, 20, display.width(),24, WHITE);
    display.setCursor(32,20);
    display.setTextSize(2);
    display.setTextColor(BLACK,WHITE);
    display.println("AYUDA DE FILM");
    display.display();
  }
}

void printReposo(){ // LISTO
  if (!debugON){  //!debugON && 
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.drawLine(63,0,63,25,WHITE);
    display.setTextSize(3);
    display.setCursor(1,1);
    display.print(String(vueltasUP));
    display.setCursor(68,1);
    display.print(String(vueltasDWN));
    display.setTextSize(1);
    display.setCursor(20,1);
    display.print("VUELTAS");
    display.setCursor(20,15);
    display.print("ARRIBA");
    display.setCursor(86,1);
    display.print("VUELTAS");
    display.setCursor(86,15);
    display.print("ABAJO");
    display.setTextSize(2);
    display.setCursor(32,30);
    display.print("SUBIR");
    if (subirYbajar){
      display.setCursor(30,50);
      display.print("BAJAR");
    }
    display.display();
  }
}

int calculaCentradoSize1 (int largoCadena){
  int largoPixelesTexto = largoCadena * 5; // en px
  int incioTextoCentrado = (128 - largoPixelesTexto)/2;
  return incioTextoCentrado;
  }

int calculaCentradoSize2 (int largoCadena){
  int largoPixelesTexto = largoCadena * 10; // en px
  int incioTextoCentrado = (128 - largoPixelesTexto)/2;
  return incioTextoCentrado;
  }

void printMesajeComun(String msgLinea1, String msgLinea2){                        
 // printDebug("entro","mensaje");
  if (!debugON){ //!debugON && 
    int incioTextoCentradoLinea1 = calculaCentradoSize2(msgLinea1.length());
    int incioTextoCentradoLinea2 = calculaCentradoSize2(msgLinea2.length());
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.drawLine(0,5,128,5,WHITE);
    display.setTextSize(2);
    display.setCursor(incioTextoCentradoLinea1,10);
    display.println(msgLinea1);
    display.setCursor(incioTextoCentradoLinea2,30);
    display.println(msgLinea2);
    display.drawLine(0,50,128,50,WHITE);
    display.display();
  }
}


void printReestablecer1(){
  if (!debugON){ 
    display.clearDisplay();
    //display.drawLine(0,2,128,2,WHITE);
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(10,6);
    display.println("REESTABL.");
    display.setCursor(15,23);
    display.println("VALORES");
    display.setTextSize(1);
    display.setCursor(10,45);
    display.println("PRESIONAR OTRA VEZ");
    display.setCursor(25,55);
    display.println("PARA CONFIRMAR");
    display.drawLine(0,40,128,40,WHITE);
    display.display();
  }
}

void printEnvolviendo(String donde){
  if (!debugON){ 
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.drawCircle(14, 25, 13, WHITE);
    display.fillTriangle(10, 15,
                     23, 25,
                     10, 35,WHITE);
    display.drawLine(0,5,128,5,WHITE);
    display.setTextSize(2);
    display.setCursor(33,10);
    display.println("ENVOLV.");
    display.setTextSize(1);
    display.setCursor(33,30);
    if (subirYbajar){
      display.println("SUBIR Y BAJAR");
      } else {
        display.println("SUBIR");
      }
    display.setCursor(33,40);
    display.println(donde);
    display.drawLine(0,50,128,50,WHITE);
    display.display();
  }
}


void printError(String msgError){
  if (!debugON){
    String msgLinea1 = "ERROR";
    int incioTextoCentradoLinea1 = calculaCentradoSize2(msgLinea1.length());
    int incioTextoCentradoLinea2 = calculaCentradoSize1(msgError.length());
    Serial.println(incioTextoCentradoLinea2);
    display.clearDisplay();
    display.fillRect(0,0,128,64,WHITE);
    display.setTextSize(2);
    display.setCursor(incioTextoCentradoLinea1,20);
    display.setTextColor(BLACK,WHITE);
    display.println(msgLinea1);
    display.setTextSize(1);
    display.setCursor(incioTextoCentradoLinea2,40);
    display.println(msgError);
    display.display();
  }
}

