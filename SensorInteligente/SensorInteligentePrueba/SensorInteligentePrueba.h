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
    SensorInteligentePrueba(int pinA0, int pinA1);
    Isigfox *sigfox;
    void inicializar();
    void calibrarBateria();
    void valoresSensados();
    int divisorVoltajeBateria();
    int divisorVoltajeVelostat();
    void bateriaMenor(int porcentajeBateria);
    void enviarBateria(long intervalo);
    void enviarSigfox(int sensor, int bateria);
    float bateria;
    int porcentajeBateria;
    int voltajeAlfombra;
    int voltajeMedido;
    int bateriaEnviar;
  private:
    int _pinA0;
    int _pinA1;
    int _sensorMin;
    int _sensorMax;
    long _tiempoAnterior;    
};

#endif /* SENSORINTELIGENTE_H */
