/*
// Archivo de ejemplo: VelostatBateria.ino
// Utilizado para captura y envío de datos de una batería al Backend de Sigfox, mediante comandos AT.

#include "SensorInteligente.h"
#include <Isigfox.h>
#include <WISOL.h>

const int pinA0 = A0;
const int pinA1 = A1;
int contador = 0;

Isigfox *Isigfox = new WISOL();
SensorInteligente sensores = SensorInteligente(pinA0, pinA1);

void setup() {
  Serial.begin(9600);
  sensores.inicializar();  
  sensores.calibrarBateria(1000.0, 10000.0, 9.0);
  Isigfox->initSigfox();
  Isigfox->testComms();
  Isigfox->getZone();
}

void loop() {
  Serial.print("PRUEBA ");
  Serial.println(contador++);

  Serial.print("1 Porcentaje de bateria = ");
  float bateria = sensores.leerPorcentajeBateria();
  delay(5);
  Serial.print(bateria);
  Serial.println("%");
  Serial.print("2 Voltaje = ");
  float voltaje = sensores.leerVoltajeVelostat();
  Serial.println(voltaje);
  Serial.println("");
  enviarSigfox(voltaje, bateria);
  delay(1200);
}

void enviarSigfox(float voltajeMedido, float porcentajeBateria) {
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
  Send_Pload(buf_str, payloadSize);
}

void Send_Pload(uint8_t *sendData, const uint8_t len){
  recvMsg *RecvMsg;
  RecvMsg = (recvMsg *)malloc(sizeof(recvMsg));
  Isigfox->sendPayload(sendData, len, 0, RecvMsg);
  for (int i = 0; i < RecvMsg->len; i++) {
    Serial.print(RecvMsg->inData[i]);
  }
  Serial.println("");
  free(RecvMsg);
}
*/
