

void printDebug(String mensajeNuevo, String valor){ //uso string para valor porque lo preformateo antes cualquiera sea el tipo
  
  static int anchoPantalla= 21;
  static int lineaDebug=0;
  static String mensajesDebug[8] = {"0","1","2","3","4","5","6","7"};
  static String mensajeAnterior ="";
  static int repeticionMensaje=1;

  if (debugON || FORZAR_DEBUG){         
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
