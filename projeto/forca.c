/*
 * Autor: Anthony Jatobá
 * Adaptado por: Fernando Ken Soares <fernando.ken@acad.pucrs.br> e Paulo Vianna Mu <paulo.mu@acad.pucrs.br>
 * Data de início: 14 de abril
 * Projeto de P1 - CC 2015.1
 * Jogo da forca simples, com a possibilidade de usar palavras personalizadas.
 */

// Descomentar a linha abaixo para ativar o modo de DEBUG do jogo.
#define DEBUG_MODE

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "lib/funcoes.c"

int main() {
	#if defined DEBUG_MODE
	inicializarDebug();
	#endif

	int opc = OPC_INVALIDA;
	int tema = 0;

	//O programa é executado enquanto opc != OPC_SAIR (sair no menu);
	while (opc != OPC_SAIR) {
		limparTela();
		inicializarJogo();

		opc = escolherModoDeJogo();

		switch (opc) {
			case OPC_PALAVRA_PREDEFINIDA: {
				tema = escolherTema();

				escolherPalavraAleatoria(tema, Forca.dica, Forca.palavra);
				break;
			} case OPC_PALAVRA_PERSONALIZADA: {
				escolherPalavraPersonalizada(Forca.dica, Forca.palavra);
				break;
			} case OPC_SAIR:
				break;
		}

		if (opc != OPC_SAIR) {
			redefinirAcertos(Forca.acertos);

			while (!Forca.venceu && !Forca.perdeu)
				mostrarForca();

			if (Forca.perdeu)
				printf("\n\n  Você perdeu! =(\n  A palavra era %s", Forca.palavra);
			else if (Forca.venceu)
				printf("\n\n  Você ganhou! :D\n  A palavra era %s", Forca.palavra);

			//Char usado pra voltar ao menu
			char voltarMenu;

			printf("\n\n  Digite alguma coisa para voltar ao menu!");
			scanf(" %c", &voltarMenu);
		}
	}

	return 0;
}

