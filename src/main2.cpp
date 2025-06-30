/*Punto 2; Consigna: Realizar un programa que mediante un boton se cambie de creciente a decreciente dos 7 segmentos (uno para unidad y otro para decena).
 Ambos contadores  iran de 0 -> 99 y de 99 -> 0 (cuando llega al max/min se resetea).*/
#include <Arduino.h>
int bot = 1; //boton (interrupcion)
int seg7_1[7] = {2, 3, 4, 5, 7, 8, 9}; //7 segmentos unidad
int seg7_2[7] = {10, 11, 12, 13, 14, 15, 16}; //7 segmentos decena
int nums[10][7] = {
  //{a, b, c, d, e, f, g},
    {0, 0, 0, 0, 0, 0, 0}, //0
    {0, 1, 1, 0, 0, 0, 0}, //1
    {1, 1, 0, 1, 1, 0, 1}, //2
    {1, 1, 1, 1, 0, 0, 1}, //3
    {0, 1, 1, 0, 0, 1, 1}, //4
    {1, 0, 1, 1, 0, 1, 1}, //5
    {1, 0, 1, 1, 1, 1, 1}, //6
    {1, 1, 1, 0, 0, 0, 0}, //7
    {1, 1, 1, 1, 1, 1, 1}, //8
    {1, 1, 1, 0, 0, 1, 1}, //9
};
int numAct = 0;
volatile bool flag = false;
bool sentido = true;
void IRAM_ATTR ISR(){
    flag = !flag;
}
int t_actual, t_previo;
int t_delay = 1000;
void setup(){
    pinMode(bot, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(bot), ISR, FALLING);
    for(int i = 0; i < 7; i++){
        pinMode(seg7_1[i], OUTPUT);
        pinMode(seg7_2[i], OUTPUT);
    }
}
void loop(){
    if(flag){
        sentido = !sentido;
        flag = !flag;
    }
    t_actual = millis();
    if(t_actual - t_previo >= t_delay){
        t_previo = t_actual;
        int decenas = numAct/10;
        int unidades = numAct%10;
        for(int i = 0; i < 7; i++){
            digitalWrite(seg7_1[i], nums[unidades][i]);
            digitalWrite(seg7_2[i], nums[decenas][i]);
        }
        if(sentido){
            numAct++;
            if(numAct > 99) {
                numAct = 0;
            }
        } else {
            numAct--;
            if(numAct < 0) {
                numAct = 99;
            }
        }
    }
}    


