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
 
//Dica da palavra para o jogador.
char dica[20];
//Palavra que o jogador deve acertar. Pode ser uma da lista acima ou personalizada.
char palavra[12];
//Variável usada para controle dos acertos do usuário. Cada letra acertada é colocada em sua posição nessa string. Quando <acertos> == <palavra>, o jogador acertou.
char acertos[12];

//Letras usadas pelo usuário e contador de letras usadas para repetições.
char letrasUsadas[26];
int numLetrasUsadas = 0;

//Contador de erros. 6 erros = derrota;
int erros = 0;

//Vetores com as palavras possíveis. A declaração do tamanho deve ser manual, pois C não permite que a constante seja declarada como dimensão do array.
const char animal[NUM_ITENS][12] = { "AVESTRUZ", "BORBOLETA", "CARANGUEJO",
			"ORANGOTANGO", "CROCODILO", "DROMEDARIO", "ROUXINOL", "CENTOPEIA",
			"GAFANHOTO", "PINTASSILGO", "HIPOPOTAMO", "LEOPARDO", "GUAXINIM",
			"JAGUATIRICA", "OSTRA", "MICO", "CHIMPANZE", "CARNEIRO", "GOLFINHO",
			"MINHOCA" };
const char comida[NUM_ITENS][12] = { "EMPADA", "FARINHA", "FEIJOADA", "COXINHA",
			"BRIGADEIRO", "CHURRASCO", "LASANHA", "MACARRONADA", "TORTA",
			"TORRADA", "PIZZA", "PANQUECA", "PIPOCA", "PAMONHA", "OVO",
			"ACARAJE", "CROISSANT", "HAMBURGUER", "BISCOITO", "BOLO" };
const char fruta[NUM_ITENS][12] = { "ABACATE", "BANANA", "CARAMBOLA", "DAMASCO", "FIGO",
			"GOIABA", "JABUTICABA", "KIWI", "LARANJA", "MELANCIA", "MANGA",
			"MARACUJA", "PESSEGO", "PITOMBA", "ROMA", "TANGERINA", "TOMATE",
			"TAMARINDO", "UVA", "UMBU" };
const char profissao[NUM_ITENS][12] = { "ADVOGADO", "BOMBEIRO", "CARPINTEIRO",
			"DESENHISTA", "ENGENHEIRO", "ESCRITOR", "FERREIRO", "GUARDA",
			"HISTORIADOR", "JORNALISTA", "LEILOEIRO", "MARINHEIRO", "OURIVES",
			"PROGRAMADOR", "PADEIRO", "RELOJOEIRO", "SILVICULTOR", "TRADUTOR",
			"VETERINARIO", "ZOOLOGO" };
const char informatica[NUM_ITENS][12] = { "LINUX", "WINDOWS", "C", "PROCESSADOR",
			"TECLADO", "MOUSE", "PROGRAMA", "ALGORITMO", "HACKER", "TOUCHPAD",
			"ASCII", "JAVA", "JAVASCRIPT", "PROGRAMADOR", "PYTHON", "INTERNET",
			"ROTEADOR", "SERVIDOR", "GOOGLE", "APPLE" };

void inicializarJogo(void) {
	system("clear");

	int i;

	//Limpa as letras usadas
	for (i = 0; i < strlen(letrasUsadas); i++)
		letrasUsadas[i] = '*';
}

/*		
	Função: int escolherModoDeJogo(void)
	Parâmetros: -
	Descrição: Mostra a tela de seleção do modo de jogo e solicita a opção do usuário.
	Retorna: O modo de jogo escolhido.
*/
int escolherModoDeJogo(void) {
	int opc;

	printf(
			"#################################### Forca #####################################");
	printf("\n\n Escolha o modo de jogo: ");
	printf("\n\n 1 - Palavras pré-definidas: ");
	printf("\n\n 2 - Palavra personalizada: ");
	printf("\n\n 3 - Sair: ");
	printf("\n\n Opção escolhida: ");
	scanf("%d", &opc);

	return opc;
}

