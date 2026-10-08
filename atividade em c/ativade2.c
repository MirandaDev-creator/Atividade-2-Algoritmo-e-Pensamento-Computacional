/* Criptografia em duas camadas: Cesar (SHIFT) + sequencia numerica
 * deslocamento da letra i = SHIFT + sequencia[i]  (mod 26)
 * Compilar: gcc -o cripto criptografia_simples.c */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int mod26(int x) { return ((x % 26) + 26) % 26; }

int eh_primo(int n) {
    for (int d = 2; d * d <= n; d++)
        if (n % d == 0) return 0;
    return n > 1;
}

/* tipo: 1=PA  2=PG  3=Fibonacci  4=Primos */
void gerar_sequencia(int tipo, int n, int a1, int r, int *seq) {
    int a = mod26(a1), f1 = 1, f2 = 1, p = 1;
    r = mod26(r);
    for (int i = 0; i < n; i++) {
        if (tipo == 1)      { seq[i] = a; a = mod26(a + r); }
        else if (tipo == 2) { seq[i] = a; a = mod26(a * r); }
        else if (tipo == 3) { seq[i] = f1; int t = mod26(f1 + f2); f1 = f2; f2 = t; }
        else { do p++; while (!eh_primo(p)); seq[i] = mod26(p); }
    }
}

/* sentido: +1 criptografa, -1 descriptografa */
void cifrar(const char *entrada, char *saida, int shift, const int *seq, int sentido) {
    int i;
    for (i = 0; entrada[i]; i++)
        saida[i] = 'a' + mod26(entrada[i] - 'a' + sentido * (shift + seq[i]));
    saida[i] = '\0';
}

void gravar_log(const char *texto) {
    FILE *f = fopen("log_execucao.txt", "a");
    if (!f) return;
    char data[32];
    time_t t = time(NULL);
    strftime(data, sizeof data, "%d/%m/%Y %H:%M:%S", localtime(&t));
    fprintf(f, "[%s] %s\n", data, texto);
    fclose(f);
}

/* Pede palavra valida (1 a 15 letras) e retorna tamanho */
int ler_palavra(char *p) {
    while (1) {
        printf("Palavra (ate 15 letras, sem acentos): ");
        scanf("%31s", p);
        int ok = strlen(p) <= 15;
        for (int i = 0; p[i]; i++)
            if (isalpha((unsigned char)p[i])) p[i] = tolower(p[i]);
            else ok = 0;
        if (ok) return strlen(p);
        printf("Palavra invalida!\n");
    }
}

void processar(int sentido) {
    char palavra[32], saida[32], log[200];
    int seq[15], shift, tipo, a1 = 1, r = 1;

    int n = ler_palavra(palavra);
    printf("SHIFT: ");
    scanf("%d", &shift);
    printf("Sequencia (1-PA 2-PG 3-Fibonacci 4-Primos): ");
    scanf("%d", &tipo);
    if (tipo == 1 || tipo == 2) {
        printf("Primeiro termo e razao: ");
        scanf("%d %d", &a1, &r);
    }

    gerar_sequencia(tipo, n, a1, r, seq);
    cifrar(palavra, saida, shift, seq, sentido);
    printf("Resultado: %s\n", saida);

    sprintf(log, "%s | %s -> %s | SHIFT: %d | Tipo: %d",
            sentido > 0 ? "CRIPTOGRAFOU" : "DESCRIPTOGRAFOU", palavra, saida, shift, tipo);
    gravar_log(log);

    if (sentido > 0) {
        FILE *f = fopen("resultado_criptografia.txt", "a");
        if (f) {
            fprintf(f, "Palavra codificada: %s | SHIFT: %d | Tipo: %d | Letras: %d\n",
                    saida, shift, tipo, n);
            fclose(f);
        }
    }
}

int main(void) {
    int op;
    do {
        printf("\n1-Criptografar  2-Descriptografar  0-Sair\nOpcao: ");
        scanf("%d", &op);
        if (op == 1 || op == 2) processar(op == 1 ? 1 : -1);
    } while (op != 0);
    return 0;
}