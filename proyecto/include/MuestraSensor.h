#ifndef MUESTRA_SENSOR_H
#define MUESTRA_SENSOR_H

// Datos que el cliente envia al servidor.
struct MuestraSensor {
    int idSensor;
    double valor;
    char tipo[12];
};

#endif
