/*
 * Autor: Anthony Jatobá
 * Adaptado por: Fernando Ken Soares <fernando.ken@acad.pucrs.br> e Paulo Vianna Mu <paulo.mu@acad.pucrs.br>
 * Data de início: 14 de abril
 * Projeto de P1 - CC 2015.1
 * Jogo da forca simples, com a possibilidade de usar palavras personalizadas.
 */

#include <stdio.h>
#include "lib/data.h"

int main() {
	#if defined DEBUG_MODE
	char mensagem[128];
	inicializarDebug();
	#endif

	int opc = OPC_INVALIDA;
	int tema = 0;

	//O programa é executado enquanto opc != OPC_SAIR (sair no menu);
	while (opc != OPC_SAIR) {
		limparTela();
		inicializarJogo();

		opc = escolherModoDeJogo();

		#if defined DEBUG_MODE
		sprintf(mensagem, "Opção escolhida: %i", opc);
		debug(mensagem);
		#endif

		switch (opc) {
			case OPC_PALAVRA_PREDEFINIDA: {
				tema = escolherTema();

				#if defined DEBUG_MODE
				sprintf(mensagem, "Tema escolhido: %i", tema);
				debug(mensagem);
				#endif

				escolherPalavraAleatoria(tema, Forca.dica, Forca.palavra);
				break;
			} case OPC_PALAVRA_PERSONALIZADA: {
				escolherPalavraPersonalizada(Forca.dica, Forca.palavra);
				break;
			} case OPC_SAIR:
				break;
		}

		if (opc != OPC_SAIR) {
			#if defined DEBUG_MODE
			sprintf(mensagem, "Dica: %s | Palavra: %s", Forca.dica, Forca.palavra);
			debug(mensagem);
			#endif

			redefinirAcertos(Forca.acertos);

			// Enquanto o jogador não vencer e nem perder
			while (!Forca.venceu && !Forca.perdeu)
				mostrarForca();

			if (Forca.perdeu) {
				#if defined DEBUG_MODE
				debug("O jogador perdeu.");
				#endif
				printf("\n\n  Você perdeu! =(\n  A palavra era %s", Forca.palavra);
			} else if (Forca.venceu) {
				#if defined DEBUG_MODE
				debug("O jogador ganhou.");
				#endif
				printf("\n\n  Você ganhou! :D\n  A palavra era %s", Forca.palavra);
			}

			//Char usado pra voltar ao menu
			char voltarMenu;

			printf("\n\n  Digite alguma coisa para voltar ao menu: ");
			scanf(" %c", &voltarMenu);
		}
	}

	return 0;
}

