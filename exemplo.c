#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cgi.h"
#include "estado.h"

#define MAX_BUFFER		10240
#define TAM				10
#define ESCALA			85
#define MAX_DUFFS 		3
#define MAX_ARMADILHAS 	3
#define MAX_ESPADAS 	1 

/**
@file exemplo.c
Resumo: Este semestre, o projecto consistia em implementarmos um jogo do tipo Roguelike, e para tal, tivemos que seguir certos objectivos que foram propostos pelos 
professores. A implementação do projecto foi feito em C, no sistema operativo Linux. Com isto em mente, decidimos fazer um jogo ao estilo "The Simpsons", no qual
o Homer vai à caça do donut e tem que ultrapassar os obstáculos e inimigos, incluindo a sua própria família.
*/


/**
* Máximo de inimigos,obstáculos,duffs,armadilhas e espadas.
*/


/**
* Verifica se é uma posição válida ou não
*/
int posicao_valida(int x, int y) {
	return x >= 0 && y >= 0 && x < TAM && y < TAM;
}


/**
* Função auxiliar que vai devolver 0/1 de acordo com a posição, se é igual ou não.
*/
int posicao_igual (POSICAO p, int x, int y) {
	return (p.x==x && p.y==y);
}

/**
* Função auxiliar que vai devolver 0/1 de acordo com a posição, se está ocupada ou não.
*/

int tem_obstaculo (ESTADO e, int x, int y) {
	int i=0;

	for (i=0;i<e.num_obstaculos;i++) 
		if (posicao_igual (e.obstaculo[i], x, y)) return 1;

	return 0;

}

/**
* Função auxiliar que vai devolver 0/1 de acordo com a posição, se está ocupada pelo inimigo ou não.
*/
int tem_inimigo (ESTADO e, int x, int y) {
	int i=0;

	for (i=0;i<e.num_inimigos; i++)
		if (posicao_igual (e.inimigo[i], x, y)) return 1;
			
	return 0;		
}
/**
* Verifica se tem duff na posição x y
*/
int tem_duff (ESTADO e, int x, int y) {
	int i=0;

	for (i=0;i<e.num_duffs; i++)
		if (posicao_igual (e.duff[i], x, y)) return 1;
			
	return 0;		
}

/**
* Verifica se tem uma espada na posição x y
*/
int tem_espada(ESTADO e, int x, int y) {
	int i=0; 

	for (i=0;i<e.num_espadas;i++)
		if (posicao_igual(e.espada[i],x,y)) return 1;

	return 0;
}

/**
* Verifica se tem armadilha na posição x y
*/
int tem_armadilha (ESTADO e, int x, int y) {
	int i=0;

	for (i=0;i<e.num_armadilhas;i++)
		if (posicao_igual(e.armadilha[i], x, y)) return 1;

	return 0;
}

/**
* Função auxiliar que vai devolver 0/1 de acordo com a posição, se está ocupada pelo jogador ou não.
*/
int tem_jogador (ESTADO e, int x, int y) {
	return posicao_igual(e.jog, x, y);
}

/**
* Função auxiliar que vai devolver 0/1 de acordo com a posição, se está ocupada pela saída ou não.
*/
int tem_saida(ESTADO e, int x, int y) {
	if (x==e.saida.x && y==e.saida.y) return 1;
	else return 0;
}

/**
* Devolve 0/1 de acordo com a posição, se está ocupada pelo obstáculo, jogador ou saída, ou não.
*/
int posicao_ocupada (ESTADO e, int x, int y) {
	return (tem_obstaculo(e, x, y) || tem_jogador(e, x, y) || tem_saida(e,x,y) ) ;
	// tem_inimigo(e, x, y) || 
}


/**
* Verifica se a posição x y está a volta do jogador ou saída
*/
int evita_a_volta (ESTADO e, int x, int y) {
	return ( (x==1 && y==0) || (x==0 && y==1) || (x==1 && y==1) || (x==TAM-1 && y==TAM-2) || (x==TAM-2 && y==TAM-1));
}

/**
* Verifica se a posição x y está ocupada pelo duff, espada, armadilha, inimigo, obstaculo, jogador, saída ou se está a volta do jogador/saída
*/
int posicao_ocupada_com_inimigo (ESTADO e, int x, int y) {
	return (tem_duff(e, x, y) || tem_espada(e,x,y) || tem_armadilha(e,x,y)|| tem_inimigo(e, x, y) || tem_obstaculo(e, x, y) || tem_jogador(e, x, y) || tem_saida(e,x,y) || evita_a_volta(e,x,y)) ;
	// 
}

