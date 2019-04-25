#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#define SCALE		50
#define TAM		10

void print_header () {
	printf ("content-type: text/html\n\n");
	printf("<svg width=600 height=600>\n ");

}


void print_foater () {

	printf ("</svg> \n");

}



int main() {
	print_header ();

	parser (getenv("QUERY_STRING"));

	print_foater ();

	return 0;

}
