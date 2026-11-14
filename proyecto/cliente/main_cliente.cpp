#include <winsock2.h>
#include <ws2tcpip.h>

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cstdlib>

#include "MuestraSensor.h"

using namespace std;

void enviarMuestra(MuestraSensor muestra) {
	
	//  Crear el socket TCP.
	SOCKET cliente = socket(AF_INET, SOCK_STREAM, 0);
	
	if (cliente == INVALID_SOCKET) {
		throw runtime_error("No se pudo crear el socket cliente.");
	}
	
	// Direccion del servidor.
	sockaddr_in servidor;
	memset(&servidor, 0, sizeof(servidor));
	
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(8080);
	servidor.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	// Conectarse al servidor.
	if (connect(cliente, (sockaddr*)&servidor,
				sizeof(servidor)) == SOCKET_ERROR) {
		
		closesocket(cliente);
		
		throw runtime_error(
							"No se pudo conectar. Inicie el servidor primero."
							);
	}
	
	// Enviar la muestra.
	int bytes = send(cliente, (const char*)&muestra,
					 sizeof(muestra), 0);
	
	if (bytes != sizeof(muestra)) {
		closesocket(cliente);
		throw runtime_error("No se pudo enviar la muestra.");
	}
	
	cout << "[CLIENTE] Muestra enviada: "
						<< muestra.tipo << endl;
	
	//  Recibir confirmacion.
	char respuesta[100] = {};
	
	int recibidos = recv(cliente, respuesta, 99, 0);
	
	if (recibidos > 0) {
		respuesta[recibidos] = '\0';
		cout << "[SERVIDOR] " << respuesta << endl;
	}
	
	//  Cerrar el socket.
	closesocket(cliente);
}

int main() {
	
	WSADATA datos;
	
	if (WSAStartup(MAKEWORD(2, 2), &datos) != 0) {
		cout << "No se pudo iniciar Winsock." << endl;
		system("pause");
		return 1;
	}
	
	try {
		
		// Tres muestras de ejemplo.
		MuestraSensor muestras[3] = {
			{101, 92.5, "Temperatura"},
		{102, 7.2, "Presion"},
			{103, 22.0, "Caudal"}
		};
		
		// Enviar las tres muestras.
		for (int i = 0; i < 3; i++) {
			enviarMuestra(muestras[i]);
		}
		
		cout << endl;
		cout << "Todas las muestras fueron enviadas."
			<< endl;
		
	}
	catch (const exception& error) {
		
		cout << "[ERROR CLIENTE] "
			<< error.what() << endl;
		
		WSACleanup();
		
		system("pause");
		
		return 1;
	}
	
	WSACleanup();
	
	// aqui mantenemos abierta la ventana
	cout << endl;
	cout << "CLIENTE FINALIZADO." << endl;
	
	system("pause");
	
	return 0;
}
