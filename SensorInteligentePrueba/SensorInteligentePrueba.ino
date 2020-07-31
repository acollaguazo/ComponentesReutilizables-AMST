#include "SensorInteligentePrueba.h"

SensorInteligentePrueba SensorInteligentePrueba;

int contador = 0;
void setup() {
  Serial.begin(9600);
  SensorInteligentePrueba.inicializar();
  Serial.println("CALIBRACION: ");
  SensorInteligentePrueba.calibrarBateria();
  Serial.println("Calibrado!");
}

void loop() {
  Serial.print("PRUEBA ");
  Serial.println(contador++);
  SensorInteligentePrueba.valoresSensados();
  Serial.print("1 Voltaje de bateria = ");
  Serial.println(SensorInteligentePrueba.bateria);
  Serial.print("2 Porcentaje de bateria = ");
  Serial.print(SensorInteligentePrueba.porcentajeBateria);
  Serial.println("%");
  Serial.print("3 Voltaje = ");
  Serial.println(SensorInteligentePrueba.voltajeMedido);
  SensorInteligentePrueba.enviarBateria(600);
  Serial.println("");
  delay(1200);
}
