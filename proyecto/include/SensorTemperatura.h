#ifndef SENSOR_TEMPERATURA_H
#define SENSOR_TEMPERATURA_H

#include "Sensor.h"

class SensorTemperatura : public Sensor {
private:
    double valorCelsius;

public:
    SensorTemperatura(int id, std::string ubicacion, double valor);
    ~SensorTemperatura();

    void tomarLectura() override;
    std::string obtenerUnidades() override;
    void procesarLectura() override;
};

#endif
