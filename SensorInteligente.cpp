/*
 * ValoresSensados.cpp - Librería para detectar tanques de gas vacíos y mesas ocupadas peso usando velostat.
 * Created by Rosa M. Pincay, July 8, 2020.
 * Released into the ESPOL domain.
 */

#include "SensorInteligente.h"
#include <Isigfox.h>
#include <WISOL.h>
#include "Arduino.h"


/*
 * Inicializa los puertos para establecer la comunicación serial UART
 */
SensorInteligente::SensorInteligente(int pinA0, int pinA1)
{
  _pinA0 = pinA0;
  _pinA1 = pinA1;
}

void SensorInteligente::inicializar()
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
void SensorInteligente::calibrarBateria(){
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
void SensorInteligente::valoresSensados()
{
    voltajeAlfombra = analogRead(_pinA0);
    voltajeMedido = (((float) voltajeAlfombra) * 5.0) / 1023.0;
    bateria = analogRead(_pinA1);
    porcentajeBateria = map(bateria, _sensorMin, _sensorMax, 0, 100);
    delay(250);  
}


/*
 * Obtiene el nivel de bateria más bajo.
 */
void SensorInteligente::bateriaMenor(int bateriaActual, int bateriaEnviar) 
{
  if ((bateriaActual < bateriaEnviar)) {
    bateriaEnviar = bateriaActual;
  }
}


/*
 * Función que envía el nivel de la batería a Sigfox
 */
void SensorInteligente::enviarBateria(long intervalo) 
{
  if (millis() - _tiempoAnterior > intervalo) {
    _tiempoAnterior = millis();
    Serial.println(bateriaEnviar);
    //enviarSigfox(voltajeAlfombra, (int)porcentajeBateria);
  }
}