/**
* Verifica se o jogador está na posição da duff
*/
int verifica_duff (ESTADO e) {
	int i=0;
	for (i=0;i<e.num_duffs;i++) {
		if (e.jog.x==e.duff[i].x && e.jog.y==e.duff[i].y) {
			return i;
		}
	}
	return -1;
}

/**
* Verifica se o jogador está na posição da espada
*/
int verifica_espada (ESTADO e) {
	int i=0;
	for (i=0;i<e.num_espadas;i++) {
		if (e.jog.x==e.espada[i].x && e.jog.y==e.espada[i].y) {
			return i;
		}
	}
	return -1;
}

/**
* Verifica se o jogador está na posição da armadilha
*/
int verifica_armadilha (ESTADO e) {
	int i=0;
	for (i=0;i<e.num_armadilhas;i++) {
		if(e.jog.x==e.armadilha[i].x && e.jog.y==e.armadilha[i].y) return i;
	}
	return -1;
}

/**
* Verifica se o jogador esta na mesma posição do inimigo
*/
int verifica_se_ataca (ESTADO e) {
	int i=0;
	for (i=0;i<e.num_inimigos;i++) {
		if (e.jog.x==e.inimigo[i].x && e.jog.y==e.inimigo[i].y) return i;
	}
	return -1;
}

/**
* Verifica se os inimigos está a volta do jogador
*/
int verifica_alcance(ESTADO e) {
	int i=0;
	
	for (i=0;i<e.num_inimigos;i++) {
		if ((e.jog.x-e.inimigo[i].x == 1 && e.jog.y==e.inimigo[i].y) || (e.jog.x-e.inimigo[i].x == -1 && e.jog.y==e.inimigo[i].y) || (e.jog.y-e.inimigo[i].y == -1 && e.jog.x==e.inimigo[i].x) || (e.jog.y-e.inimigo[i].y == 1 && e.jog.x==e.inimigo[i].x)) 
		 return i;
	}

	return -1;
}

/**
* Serve para abrir o ficheiro e guardar
*/
void escrever_ficheiro(ESTADO e, char *f) {
	FILE *gamesave;
	

	gamesave=fopen("/tmp/gamesave.txt","w");

	fprintf (gamesave,"%s",estado2str(e));
	fclose(gamesave);
	
}

/**
* Imprime o quadrado com as dimensões ESCALA x ESCALA , na posição X Y e com as cores que pretendemos que desenhe. 
*/
void imprime_casa(int x, int y) {
	char *cor[] = {"#fdd71e", "#fdd71e"};
	int idx = (x + y) % 2;
	QUADRADO(x, y,ESCALA, cor[idx]);
}

/**
* Imprime o quadrado com as dimensões ESCALA x ESCALA , na posição X Y e com a cor vermelha
*/
void imprime_sangue(int x, int y) {
	QUADRADO (x,y,ESCALA,"#FF0000");
}

/**
* Imprime o quadrado com as dimensões ESCALA x ESCALA , na posição X Y e com a cor laranja 
*/
void imprime_ataque(int x, int y) {
	QUADRADO (x,y,ESCALA,"#ffa500");
}

/**
* Faz o mesmo que a função imprime_casa, só que em vez de desenhar com uma cor, fica transparente. 
*/

void imprime_casa_transparente(int x, int y) {
	QUADRADO_TRANSP(x, y,ESCALA);
}

/**
* Muda a posição do jogador
*/
ESTADO aplica_acao(ESTADO e, int x, int y) {
	e.jog.x=x;
	e.jog.y=y;
	
	return e;
}



/**
* Desenha os inimigos numa posição aleatória e aumenta o número de inimigos
*/
ESTADO inicializar_inimigo(ESTADO e) {
	int X, Y;
	do {
		X = random()%TAM;
		Y = random()%TAM;
	} while (posicao_ocupada_com_inimigo(e, X, Y));
	
	e.inimigo[(int) e.num_inimigos].x = X;
	e.inimigo[(int) e.num_inimigos].y = Y;
	e.vida_inimigo[(int) e.num_inimigos]=10;
	e.num_inimigos++;
	
	return e;
}

