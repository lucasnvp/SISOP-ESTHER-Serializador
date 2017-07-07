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

//static const char* PROGRAMA =
//		"begin\n"
//		"variables a, b\n"
//		"a = 3\n"
//		"b = 5\n"
//		"a = b + 12\n"
//		"end\n"
//		"\n";

static const char* PROGRAMA =
		"begin\n"
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

int main(void) {
	puts("Bidireccionalidad Cliente"); /* prints Bidireccionalidad Cliente */

	//Conecto el socket
	uint32_t server = connect_server("127.0.0.1",8080);

	//Bucle principal
	while(1){
		char* buff=malloc(256);
		fgets(buff,256,stdin);
		int dimen = strlen(buff) - 1;

		printf("la dimension es: %d \n", dimen);
/*
		//Serializar un string
		serializar_int(server,1);

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
*/

		char* programa = strdup(PROGRAMA);
		t_metadata_program* metadata = metadata_desde_literal(programa);

		//Serializar un PCB
		serializar_int(server,2);

		//Creo un PCB
		PCB_t* PCB = PCB_new_pointer(1, 4, metadata);

		//Muestro el PCB
		print_PCB(PCB);

		//Serializo
		serializar_pcb(server, PCB);

	}

	return EXIT_SUCCESS;
}

