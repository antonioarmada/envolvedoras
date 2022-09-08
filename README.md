# REPARACIÓN DE ENVOLVEDORAS LANTECH

### INTRODUCCIÓN

Nos llegaron 3 envolvedoras Lantech a las que les faltaba el 90% de los componentes eléctricos/electrónicos entre los que se encontraba la placa con el microcontrolador y por ende el software. Nuestro trabajo fue reponer las funciones originales y ponerlas en funcionamiento, para esto realizamos lo siguiente:

* Repusimos los drivers de los motores DC del delivery de film y de giro de tornamesa, los que son comandados por relés tipo SSR. 
* Reemplazamos la placa controladora (MASTER), esta contiene un Arduino Mega 2560 entre otra electrónica
* Reemplazamos panel de mando, este también es comandado otro Arduino Mega2560 (SLAVE) el que controla la pantalla y las entrada de los pulsadoras. Se comunica con la placa Master con un protocolo propio HALFDUPLEX mediante módulos RS485.
* Reemplazamos el amplificador de la celda de carga que sensa la tensión del film.
* Repusimos sensores de proximidad inductivos faltantes.

### SOBRE EL SOFTWARE



