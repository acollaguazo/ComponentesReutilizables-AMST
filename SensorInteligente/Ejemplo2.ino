#include "SensorInteligente.h"

const int pinA0 = A0;
int contador = 0;

SensorInteligente medicionBateria = SensorInteligente(pinA0, 1000, 10000, 9);

void setup() {
  Serial.begin(9600);
  medicionBateria.inicializar();
}

void loop() {
  Serial.print("PRUEBA ");
  Serial.println(contador++);
  Serial.print("1 Voltaje de bateria = ");
  float bateria = medicionBateria.leerPorcentajeBateria();
  Serial.println(medicionBateria.leerVoltajeBateria());
  Serial.print("2 Porcentaje de bateria = ");
  Serial.print(bateria);
  Serial.println("%");
  medicionBateria.enviarBateria(600);
  Serial.println("");
  delay(1200);
}
