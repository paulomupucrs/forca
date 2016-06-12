#include "data.h"
#include "funcoes.h"

struct DadosDaForca Forca;

#if defined DEBUG_MODE
char mensagem[128];
#endif

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
	Procedimento: void redefinirAcertos(char *acertos)
	Parâmetros: char *acertos - Ponteiro da variável que armazena os acertos
	Descrição: Preenche a variável de acertos com asteriscos, que representam caracteres desconhecidos.
	Retorna: -
*/
void redefinirAcertos(char *acertos) {
	int i, len;

	for (i = 0, len = strlen(Forca.palavra); i < len; i++)
		acertos[i] = '*';

	acertos[len] = '\0';
}

/*
	Procedimento: void inicializarJogo(void)
	Parâmetros: -
	Descrição: Reseta as variáveis para começar o jogo do 0;
	Retorna: -
*/
void inicializarJogo(void) {
	int i;

	Forca.numLetrasUsadas = 0;
	Forca.erros = 0;
	Forca.venceu = 0;
	Forca.perdeu = 0;

	for (i = 0; i < strlen(Forca.letrasUsadas); i++)
		Forca.letrasUsadas[i] = '*';
}

/*		
	Função/Procedimento: int escolherModoDeJogo(void)
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
	Função/Procedimento: int escolherTema(void)
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
	Procedimento: void escolherPalavraAleatoria(int tema, char *dica, char *palavra)
	Parâmetros:
			int tema - identificador do tema escolhido
			char *dica - Ponteiro da variável que armazena a dica
			char *palavra - Ponteiro da variável que armazena a palavra
	Descrição: Pega uma palavra aleatória de acordo com o tela escolhido.
	Retorna: -
*/
void escolherPalavraAleatoria(int tema, char *dica, char *palavra) {
//	srand(time(NULL));

	switch (tema) {
		case TEMA_ANIMAIS: {
			strcpy(dica, "Animais");
			strcpy(palavra, animal[rand() % MAX_ITENS_POR_TEMA]);
			break;
		} case TEMA_COMIDA: {
			strcpy(dica, "Comida");
			strcpy(palavra, comida[rand() % MAX_ITENS_POR_TEMA]);
			break;
		} case TEMA_FRUTAS: {
			strcpy(dica, "Frutas");
			strcpy(palavra, fruta[rand() % MAX_ITENS_POR_TEMA]);
			break;
		} case TEMA_PROFISSAO: {
			strcpy(dica, "Profissão");
			strcpy(palavra, profissao[rand() % MAX_ITENS_POR_TEMA]);
			break;
		} case TEMA_INFORMATICA: {
			strcpy(dica, "Informática");
			strcpy(palavra, informatica[rand() % MAX_ITENS_POR_TEMA]);
			break;
		}
	}
}

/*
	Procedimento: void escolherPalavraPersonalizada(char *dica, char *palavra)
	Parâmetros:
			char *dica - Ponteiro da variável que armazena a dica
			char *palavra - Ponteiro da variável que armazena a palavra	
	Descrição: Solicita ao usuário para digitar a dica e a palavra a ser advinhada, armazenando ambas na memória.
	Retorna: -
*/
void escolherPalavraPersonalizada(char *dica, char *palavra) {
	printf("\n Digite a dica: ");
	scanf(" %[^\n]", dica);
	printf("\n Digite a palavra a ser adivinhada: ");
	scanf(" %[^\n]", palavra);

	// Limpa a entrada de dados
	clean_stdin();

	int i;

	for (i = 0; i < strlen(palavra); i++)
		palavra[i] = toupper(palavra[i]);
}

