/*
 ============================================================================
 Name        : BidireccionalidadCliente.c
 Author      : Lucas Visser
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include <parser/metadata_program.h>
#include "servidor/servidor.h"
#include "serializador/serializador.h"
#include "pcb/pcb.h"
#include "dummy-programs/programs.h"

int main(void) {
	puts("Bidireccionalidad Cliente"); /* prints Bidireccionalidad Cliente */

	//Conecto el socket
	uint32_t server = connect_server("127.0.0.1", 8080);

	//Bucle principal
	while (1) {
		char* comando = malloc(4);
		fgets(comando, 4, stdin);

		switch (atoi(comando)) {
		case 1: {
			char* buff = malloc(256);
			fgets(buff, 256, stdin);
			int dimen = strlen(buff) - 1;

			printf("Serializar String\n");
			serializar_int(server, 1);

			//Serializo el path
			char* stringToSend = strndup(buff, dimen);
			serializar_string(server, PROGRAMA3);
			free(stringToSend);
			free(buff);
			break;
		}

		case 2: {
			char* buff = malloc(256);
			fgets(buff, 256, stdin);

			printf("Serializar Int\n");
			serializar_int(server, 2);
			serializar_int(server,atoi(buff));
			free(buff);
			break;
		}

		case 3: {
			printf("Serializar PCB\n");
			char* programa = strdup(PROGRAMA1);
			t_metadata_program* metadata = metadata_desde_literal(programa);

			//Creo un PCB
			PCB_t* PCB = PCB_new_pointer(1, 4, metadata, 5);

			//Agrego una linea de stack
			VARIABLE_T * variableA = variable_new('a',0,0,4);
			VARIABLE_T * variableG = variable_new('g',0,4,4);

			//Linea Stack 1
			t_list* list_vars = list_create();
			list_add(list_vars, variableA);
			list_add(list_vars, variableG);

			STACKPOINTER_T * lineSP = stack_new(NULL,list_vars,NULL,NULL);
			list_add(PCB->StackPointer, lineSP);

			//Linea Stack 2
			VARIABLE_T * variableACopy = variable_new('a',0,8,4);

			t_list* list_args = list_create();
			list_add(list_args, variableACopy);

			STACKPOINTER_T * lineSP2 = stack_new(list_args,NULL,3,variableG);
			list_add(PCB->StackPointer, lineSP2);

			//Muestro el PCB
			print_PCB(PCB);

			//Serializo
			serializar_int(server, 3);
			serializar_pcb(server, PCB);

			break;
		}

		case 4: {
			printf("Serializar una variable de stack\n");

			VARIABLE_T* unaVariable =  variable_new('a', 0, 4, 4);
			print_variable(unaVariable);

			serializar_int(server, 4);
			serializar_variable_t(server, unaVariable);
			break;
		}

		case 5: {
			printf("Serializar un stack\n");
			VARIABLE_T * variableA = variable_new('a',0,0,4);
			VARIABLE_T * variableG = variable_new('g',0,4,4);
			t_list* list_vars = list_create();
			list_add(list_vars, variableA);
			list_add(list_vars, variableG);
			STACKPOINTER_T * lineSP = stack_new(NULL, list_vars, 3,variableG);

			print_LineStack(lineSP);

			serializar_int(server, 5);
			serializar_stackpointer(server, lineSP);
			break;
		}

		default: {
			printf("Error en el comando\n");
		}

		}
	}

	return EXIT_SUCCESS;
}

