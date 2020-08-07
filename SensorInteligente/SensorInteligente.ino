
#include "SensorInteligente.h"

#include <Isigfox.h>
#include <WISOL.h>

const int pinA0 = A0;
const int pinA1 = A1;
int contador = 0;
Isigfox *Isigfox = new WISOL();
SensorInteligente sensores = SensorInteligente(pinA0, pinA1);


typedef union{
    uint16_t number;
    uint8_t bytes[2];
} UINT16_t;

void setup() {
  Serial.begin(9600);
  
  sensores.inicializar();
  
  Serial.println("CALIBRACION: ");
  sensores.calibrarBateria();
  Serial.println("Calibrado!");

  /*Isigfox->initSigfox();
  Isigfox->testComms();*/
}

void loop() {
  Serial.print("PRUEBA ");
  Serial.println(contador++);
  Serial.print("1 Voltaje de bateria = ");
  Serial.println(sensores.leerVoltajeBateria());
  Serial.print("2 Porcentaje de bateria = ");
  Serial.print(sensores.leerPorcentajeBateria());
  Serial.println("%");
  Serial.print("3 Voltaje = ");
  float voltaje = sensores.leerVoltajeVelostat();
  Serial.println(voltaje);
  //sensores.enviarBateria(600);
  Serial.println("");
  enviarSigfox(voltaje, sensores.leerPorcentajeBateria());
  delay(1200);
}

void enviarSigfox(float voltajeMedido, float porcentajeBateria) {
  byte *float_velostat = (byte *)&voltajeMedido;
  byte *float_bateria = (byte *)&porcentajeBateria;

  const uint8_t payloadSize = 4;
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
  int len = 4;
  recvMsg *RecvMsg;
  RecvMsg = (recvMsg *)malloc(sizeof(recvMsg));
  Isigfox->sendPayload(sendData, len, 0, RecvMsg);
  for (int i = 0; i < RecvMsg->len; i++) {
    Serial.print(RecvMsg->inData[i]);
  }
  Serial.println("");
  free(RecvMsg);
}
