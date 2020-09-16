/*
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
  int bateria = 81;
  Serial.print(bateria);
  Serial.println("%");
  Serial.print(" 2 Voltaje del velostat = ");
  float voltaje = 1.751;
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
    
  uint8_t *sendData = bufferDatos;
  for (int i = 0; i < sizeof(bufferDatos); i++) {
    char cad[2];
    //cad[2] = imprimirEnHex(bufferDatos[i]);
    sprintf(cad, "%02x", bufferDatos[i]);
    strcat(cadena, cad);
  }
  Serial.println(millis());
  Serial.print(" Cadena: "); 
  Serial.println(cadena);
  char * enviar = sensores.rot47(cadena);
  Serial.println(enviar);
  
  uint8_t *c = (uint8_t *)cadena;
  const uint8_t payload = 10;
  uint8_t newBuffer[payload];
  newBuffer[0]= c[0];
  newBuffer[1]= c[1];
  newBuffer[2]= c[2];
  newBuffer[3]= c[3];
  newBuffer[4]= c[4];
  newBuffer[5]= c[5];
  newBuffer[6]= c[6];
  newBuffer[7]= c[7];
  newBuffer[8]= c[8];
  newBuffer[9]= c[9];
  Send_Pload(newBuffer, 10);
 
  memset(enviar, '\0', strlen(enviar));
  memset(cadena, '\0', strlen(cadena));

  delay(3000);
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
*/
