/*
 ============================================================================
 Name        : BidireccionalidadServidor.c
 Author      : Lucas Visser
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "servidor/servidor.h"
#include "serializador/serializador.h"
#include "pcb/pcb.h"

#define CANTCONECIONES 1

int main(void) {
	puts("Bidireccionalidad Servidor"); /* prints Bidireccionalidad Servidor */

	//Creacion del servidor consola
	uint32_t servidor = build_server(8080, CANTCONECIONES);

	//El socket esta listo para escuchar
	if (servidor > 0) {
		printf("Servidor escuchando\n");
	}

	//uint32_t cliente = accept_conexion(servidor);

	// Variables para el servidor
	fd_set master;   	// conjunto maestro de descriptores de fichero
	fd_set read_fds; // conjunto temporal de descriptores de fichero para select()
	uint32_t fdmax;			// número máximo de descriptores de fichero
	int i;				// variable para el for
	FD_ZERO(&master);	// borra los conjuntos maestro
	FD_ZERO(&read_fds);	// borra los conjuntos temporal

	// añadir listener al conjunto maestro
	FD_SET(servidor, &master);

	// seguir la pista del descriptor de fichero mayor
	fdmax = servidor; // por ahora es éste

	// bucle principal
	while (true) {
		read_fds = master; // cópialo
		if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1) {
			perror("select");
			exit(1);
		}
		// explorar conexiones existentes en busca de datos que leer
		for (i = 0; i <= fdmax; i++) {
			if (FD_ISSET(i, &read_fds)) { // ¡¡tenemos datos!!
				if (i == servidor) {
					// acepto una nueva conexion
					uint32_t newfd = accept_conexion(servidor);
					FD_SET(newfd, &master); // añadir al conjunto maestro
					if (newfd > fdmax) {    // actualizar el máximo
						fdmax = newfd;
					}
				} else {
					//Recibo el comando
					uint32_t command = deserializar_int(i);

					// gestionar datos de un cliente
					if (command <= 0) {
						close(i); // Close conexion
						FD_CLR(i, &master); // eliminar del conjunto maestro
					} else {
						connection_handler(i, command);
					}
				}
			}
		}
	}

	return EXIT_SUCCESS;
}

void connection_handler(uint32_t socket, uint32_t command) {
	switch (command) {

	case 1: {
		printf("Deserializar String\n");
		t_SerialString* PATH = malloc(sizeof(t_SerialString));
		deserializar_string(socket, PATH);
		printf("Los bytes del mensaje mensaje son: %d\n", PATH->sizeString);
		printf("El mensaje es: %s\n", PATH->dataString);
		free(PATH->dataString);
		free(PATH);
		break; /* optional */
	}

	case 2: {
		printf("Deserializar Int\n");
		uint32_t nro = deserializar_int(socket);
		printf("El nro deserializar: %d\n", nro);
		break; /* optional */
	}

	case 3: {
		printf("Deserializar PCB\n");
		PCB_t* PCB = PCB_new_pointer(0, 0, NULL);
		deserializar_pcb(socket, PCB);
		print_PCB(PCB);
		PCB_free(PCB);
		break;
	}

	case 4: {
		printf("Deserializar Variable de stack\n");
		VARIABLE_T* unaVariable = deserializar_variable_t(socket);
		print_variable(unaVariable);
		free(unaVariable);
		break;
	}

	case 5: {
		printf("Deserializar una lina de stack\n");
		STACKPOINTER_T* lineSP = deserializar_stackpointer(socket);
		print_LineStack(lineSP);
		free(lineSP);
		break;
	}

	default: /* Optional */
		printf("Error en el comando\n");
	}
}
