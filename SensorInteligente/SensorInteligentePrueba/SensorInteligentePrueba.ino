#include "SensorInteligentePrueba.h"

const int pinA0 = A0;
const int pinA1 = A1;

SensorInteligentePrueba sensorInteligentePrueba(pinA0, pinA1);

void setup() {
  Serial.begin(9600);
  sensorInteligentePrueba.inicializar();
}

void loop() {
  //sensorInteligente.calibrarBateria();
  sensorInteligentePrueba.valoresSensados();
  sensorInteligentePrueba.bateriaMenor(sensorInteligentePrueba.porcentajeBateria);
  sensorInteligentePrueba.enviarBateria(600000);
  delay(3000);
}
