/** Librería para detección de pesos usando velostat y para realizar mediciones de batería.
 * Archivo:   SensorInteligente.h
 * Autor:     Rosa Pincay Jiménez
 * Creado:    8 de julio de 2020
 */

#ifndef SENSORINTELIGENTE_H
#define SENSORINTELIGENTE_H
#include "Arduino.h"

class SensorInteligente
{
  public:
  
    // Constructores de la librería
    SensorInteligente(int pinA1, float r1, float r2, float vin);
    SensorInteligente(int pinA0, int pinA1);
    
    // Funciones
    void inicializar();
    void calibrarBateria(float rBajo, float rArriba, float vIn);
    void enviarBateria(long intervalo, float porcentajeBateria);    
    void enviarPorcentajeBateria(int porcentaje);
    float bateriaMenor(float porcentajeBateria);    
    float leerVoltajeBateria();
    float leerPorcentajeBateria();
    float leerVoltajeVelostat();

    // Variables
    float voltajeBateria;
    float bateria;
    float porcentajeBateria;
    float voltajeMedido;
    float bateriaEnviar;    
    int voltajeAlfombra;
    
  private:
  
    int _pinA0;
    int _pinA1;
    int _r1;
    int _r2;
    int _vin;
    float _sensorMax;
    long _tiempoAnterior;
    
};

#endif /* SENSORINTELIGENTE_H */