/**
* Desenha os números de inimigos até um limite, neste caso será 10.
*/
ESTADO inicializar_inimigos(ESTADO e, int num) {

	int i;

	for (i=0; i< num; i++) {
		e=inicializar_inimigo(e);
		e.inimigo_img[i]=i;
	}
	
	return e;

}


/**
* Desenhar os obstáculos numa posição aleatória e aumenta o número de obstáculos
*/
ESTADO inicializar_obstaculo(ESTADO e) {
	int X, Y;
	do {
		X=random()%TAM;
		Y=random()%TAM;
	
	} while (posicao_ocupada_com_inimigo(e,X,Y));
	e.obstaculo[(int) e.num_obstaculos].x=X;
	e.obstaculo[(int) e.num_obstaculos].y=Y;
	e.num_obstaculos++;

	return e;

}

/**
* Desenha os obstáculos até um limite, neste caso, o limite será 25.
*/
ESTADO inicializar_obstaculos(ESTADO e, int num) {
	int i=0;
	for (i=0;i<num;i++) e=inicializar_obstaculo(e);
	return e;

}

/**
* Desenha os duffs numa posição aleatória e aumenta o número de duffs
*/
ESTADO inicializar_duff (ESTADO e) {
	int X, Y;
	do {
		X= random()%TAM;
		Y= random()%TAM;
	} while (posicao_ocupada_com_inimigo(e, X,Y));

	e.duff[(int) e.num_duffs].x=X;
	e.duff[(int) e.num_duffs].y=Y;
	e.num_duffs++;

	return e;
}

/**
* Desenha as espadas numa posição aleatória e aumenta o número de espadas
*/
ESTADO inicializar_espada (ESTADO e) {
	int X, Y;
	do {
		X=random()%TAM;
		Y=random()%TAM;
	} while (posicao_ocupada_com_inimigo(e,X,Y));
	e.espada[(int) e.num_espadas].x=X;
	e.espada[(int) e.num_espadas].y=Y;
	e.num_espadas++;

	return e;
}

/**
* Desenha os armadilhas numa posição aleatória e aumenta o número de armadilhas
*/
ESTADO inicializar_armadilha (ESTADO e) {
	int X,Y;
	do {
		X=random()%TAM;
		Y=random()%TAM;
	}
	while (posicao_ocupada_com_inimigo(e,X,Y));

	e.armadilha[(int) e.num_armadilhas].x=X;
	e.armadilha[(int) e.num_armadilhas].y=Y;
	e.num_armadilhas++;

	return e;
}


/**
* Desenha os duffs até um limite, neste caso, o limite será 3.
*/
ESTADO inicializar_duffs(ESTADO e, int num) {
	int i=0;
	for (i=0;i<num;i++) e=inicializar_duff(e);
	return e;
}

/**
* Desenha os obstáculos até um limite, neste caso, o limite será 1.
*/
ESTADO inicializar_espadas(ESTADO e, int num) {
	int i=0;
	for (i=0;i<num;i++) e=inicializar_espada(e);
	return e;
}

/**
* Desenha os obstáculos até um limite, neste caso, o limite será 3.
*/
ESTADO inicializar_armadilhas(ESTADO e, int num) {
	int i=0;
	for (i=0;i<num;i++) e=inicializar_armadilha(e);
	return e;
}


/**
* Muda a posição do inimigo para cima
*/
ESTADO move_cima(ESTADO e, int inimigo) {
	e.inimigo[inimigo].y= e.inimigo[inimigo].y+1;
	return e;
}

/**
* Muda a posição do inimigo para baixo
*/
ESTADO move_baixo(ESTADO e, int inimigo) {
	e.inimigo[inimigo].y= e.inimigo[inimigo].y-1;
	return e;
}

/**
* Muda a posição do inimigo para esquerda
*/
ESTADO move_esquerda(ESTADO e, int inimigo) {
	e.inimigo[inimigo].x= e.inimigo[inimigo].x-1;
	return e;
}


/**
* Muda a posição do inimigo para direita
*/
ESTADO move_direita(ESTADO e, int inimigo) {
	e.inimigo[inimigo].x= e.inimigo[inimigo].x+1;
	return e;
}

/**
* Muda a posição do inimigo para diagonal
*/
ESTADO move_diagonal1 (ESTADO e, int inimigo) {
	e.inimigo[inimigo].x= e.inimigo[inimigo].x-1;
	e.inimigo[inimigo].y=e.inimigo[inimigo].y+1;
	return e;	
}


