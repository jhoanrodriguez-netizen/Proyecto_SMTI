#include <winsock2.h>
#include <ws2tcpip.h>

#include "ServidorSMTI.h"
#include "MuestraSensor.h"
#include "SensorTemperatura.h"
#include "SensorPresion.h"
#include "SensorCaudal.h"

#include <iostream>
#include <cstring>
#include <stdexcept>

ServidorSMTI::ServidorSMTI(int _puerto, int _cantidad) {
    puerto = _puerto;
    cantidadMuestras = _cantidad;
}

void ServidorSMTI::iniciar(ListaGen<Sensor*>& lista) {
    // Crear el socket TCP.
    SOCKET servidor = socket(AF_INET, SOCK_STREAM, 0);

    if (servidor == INVALID_SOCKET) {
        throw std::runtime_error("No se pudo crear el socket.");
    }

    // Preparar la direccion del servidor.
    sockaddr_in direccion;
    std::memset(&direccion, 0, sizeof(direccion));

    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = htonl(INADDR_ANY);
    direccion.sin_port = htons(puerto);

    // Asociar el socket al puerto.
    if (bind(servidor, (sockaddr*)&direccion, sizeof(direccion)) == SOCKET_ERROR) {
        closesocket(servidor);
        throw std::runtime_error("No se pudo ocupar el puerto 8080.");
    }

    // Dejar el servidor escuchando.
    if (listen(servidor, 5) == SOCKET_ERROR) {
        closesocket(servidor);
        throw std::runtime_error("No se pudo iniciar listen.");
    }

    std::cout << "[SERVIDOR SMTI] Escuchando en el puerto "
              << puerto << std::endl;

    // Recibir la cantidad de muestras indicada.
    for (int i = 0; i < cantidadMuestras; i++) {
        sockaddr_in direccionCliente;
        int tamano = sizeof(direccionCliente);

        SOCKET cliente = accept(servidor,
                                (sockaddr*)&direccionCliente,
                                &tamano);

        if (cliente == INVALID_SOCKET) {
            closesocket(servidor);
            throw std::runtime_error("No se pudo aceptar al cliente.");
        }

        MuestraSensor muestra = {};
        int bytes = recv(cliente, (char*)&muestra, sizeof(muestra), 0);

        if (bytes != sizeof(muestra)) {
            closesocket(cliente);
            closesocket(servidor);
            throw std::runtime_error("No se recibio la muestra completa.");
        }

        muestra.tipo[11] = '\0';

        // Crear el sensor correspondiente.
        Sensor* nuevo = nullptr;

        if (strcmp(muestra.tipo, "Temperatura") == 0) {
            nuevo = new SensorTemperatura(muestra.idSensor, "Planta",
                                          muestra.valor);
        }
        else if (strcmp(muestra.tipo, "Presion") == 0) {
            nuevo = new SensorPresion(muestra.idSensor, "Planta",
                                      muestra.valor);
        }
        else if (strcmp(muestra.tipo, "Caudal") == 0) {
            nuevo = new SensorCaudal(muestra.idSensor, "Planta",
                                     muestra.valor);
        }
        else {
            closesocket(cliente);
            closesocket(servidor);
            throw std::runtime_error("Tipo de sensor desconocido.");
        }

        lista.insertar(nuevo);

        const char* respuesta = "Muestra recibida";
        send(cliente, respuesta, (int)strlen(respuesta), 0);

        std::cout << "[RECIBIDO] ID: " << muestra.idSensor
                  << " | Tipo: " << muestra.tipo
                  << " | Valor: " << muestra.valor << std::endl;

        closesocket(cliente);
    }

    closesocket(servidor);
    std::cout << "[SERVIDOR] Recepcion terminada." << std::endl;
}
