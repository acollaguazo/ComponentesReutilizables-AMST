#include "SensorInteligente.h"
#include <Isigfox.h>
#include <WISOL.h>

const int pinA0 = A0;
const int pinA1 = A1;
int contador = 0;

Isigfox *Isigfox = new WISOL();
SensorInteligente medicionBateria = SensorInteligente(pinA0, 1000, 10000, 9);
SensorInteligente sensores = SensorInteligente(pinA0, pinA1);

void setup() {
  Serial.begin(9600);
  sensores.inicializar();  
 
  Isigfox->initSigfox();
  Isigfox->testComms();
  Isigfox->getZone();
}

void loop() {
  sensores.calibrarBateria(1000.0, 10000.0, 9.0);
  //Isigfox->getZone();
  Serial.print("PRUEBA ");
  Serial.println(contador++);
  Serial.print("1 Voltaje de bateria = ");
  float bateria = sensores.leerPorcentajeBateria();
  Serial.println(sensores.leerVoltajeBateria());
  Serial.print("2 Porcentaje de bateria = ");
  Serial.print(bateria);
  Serial.println("%");
  Serial.print("3 Voltaje = ");
  float voltaje = sensores.leerVoltajeVelostat();
  Serial.println(voltaje);
  //sensores.enviarBateria(600);
  Serial.println("");
  enviar(voltaje, (int)bateria);
  delay(1200);
}

void enviar(float sensor, int bateria){
  Serial.println("AT$RC");
  delay(500);
  Serial.print("AT$SF=");
  if(sensor<0.078)Serial.print("000");
  else if(sensor<1.25)Serial.print("00");
  else if(sensor<20.019)Serial.print("0");
  Serial.print(sensor,HEX);
  if (bateria < 16)Serial.print("0");
  Serial.println(bateria,HEX);
}

void enviarBateria(int bateria){
  Serial.println("AT$RC");
  Serial.print("AT$SF=");
  //That's correct, but I should use int value
  if (bateria < 16)Serial.print("0");
  Serial.println(bateria,HEX);
}

void enviarSigfox(float voltajeMedido, int porcentajeBateria) {
  byte *float_velostat = (byte *)&voltajeMedido;
  byte *float_bateria = (byte *)&porcentajeBateria;
  const uint8_t payloadSize = 9;
  uint8_t buf_str[payloadSize];
  buf_str[0] = float_velostat[0];
  buf_str[1] = float_velostat[1];
  buf_str[2] = float_velostat[2];
  buf_str[3] = float_velostat[3];
  buf_str[4] = float_bateria[0];
  buf_str[5] = float_bateria[1];  
  buf_str[6] = float_bateria[2];
  buf_str[7] = float_bateria[3];
  
  uint8_t *sendData = buf_str;
  int len = 9;
  recvMsg *RecvMsg;
  RecvMsg = (recvMsg *)malloc(sizeof(recvMsg));
  Isigfox->sendPayload(sendData, len, 0, RecvMsg);
  for (int i = 0; i < RecvMsg->len; i++) {
    Serial.print(RecvMsg->inData[i]);
  }
  Serial.println("");
  free(RecvMsg);
}
