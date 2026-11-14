#include "SensorCaudal.h"

SensorCaudal::SensorCaudal(int id, std::string ubicacion, double valor)
    : Sensor(id, ubicacion, valor) {
}

SensorCaudal::~SensorCaudal() {
    std::cout << "[DERIVADA] Sensor de caudal liberado." << std::endl;
}

void SensorCaudal::tomarLectura() {
    std::cout << "[CAUDAL] ID: " << id
              << " | Ubicacion: " << ubicacion
              << " | Valor: " << lectura
              << " " << obtenerUnidades() << std::endl;
}

std::string SensorCaudal::obtenerUnidades() {
    return "L/min";
}

void SensorCaudal::procesarLectura() {
    tomarLectura();
}
