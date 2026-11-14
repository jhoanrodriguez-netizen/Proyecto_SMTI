#ifndef SERVIDOR_SMTI_H
#define SERVIDOR_SMTI_H

#include "ListaGen.h"
#include "Sensor.h"

class ServidorSMTI {
private:
    int puerto;
    int cantidadMuestras;

public:
    ServidorSMTI(int _puerto, int _cantidad);
    void iniciar(ListaGen<Sensor*>& lista);
};

#endif
