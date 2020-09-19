/**
 * @file    VelostatBateriaAT.ino
 * @brief   Archivo de ejemplo que puede ser utilizado para captura/envío del
 *          voltaje de un sensor de peso y del porcentaje de una batería
 *          al Backend de Sigfox, haciendo uso de comandos AT.
 */                

#include <SensorInteligente.h>

const int pinA0 = A0;
const int pinA1 = A1;
int contador = 1;
char cadena[11];
char cadenaEnviar[11];
SensorInteligente sensores = SensorInteligente(pinA0, pinA1);

void setup() {
  Serial.begin(9600);
  sensores.inicializar();
  sensores.calibrarBateria(1220.0, 1000.0, 9);
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
  float voltaje = sensores.leerVoltajeVelostat();
  Serial.println(voltaje);
  uint8_t byteBateria = (uint8_t)bateria;
  byte *float_velostat = (byte *)&voltaje;
  const uint8_t payloadSize = 5;
  uint8_t bufferDatos[payloadSize];
  bufferDatos[0] = float_velostat[0];
  bufferDatos[1] = float_velostat[1];
  bufferDatos[2] = float_velostat[2];
  bufferDatos[3] = float_velostat[3];
  bufferDatos[4] = byteBateria;
  
  uint8_t *sendData = bufferDatos;
  
  Serial.print(" Bateria en hexadecimal: ");
  Serial.println(bufferDatos[4],HEX);
  
  for (int i = 0; i < sizeof(bufferDatos); i++) {
    char cad[2];
    sprintf(cad, "%02x", bufferDatos[i]);
    strcat(cadena, cad);
  }
  Serial.print(" Cadena: "); 
  Serial.println(cadena);
  char *enviar = sensores.rot47(cadena);
 
  /*La cadena enviar no se puede enviar por lo que contiene caracteres especiales que no son aceptados 
  * por el backend de Sigfox por lo que se hace un casting hacia uint8_t para almacenar los caracteres
  * de la cadena como bytes uint8_t *c = (uint8_t *)cadena, para alli recorrer el buffer, concatenar en
  * cadenaEnviar y enviar mediante comandos AT.
  */
  Serial.print(" rot 47: "); 
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
  
  for (int i = 0; i < sizeof(newBuffer); i++) {
    char cad1[2];
    sprintf(cad1, "%02x", newBuffer[i]);
    strcat(cadenaEnviar, cad1);
  }  
  Serial.println("AT$RC");
  delay(100);
  Serial.print("AT$SF=");
  Serial.println(cadenaEnviar);
  memset(enviar, '\0', strlen(enviar));
  memset(cadena, '\0', strlen(cadena));
  memset(cadenaEnviar, '\0', strlen(cadenaEnviar));
  delay(3000);
}
