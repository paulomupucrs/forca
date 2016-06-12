#include "data.h"
#include "funcoes.h"

char g_dica[MAX_TAMANHO_DICA];
char g_palavra[MAX_TAMANHO_PALAVRA];
char g_acertos[MAX_TAMANHO_PALAVRA];

char g_letrasUsadas[26];
int g_numLetrasUsadas = 0;

int g_erros = 0;

/*
	Função/Procedimento: int clean_stdin(void)
	Parâmetros: -
	Descrição: Limpa a entrada de dados do terminal.
	Retorna: 1 (sempre)
*/
int clean_stdin() {
	while (getchar() != '\n');

	return 1;
}

/*
	Procedimento: void limparTela(void)
	Parâmetros: -
	Descrição: Chama a função system com o comando "clear", para limpar o terminal.
	Retorna: -
*/

void limparTela(void) {
	system("clear");
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
	Procedimento: void inicializarJogo(void)
	Parâmetros: -
	Descrição: Limpa o conteúdo do terminal e reseta o vetor de letras utilizadas.
	Retorna: -
*/
void inicializarJogo(void) {
	limparTela();

	int i;

	//Limpa as letras usadas
	for (i = 0; i < strlen(g_letrasUsadas); i++)
		g_letrasUsadas[i] = '*';
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
		printf("\n\n 1 - Palavra pré-definida: ");
		printf("\n\n 2 - Palavra personalizada: ");
		printf("\n\n 3 - Sair: ");
		printf("\n\n Opção escolhida: ");
	} while (((scanf("%d%c", &opc, &c) != 2 || c != '\n') && clean_stdin()) || opc < OPC_PALAVRA_PREDEFINIDA || opc > OPC_SAIR);

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
		printf("\n\n 4 - Profissão: ");
		printf("\n\n 5 - Informática: ");
		printf("\n\n Tema escolhido: ");
	} while (((scanf("%d%c", &tema, &c) != 2 || c != '\n') && clean_stdin()) || tema < TEMA_ANIMAIS || tema > TEMA_INFORMATICA);

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
		case TEMA_ANIMAIS: {
			strcpy(g_dica, "Animais");
			//Seleciona uma palavra aleatória
			strcpy(g_palavra, animal[rand() % MAX_ITENS_POR_TEMA]);
			break;
		} case TEMA_COMIDA: {
			strcpy(g_dica, "Comida");
			strcpy(g_palavra, comida[rand() % MAX_ITENS_POR_TEMA]);
			break;
		} case TEMA_FRUTAS: {
			strcpy(g_dica, "Frutas");
			strcpy(g_palavra, fruta[rand() % MAX_ITENS_POR_TEMA]);
			break;
		} case TEMA_PROFISSAO: {
			strcpy(g_dica, "Profissão");
			strcpy(g_palavra, profissao[rand() % MAX_ITENS_POR_TEMA]);
			break;
		} case TEMA_INFORMATICA: {
			strcpy(g_dica, "Informática");
			strcpy(g_palavra, informatica[rand() % MAX_ITENS_POR_TEMA]);
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

/*
	Função: int verificarPalpite(char palpite)
	Parâmetros: char palpite - Palpite do jogador
	Descrição: Verifica se o palpite do jogador é válido.
	Retorna: 0 se é inválido, 1 se é válido.
*/
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

