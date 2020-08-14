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
#include "Arduino.h"

class SensorInteligente
{
  public:
    /*
     * Crea un objeto de tipo SensorInteligente, 
     * para medir el voltaje del velostat.
     * 
     * @param pinA0: pin análogo al que se conecta la bateria
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
    void calibrarBateria(float rBajo, float rArriba, float vIn);
    float leerVoltajeBateria();
    float voltajeBateria;
    float leerPorcentajeBateria();
    float leerVoltajeVelostat();
    void bateriaMenor(float porcentajeBateria);
    void enviarBateria(long intervalo);
    float bateria;
    float porcentajeBateria;
    int voltajeAlfombra;
    float voltajeMedido;
    float bateriaEnviar;
  private:
    int _pinA0;
    int _pinA1;
    float _sensorMax;
    long _tiempoAnterior;
    
};

#endif /* SENSORINTELIGENTE_H */