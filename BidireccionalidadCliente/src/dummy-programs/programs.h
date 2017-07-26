static const char* PROGRAMA1 = "begin\n"
		"variables a, b\n"
		"a = 3\n"
		"b = 5\n"
		"a = b + 12\n"
		"end\n"
		"\n";

static const char* PROGRAMA2 = "begin\n"
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

static const char* PROGRAMA3 =
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