/**
* Muda a posição do inimigo para diagonal
*/
ESTADO move_diagonal2 (ESTADO e, int inimigo) {
	e.inimigo[inimigo].x= e.inimigo[inimigo].x+1;
	e.inimigo[inimigo].y=e.inimigo[inimigo].y+1;
	return e;	
}


/**
* Muda a posição do inimigo para diagonal
*/
ESTADO move_diagonal3 (ESTADO e, int inimigo) {
	e.inimigo[inimigo].x= e.inimigo[inimigo].x-1;
	e.inimigo[inimigo].y=e.inimigo[inimigo].y-1;
	return e;	
}


/**
* Muda a posição do inimigo para diagonal
*/
ESTADO move_diagonal4 (ESTADO e, int inimigo) {
	e.inimigo[inimigo].x= e.inimigo[inimigo].x+1;
	e.inimigo[inimigo].y=e.inimigo[inimigo].y-1;
	return e;	
}


/**
* Fica na mesma posição 
*/
ESTADO fica_posicao (ESTADO e, int inimigo) {
	e.inimigo[inimigo].x= e.inimigo[inimigo].x;
	e.inimigo[inimigo].y=e.inimigo[inimigo].y;
	return e;	
}


/**
* Muda a posição do inimigo
*/
ESTADO iniciar_movimento_inimigo (ESTADO e, int x_atual, int y_atual, int inim) {
	
	int x=random()%9;	
	
	if (x==1 && (posicao_valida(x_atual,y_atual+1) && (posicao_ocupada_com_inimigo(e,x_atual,y_atual+1)==0))) e=move_cima(e,inim); 	
	else {
		if (x==2 && (posicao_valida(x_atual,y_atual-1) && (posicao_ocupada_com_inimigo(e,x_atual,y_atual-1)==0))) e=move_baixo(e,inim);	
		else {
			if (x==3 && (posicao_valida(x_atual-1,y_atual) && (posicao_ocupada_com_inimigo(e,x_atual-1,y_atual)==0))) e=move_esquerda(e,inim);	
			else {
				if (x==4 && (posicao_valida(x_atual+1,y_atual) && (posicao_ocupada_com_inimigo(e,x_atual+1,y_atual)==0))) e=move_direita(e,inim);	
				else {
					if (x==5 && (posicao_valida(x_atual-1,y_atual+1) && (posicao_ocupada_com_inimigo(e,x_atual-1,y_atual+1)==0))) e=move_diagonal1(e,inim);
					else {
						if (x==6 && (posicao_valida(x_atual+1,y_atual+1) && (posicao_ocupada_com_inimigo(e,x_atual+1,y_atual+1)==0))) e=move_diagonal2(e,inim);
						else {
							if (x==7 && (posicao_valida(x_atual-1,y_atual-1) && (posicao_ocupada_com_inimigo(e,x_atual-1,y_atual-1)==0))) e=move_diagonal3(e,inim);
							else {
								if (x==8 && (posicao_valida(x_atual+1,y_atual-1) && (posicao_ocupada_com_inimigo(e,x_atual+1,y_atual-1)==0))) e=move_diagonal4(e,inim);
								else fica_posicao(e,inim); 
							}
						}
					}
				}
			}
		}
		
	}
	return e;
}



/**
* Muda a posição dos inimigos
*/
ESTADO inimigos_movem (ESTADO e, int num) {

	int i=0;

	for (i=0;i<num;i++) 
		e=iniciar_movimento_inimigo(e, e.inimigo[i].x, e.inimigo[i].y, i);

	return e;
}


/**
* Bebe a duff, e aumenta a vida e score.
*/
ESTADO bebe_duff(ESTADO e) {
	int pos=verifica_duff(e);
	if (pos!=-1) {
		e.mostra_duff=1;
		e.num_duffs--;
		e.duff[pos]=e.duff[(int)e.num_duffs];
		e.vida_jog+=10;
		e.score+=30;

	}
	return e;
}

/**
* Apanha a espada e aumenta o dano do ataque.
*/
ESTADO aumenta_ataque (ESTADO e) {
	int pos=verifica_espada(e);
	if (pos!=-1) {
		e.num_espadas--;
		e.espada[pos]=e.espada[(int) e.num_espadas];
		e.dano=1;
		e.ataque_jog +=20;
		e.score+=10;
	}	
	return e;
}


