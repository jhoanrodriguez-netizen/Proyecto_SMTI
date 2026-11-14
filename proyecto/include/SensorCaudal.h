#ifndef SENSOR_CAUDAL_H
#define SENSOR_CAUDAL_H

#include "Sensor.h"

class SensorCaudal : public Sensor {
public:
    SensorCaudal(int id, std::string ubicacion, double valor);
    ~SensorCaudal();

    void tomarLectura() override;
    std::string obtenerUnidades() override;
    void procesarLectura() override;
};

#endif
