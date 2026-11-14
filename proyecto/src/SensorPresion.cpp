#include "SensorPresion.h"

SensorPresion::SensorPresion(int id, std::string ubicacion, double valor)
    : Sensor(id, ubicacion, valor) {
}

SensorPresion::~SensorPresion() {
    std::cout << "[DERIVADA] Sensor de presion liberado." << std::endl;
}

void SensorPresion::tomarLectura() {
    std::cout << "[PRESION] ID: " << id
              << " | Ubicacion: " << ubicacion
              << " | Valor: " << lectura
              << " " << obtenerUnidades() << std::endl;
}

std::string SensorPresion::obtenerUnidades() {
    return "bar";
}

void SensorPresion::procesarLectura() {
    tomarLectura();
}
