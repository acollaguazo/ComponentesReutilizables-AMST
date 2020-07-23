#include "SensorInteligente.h"

const int pinA0 = A0;
const int pinA1 = A1;

SensorInteligente sensorInteligente(pinA0, pinA1);

void setup() {
  Serial.begin(9600);
  sensorInteligente.inicializar();
}

void loop() {
  sensorInteligente.calibrarBateria();
  sensorInteligente.valoresSensados();
  sensorInteligente.enviarBateria(600000);
  delay(3000);
}
