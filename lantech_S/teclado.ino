#include <Servo.h>
Servo servo1;
 
int pin = 7;
int pulsoMinimo = 580;
int pulsoMaximo = 2500;
int angulo = 0;
int lectura;
 
void setup() {
  servo1.attach(pin,pulsoMinimo,pulsoMaximo);
  pinMode(A0,INPUT);
}
 
void loop() {
  lectura = analogRead(A7);
  angulo = map(lectura,0,1023,0,180); // Escalar la lectura a un valor de 0 a 180
  servo1.write(angulo);
  delay(10);
}