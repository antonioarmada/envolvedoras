# REPARACIÓN DE ENVOLVEDORAS LANTECH

### INTRODUCCIÓN

Nos llegaron 3 envolvedoras Lantech a las que les faltaba el 90% de los componentes eléctricos/electrónicos entre los que se encontraba la placa con el microcontrolador y por ende el software. Nuestro trabajo fue reponer las funciones originales y ponerlas en funcionamiento, para esto realizamos lo siguiente:

* Instalamos drivers para los motores DC del delivery de film y de giro de tornamesa, los que son comandados por relés tipo SSR. 
* Repusimos la placa controladora instalando una de fabricación propia, esta contiene un Arduino Mega 2560 (MASTER) entre otros componentes electrónicos.  
* Fabricamos un nuevo panel de mando. Este también es comandado otro Arduino Mega2560 (SLAVE) el que controla la pantalla y las entrada de los pulsadores. Se comunica con la placa Master con un protocolo propio HALFDUPLEX mediante módulos RS485.
* Reemplazamos el amplificador de la celda de carga que sensa la tensión del film.
* Repusimos sensores de proximidad inductivos faltantes.
* Repusimos cables dañados.

En el transcurso del trabajo, luego que los PCBs de las placas de control (Master) fuesen fabricados e instalados, empezamos a tener problemas con las emisiones electromagnétias generadas por los drivers de los motores que fabricó MOCBOS (únicos que se conseguían en el país para estos motores). Esto nos llevó a tener realizar algunas modificaciones en el PCB de la placa de control, a sumar un BUS de daos con módulos R485 para la comunicación con el Panel de Control y a estipular un pequeño tiempo de _hold_ en los pulsadores de mando.


### SOBRE EL SOFTWARE

Desarrollado en C++ para las placas Arduino instaladas, en el presente respositorio la carpeta _lantech_M_ contiene el software para la placa Master (en gabinete principal) mientras que la carpeta _lantech_S_ contiene el software de panel de mando. Este último es el mismo para las tres máquinas, sin embargo en el software correspondiente a la placa Master hay una variación en el parámetro de configuración LIMITE_ERROR_FUERZA_FILM del archivo _config.h_ tal como se indica en los comentarios del archivo.


### DIAGRAMAS ELÉCTRONICOS / ELÉCTRICOS

Pueden encontrarse los siguientes diagramas en [__este link__](https://drive.google.com/drive/folders/1LIKxtBfPF05VEppYgutul-coLsBpfSoM?usp=sharing)
* __master_semantico_actualizado.pdf__: Diagrama semántico de la placa Master.
* __master_PCB.pdf__: serigrafía y pistas del PCB de la placa Master para referencia y fácil identificación de conexiones.
* __fabricar_PCB_placa_Master.zip__: archivos necesarios para rehacer el PCB de la placa Master.
* __ELECTRONICO_ORIGINAL.pdf__: diagrama eléctrico/electrónico de las conexiones originales que tenían estas máquinas de fábrica, se icluyen como referencia ya que se intentó respetar lo más posible esta configuración. Puede servir de guía.
* __BNN-BLN Manual.pdf__ es el manual de los controladores nuevos de los motores de la Tornamesa y entrega de film. (El controlador de subida/bajada del carro de film es original)

### RESOLUCIÓN DE PROBLEMAS

Las placas cuentan con distintos indicadores que pueden ayudar a detectar problemas.
* La placa Master tiene un _dipswitch_ que en posición _ON_ (antes del encender la máquina) inicia la máquina modo DEBUG, por lo que en la pantalla del panel de control se pueden ver mensejes del software corriendo en esa placa. Mientras que para ver los mensajes de la placa Master, se debe conectar un diplay _OLED 128x64 1.3" I2C_ (no incluido) en la ficha correspondiente señalada con serigrafía en el PCB.
* La placa Master tiene un LED con serigrafía "OK" que debe estar parpadeando (_heartbeat_) siempre que el software esté corriendo. El motivo mas común para que se detenga es la parada de emergencia que realiza al estar "abierto" el final de carrera que sensa el estado de la banda que mueve el carro de film.
* En el Arduino del panel de control se usa el _BUILD-IN LED_ con el mismo fin. 
* La placa Master tiene varios LEDs que indican el estado de los finales de carrera que se encuentran en la máquina, como asi tambien otro que indica la señal para la conmutación de la velocidad de giro de la tornamesa.
* Las fuentes stepdown y el módulo RS-485 tienen LEDs rojos que indican que están recibiendo tensión. 


## + INFO

Comunicarse con **Antonio Armada**
+54 291 4730699 / antonioarmada@gmail.com



