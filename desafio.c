/*  Codificação por transposição de colunas
    — solução "básica" (sem ponteiros avançados, sem libs sofisticadas)  */

#include <stdio.h>

#define MAX_N   10000       /* limite do enunciado            */
#define MAX_K   26          /* M < 27 → até 26 caracteres     */

/* matriz grande o bastante:
   10 000 linhas × 26 colunas = 260 000 bytes (≈ 0,25 MB)           */
char tabela[MAX_N][MAX_K];

/* função simples para converter para minúscula */
char para_minuscula(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

int main(void)
{
    int N, K;                  /* tamanhos lidos */
    char chave[MAX_K + 1];     /* +1 p/ terminador '\0' */
    char texto[MAX_N];         /* mensagem sem espaços  */
    int i, r, c;

    /* --- 1. Lê N (nº de caracteres da mensagem, sem espaços) --- */
    if (scanf("%d", &N) != 1 || N <= 0 || N >= MAX_N) return 0;
    getchar();                     /* consome '\n' após o número  */

    /* --- 2. Captura a mensagem, ignorando espaços e quebras --- */
    int lidos = 0;
    while (lidos < N) {
        int ch = getchar();
        if (ch == EOF) break;
        if (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t') continue;
        texto[lidos++] = (char)ch;
    }

    /* --- 3. Lê K (tamanho da chave) e depois a própria chave --- */
    if (scanf("%d", &K) != 1 || K <= 0 || K > MAX_K) return 0;
    getchar();                     /* consome '\n' após o número  */
    int k_idx = 0;
    while (k_idx < K) {
        int ch_k = getchar();
        if (ch_k == EOF) {
            // Handle error: Unexpected EOF while reading key
            // For now, assume valid input as per problem statement
            break;
        }
        if (ch_k != ' ' && ch_k != '\n' && ch_k != '\r' && ch_k != '\t') {
            chave[k_idx++] = (char)ch_k;
        }
    }
    chave[k_idx] = '\0'; // Null-terminate the key

    /* --- 4. Preenche a tabela linha a linha --- */
    int linhas = (N + K - 1) / K;      /* arredonda para cima       */
    int idx = 0;                       /* posição no texto original */
    for (r = 0; r < linhas; ++r) {
        for (c = 0; c < K; ++c) {
            if (idx < N)
                tabela[r][c] = texto[idx++];
            else
                tabela[r][c] = 'x';    /* completa com 'x'          */
        }
    }

    /* --- 5. Emite a mensagem codificada coluna a coluna,
             seguindo ordem alfabética da chave ------------------ */
    for (int letra = 'a'; letra <= 'z'; ++letra) {
        for (c = 0; c < K; ++c) {
            if (para_minuscula(chave[c]) == letra) {
                for (r = 0; r < linhas; ++r)
                    printf("%c", tabela[r][c]);
            }
        }
    }
    printf("\n");
    return 0;
}
