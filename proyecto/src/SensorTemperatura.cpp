#include "SensorTemperatura.h"

SensorTemperatura::SensorTemperatura(int id, std::string ubicacion,
                                     double valor)
    : Sensor(id, ubicacion, valor) {
    valorCelsius = valor;
}

SensorTemperatura::~SensorTemperatura() {
    std::cout << "[DERIVADA] Sensor de temperatura liberado." << std::endl;
}

void SensorTemperatura::tomarLectura() {
    std::cout << "[TEMPERATURA] ID: " << id
              << " | Ubicacion: " << ubicacion
              << " | Valor: " << valorCelsius
              << " " << obtenerUnidades() << std::endl;
}

std::string SensorTemperatura::obtenerUnidades() {
    return "C";
}

void SensorTemperatura::procesarLectura() {
    tomarLectura();
}
