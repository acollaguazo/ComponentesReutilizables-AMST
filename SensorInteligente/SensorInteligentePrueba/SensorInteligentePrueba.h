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

#ifndef SENSORINTELIGENTEPRUEBA_H
#define SENSORINTELIGENTEPRUEBA_H
#include "Arduino.h"
#include <Isigfox.h>
#include <WISOL.h>

class SensorInteligentePrueba
{
  public:
    SensorInteligentePrueba();
    Isigfox *sigfox;
    void inicializar();
    void calibrarBateria();
    void valoresSensados();
    float divisorVoltajeBateria();
    float divisorVoltajeVelostat();
    void bateriaMenor(float porcentajeBateria);
    void enviarBateria(long intervalo);
    void enviarSigfox(int sensor, int bateria);
    float bateria;
    float porcentajeBateria;
    int voltajeAlfombra;
    float voltajeMedido;
    float bateriaEnviar;
  private:
    int _pinA0;
    int _pinA1;
    float _sensorMin;
    float _sensorMax;
    long _tiempoAnterior;    
};

#endif /* SENSORINTELIGENTE_H */
