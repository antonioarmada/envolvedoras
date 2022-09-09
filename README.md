# REPARACIÓN DE ENVOLVEDORAS LANTECH

### INTRODUCCIÓN

Nos llegaron 3 envolvedoras Lantech a las que les faltaba el 90% de los componentes eléctricos/electrónicos entre los que se encontraba la placa con el microcontrolador y por ende el software. Nuestro trabajo fue reponer las funciones originales y ponerlas en funcionamiento, para esto realizamos lo siguiente:

* Instalamos drivers para los motores DC del delivery de film y de giro de tornamesa, los que son comandados por relés tipo SSR. 
* Repusimos la placa controladora instalando una de fabricación propia, esta contiene un Arduino Mega 2560 (MASTER) entre otros componentes electrónicos.  
* Fabricamos un nuevo panel de mando. Este también es comandado otro Arduino Mega2560 (SLAVE) el que controla la pantalla y las entrada de los pulsadores. Se comunica con la placa Master con un protocolo propio HALFDUPLEX mediante módulos RS485.
* Reemplazamos el amplificador de la celda de carga que sensa la tensión del film.
* Repusimos sensores de proximidad inductivos faltantes.
* Repusimos cables dañados.


### SOBRE EL SOFTWARE

Desarrollado en C++ para las placas Arduino instaladas, en el presente respositorio la carpeta _lantech_M_ contiene el software para la placa Master (en gabinete principal) mientras que la carpeta _lantech_S_ contiene el software de panel de mando. Este último es el mismo para las tres máquinas, sin embargo en el software correspondiente a la placa Master hay una variación en el parámetro de configuración LIMITE_ERROR_FUERZA_FILM del archivo _config.h_ tal como se indica en los comentarios del archivo.


### DIAGRAMAS ELÉCTRONICOS / ELÉCTRICOS

Pueden encontrarse los siguientes diagramas en [este link](https://drive.google.com/drive/folders/1LIKxtBfPF05VEppYgutul-coLsBpfSoM?usp=sharing)
* __master_semantico_actualizado.pdf__: Diagrama semántico de la placa Master.
* __master_PCB.pdf__: serigrafía y pistas del PCB de la placa Master para referencia y fácil identificación de conexiones.
* __fabricar_PCB_placa_Master.zip__: archivos necesarios para rehacer el PCB de la placa Master.
* __ELECTRONICO_ORIGINAL.pdf__: diagrama eléctrico/electrónico de las conexiones originales que tenían estas máquinas de fábrica, se icluyen como referencia ya que se intentó respetar lo más posible esta configuración. Puede servir de guía.


## + INFO

Comunicarse con **Antonio Armada**
+54 291 4730699 / antonioarmda@gmail.com



