/*
 * ValoresSensados.cpp - Librería para detectar tanques de gas vacíos y mesas ocupadas peso usando velostat.
 * Created by Rosa M. Pincay, July 8, 2020.
 * Released into the ESPOL domain.
 */

#include "SensorInteligentePrueba.h"
#include <Isigfox.h>
#include <WISOL.h>
#include "Arduino.h"


/*
 * Inicializa los puertos para establecer la comunicación serial UART
 */
SensorInteligentePrueba::SensorInteligentePrueba(int pinA0, int pinA1)
{
  _pinA0 = pinA0;
  _pinA1 = pinA1;
}

void SensorInteligentePrueba::inicializar()
{
  _sensorMin = 1023;
  _sensorMax = 0;
  _tiempoAnterior = 0;
  sigfox = new WISOL();
  sigfox->initSigfox();
  sigfox->testComms(); 
  bateriaEnviar = 100;
}

/*
 * Realiza una lectura del valor sensado por la batería para poder calibrarla
 */
void SensorInteligentePrueba::calibrarBateria(){
  while (millis() < 5000) {
    bateria = analogRead(_pinA1);
    if (bateria > _sensorMax) {
      _sensorMax = bateria;
    }
    if (bateria < _sensorMin) {
      _sensorMin = bateria;
    }
  }
}

/*
 * Toma los valores sensados por el velostat y de la batería. 
 * Se convierte el valor de la entrada analógica para el voltaje y,
 * se calibra el nivel de la batería para que esté en el rango 0 - 100.
 */
void SensorInteligentePrueba::valoresSensados()
{
    //voltajeAlfombra = analogRead(_pinA0);
    //voltajeMedido = (((float) randomNumberVelostat) * 5.0) / 1023.0;
    voltajeMedido = SensorInteligentePrueba::divisorVoltajeVelostat();
    bateria = SensorInteligentePrueba::divisorVoltajeBateria();
    //porcentajeBateria = map(bateria, _sensorMin, _sensorMax, 0, 100);
    porcentajeBateria = map(bateria, 0, 716, 0, 100);
    delay(250);  
}


/*
 * Obtiene el nivel de bateria más bajo.
 */
void SensorInteligentePrueba::bateriaMenor(int porcentajeBateria) 
{
  if ((porcentajeBateria < bateriaEnviar)) {
    bateriaEnviar = porcentajeBateria;
  }
}


/*
 * Función que envía el nivel de la batería a Sigfox
 */
void SensorInteligentePrueba::enviarBateria(long intervalo) 
{
  if (millis() - _tiempoAnterior > intervalo) {
    _tiempoAnterior = millis();
    Serial.println(bateriaEnviar);
    SensorInteligentePrueba::enviarSigfox(voltajeAlfombra, (int)porcentajeBateria);
  }
}

//Devuelve valor del sensor ya convertido, en el rango [0, 5].
int SensorInteligentePrueba::divisorVoltajeVelostat(){
  int rBajo = 10000;
  int rArriba = random(0, 500);
  return (rBajo/(rBajo+10000))*5;
}

//Devuelve valor de la batería ya convertido, en el rango [0, 5].
int SensorInteligentePrueba::divisorVoltajeBateria(){
  int vIn = random(1, 9);
  int rBajo = 1000;
  int rArriba = 1000;
  return (rBajo/(rBajo+rArriba))*vIn;
}

void SensorInteligentePrueba::enviarSigfox(int sensor, int bateria) {
  const uint8_t payloadSize = 16;
  uint8_t buf_stri[payloadSize];
  buf_stri[0] = sensor;
  buf_stri[1] = bateria;
  uint8_t *sendData = buf_stri;
  int len = strlen((char * )buf_stri);
  recvMsg *RecvMsg;
  RecvMsg = (recvMsg *)malloc(sizeof(recvMsg));
  sigfox->sendPayload(sendData, len, 0, RecvMsg);
  for (int i = 0; i < len; i++) {
    Serial.print(RecvMsg->inData[i]);
  }
  Serial.println("Received");
  free(RecvMsg);
}
