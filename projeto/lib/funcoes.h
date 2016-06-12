extern int clean_stdin(void);
extern void limparTela(void);

extern void resetarAcertosDaPalavra(void);
extern void inicializarJogo(void);

extern int escolherModoDeJogo(void);
extern int escolherTema(void);
extern void escolherPalavraAleatoria(int);
extern void escolherPalavraPersonalizada(void);

extern int verificarPalpite(char);
extern char lerPalpite(void);

extern void desenharBoneco(int);
extern void desenharPalavra(void);

extern void mostrarForca(void);

#if defined DEBUG_MODE
extern void inicializarDebug(void);
#endif
