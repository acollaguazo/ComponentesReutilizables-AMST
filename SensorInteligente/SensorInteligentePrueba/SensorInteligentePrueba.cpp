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
SensorInteligentePrueba::SensorInteligentePrueba()
{
  
}

void SensorInteligentePrueba::inicializar()
{
  _sensorMin = 5.0;
  _sensorMax = 0.0;
  _tiempoAnterior = 0.0;
  //sigfox = new WISOL();
  //sigfox->initSigfox();
  //sigfox->testComms(); 
  bateriaEnviar = 100.0;
  porcentajeBateria = 0.0;
  bateria = 0.0;
  voltajeMedido =0.0;
}

/*
 * Realiza una lectura del valor sensado por la batería para poder calibrarla
 */
void SensorInteligentePrueba::calibrarBateria(){
  while (millis() < 50) {
    bateria = SensorInteligentePrueba::divisorVoltajeBateria();
    if (bateria > _sensorMax) {
      _sensorMax = bateria;
    }
    if (bateria < _sensorMin) {
      _sensorMin = bateria;
    }
    Serial.print(_sensorMin);
    Serial.print(_sensorMax);
    Serial.println("Calibrado");
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
    int randomNumberVelostat = random(0,1023);
    voltajeMedido = (((float) randomNumberVelostat) * 5.0) / 1023.0;
    //voltajeMedido = SensorInteligentePrueba::divisorVoltajeVelostat();
    bateria = SensorInteligentePrueba::divisorVoltajeBateria();
    porcentajeBateria = map(bateria, 0, 7, 0, 100);
    //SensorInteligentePrueba::bateriaMenor(porcentajeBateria);
    //porcentajeBateria = map(bateria, 0, 7, 0, 100);
    //delay(250);  
}


/*
 * Obtiene el nivel de bateria más bajo.
 */
void SensorInteligentePrueba::bateriaMenor(float porcentajeBateria) 
{
  if ((porcentajeBateria <= SensorInteligentePrueba::bateriaEnviar)) {
      SensorInteligentePrueba::bateriaEnviar = porcentajeBateria;
  }else{
    return;
  }
}


/*
 * Función que envía el nivel de la batería a Sigfox
 */
void SensorInteligentePrueba::enviarBateria(long intervalo) 
{
  SensorInteligentePrueba::bateriaMenor(porcentajeBateria);
  long tiempoA = millis();  
  if (tiempoA - _tiempoAnterior > intervalo) {
    _tiempoAnterior = tiempoA;
    if(bateriaEnviar > 10){
    Serial.print(bateriaEnviar);
    Serial.println(" <- Enviando...");
    }else{
    Serial.println("Bateria baja :(");
    }
    //SensorInteligentePrueba::enviarSigfox(voltajeAlfombra, (int)porcentajeBateria);
  }
}

//Devuelve valor del sensor ya convertido, en el rango [0, 5].
float SensorInteligentePrueba::divisorVoltajeVelostat(){
  float valor =0.0, suma, mult;
  float rBajo = 10000.0;
  float rArriba = random(0.0, 500.0);
  
  //Serial.print("arriba ");
  //Serial.println(rArriba);
  //suma = ;
  valor = rBajo / (rArriba + rBajo) * 5.0;
  //valor = mult * 5;
  //Serial.print("valor ");
  //Serial.println(valor);
  return valor;
}

//Devuelve valor de la batería ya convertido, en el rango [0, 5].
float SensorInteligentePrueba::divisorVoltajeBateria(){
  float vIn = random(0.9, 9);
  float rBajo = 1000;
  float rArriba = 1000;
  float valor;
  valor = (rBajo/(rBajo+rArriba))*vIn;
  return valor;
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
