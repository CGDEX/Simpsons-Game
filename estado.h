#ifndef ___ESTADO_H___
#define ___ESTADO_H___

/**
@file estado.h
Definição do estado e das funções que convertem estados em strings e vice-versa
*/

/** \brief O nº máximo de inimigos */
#define MAX_INIMIGOS		10
/** \brief O número máximo de obstáculos */
#define MAX_OBSTACULOS		25
/** \brief O número máximo de duffs */
#define MAX_DUFFS			3
/** \brief O número máximo de armadilhas */
#define MAX_ARMADILHAS		3
/** \brief O número máximo de espadas */
#define MAX_ESPADAS			1
/**
\brief Estrutura que armazena uma posição
*/
typedef struct posicao {
	char x;
	char y;
} POSICAO;

/**
\brief Estrutura que armazena o estado do jogo
*/
typedef struct estado {
	/**\brief Posição do jogador */
	POSICAO jog;
	/**\brief Vida do jogador */
	int vida_jog;
	/**\brief Dano do ataque do jogador */
	int ataque_jog;
	/**\brief Número de inimigos existente no jogo */
	char num_inimigos;
	/**\brief Número de duffs existente no jogo */
	char num_duffs;
	/**\brief Número de obstáculos existente no jogo */
	char num_obstaculos;
	/**\brief Número de armadilhas existente no jogo */
	char num_armadilhas;
	/**\brief Número de espadas existente no jogo */
	char num_espadas;
	/**\brief Array com a posição dos inimigos */
	POSICAO inimigo[MAX_INIMIGOS];
	/**\brief A vida dos inimigos*/
	int vida_inimigo[MAX_INIMIGOS];
	/**\brief Ataque do inimigo */
	int ataque_ini;
	/**\brief Array com a posição dos obstáculos */
	POSICAO obstaculo[MAX_OBSTACULOS];
	/**\brief Array com a posição dos duffs */
	POSICAO duff[MAX_DUFFS];
	/**\brief Array com a posição das armadilhas */
	POSICAO armadilha[MAX_ARMADILHAS];
	/**\brief Array com a posição das espadas */
	POSICAO espada[MAX_ESPADAS];
	/**\brief Para saber quando deve mostrar a imagem do jogador ou não */
	int jog_img;
	/**\brief Muda a imagem do donut para uma com o next level */
	int donut_img;
	/**\brief Imagem de cada inimigo */
	int inimigo_img[MAX_INIMIGOS];
	/**\brief Verifica se chegou à saida, 0/1*/
	int chegou_saida;
	/**\brief Guarda o score */
	int score;
	/**\brief Guarda o melhor score */
	int best_score;
	/**\brief Para saber quando deve mostrar a imagem "Boa.jpg" */
	int mostra_duff;
	/**\brief Para saber quando deve saltar mais que uma casa */
	int salta_casas;
	/**\brief Para saber quando o ataque do jogador aumenta */
	int dano;
	/**\brief Para saber quando deve imprimir um quadrado vermelho */
	int mostra_sangue;
	/**\brief Para saber se o jogador foi atacado, caso for atacado imprime um quadrado laranja*/
	int mostra_vitima;
	/**\brief Para saber a posição do inimigo que atacou o jogador */
	POSICAO atacado;
	/**\brief Para saber a posição do inimigo que morreu */
	POSICAO sangue;
	/**\brief Coordenadas do donut à espera de ser comido */	
	POSICAO saida;
} ESTADO;


/**
\brief Função que converte um estado numa string
@param e O estado
@returns A string correspondente ao estado e
*/
char *estado2str(ESTADO e);

/**
\brief Função que converte uma string num estado 
@param argumentos Uma string contendo os argumentos passados à CGI
@returns O estado correspondente à string dos argumentos
*/
ESTADO str2estado(char *argumentos);

#endif
