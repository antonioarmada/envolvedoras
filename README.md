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


### DIAGRAMAS ELECTRÓNICOS

En la carpeta _diagramas_ se incluyen diagramas electrónicos y eléctricos parciales.


## + INFO

Comunicarse con **Antonio Armada**
+54 291 4730699 / antonioarmda@gmail.com



