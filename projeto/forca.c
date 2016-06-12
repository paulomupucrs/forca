/*
 * Autor: Anthony Jatobá
 * Adaptado por: Fernando Ken Soares <fernando.ken@acad.pucrs.br> e Paulo Vianna Mu <paulo.mu@acad.pucrs.br>
 * Data de início: 14 de abril
 * Projeto de P1 - CC 2015.1
 * Jogo da forca simples, com a possibilidade de usar palavras personalizadas.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "lib/funcoes.c"

int main() {
	//Variáveis de opção dos menus de jogo e de tema.
	int opc = OPC_INVALIDA;
	int tema = 0;

	//O programa é executado enquanto opc != OPC_SAIR (sair no menu);
	while (opc != OPC_SAIR) {
		inicializarJogo();

		opc = escolherModoDeJogo();

		switch (opc) {
			case OPC_PALAVRA_PREDEFINIDA: {
				tema = escolherTema();

				escolherPalavraAleatoria(tema);
				break;
			} case OPC_PALAVRA_PERSONALIZADA: {
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

