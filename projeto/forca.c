/*
 * Autor: Anthony Jatobá
 * Adaptado por: Fernando Ken Soares <fernando.ken@acad.pucrs.br> e Paulo Vianna Mu <paulo.mu@acad.pucrs.br>
 * Data de início: 14 de abril
 * Projeto de P1 - CC 2015.1
 * Jogo da forca simples, com a possibilidade de usar palavras personalizadas.
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define NUM_ITENS 20
#define	OPC_NEM 0
#define OPC_PREDEF 1
#define OPC_PERS 2
#define OPC_SAIR 3
#define MAX_TAMANHO_PALAVRA 12

//Dica da palavra para o jogador.
char g_dica[20];
//Palavra que o jogador deve acertar. Pode ser uma da lista acima ou personalizada.
char g_palavra[MAX_TAMANHO_PALAVRA];
//Variável usada para controle dos acertos do usuário. Cada letra acertada é colocada em sua posição nessa string. Quando <acertos> == <palavra>, o jogador acertou.
char g_acertos[MAX_TAMANHO_PALAVRA];

//Letras usadas pelo usuário e contador de letras usadas para repetições.
char g_letrasUsadas[26];
int g_numLetrasUsadas = 0;

//Contador de erros. 6 erros = derrota;
int g_erros = 0;

//Vetores com as palavras possíveis. A declaração do tamanho deve ser manual, pois C não permite que a constante seja declarada como dimensão do array.
const char animal[NUM_ITENS][MAX_TAMANHO_PALAVRA] = { "AVESTRUZ", "BORBOLETA", "CARANGUEJO",
			"ORANGOTANGO", "CROCODILO", "DROMEDARIO", "ROUXINOL", "CENTOPEIA",
			"GAFANHOTO", "PINTASSILGO", "HIPOPOTAMO", "LEOPARDO", "GUAXINIM",
			"JAGUATIRICA", "OSTRA", "MICO", "CHIMPANZE", "CARNEIRO", "GOLFINHO",
			"MINHOCA" };
const char comida[NUM_ITENS][MAX_TAMANHO_PALAVRA] = { "EMPADA", "FARINHA", "FEIJOADA", "COXINHA",
			"BRIGADEIRO", "CHURRASCO", "LASANHA", "MACARRONADA", "TORTA",
			"TORRADA", "PIZZA", "PANQUECA", "PIPOCA", "PAMONHA", "OVO",
			"ACARAJE", "CROISSANT", "HAMBURGUER", "BISCOITO", "BOLO" };
const char fruta[NUM_ITENS][MAX_TAMANHO_PALAVRA] = { "ABACATE", "BANANA", "CARAMBOLA", "DAMASCO", "FIGO",
			"GOIABA", "JABUTICABA", "KIWI", "LARANJA", "MELANCIA", "MANGA",
			"MARACUJA", "PESSEGO", "PITOMBA", "ROMA", "TANGERINA", "TOMATE",
			"TAMARINDO", "UVA", "UMBU" };
const char profissao[NUM_ITENS][MAX_TAMANHO_PALAVRA] = { "ADVOGADO", "BOMBEIRO", "CARPINTEIRO",
			"DESENHISTA", "ENGENHEIRO", "ESCRITOR", "FERREIRO", "GUARDA",
			"HISTORIADOR", "JORNALISTA", "LEILOEIRO", "MARINHEIRO", "OURIVES",
			"PROGRAMADOR", "PADEIRO", "RELOJOEIRO", "SILVICULTOR", "TRADUTOR",
			"VETERINARIO", "ZOOLOGO" };
const char informatica[NUM_ITENS][MAX_TAMANHO_PALAVRA] = { "LINUX", "WINDOWS", "C", "PROCESSADOR",
			"TECLADO", "MOUSE", "PROGRAMA", "ALGORITMO", "HACKER", "TOUCHPAD",
			"ASCII", "JAVA", "JAVASCRIPT", "PROGRAMADOR", "PYTHON", "INTERNET",
			"ROTEADOR", "SERVIDOR", "GOOGLE", "APPLE" };

void limparTela(void) {
	system("clear");
}

void inicializarJogo(void) {
	limparTela();

	int i;

	//Limpa as letras usadas
	for (i = 0; i < strlen(g_letrasUsadas); i++)
		g_letrasUsadas[i] = '*';
}

int clean_stdin() {
	while (getchar() != '\n');

	return 1;
}

/*		
	Procedimento: int escolherModoDeJogo(void)
	Parâmetros: -
	Descrição: Mostra a tela de seleção do modo de jogo e solicita a opção do usuário.
	Retorna: O modo de jogo escolhido.
*/
int escolherModoDeJogo(void) {
	int opc;
	char c;

	do {
		limparTela();

		printf(
				"#################################### Forca #####################################");
		printf("\n\n Escolha o modo de jogo: ");
		printf("\n\n 1 - Palavras pré-definidas: ");
		printf("\n\n 2 - Palavra personalizada: ");
		printf("\n\n 3 - Sair: ");
		printf("\n\n Opção escolhida: ");
	} while (((scanf("%d%c", &opc, &c) != 2 || c != '\n') && clean_stdin()) || opc < OPC_PREDEF || opc > OPC_SAIR);

	return opc;
}

