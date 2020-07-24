#include "SensorInteligente.h"

const int pinA0 = A0;
const int pinA1 = A1;

SensorInteligente sensorInteligente(pinA0, pinA1);

void setup() {
  Serial.begin(9600);
  sensorInteligente.inicializar();
}

void loop() {
  //sensorInteligente.calibrarBateria();
  sensorInteligente.valoresSensados();
  sensorInteligente.enviarBateria(600000);
  delay(3000);
}

//Devuelve valor del sensor ya convertido, en el rango [0, 5].
/*int aleatoriosDivisorVoltajeVelostat(){
  int rBajo = 10000;
  int rArriba = random(0, 500);
  return (rBajo/(rBajo+10000))*5;
}

//Devuelve valor de la batería ya convertido, en el rango [0, 5].
int aleatoriosDivisorVoltajeBateria(){
  int vIn = random(1, 9);
  int rBajo = 1000;
  int rArriba = 1000;
  return (rBajo/(rBajo+rArriba))*vIn;
}*/