/**
* Usa a armadilha que pode ter que voltar para a posição inicial ou pode saltar mais que uma casa
*/
ESTADO usa_armadilha(ESTADO e) {
	int pos = verifica_armadilha(e);
	srandom(time(NULL));
	int escolha=random()%3;	
	
	if(pos!=-1) {

		e.num_armadilhas--;
		e.armadilha[pos]=e.armadilha[(int) e.num_armadilhas];
		
		if (escolha==0) {
			e.jog.x=TAM-1;
			e.jog.y=TAM-1;
		}
		if (escolha!=0){
			e.salta_casas=1;
			e.score+=10;
		}
	}
	
	return e;
}



/**
* Vai iniciar um nivel aleatório, com 10 inimigos e 25 obstáculos.
*/
ESTADO inicializar() {
	srandom(time(NULL));
	ESTADO e = {{0}};
	e.jog.x = TAM-1;
	e.jog.y = TAM-1;
	e.saida.x=0;
	e.saida.y=0;
	e.vida_jog=50;
	e.ataque_jog=5;
	e.score=0;
	e.salta_casas=0;
	e.mostra_sangue=0;
	e.mostra_vitima=0;
	e=inicializar_inimigos(e,MAX_INIMIGOS);
	e=inicializar_obstaculos(e,MAX_OBSTACULOS);
	e=inicializar_duffs(e,MAX_DUFFS);
	e=inicializar_armadilhas(e,MAX_ARMADILHAS);
	e=inicializar_espadas(e,MAX_ESPADAS);

	return e;
}


/**
* Função auxiliar que vai imprimir os movimentos possiveis ou não.
*/
void imprime_movimento(ESTADO e, int dx, int dy) {
	int x = e.jog.x + dx;
	int y = e.jog.y + dy;
	char link[MAX_BUFFER];

	if(!posicao_valida(x, y))
		return;
	
	if (posicao_ocupada(e , x, y) && !tem_saida(e, x, y))
		return;	

	sprintf(link, "http://localhost/cgi-bin/exemplo?%s,%d,%d", "/tmp/gamesave.txt", x, y);
	e = aplica_acao(e,x,y);

	ABRIR_LINK(link);
	imprime_casa_transparente(x, y);
	FECHAR_LINK;
}

/**
* Função que vai imprimir os movimentos possiveis.
*/
void imprime_movimentos(ESTADO e) {
	int dx;
	int dy;

	if (e.salta_casas==0) {
		for (dx=-1; dx<=1; dx++) 
			for (dy=-1;dy<=1;dy++)
				if (dx!=0 || dy!=0) 
					imprime_movimento(e, dx, dy);	
	}

	if (e.salta_casas==1) {
		for (dx=-2; dx<=2; dx++) 
			for (dy=-2;dy<=2;dy++)
				if (dx!=0 || dy!=0) 
					imprime_movimento(e, dx, dy);
	
	}

	if(e.salta_casas==2) {
		for (dx=0; dx<=1; dx++) 
				for (dy=0;dy<=1;dy++)
					if (dx!=0 || dy!=0) 
						imprime_movimento(e, dx, dy);
		
	}			
}		

/**
* Função que imprime a imagem do jogador.
*/
void imprime_jogador(ESTADO e) {

	if (e.jog_img==1) IMAGEM(e.jog.x, e.jog.y, ESCALA, "");
	else IMAGEM(e.jog.x, e.jog.y, ESCALA, "Homer.png");
	imprime_movimentos(e);
}


/**
* Função que imprime o quadrado quando é atacado ou se bebou duff.
*/
void imprime_informacao(ESTADO e) {
	int enemy=verifica_alcance(e);
	
	
	if (enemy!=-1) {
		IMAGEM(3,2,290,"Aviso.jpg");
		return;
	}

	if (e.mostra_duff==1) { 
		IMAGEM(3,2,290,"Boa.jpg");
		
	}
}

/**
* Função que imprime a imagem dos inimigos
*/
void imprime_inimigos(ESTADO e) {
	int i;
	char *nome[] = {
		"Inimigo1.png",
		"Inimigo2.png",
		"Inimigo3.png",
		"Inimigo4.png",
		"Inimigo5.png",
		"Inimigo6.png",
		"Inimigo7.png",
		"Inimigo8.png",
		"Inimigo9.png",
		"Inimigo10.png",
	};
	


	for(i = 0; i < e.num_inimigos; i++) {
		IMAGEM(e.inimigo[i].x, e.inimigo[i].y, ESCALA, nome[e.inimigo_img[i]%20]);
	}
}