/*
	Procedimento: int escolherTema(void)
	Parâmetros: -
	Descrição: Mostra a tela de seleção de tema e solicita a opção do usuário.
	Retorna: O tema escolhido.
*/
int escolherTema(void) {
	int tema;
	char c;

	do {
		limparTela();

		printf(
			"#################################### Forca #####################################");
		printf("\n\n Escolha o tema para jogar: ");
		printf("\n\n 1 - Animais: ");
		printf("\n\n 2 - Comida: ");
		printf("\n\n 3 - Frutas: ");
		printf("\n\n 4 - Profissao: ");
		printf("\n\n 5 - Informatica: ");
		printf("\n\n Tema escolhido: ");
	} while (((scanf("%d%c", &tema, &c) != 2 || c != '\n') && clean_stdin()) || tema < 1 || tema > 5);

	return tema;
}

/*
	Procedimento: void escolherPalavraAleatoria(int tema)
	Parâmetros: int tema - identificador do tema escolhido
	Descrição: Pega uma palavra aleatória de acordo com o tela escolhido.
	Retorna: -
*/
void escolherPalavraAleatoria(int tema) {
	//Para gerar números aleatórios
	srand(time(NULL));

	switch (tema) {
		case 1: {
			strcpy(g_dica, "Animal");
			//Seleciona uma palavra aleatória
			strcpy(g_palavra, animal[rand() % NUM_ITENS]);
			break;
		} case 2: {
			strcpy(g_dica, "Comida");
			strcpy(g_palavra, comida[rand() % NUM_ITENS]);
			break;
		} case 3: {
			strcpy(g_dica, "Fruta");
			strcpy(g_palavra, fruta[rand() % NUM_ITENS]);
			break;
		} case 4: {
			strcpy(g_dica, "Profissao");
			strcpy(g_palavra, profissao[rand() % NUM_ITENS]);
			break;
		} case 5: {
			strcpy(g_dica, "Informatica");
			strcpy(g_palavra, informatica[rand() % NUM_ITENS]);
			break;
		}
	}
}

/*
	Procedimento: void escolherPalavraPersonalizada(void)
	Parâmetros: -
	Descrição: Solicita ao usuário para digitar a dica e a palavra a ser advinhada, armazenando ambas na memória.
	Retorna: -
*/
void escolherPalavraPersonalizada(void) {
	printf("\n Digite a dica: ");
	scanf(" %[^\n]", g_dica);
	printf("\n Digite a palavra a ser adivinhada: ");
	scanf(" %[^\n]", g_palavra);

	int i;

	for (i = 0; i < strlen(g_palavra); i++)
		g_palavra[i] = toupper(g_palavra[i]);
}

int verificarPalpite(char palpite) {
	int retorna;

	switch (palpite) {
		case 65 ... 90: {
			retorna = 1;
			break;
		} case 97 ... 122: {
			retorna = 1;
			break;
		} default: {
			retorna = 0;
			break;
		}
	}

	return retorna;
}

/*
	Procedimento: char lerPalpite(void)
	Parâmetros: -
	Descrição: Lê um palpite inserido pelo usuário e retorna o caractere digitado.
	Retorna: O caractere digitado.
*/
char lerPalpite(void) {
	char palpite;
	char c;

	int verificar = -1;
	do {
		printf("\n\n  Digite seu palpite: ");
	} while( ((scanf("%c%c", &palpite, &c) != 2 || c != '\n') && clean_stdin()) || !verificarPalpite(palpite));

	palpite = toupper(palpite);

	return palpite;
}

