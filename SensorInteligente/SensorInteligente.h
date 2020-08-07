/*
 * ValoresSensados.h - Librería para detectar tanques de gas vacíos y mesas ocupadas peso usando velostat.
 * Created by Rosa M. Pincay, July 7, 2020.
 * Released into the ESPOL domain.
 */

/* 
 * File:   SensorInteligente.h
 * Author: Rosa Pincay
 *
 * Created on 8 de julio de 2020
 */

#ifndef SENSORINTELIGENTE_H
#define SENSORINTELIGENTE_H
/*#include "Arduino.h"
#include <Isigfox.h>*/
#include <WISOL.h>

class SensorInteligente
{
  public:
    /*typedef struct _recvMsg{
      int len;
      char* inData;
    } recvMsg;
    Isigfox *Isigfox;
    typedef union{
    uint16_t number;
    uint8_t bytes[2];
} UINT16_t;*/

    /*
     * Crea un objeto de tipo SensorInteligente, 
     * para medir el voltaje del velostat.
     * 
     * @param pinA0: pin análogo al que se conecta el velostat
     */
    SensorInteligente(int pinA0);
    /*
     * Crea un objeto de tipo SensorInteligente, 
     * para medir los valores de la batería y el velostat.
     * 
     * @param pinA0: pin análogo al que se conecta el velostat
     * @param pinA1: pin análogo al que se conecta la fuente de alimentación
     */
    SensorInteligente(int pinA0, int pinA1);   
    void inicializar();
    void calibrarBateria();
    float leerVoltajeBateria();
    float leerPorcentajeBateria();
    float leerVoltajeVelostat();
    void valoresSensados();
    void bateriaMenor(float porcentajeBateria);
    void enviarBateria(long intervalo);
    void EnviarSigfox();
    float bateria;
    float porcentajeBateria;
    int voltajeAlfombra;
    float voltajeMedido;
    float voltajeBateria;
    float bateriaEnviar;
  private:
    int _pinA0;
    int _pinA1;
    float _sensorMin;
    float _sensorMax;
    long _tiempoAnterior;
    
};

#endif /* SENSORINTELIGENTE_H */
