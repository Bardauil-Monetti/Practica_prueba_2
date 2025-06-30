//Punto 1; Consigna: Cambiar estado de LED mediante un pulsador como interrupcion.
#include <Arduino.h>
int bot = 1; //boton (interrupcion)
int led = 2; //led
volatile bool flag = false;
bool estado = false;
void IRAM_ATTR ISR() {
  flag = !flag; 
}
void setup(){
  pinMode(led, OUTPUT);
  pinMode(bot, INPUT_PULLUP); //Estado logico normal del boton --> 1
  attachInterrupt(digitalPinToInterrupt(bot), ISR, FALLING);
}
void loop(){
  if(flag){
    estado = !estado;
    flag = !flag;
  }
  digitalWrite(led, estado);
}