/*
	Procedimento: void desenharBoneco(int erros)
	Parâmetros: int erros - Quantidade de erros da forca
	Descrição: Desenha o boneco na tela conforme a quantidade de erros.
	Retorna: -
*/
void desenharBoneco(int erros) {
	printf("\n\n");
	printf("  ##########***##  \n");	
	
	if (erros > 0 && erros <= 5) {
		printf("  ####       *    \n");
		printf("  ####      ***   \n");
		printf("  ##       *o o*  \n");
		printf("  ##       * ^'*  \n");
		printf("  ##         *    \n");
	} else if (erros == 6) {
		printf("  ####       *    \n");
		printf("  ####      ***   \n");
		printf("  ##       *X X*  \n");
		printf("  ##       * ^ *  \n");
		printf("  ##         *    \n");
	}

	int i;

	switch (erros) {
		case 0: {	
			printf("  ####              \n");
			printf("  ####              \n");		
			for(i = 0; i < 9; i ++) {
				printf("  ##              \n");
			}
			break;
		} case 1: {
			for(i = 0; i < 6; i ++) {
				printf("  ##              \n");
			}			
			break;
		} case 2: {
			printf("  ##         |    \n");
			printf("  ##         |    \n");
			printf("  ##         |    \n");
			printf("  ##         |    \n");
			printf("  ##         |    \n");
			printf("  ##              \n");
			printf("  ##              \n");
			break;
		} case 3: {
			printf("  ##         |    \n");
			printf("  ##        /|    \n");
			printf("  ##       / |    \n");
			printf("  ##         |    \n");
			printf("  ##         |    \n");
			printf("  ##              \n");
			printf("  ##              \n");
			break;
		} case 4: {
			printf("  ##         |    \n");
			printf("  ##        /|\\  \n");
			printf("  ##       / | \\ \n");
			printf("  ##         |    \n");
			printf("  ##         |    \n");
			printf("  ##              \n");
			printf("  ##              \n");
			break;
		} case 5: {
			printf("  ##         |    \n");
			printf("  ##        /|\\  \n");
			printf("  ##       / | \\ \n");
			printf("  ##         |    \n");
			printf("  ##         |    \n");
			printf("  ##        /     \n");
			printf("  ##       /      \n");
			break;
		} case 6: {

			printf("  ##         |    \n");
			printf("  ##        /|\\   \n");
			printf("  ##       / | \\  \n");
			printf("  ##         |    \n");
			printf("  ##         |    \n");
			printf("  ##        / \\   \n");
			printf("  ##       /   \\  \n");
			break;
		}
	}

	printf("  ##               \n");
	printf("  #######################\n\n  ");
}

/*
	Procedimento: void desenharPalavra(void)
	Parâmetros: -
	Descrição: Desenha os espaços e as letras corretas na tela.
	Retorna: -
*/
void desenharPalavra(void) {
	int i;

	//Desenha os espaços para as letras
	for (i = 0; i < strlen(g_palavra); i++) {
		if (g_acertos[i] == '*')
			printf("_ ");
		else
			printf("%c ", g_acertos[i]);
	}
}

/*
	Procedimento: void resetarAcertosDaPalavra(void)
	Parâmetros: -
	Descrição: Reseta as letras que o jogador acertou da palavra.
	Retorna: -
*/
void resetarAcertosDaPalavra(void) {
	int i;

	//Preenche a variável acertos com asteriscos, que representam caracteres desconhecidos
	for (i = 0; i < strlen(g_palavra); i++)
		g_acertos[i] = '*';

	g_acertos[strlen(g_palavra)] = '\0';
}

/*
	Procedimento: void mostrarForca(void)
	Parâmetros:	-
	Descrição: Mostra a forca na tela (as letras utilizadas, o boneco, a palavra, etc).
	Retorna: -
*/
void mostrarForca(void) {
	limparTela();

	printf(
			"#################################### Forca #####################################");
	printf("\n\n  Dica: %s   Letras usadas: ", g_dica);

	int i;

	for (i = 0; i < g_numLetrasUsadas; i++)
		printf("%c ", g_letrasUsadas[i]);

	desenharBoneco(g_erros);
	desenharPalavra();

	if (strcmp(g_palavra, g_acertos) != 0 && g_erros != 6) {
		//Palpite do jogador.
		char palpite = lerPalpite();

		int usada = 0;

		//checa se a letra já foi usada
		for (i = 0; i < 26; i++) {
			if (g_letrasUsadas[i] == palpite)
				usada = 1;
		}

		//Se não foi usada
		if (usada == 0) {
			g_letrasUsadas[g_numLetrasUsadas] = palpite;
			g_numLetrasUsadas++;

			//Variável de controle; 0 = não contem o
			int contemPalpite = 0;

			//Verifica se a palavra contém o palpite do usuário. A variável contemPalpite é usada para o controle dos erros
			for (i = 0; i < strlen(g_palavra); i++) {
				if (palpite == g_palavra[i]) {
					g_acertos[i] = palpite;
					contemPalpite = 1;
				}
			}

			if (contemPalpite == 0)
				g_erros++;
		}

	}
}

int main() {
	//Variáveis de opção dos menus de jogo e de tema.
	int opc = OPC_NEM;
	int tema = 0;

	//O programa é executado enquanto opc != OPC_SAIR (sair no menu);
	while (opc != OPC_SAIR) {
		inicializarJogo();

		opc = escolherModoDeJogo();

		switch (opc) {
			case OPC_PREDEF: {
				tema = escolherTema();

				escolherPalavraAleatoria(tema);
				break;
			} case OPC_PERS: {
				escolherPalavraPersonalizada();
				break;
			} case OPC_SAIR:
				break;
		}

		if (opc != OPC_SAIR) {
			resetarAcertosDaPalavra();

			while (strcmp(g_palavra, g_acertos) != 0 && g_erros != 6)
				mostrarForca();

			if (g_erros == 6)
				printf("\n  Você perdeu! =(\n  A palavra era %s", g_palavra);
			else
				printf("\n  Você ganhou! :D A palavra era %s", g_palavra);

			//Char usado pra voltar ao menu
			char voltarMenu;

			printf("\n\n  Digite alguma coisa para voltar ao menu!");
			scanf(" %c", &voltarMenu);
		}
	}

	return 0;
}
