#include "SensorInteligente.h"

const int pinA1 = A1;
int contador = 0;

SensorInteligente medicionBateria = SensorInteligente(pinA1, 1000.0, 10000.0, 9.0);

void setup() {
  Serial.begin(9600);
  medicionBateria.inicializar();
}

void loop() {
  
  medicionBateria.calibrarBateria(1000.0, 10000.0, 9.0);
  Serial.print("PRUEBA ");
  Serial.println(contador++);
  Serial.print("1 Voltaje de bateria = ");
  int bateria = medicionBateria.leerPorcentajeBateria();
  /*Serial.println(medicionBateria.leerVoltajeBateria());
  Serial.print("2 Porcentaje de bateria = ");
  Serial.print(bateria);
  Serial.println("%");*/
  medicionBateria.enviarBateria(600);
  Serial.println(bateria);
  //enviarPorcentajeBateria((int)bateria);
  
  /*delay(100);
  Serial.println("AT$RC");
  delay(1000);
  Serial.print("AT$SF=");
  //That's correct, but I should use int value
  //if (bateria < 16)Serial.print("0");
  Serial.println(bateria, HEX);
  delay(20000);*/

  
  Serial.println("");
  delay(1200);
}


void enviarPorcentajeBateria(int bateria){
  //Serial.println("AT$RC");
  Serial.print("AT$SF=");
  //That's correct, but I should use int value
  if (bateria < 16)Serial.print("0");
  Serial.println(bateria, HEX);
}
