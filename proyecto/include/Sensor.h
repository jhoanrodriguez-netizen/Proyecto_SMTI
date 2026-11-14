#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <string>

class Sensor {
protected:
    int id;
    std::string ubicacion;
    double lectura;

public:
    Sensor(int _id, std::string _ubicacion, double _lectura);
    virtual ~Sensor();

    int getId() const;
    double getLectura() const;

    virtual void tomarLectura() = 0;
    virtual std::string obtenerUnidades() = 0;
    virtual void procesarLectura() = 0;

    friend std::ostream& operator<<(std::ostream& salida, const Sensor& s);
};

#endif
