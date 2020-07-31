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

class SensorInteligentePrueba
{
  public:
    SensorInteligentePrueba();
    void inicializar();
    void calibrarBateria();
    void valoresSensados();
    float divisorVoltajeBateria();
    float divisorVoltajeVelostat();
    void bateriaMenor(float porcentajeBateria);
    void enviarBateria(long intervalo);
    float bateria;
    float porcentajeBateria;
    int voltajeAlfombra;
    float voltajeMedido;
    float bateriaEnviar;
  private:
    float _sensorMin;
    float _sensorMax;
    long _tiempoAnterior;    
};

#endif /* SENSORINTELIGENTE_H */
