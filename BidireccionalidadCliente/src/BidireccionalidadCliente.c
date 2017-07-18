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

/*
static const char* PROGRAMA = "begin\n"
		"variables a, b\n"
		"a = 3\n"
		"b = 5\n"
		"a = b + 12\n"
		"end\n"
		"\n";
*/

/*
static const char* PROGRAMA = "begin\n"
 "variables f, i, t\n"

 "#`i`: Iterador\n"
 "i=0\n"

 "#`f`: Hasta donde contar\n"
 "f=20\n"
 ":inicio\n"

 "#Incrementar el iterador\n"
 "i=i+1\n"

 "#Imprimir el contador\n"
 "print i\n"

 "#`t`: Comparador entre `i` y `f`\n"
 "t=f-i\n"
 "#De no ser iguales, salta a inicio\n"
 "jnz t inicio\n"

 "end\n"
 "\n";
*/

static const char* PROGRAMA =
	"#!/usr/bin/ansisop\n"

	"function imprimir\n"
	"	wait mutexA\n"
	"		print $0+1\n"
	"	signal mutexB\n"
	"end\n"

	"begin\n"
	"variables f,  A,  g\n"
	"	A = 	0\n"
	"	!Global = 1+A\n"
	"	print !Global\n"
	"	jnz !Global Siguiente\n"
	":Proximo\n"

	"	f = 8\n"
	"	g <- doble !Global\n"
	"	io impresora 20\n"
	"	:Siguiente\n"
	"	imprimir A\n"
	"	textPrint    Hola Mundo!\n"

	"	sumar1 &g\n"
	"	print 		g\n"

	"	sinParam\n"

	"end\n"

	"function sinParam\n"
	"	textPrint Bye\n"
	"end\n"

	"#Devolver el doble del\n"
	"#primer parametro\n"
	"function doble\n"
	"variables f\n"
	"	f = $0 + $0\n"
	"	return f\n"
	"end\n"

	"function sumar1\n"
	"	*$0 = 1 + *$0\n"
	"end\n"
	"\n";


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
			t_SerialString* PATH = malloc(sizeof(t_SerialString));
			PATH->sizeString = dimen;
			PATH->dataString = malloc(PATH->sizeString);
			PATH->dataString = buff;
			//Serializo el path
			serializar_string(server, PATH);
			free(buff);
			buff = NULL;
			PATH->dataString = NULL;
			free(PATH);
			break;
		}

		case 2: {
			char* buff = malloc(256);
			fgets(buff, 256, stdin);
			int dimen = strlen(buff) - 1;

			printf("Serializar Int\n");
			serializar_int(server, 2);
			serializar_int(server,atoi(buff));
			free(buff);
			break;
		}

		case 3: {
			printf("Serializar PCB\n");
			char* programa = strdup(PROGRAMA);
			t_metadata_program* metadata = metadata_desde_literal(programa);

			//Creo un PCB
			PCB_t* PCB = PCB_new_pointer(1, 4, metadata);

			//Agrego una linea de stack
			VARIABLE_T * variableA = variable_new('a',0,0,4);
			VARIABLE_T * variableG = variable_new('g',0,4,4);
			STACKPOINTER_T * lineSP = stack_new(0,0,NULL,variableA);
			list_add(PCB->StackPointer, lineSP);
			STACKPOINTER_T * lineSP2 = stack_new(0,0,3,variableG);
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
			STACKPOINTER_T * lineSP = stack_new(0,0,5,variableA);

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