/**
* Função que imprime a imagem dos duffs.
*/
void imprime_duffs(ESTADO e) {
	int i=0;
	for (i=0;i<e.num_duffs;i++) {
		IMAGEM(e.duff[i].x,e.duff[i].y,ESCALA,"Duff.png");
	}
}


/**
* Função que imprime a imagem das armadilhas
*/
void imprime_armadilhas(ESTADO e) {
	int i=0;
	for (i=0;i<e.num_armadilhas;i++) IMAGEM(e.armadilha[i].x,e.armadilha[i].y,ESCALA,"Misterio.png");
}


/**
* Função que imprime a imagem da espada.
*/
void imprime_espada(ESTADO e) {
	int i=0;
	for (i=0;i<e.num_espadas;i++) IMAGEM(e.espada[i].x,e.espada[i].y,ESCALA,"Espada.png");
}


/**
* Função que imprime a imagem dos obstáculos
*/
void imprime_obstaculos(ESTADO e) {
	int i;
	for(i = 0; i < e.num_obstaculos; i++)
		IMAGEM(e.obstaculo[i].x, e.obstaculo[i].y, ESCALA, "Krusty.png");
}



/**
* Função que imprime a saída, que neste caso vai ser um donut.
*/
void imprime_donut(ESTADO e) {
	if (e.donut_img==1) IMAGEM(9,9,ESCALA,"Next.png");
	else IMAGEM(0,0,ESCALA,"donut.png");
}

/**
* Função que imprime o background do jogo.
*/
void desenha_background() {
	IMAGEM(0,0,850,"Simpsons5.jpg");
}


/**
* Função que imprime a vida do jogador
*/

void imprime_vida (ESTADO e) {

	if (e.vida_jog==50) IMAGEM (0,2,350,"50.png");
	else if (e.vida_jog==60) IMAGEM (0,2,350,"60.png");
	else if (e.vida_jog==70) IMAGEM (0,2,350,"70.png");
	else if (e.vida_jog==80) IMAGEM (0,2,350,"80.png");
	else if (e.vida_jog==40) IMAGEM (0,2,350,"40.png");
	else if (e.vida_jog==35) IMAGEM (0,2,350,"35.png");
	else if (e.vida_jog==30) IMAGEM (0,2,350,"30.png");
	else if (e.vida_jog==25) IMAGEM (0,2,350,"25.png");
	else if (e.vida_jog==20) IMAGEM (0,2,350,"20.png");
	else if (e.vida_jog==15) IMAGEM (0,2,350,"15.png");
	else if (e.vida_jog==10) IMAGEM (0,2,350,"10.png");
	else if (e.vida_jog==5) IMAGEM (0,2,350,"5.png");
	else if (e.vida_jog==0) IMAGEM (0,2,350,"0.png");
}


/**
* Função que imprime a espada enquanto é usado pelo jogador
*/
void imprime_espada_uso (ESTADO e) {
	if (e.ataque_jog>5) IMAGEM(7,17,50,"EspadaVermelha.png");

}


/**
* Função que imprime o best score.
*/
void imprime_best_score(ESTADO e) {
	if(e.best_score==0) IMAGEM (3,1,290,"B0.jpg");
	else if (e.best_score==10) IMAGEM(3,1,290,"B10.jpg");
	else if (e.best_score==20) IMAGEM (3,1,290,"B20.jpg");
	else if (e.best_score==30) IMAGEM (3,1,290,"B30.jpg");
	else if (e.best_score==40) IMAGEM (3,1,290,"B40.jpg");
	else if (e.best_score==50) IMAGEM (3,1,290,"B50.jpg");
	else if (e.best_score==60) IMAGEM (3,1,290,"B60.jpg");
	else if (e.best_score==70) IMAGEM (3,1,290,"B70.jpg");
	else if (e.best_score==80) IMAGEM (3,1,290,"B80.jpg");
	else if (e.best_score==90) IMAGEM (3,1,290,"B90.jpg");
	else if (e.best_score==100) IMAGEM (3,1,290,"B100.jpg");
	else if (e.best_score==110) IMAGEM (3,1,290,"B110.jpg");
	else if (e.best_score==120) IMAGEM (3,1,290,"B120.jpg");
	else if (e.best_score==130) IMAGEM (3,1,290,"B130.jpg");
	else if (e.best_score==140) IMAGEM (3,1,290,"B140.jpg");
	else if (e.best_score==150) IMAGEM (3,1,290,"B150.jpg");
}

