#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogo.h"
#include "estado.h"
#define SCALE		50
#define TAM		10
#define PLAYER_IMAGE		0
#define INI_IMAGE		1
#define OBS_IMAGE		2
#define MAX_BUFFER		1024


char * imagens [] = {
	"Minotaur05_DD.png",
	"Orc_03.png",
	"lava_pool1.png"
};

void print_cell(int C, int L, char * cor) {

	printf("<rect x=%d y=%d width=%d height=%d fill=%s />\n",SCALE*C, SCALE*L, SCALE, SCALE, cor);



}


void print_board () {

	int C, L;
	char * cor[] = {"#444400","#333300"};
	for (L = 0; L < TAM; L++)
		for (C = 0; C < TAM; C++) {
			int IDX = (L + C) % 2;
			print_cell(C , L, cor[IDX]);
		}
}

int valid (int X, int Y) {
	return X >= 0 && X < TAM && Y >= 0 && Y < TAM;

}


void print_move (int X, int Y) {
	char * cor[] = {"#666600","#555500"};
	int IDX = (X + Y) % 2;
	if (!valid(X,Y)) return;	
	printf ("<a xlink:href=\"http://localhost/cgi-bin/jogo?%d,%d\">\n",X, Y);
	print_cell(X, Y, cor[IDX]);
	printf ("</a>\n");

}


void print_moves (int X, int Y) {
	POSICAO movimentos[] = {
		{ -1 , 0 },
		{ +1 , 0 },
		{ 0 , -1 },
		{ 0 , +1 }			
	};
	int moves = 4;	
	int i;

	for (i = 0;i < moves; i++) {
		
		print_move(X + movimentos[i].X, Y + movimentos[i].Y);
	}

}

void print_image (int X, int Y, int index) {
	int tam = SCALE;
	char * nome = "http://localhost/images/%s";
	char ficheiro [MAX_BUFFER];
	sprintf (ficheiro, nome, imagens[index]);

	printf("<image x=%d y=%d width=%d height=%d xlink:href=%s /> \n", 
		SCALE*X, SCALE*Y, tam, tam, ficheiro);


}



void print_player(ESTADO e) {
	int X = e.jog.X;
	int Y = e.jog.Y;	




	print_image (X,Y,PLAYER_IMAGE);
	print_moves(X,Y);
}


void print_inimigos(ESTADO e) {

	int i;

	for (i = 0; i < e.num_inimigos; i++)
		print_image(e.inimigo[i].X,e.inimigo[i].Y,INI_IMAGE);


}




void print_obstaculos(ESTADO e) {

	int i;

	for (i = 0; i < e.num_obstaculos; i++)
		print_image(e.obstaculo[i].X,e.obstaculo[i].Y,OBS_IMAGE);


}





ESTADO inicializar () {

	ESTADO e;
	e.num_inimigos=3;
	e.num_obstaculos=2;
	e.inimigo[0].X = 2;
	e.inimigo[0].Y = 3;
	e.inimigo[1].X = 4;
	e.inimigo[1].Y = 5;
	e.inimigo[2].X = 6;
	e.inimigo[2].Y = 7;
	e.obstaculo[0].X=7;
	e.obstaculo[0].Y=4;
	e.obstaculo[1].X=5;
	e.obstaculo[1].Y=3;
	e.jog.X= 5;
	e.jog.Y= 9;

	return e;
}

ESTADO ler_inimigos(ESTADO e, char * args) {
	int i;
	char resto  [MAX_BUFFER];
	sscanf ( args, "%d,%s", &e.num_inimigos, resto);

	for (i=0;i<e.num_inimigos;i++) {
		sscanf (resto, "%d,%d,%s", &(e.inimigo[i].X), &(e.inimigo[i].Y), resto);	

	}
	return e;
}



ESTADO str2estado (char * argumentos) {
	ESTADO e;
	int X=0, Y=0;
	char resto  [MAX_BUFFER];
	sscanf(argumentos, "%d,%d,%s",&X,&Y,resto);
	e.jog.X = X;
	e.jog.Y= Y;	
	e = ler_inimigos(e, resto);
	return e;
}


void parser (char *argumentos) {

	
	ESTADO e;
	
	if (strlen(argumentos)!=0) {
		e = str2estado(argumentos);
	} else e=inicializar();	
	
	print_board();
	print_player(e);
	print_inimigos(e);
	print_obstaculos(e);
}



