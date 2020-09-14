// @file    VelostatBateria.ino
// @brief   Archivo de ejemplo que puede ser utilizado para captura/envío del
//          voltaje de un sensor de peso y del porcentaje de una batería 
//          al Backend de Sigfox, haciendo uso de comandos AT.

#include "SensorInteligente.h"
#include <WISOL.h>
#include <Isigfox.h>

const int pinA0 = A0;
const int pinA1 = A1;
int contador = 1;
char cadena[11];
Isigfox *Isigfox = new WISOL();
SensorInteligente sensores = SensorInteligente(pinA0, pinA1);

void setup() {
  Serial.begin(9600);
  sensores.inicializar();
  sensores.calibrarBateria(1220.0, 1000.0, 9);
  Isigfox->initSigfox();
  Isigfox->testComms();
}

void loop() {
  Serial.println();
  Serial.print("PRUEBA ");
  Serial.println(contador++);
  Serial.print(" 1 Porcentaje de bateria = ");
  int bateria = sensores.leerPorcentajeBateria();
  Serial.print(bateria);
  Serial.println("%");
  Serial.print(" 2 Voltaje del velostat = ");
  float voltaje = sensores.leerVoltajeBateria();
  Serial.println(voltaje);
  //sensores.leerVoltajeVelostat();
  uint8_t byteBateria = (uint8_t)bateria;
  // Serial.println("");
  byte *float_velostat = (byte *)&voltaje;
  //byte *float_bateria = (byte *)&bateria;
  const uint8_t payloadSize = 5;
  uint8_t bufferDatos[payloadSize];
  bufferDatos[0] = float_velostat[0];
  bufferDatos[1] = float_velostat[1];
  bufferDatos[2] = float_velostat[2];
  bufferDatos[3] = float_velostat[3];
  bufferDatos[4] = byteBateria;
  /*
  bufferDatos[5] = float_bateria[1];  
  bufferDatos[6] = float_bateria[2];
  bufferDatos[7] = float_bateria[3];
  Serial.print(" Bateria en hexadecimal: ");
  Serial.println(bufferDatos[4],HEX);
  */
  
  uint8_t *sendData = bufferDatos;
  
  Send_Pload(sendData, payloadSize);
  
  delay(3000);
}

void enviarSigfox(float voltajeMedido, float porcentajeBateria) {
  
//  Send_Pload(bufferDatos, payloadSize);
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

void imprimirEnHex(uint8_t num){
  char str[2];
  sprintf(str, "%02x", num);
  Serial.print(str);
}

char *rot47(char *s)
{
  char *p = s;
  while(*p) {
  if(*p >= '!' && *p <= 'O'){
  *p = ((*p + 47) % 127);
  }else if(*p >= 'P' && *p <= '~'){
  *p = ((*p - 47) % 127);
  }
  p++;
  }
  return s;
}
