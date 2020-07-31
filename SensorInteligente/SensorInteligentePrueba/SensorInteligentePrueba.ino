#include "SensorInteligentePrueba.h"

SensorInteligentePrueba SensorInteligentePrueba;

void setup() {
  Serial.begin(9600);
  SensorInteligentePrueba.inicializar();
  /*Serial.println("CALIBRACION: ");
  SensorInteligentePrueba.calibrarBateria();*/
}

void loop() {
  Serial.println("Prueba");
  SensorInteligentePrueba.valoresSensados();
  Serial.print("Voltaje de bateria ");
  Serial.println(SensorInteligentePrueba.bateria);
  Serial.print("Bateria ");
  Serial.print(SensorInteligentePrueba.porcentajeBateria);
  Serial.println("%");
  /*Serial.print("voltaje ");
  Serial.println(SensorInteligentePrueba.voltajeMedido);*/
  //SensorInteligentePrueba.bateriaMenor(SensorInteligentePrueba.porcentajeBateria);
  SensorInteligentePrueba.enviarBateria(600);
  delay(1000);
}
