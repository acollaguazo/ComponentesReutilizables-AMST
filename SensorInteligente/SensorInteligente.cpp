/*
 * ValoresSensados.cpp - Librería para detectar tanques de gas vacíos y mesas ocupadas peso usando velostat.
 * Created by Rosa M. Pincay, July 8, 2020.
 * Released into the ESPOL domain.
 */

#include "SensorInteligente.h"
#include "Arduino.h"

/** Crea un objeto de tipo SensorInteligente.
 * Sirve para medir el voltaje del velostat.
 * 
 * @param pinA0: pin análogo al que se conecta el velostat.
 */
SensorInteligente::SensorInteligente(int pinA0)
{
  _pinA0 = pinA0;
  Serial.begin(9600);
}

/*
 * Inicializa los puertos para establecer la comunicación serial UART
 */
SensorInteligente::SensorInteligente(int pinA0, int pinA1)
{
  _pinA0 = pinA0;
  _pinA1 = pinA1;
  Serial.begin(9600);
}

void SensorInteligente::inicializar()
{
  _sensorMin = 1023;
  _sensorMax = 0;
  _tiempoAnterior = 0.0;
  /*Isigfox = new WISOL();
  Isigfox->initSigfox();
  Isigfox->testComms();*/ 
  bateriaEnviar = 100.0;
  porcentajeBateria = 0.0;
  bateria = 0.0;
  voltajeMedido = 0.0;
}

/*
 * Realiza la lectura del voltaje de la batería durante los primeros 2 segundos 
 * para establecer los valores de entrada mínimo y máximos.
 */
void SensorInteligente::calibrarBateria(){
  while (millis() < 2000) {
    bateria = analogRead(_pinA1);
    if (bateria > _sensorMax) {
      _sensorMax = bateria;
    }
    if (bateria < _sensorMin) {
      _sensorMin = bateria;
    }
    Serial.print(_sensorMin);
    Serial.print("  ");
    Serial.println(_sensorMax);
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

float SensorInteligente::leerPorcentajeBateria()
{
    bateria = analogRead(_pinA1);
    porcentajeBateria = map(bateria, _sensorMin, _sensorMax, 0, 100);
    return porcentajeBateria;
}

float SensorInteligente::leerVoltajeVelostat()
{
    voltajeAlfombra = analogRead(_pinA0);
    voltajeMedido = (((float) voltajeAlfombra) * 5.0) / 1023.0;
    Serial.print(voltajeMedido);
    if(voltajeMedido < 1.0){
      Serial.println(" - Sin presionar");
    }else if(voltajeMedido < 3.0){
      Serial.println(" - Presionando ligeramente");
    }else if (voltajeMedido < 4.0){ 
      Serial.println(" - Presionando medianamemente");
    }else{
      Serial.println(" - Presionando fuertemente");
    }
    return voltajeMedido;
}
/*
 * Obtiene el nivel de bateria más bajo.
 * @params porcentajeBateria
 */
void SensorInteligente::bateriaMenor(float porcentajeBateria) 
{
  if ((porcentajeBateria < bateriaEnviar)) {
    bateriaEnviar = porcentajeBateria;
  }else{
    return;
  }
}


/*
 * Función que envía el nivel de la batería a Sigfox en el intervalo asignado
 */
void SensorInteligente::enviarBateria(long intervalo) 
{
  long tiempoA = millis();  
  if (tiempoA - _tiempoAnterior > intervalo) {
    _tiempoAnterior = tiempoA;
    if(porcentajeBateria > 10){
      Serial.print(porcentajeBateria);
      Serial.println(" <- Enviando...");
    }else{
      Serial.println("Bateria baja :(");
    }
  }
}
