#include <stdio.h>
#include <stdlib.h>
extern int errno;

typedef struct {
	int hp;
	int posX;
	int posY;
	char nome[20];
}ESTADO;




int main () {
	FILE *f;
	ESTADO e;


	if ((f=fopen("config","r")) == NULL) {
		perror("Não conseguiu abrir o ficheiro");
		exit(1);	
	}
	fscanf(f,"%19s",e.nome);
	fscanf(f,"%d",&e.hp);
	printf("%d\n",e.hp);
	printf("%s\n",e.nome);
	fclose(f);

	return 0;
}