/*
	Função: int verificarPalpite(char palpite)
	Parâmetros: char palpite - Palpite do jogador
	Descrição: Verifica se o palpite do jogador é válido.
	Retorna: 0 se é inválido, 1 se é válido.
*/
int verificarPalpite(char palpite) {
	if ((palpite > 64 && palpite < 91) || (palpite > 96 && palpite < 123))
		return 1;

	return 0;
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
	// Desenha o cabeçalho
	printf("\n\n");
	printf("  ##########***##  \n");	
	
	// Desenha a cabeça
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

	// Desenha o corpo
	int i;

	switch (erros) {
		case 0: {	
			printf("  ####              \n");
			printf("  ####              \n");
		
			for(i = 0; i < 9; i ++)
				printf("  ##              \n");

			break;
		} case 1: {
			for(i = 0; i < 6; i ++)
				printf("  ##              \n");

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

	// Desenha a base
	printf("  ##               \n");
	printf("  #######################\n\n  ");
}

/*
	Procedimento: void desenharPalavra(char *palavra)
	Parâmetros: char *palavra - Ponteiro da palavra a ser desenhada
	Descrição: Desenha os espaços e as letras corretas na tela.
	Retorna: -
*/
void desenharPalavra(char *palavra) {
	int i;

	for (i = 0; i < strlen(palavra); i++) {
		if (Forca.acertos[i] == '*')
			printf("_ ");
		else 
			printf("%c ", Forca.acertos[i]);
	}
}

/*
	Procedimento: void mostrarForca(void)
	Parâmetros:	-
	Descrição: Mostra a forca na tela (as letras utilizadas, o boneco, a palavra, etc).
	Retorna: -
*/
void mostrarForca(void) {
	int i;

	limparTela();

	// Desenha o cabeçalho, a dica e as letras já utilizadas
	printf(
			"#################################### Forca #####################################");
	printf("\n\n  Dica: %s   Letras usadas: ", Forca.dica);

	for (i = 0; i < Forca.numLetrasUsadas; i++)
		printf("%c ", Forca.letrasUsadas[i]);

	// Desenha o boneco e as posições da palavra
	desenharBoneco(Forca.erros);
	desenharPalavra(Forca.palavra);

	#if defined DEBUG_MODE
	sprintf(mensagem, "Erros: %i", Forca.erros);
	debug(mensagem);
	#endif

	// Se a quantidade de erros é diferente de 6...
	if (Forca.erros != 6) {
		// Se o jogador ainda não acertou a palavra
		if (strcmp(Forca.palavra, Forca.acertos) != 0) {
			// Obtém o palpite do jogador
			char palpite = lerPalpite();
			int usada = 0;

			#if defined DEBUG_MODE
			sprintf(mensagem, "Palpite: %c", palpite);
			debug(mensagem);
			#endif

			// Verifica se a letra já foi usada
			for (i = 0; i < MAX_LETRAS; i++) {
				if (Forca.letrasUsadas[i] == palpite) {
					usada = 1;
					break;
				}
			}

			// Se não foi usada...
			if (!usada) {
				#if defined DEBUG_MODE
				debug("Palpite ainda não foi utilizado. Verificando se a palavra contém o palpite...");
				#endif
				int contemPalpite = 0;

				// Armazena a letra no vetor de letras utilizadas, na primeira posição não-ocupada
				Forca.letrasUsadas[Forca.numLetrasUsadas] = palpite;
				// Incrementa a posição
				Forca.numLetrasUsadas++;

				// Verifica se a palavra contém o palpite do jogador
				for (i = 0; i < strlen(Forca.palavra); i++) {
					if (palpite == Forca.palavra[i]) {
						// Caso contenha, marca o acerto
						Forca.acertos[i] = palpite;
						contemPalpite = 1;
					}
				}

				// Caso a palavra não tenha o palpite do jogador, incrementa a quantidade de erros
				if (!contemPalpite) {
					#if defined DEBUG_MODE
					debug("A palavra não contém o palpite do jogador.");
					#endif
					Forca.erros++;
				}
				#if defined DEBUG_MODE
				else
					debug("A palavra contém o palpite do jogador.");
				#endif
			}
			#if defined DEBUG_MODE
			else
				debug("Palpite já utilizado.");
			#endif
		} else
			Forca.venceu = 1;
	} else
		Forca.perdeu = 1;
}

#if defined DEBUG_MODE
void debug(char *mensagem) {
	char escrever[135];

	sprintf(escrever, "%s\n", mensagem);

	FILE *log = fopen("log.txt", "a");
	fputs(escrever, log);
	fclose(log);
}

/*
	Procedimento: void inicializarDebug(void)
	Parâmetros: -
	Descrição: Inicializa o modo de debug do jogo, mostrando todas as palavras disponíveis em suas categorias.
	Retorna: -
*/
void inicializarDebug(void) {
	char c;
	int i;

	printf("\n===========[MODO DE DEBUG]===========\n");

	printf("[Tema: ANIMAIS]\n");
	for (i = 0; i < MAX_ITENS_POR_TEMA; i++)
		printf("%s ", animal[i]);

	printf("\n\n");

	printf("[Tema: COMIDA]\n");
	for (i = 0; i < MAX_ITENS_POR_TEMA; i++)
		printf("%s ", comida[i]);

	printf("\n\n");

	printf("[Tema: FRUTAS]\n");
	for (i = 0; i < MAX_ITENS_POR_TEMA; i++)
		printf("%s ", fruta[i]);

	printf("\n\n");

	printf("[Tema: PROFISSÃO]\n");
	for (i = 0; i < MAX_ITENS_POR_TEMA; i++)
		printf("%s ", profissao[i]);

	printf("\n\n");

	printf("[Tema: INFORMATICA]\n");
	for (i = 0; i < MAX_ITENS_POR_TEMA; i++)
		printf("%s ", informatica[i]);

	printf("\n\nDigite algum caractere e pressione ENTER para continuar: ");
	scanf("%c", &c);
}
#endif