/**
* Função que imprime o score.
*/
void imprime_score(ESTADO e) {
	
	if (e.score==0) IMAGEM (3,0,290,"0.jpg");
	else if (e.score==10) IMAGEM (3,0,290,"10.jpg");
	else if (e.score==20) IMAGEM (3,0,290,"20.jpg");
	else if (e.score==30) IMAGEM (3,0,290,"30.jpg");
	else if (e.score==40) IMAGEM (3,0,290,"40.jpg");
	else if (e.score==50) IMAGEM (3,0,290,"50.jpg");
	else if (e.score==60) IMAGEM (3,0,290,"60.jpg");
	else if (e.score==70) IMAGEM (3,0,290,"70.jpg");
	else if (e.score==80) IMAGEM (3,0,290,"80.jpg");
	else if (e.score==90) IMAGEM (3,0,290,"90.jpg");
	else if (e.score==100) IMAGEM (3,0,290,"100.jpg");
	
	int hs;
	int s[4];

	FILE *gamesave;
		gamesave=fopen("/tmp/score.txt","r+");
		
		if (gamesave!=NULL) { 
			
			hs=0;
			while (fscanf(gamesave,"%d\n",&s[hs])!=EOF){
				hs++;
			}
			for (int i=hs;i<4;i++)
				s[hs]=0;
			fclose(gamesave);
	}
	e.best_score=s[1];


	imprime_best_score(e);
}



/**
* Função que verifica se o jogador está na mesma posição do inimigo e ataca
*/
ESTADO atacar_inimigos (ESTADO e) {
	int pos = verifica_se_ataca(e);
	int vida = e.vida_inimigo[pos]-e.ataque_jog;
	
	if (pos!=-1) {
		
		if (vida <= 0) {
			e.num_inimigos--;
			e.mostra_sangue=1;
			e.sangue.x = e.inimigo[pos].x;
			e.sangue.y=e.inimigo[pos].y;
			e.inimigo[pos].x=e.inimigo[(int)e.num_inimigos].x;
			e.inimigo[pos].y=e.inimigo[(int)e.num_inimigos].y;
			e.inimigo_img[pos]=e.inimigo_img[(int)e.num_inimigos];
		}
		else {
			e.vida_inimigo[pos] -= e.ataque_jog;
		}

	}
return e;
}


/**
* Função que faz com que os inimigos ataquem o jogador.
*/
ESTADO inimigos_atacam(ESTADO e) {
	int ataca=verifica_alcance(e);

	if (ataca!=-1) {
		e.vida_jog-=10;
		e.mostra_vitima=1;
		e.atacado.x=e.inimigo[ataca].x;
		e.atacado.y=e.inimigo[ataca].y;
	}

	return e;
}


/**
* Função que lé o estado, se o estado começa sem argumentos, vai gerar um nivel aleatório.
*/

ESTADO ler_ficheiro(char *f) {
	ESTADO e;
	char texto[5000];

	FILE *gamesave = fopen("/tmp/gamesave.txt","r+");
	
	if (gamesave!=NULL) {
    	fgets(texto, 5000, gamesave);
    	e = str2estado(texto);
    	fclose(gamesave);
	} else {
		perror("erro: ");
		exit(1);
	}
    
    return e;
}


/**
* Função que lê o estado
*/
ESTADO ler_estado(){
	
	char *args = getenv("QUERY_STRING");
	char filename[1024]="/tmp/gamesave.txt";
	int novoX, novoY;
	
	if(strlen(args) == 0) return inicializar();
	
	sscanf(args, "%[^,],%d,%d", filename, &novoX, &novoY);
	ESTADO e = ler_ficheiro(filename);
	e = aplica_acao(e, novoX, novoY);
	
	if (e.chegou_saida==1 && (e.jog.x!=e.saida.x || e.jog.y!=e.saida.y)) e=inicializar();

	return e;
}


