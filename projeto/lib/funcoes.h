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
extern void inicializarDebug(void);
#endif
