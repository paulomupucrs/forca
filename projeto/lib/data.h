#define OPC_INVALIDA			0
#define OPC_PALAVRA_PREDEFINIDA		1
#define OPC_PALAVRA_PERSONALIZADA	2
#define OPC_SAIR			3

#define MAX_ITENS_POR_TEMA 		20
#define MAX_TAMANHO_DICA		20
#define MAX_TAMANHO_PALAVRA		12

#define TEMA_INVALIDO			0
#define TEMA_ANIMAIS			1
#define TEMA_COMIDA			2
#define TEMA_FRUTAS			3
#define TEMA_PROFISSAO			4
#define TEMA_INFORMATICA		5

//Dica da palavra para o jogador.
extern char g_dica[MAX_TAMANHO_DICA];
//Palavra que o jogador deve acertar. Pode ser uma da lista acima ou personalizada.
extern char g_palavra[MAX_TAMANHO_PALAVRA];
//Variável usada para controle dos acertos do usuário. Cada letra acertada é colocada em sua posição nessa string. Quando <acertos> == <palavra>, o jogador acertou.
extern char g_acertos[MAX_TAMANHO_PALAVRA];

//Letras usadas pelo usuário e contador de letras usadas para repetições.
extern char g_letrasUsadas[26];
extern int g_numLetrasUsadas;

//Contador de erros. 6 erros = derrota;
extern int g_erros;

const char animal[MAX_ITENS_POR_TEMA][MAX_TAMANHO_PALAVRA] = { "AVESTRUZ", "BORBOLETA", "CARANGUEJO",
			"ORANGOTANGO", "CROCODILO", "DROMEDARIO", "ROUXINOL", "CENTOPEIA",
			"GAFANHOTO", "PINTASSILGO", "HIPOPOTAMO", "LEOPARDO", "GUAXINIM",
			"JAGUATIRICA", "OSTRA", "MICO", "CHIMPANZE", "CARNEIRO", "GOLFINHO",
			"MINHOCA" };

const char comida[MAX_ITENS_POR_TEMA][MAX_TAMANHO_PALAVRA] = { "EMPADA", "FARINHA", "FEIJOADA", "COXINHA",
			"BRIGADEIRO", "CHURRASCO", "LASANHA", "MACARRONADA", "TORTA",
			"TORRADA", "PIZZA", "PANQUECA", "PIPOCA", "PAMONHA", "OVO",
			"ACARAJE", "CROISSANT", "HAMBURGUER", "BISCOITO", "BOLO" };

const char fruta[MAX_ITENS_POR_TEMA][MAX_TAMANHO_PALAVRA] = { "ABACATE", "BANANA", "CARAMBOLA", "DAMASCO", "FIGO",
			"GOIABA", "JABUTICABA", "KIWI", "LARANJA", "MELANCIA", "MANGA",
			"MARACUJA", "PESSEGO", "PITOMBA", "ROMA", "TANGERINA", "TOMATE",
			"TAMARINDO", "UVA", "UMBU" };

const char profissao[MAX_ITENS_POR_TEMA][MAX_TAMANHO_PALAVRA] = { "ADVOGADO", "BOMBEIRO", "CARPINTEIRO",
			"DESENHISTA", "ENGENHEIRO", "ESCRITOR", "FERREIRO", "GUARDA",
			"HISTORIADOR", "JORNALISTA", "LEILOEIRO", "MARINHEIRO", "OURIVES",
			"PROGRAMADOR", "PADEIRO", "RELOJOEIRO", "SILVICULTOR", "TRADUTOR",
			"VETERINARIO", "ZOOLOGO" };

const char informatica[MAX_ITENS_POR_TEMA][MAX_TAMANHO_PALAVRA] = { "LINUX", "WINDOWS", "C", "PROCESSADOR",
			"TECLADO", "MOUSE", "PROGRAMA", "ALGORITMO", "HACKER", "TOUCHPAD",
			"ASCII", "JAVA", "JAVASCRIPT", "PROGRAMADOR", "PYTHON", "INTERNET",
			"ROTEADOR", "SERVIDOR", "GOOGLE", "APPLE" };