/**
* Função que quando chega a saída altera o estado
*/
ESTADO chegou_saida(ESTADO e) {
	e.num_inimigos=0;
		e.mostra_sangue=0;
		e.mostra_vitima=0;
		e.num_obstaculos=0;
		e.num_duffs=0;
		e.num_espadas=0;
		e.num_armadilhas=0;
		e.ataque_jog=5;
		e.chegou_saida=1;
		e.jog_img=1;
		e.donut_img=1;
		e.jog.x=9;
		e.jog.y=8;
		e.salta_casas=2;
		e.best_score=e.score;
	
return e;
}


/**
* Função que grava o score num ficheiro.
*/
void grava_score (ESTADO e) {
	
		srandom(time(NULL));
		int hs;
		int s[4];

		for (int i=0;i<4;i++) s[i]=0;
		
		FILE *gamesave;
		gamesave=fopen("/tmp/score.txt","r+");
		
		if (gamesave!=NULL) { 
			
			hs=0;
			while (fscanf(gamesave,"%d\n",&s[hs])!=EOF){
				hs++;
			}
			for (int i=hs;i<4;i++)
				s[hs]=0;
			fclose(gamesave);
	}
		
		gamesave=fopen("/tmp/score.txt","w");
		fprintf (gamesave,"%d\n",e.score );
		for (hs=1;hs<4;hs++){
			if (e.score<=s[hs])
				fprintf (gamesave,"%d\n",s[hs]);
			else{ 
				fprintf (gamesave,"%d\n",e.score);
				for(;hs<3;hs++){
					fprintf (gamesave,"%d\n",s[hs]);
					
				}
				
			}
		}

		fclose(gamesave);
}


/**
* Função que atualiza o estado
*/
ESTADO atualiza_o_estado(ESTADO e) {

	e=bebe_duff(e);
	e=usa_armadilha(e);
	e=atacar_inimigos(e);
	e=inimigos_movem(e,MAX_INIMIGOS);
	e=inimigos_atacam(e);
	e=aumenta_ataque(e);


return e;
}


/**
* Função que imprime o jogo do estado
*/
void imprime_jogo(ESTADO e) {
	imprime_informacao(e);
	imprime_inimigos(e);	
	imprime_obstaculos(e);
	imprime_donut(e);
	imprime_duffs(e);
	imprime_espada(e);
	imprime_armadilhas(e);
	imprime_jogador(e);
	imprime_vida(e);
	imprime_score(e);
	imprime_espada_uso(e);

}


/**
* Função que altera o valor do sangue
*/
ESTADO deve_imprimir_sangue(ESTADO e) {
	
	if (e.mostra_sangue==1) {
		imprime_sangue(e.sangue.x,e.sangue.y);
		e.mostra_sangue=0;
	}
	
	return e;
}


/**
* Função que altera o valor do ataque
*/
ESTADO mostra_ataque (ESTADO e) {

	if (e.mostra_vitima==1 && e.vida_jog>0) {
		imprime_ataque(e.atacado.x,e.atacado.y);
		e.mostra_vitima=0;
	}

	return e;
}



/**
* Função que desenha o estado
*/
void desenha_nivel(ESTADO e) {

	int x,y;
	srandom(time(NULL));
		
	e=atualiza_o_estado(e);

	COMECAR_HTML;
	ABRIR_SVG(1200,1500);


	for(y = 0; y < 10; y++)
		for(x = 0; x < 10; x++)
			imprime_casa(x, y);
	
	desenha_background();

	e=deve_imprimir_sangue(e);
	e=mostra_ataque(e);
	
	if (e.vida_jog==0) e=inicializar();

	if(e.jog.x == 0 && e.jog.y == 0) {
		IMAGEM(0,0,850,"Winner.jpg");
		e=chegou_saida(e);
		grava_score(e);

	}
	
 	imprime_jogo(e);

	if (e.mostra_duff==1) e.mostra_duff=0;
	if (e.salta_casas==1) e.salta_casas=0;
	escrever_ficheiro(e,"/tmp/gamesave.txt");

	FECHAR_SVG;
}


/**
* Função que inicia o jogo ou lé o estado atual
*/
void inicio(){
	char texto[5000];
	FILE *gamesave = fopen("/tmp/gamesave.txt","r+");
	
	if (gamesave!=NULL) {	
		fgets(texto, 5000, gamesave);
		fclose(gamesave);

	}
	ESTADO e = ler_estado(); 
	desenha_nivel(e);
}


/**
* Função main
*/
int main() {
	inicio();
	return 0;
}	