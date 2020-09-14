/** @file     SensorInteligente.h
 *  @date     8 de julio de 2020
 *  @authors  Rosa Pincay, Javier Arce
 *  @brief    Librería para detección de pesos usando velostat y para realizar mediciones de batería. 
 *            Incluye el envío de datos encriptados a Sigfox Backend.    
 */

#ifndef SENSORINTELIGENTE_H
#define SENSORINTELIGENTE_H
#include "Arduino.h"

class SensorInteligente
{
  public:
    // Constructores de la librería
    SensorInteligente();
    SensorInteligente(int pinA1);
    SensorInteligente(int pinA0, int pinA1);
    
    // Funciones
    void inicializar();
    void tiempoEspera(long intervalo, float voltajeSensor, float porcentajeBateria, void (*funcionEnvio)(float, float));
    void calibrarBateria(float rBajo, float rArriba, float vIn);
    void enviarBateria(long intervalo, int porcentajeBateria);    
    void enviarPorcentajeBateria(int porcentaje);
    int compararNivelBateria(int porcentajeBateria);    
    float leerVoltajeBateria();
    int leerPorcentajeBateria();
    float leerVoltajeVelostat();
    char *rot47(char *s);

    // Variables
    float voltajeBateria;
    int porcentajeBateria;     
    int nivelBateriaMayor;
    float voltajeSensor;  
    
  private:
    int _pinA0;
    int _pinA1;
    int _limiteMaximoBateria; 
    unsigned long _tiempoAnterior;  
};

#endif /* SENSORINTELIGENTE_H */