/*
	Função: int escolherTema(void)
	Parâmetros: -
	Descrição: Mostra a tela de seleção de tema e solicita a opção do usuário.
	Retorna: O tema escolhido.
*/
int escolherTema(void) {
	int tema;

	system("clear");

	printf(
			"#################################### Forca #####################################");
	printf("\n\n Escolha o tema para jogar: ");
	printf("\n\n 1 - Animais: ");
	printf("\n\n 2 - Comida: ");
	printf("\n\n 3 - Frutas: ");
	printf("\n\n 4 - Profissao: ");
	printf("\n\n 5 - Informatica: ");
	printf("\n\n Tema escolhido: ");
	scanf(" %d", &tema);

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
			strcpy(dica, "Animal");
			//Seleciona uma palavra aleatória
			strcpy(palavra, animal[rand() % NUM_ITENS]);
			break;
		} case 2: {
			strcpy(dica, "Comida");
			strcpy(palavra, comida[rand() % NUM_ITENS]);
			break;
		} case 3: {
			strcpy(dica, "Fruta");
			strcpy(palavra, fruta[rand() % NUM_ITENS]);
			break;
		} case 4: {
			strcpy(dica, "Profissao");
			strcpy(palavra, profissao[rand() % NUM_ITENS]);
			break;
		} case 5: {
			strcpy(dica, "Informatica");
			strcpy(palavra, informatica[rand() % NUM_ITENS]);
			break;
		} default:
			break;
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
	scanf(" %[^\n]", dica);
	printf("\n Digite a palavra a ser adivinhada: ");
	scanf(" %[^\n]", palavra);

	int i;

	for (i = 0; i < strlen(palavra); i++)
		palavra[i] = toupper(palavra[i]);
}

