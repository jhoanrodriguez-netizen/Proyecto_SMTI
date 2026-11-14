#include <winsock2.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "ServidorSMTI.h"
#include "ListaGen.h"
#include "Sensor.h"

using namespace std;

int main() {
	
	WSADATA datos;
	
	if (WSAStartup(MAKEWORD(2, 2), &datos) != 0) {
		cout << "No se pudo iniciar Winsock." << endl;
		system("pause");
		return 1;
	}
	
	try {
		
		// Crear la lista de sensores.
		ListaGen<Sensor*> lista;
		
		// Crear el servidor en el puerto 8080.
		ServidorSMTI servidor(8080, 3);
		
		cout << "================================" << endl;
		cout << "     SERVIDOR SMTI" << endl;
		cout << "================================" << endl;
		
		// Iniciar el servidor.
		servidor.iniciar(lista);
		
		// Procesar los sensores recibidos.
		cout << endl;
		cout << "--- PROCESAMIENTO DE SENSORES ---"
			<< endl;
		
		lista.procesarTodo();
		
		// Buscar un sensor por su ID.
		cout << endl;
		cout << "--- BUSQUEDA DEL SENSOR 101 ---"
			<< endl;
		
		Sensor* encontrado = lista.buscarPorID(101);
		
		if (encontrado != nullptr) {
			cout << *encontrado << endl;
		}
		else {
			cout << "Sensor no encontrado." << endl;
		}
		
		// Mostrar lecturas criticas.
		cout << endl;
		cout << "--- LECTURAS CRITICAS ---" << endl;
		
		lista.filtrarLecturasCriticas(80.0);
		
		// Eliminar un sensor por su ID.
		cout << endl;
		cout << "--- ELIMINAR SENSOR 102 ---" << endl;
		
		lista.eliminarPorID(102);
		
	}
	catch (const exception& error) {
		
		cout << "[EXCEPCION SMTI] "
			<< error.what() << endl;
		
		WSACleanup();
		
		system("pause");
		
		return 1;
	}
	
	WSACleanup();
	
	cout << endl;
	cout << "SERVIDOR FINALIZADO." << endl;
	
	// Mantener abierta la ventana.
	system("pause");
	
	return 0;
}
