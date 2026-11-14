#ifndef SENSOR_PRESION_H
#define SENSOR_PRESION_H

#include "Sensor.h"

class SensorPresion : public Sensor {
public:
    SensorPresion(int id, std::string ubicacion, double valor);
    ~SensorPresion();

    void tomarLectura() override;
    std::string obtenerUnidades() override;
    void procesarLectura() override;
};

#endif