/*
	Procedimento: void desenharBoneco(int erros)
	Parâmetros: int erros - Quantidade de erros da forca
	Descrição: Desenha o boneco na tela conforme a quantidade de erros.
	Retorna: -
*/
void desenharBoneco(int erros) {
	switch (erros) {
		case 0: {
			printf("\n\n");
			printf("  ##########***##  \n");
			printf("  ####            \n");
			printf("  ####            \n");
			printf("  ##              \n");
			printf("  ##              \n");
			printf("  ##              \n");
			printf("  ##              \n");
			printf("  ##              \n");
			printf("  ##              \n");
			printf("  ##              \n");
			printf("  ##              \n");
			printf("  ##              \n");
			printf("  ##              \n");
			break;
		} case 1: {
			printf("\n\n");
			printf("  ##########***##  \n");
			printf("  ####       *    \n");
			printf("  ####      ***   \n");
			printf("  ##       *o o*  \n");
			printf("  ##       * ^ *  \n");
			printf("  ##         *    \n");
			printf("  ##              \n");
			printf("  ##              \n");
			printf("  ##              \n");
			printf("  ##              \n");
			printf("  ##              \n");
			printf("  ##              \n");
			printf("  ##              \n");
			break;
		} case 2: {
			printf("\n\n");
			printf("  ##########***##  \n");
			printf("  ####       *    \n");
			printf("  ####      ***   \n");
			printf("  ##       *o o*  \n");
			printf("  ##       * ^ *  \n");
			printf("  ##         *    \n");
			printf("  ##         |    \n");
			printf("  ##         |    \n");
			printf("  ##         |    \n");
			printf("  ##         |    \n");
			printf("  ##         |    \n");
			printf("  ##              \n");
			printf("  ##              \n");
			break;
		} case 3: {
			printf("\n\n");
			printf("  ##########***##  \n");
			printf("  ####       *    \n");
			printf("  ####      ***   \n");
			printf("  ##       *o o*  \n");
			printf("  ##       * ^ *  \n");
			printf("  ##         *    \n");
			printf("  ##         |    \n");
			printf("  ##        /|    \n");
			printf("  ##       / |    \n");
			printf("  ##         |    \n");
			printf("  ##         |    \n");
			printf("  ##              \n");
			printf("  ##              \n");
			break;
		} case 4: {
			printf("\n\n");
			printf("  ##########***##  \n");
			printf("  ####       *    \n");
			printf("  ####      ***   \n");
			printf("  ##       *o o*  \n");
			printf("  ##       * ^ *  \n");
			printf("  ##         *    \n");
			printf("  ##         |    \n");
			printf("  ##        /|\\  \n");
			printf("  ##       / | \\ \n");
			printf("  ##         |    \n");
			printf("  ##         |    \n");
			printf("  ##              \n");
			printf("  ##              \n");
			break;
		} case 5: {
			printf("\n\n");
			printf("  ##########***##  \n");
			printf("  ####       *    \n");
			printf("  ####      ***   \n");
			printf("  ##       *o o*  \n");
			printf("  ##       * ^ *  \n");
			printf("  ##         *    \n");
			printf("  ##         |    \n");
			printf("  ##        /|\\  \n");
			printf("  ##       / | \\ \n");
			printf("  ##         |    \n");
			printf("  ##         |    \n");
			printf("  ##        /     \n");
			printf("  ##       /      \n");
			break;
		} case 6: {
			printf("\n\n");
			printf("  ##########***##  \n");
			printf("  ####       *    \n");
			printf("  ####      ***   \n");
			printf("  ##       *X X*  \n");
			printf("  ##       * ^ *  \n");
			printf("  ##         *    \n");
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
	for (i = 0; i < strlen(palavra); i++) {
		if (acertos[i] == '*')
			printf("_ ");
		else
			printf("%c ", acertos[i]);
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
	for (i = 0; i < strlen(palavra); i++)
		acertos[i] = '*';

	acertos[strlen(palavra)] = '\0';
}

/*
	Procedimento: void mostrarForca(void)
	Parâmetros:	-
	Descrição: Mostra a forca na tela (as letras utilizadas, o boneco, a palavra, etc).
	Retorna: -
*/
void mostrarForca(void) {
	system("clear");

	printf(
			"#################################### Forca #####################################");
	printf("\n\n  Dica: %s   Letras usadas: ", dica);

	int i;

	for (i = 0; i < numLetrasUsadas; i++)
		printf("%c ", letrasUsadas[i]);

	desenharBoneco(erros);
	desenharPalavra();

	if (strcmp(palavra, acertos) != 0 && erros != 6) {
		//Palpite do jogador.
		char palpite;

		printf("\n\n  Digite seu palpite: ");
		scanf(" %c", &palpite);
		palpite = toupper(palpite);

		int usada = 0;

		//checa se a letra já foi usada
		for (i = 0; i < 26; i++) {
			if (letrasUsadas[i] == palpite)
				usada = 1;
		}

		//Se não foi usada
		if (usada == 0) {
			letrasUsadas[numLetrasUsadas] = palpite;
			numLetrasUsadas++;

			//Variável de controle; 0 = não contem o
			int contemPalpite = 0;

			//Verifica se a palavra contém o palpite do usuário. A variável contemPalpite é usada para o controle dos erros
			for (i = 0; i < strlen(palavra); i++) {
				if (palpite == palavra[i]) {
					acertos[i] = palpite;
					contemPalpite = 1;
				}
			}

			if (contemPalpite == 0)
				erros++;
		}

	}
}

int main() {
	//Variáveis de opção dos menus de jogo e de tema.
	int opc = OPC_NEM;
	int tema = 0;

	//O programa é executado enquanto opc != OPC_SAIR (sair no menu);
	while (opc != OPC_SAIR) {
		do {
			inicializarJogo();

			opc = escolherModoDeJogo();

			switch (opc) {
				case OPC_PREDEF: {
					do
						tema = escolherTema();
					while (tema < 1 || tema > 5);

					escolherPalavraAleatoria(tema);
					break;
				} case OPC_PERS: {
					escolherPalavraPersonalizada();
					break;
				} case OPC_SAIR:
					break;
			}
		} while (opc != OPC_PREDEF && opc != OPC_PERS && opc != OPC_SAIR);

		if (opc != OPC_SAIR) {
			resetarAcertosDaPalavra();

			while (strcmp(palavra, acertos) != 0 && erros != 6)
				mostrarForca();

			if (erros == 6)
				printf("\n  Você perdeu! =(\n  A palavra era %s", palavra);
			else
				printf("\n  Você ganhou! :D A palavra era %s", palavra);

			//Char usado pra voltar ao menu
			char voltarMenu;

			printf("\n\n  Digite alguma coisa para voltar ao menu!");
			scanf(" %c", &voltarMenu);
		}
	}

	return 0;
}
