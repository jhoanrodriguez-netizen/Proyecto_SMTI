#include "Sensor.h"

Sensor::Sensor(int _id, std::string _ubicacion, double _lectura) {
    id = _id;
    ubicacion = _ubicacion;
    lectura = _lectura;
}

Sensor::~Sensor() {
    std::cout << "[BASE] Sensor " << id << " liberado." << std::endl;
}

int Sensor::getId() const {
    return id;
}

double Sensor::getLectura() const {
    return lectura;
}

std::ostream& operator<<(std::ostream& salida, const Sensor& s) {
    salida << "ID: " << s.id
           << " | Ubicacion: " << s.ubicacion
           << " | Lectura: " << s.lectura;
    return salida;
}
