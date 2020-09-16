
// @file    Bateria.ino
// @brief   Archivo de ejemplo que puede ser utilizado para la captura/envío del
//          porcentaje de una batería al Backend de Sigfox, mediante comandos AT.
 
#include "SensorInteligente.h"

const int pinA1 = A1;
int contador = 1;

SensorInteligente medicionBateria = SensorInteligente(pinA1);

void setup() {
  Serial.begin(9600);
  medicionBateria.inicializar();  
  medicionBateria.calibrarBateria(1220.0, 1000.0, 9);
}

void loop() {
  Serial.println();
  Serial.print("PRUEBA ");
  Serial.println(contador++);
  Serial.print("1 Voltaje de bateria = ");
  Serial.println(medicionBateria.leerVoltajeBateria(), 5);
  int bateria = medicionBateria.leerPorcentajeBateria();
  Serial.print("2 Porcentaje de bateria = ");
  Serial.print(bateria);
  Serial.println("%");
  medicionBateria.enviarBateria(10000, bateria);
  delay(1000);
}
