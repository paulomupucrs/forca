// Descomentar a linha abaixo para ativar o modo de DEBUG do jogo.
#define DEBUG_MODE

#define OPC_INVALIDA			0
#define OPC_PALAVRA_PREDEFINIDA		1
#define OPC_PALAVRA_PERSONALIZADA	2
#define OPC_SAIR			3

#define MAX_ITENS_POR_TEMA 		20
#define MAX_LETRAS			26
#define MAX_TAMANHO_DICA		20
#define MAX_TAMANHO_PALAVRA		12

#define TEMA_INVALIDO			0
#define TEMA_ANIMAIS			1
#define TEMA_COMIDA			2
#define TEMA_FRUTAS			3
#define TEMA_PROFISSAO			4
#define TEMA_INFORMATICA		5

struct DadosDaForca {
	char dica[MAX_TAMANHO_DICA];
	char palavra[MAX_TAMANHO_PALAVRA];
	char acertos[MAX_TAMANHO_PALAVRA];
	char letrasUsadas[MAX_LETRAS];
	int numLetrasUsadas;
	int erros;
	int venceu;
	int perdeu;
};
extern struct DadosDaForca Forca;

static const char animal[MAX_ITENS_POR_TEMA][MAX_TAMANHO_PALAVRA] = { "AVESTRUZ", "BORBOLETA", "CARANGUEJO",
			"ORANGOTANGO", "CROCODILO", "DROMEDARIO", "ROUXINOL", "CENTOPEIA",
			"GAFANHOTO", "PINTASSILGO", "HIPOPOTAMO", "LEOPARDO", "GUAXINIM",
			"JAGUATIRICA", "OSTRA", "MICO", "CHIMPANZE", "CARNEIRO", "GOLFINHO",
			"MINHOCA" };

static const char comida[MAX_ITENS_POR_TEMA][MAX_TAMANHO_PALAVRA] = { "EMPADA", "FARINHA", "FEIJOADA", "COXINHA",
			"BRIGADEIRO", "CHURRASCO", "LASANHA", "MACARRONADA", "TORTA",
			"TORRADA", "PIZZA", "PANQUECA", "PIPOCA", "PAMONHA", "OVO",
			"ACARAJE", "CROISSANT", "HAMBURGUER", "BISCOITO", "BOLO" };

static const char fruta[MAX_ITENS_POR_TEMA][MAX_TAMANHO_PALAVRA] = { "ABACATE", "BANANA", "CARAMBOLA", "DAMASCO", "FIGO",
			"GOIABA", "JABUTICABA", "KIWI", "LARANJA", "MELANCIA", "MANGA",
			"MARACUJA", "PESSEGO", "PITOMBA", "ROMA", "TANGERINA", "TOMATE",
			"TAMARINDO", "UVA", "UMBU" };

static const char profissao[MAX_ITENS_POR_TEMA][MAX_TAMANHO_PALAVRA] = { "ADVOGADO", "BOMBEIRO", "CARPINTEIRO",
			"DESENHISTA", "ENGENHEIRO", "ESCRITOR", "FERREIRO", "GUARDA",
			"HISTORIADOR", "JORNALISTA", "LEILOEIRO", "MARINHEIRO", "OURIVES",
			"PROGRAMADOR", "PADEIRO", "RELOJOEIRO", "SILVICULTOR", "TRADUTOR",
			"VETERINARIO", "ZOOLOGO" };

static const char informatica[MAX_ITENS_POR_TEMA][MAX_TAMANHO_PALAVRA] = { "LINUX", "WINDOWS", "C", "PROCESSADOR",
			"TECLADO", "MOUSE", "PROGRAMA", "ALGORITMO", "HACKER", "TOUCHPAD",
			"ASCII", "JAVA", "JAVASCRIPT", "PROGRAMADOR", "PYTHON", "INTERNET",
			"ROTEADOR", "SERVIDOR", "GOOGLE", "APPLE" };

extern int clean_stdin(void);
extern void limparTela(void);

extern void redefinirAcertos(char *);
extern void inicializarJogo(void);

extern int escolherModoDeJogo(void);
extern int escolherTema(void);
extern void escolherPalavraAleatoria(int, char *, char *);
extern void escolherPalavraPersonalizada(char *, char *);

extern int verificarPalpite(char);
extern char lerPalpite(void);

extern void desenharBoneco(int);
extern void desenharPalavra(char *);

extern void mostrarForca(void);

#if defined DEBUG_MODE
extern void debug(char *);
extern void inicializarDebug(void);
#endif
