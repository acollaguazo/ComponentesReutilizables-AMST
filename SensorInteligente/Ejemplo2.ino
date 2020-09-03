#include "SensorInteligente.h"

const int pinA1 = A0;
int contador = 1;

SensorInteligente medicionBateria = SensorInteligente(pinA1, 1000.0, 10000.0, 9.0);

void setup() {
  Serial.begin(9600);
  medicionBateria.inicializar();  
  medicionBateria.calibrarBateria(3300.0, 33000.0, 9.0);
}

void loop() {
  Serial.println();
  Serial.print("PRUEBA ");
  Serial.println(contador++);
  //Serial.print("1 Voltaje de bateria = ");
  //Serial.println(medicionBateria.leerVoltajeBateria());
  float bateria = medicionBateria.leerPorcentajeBateria();
  /*Serial.print("2 Porcentaje de bateria = ");
  Serial.print(bateria);
  Serial.println("%");*/
  medicionBateria.enviarBateria(10000, bateria);
  //Serial.println(bateria);
  //enviarPorcentajeBateria((int)bateria);
  //delay(5000);
}
