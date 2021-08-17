/****************************************************************
 Problema 4
 Variantes SARS-CoV-2
 Tempo limite: 0,5s (C/C++)
 Autor: Gaspar Andrade - 133633
 UC: PAA - ICT/UNIFESP
 ****************************************************************/
#include <cstdio>
#include <cstring>

#define TAM_MAX 1000

int lcs(char *a, char *b, int a_tam, int b_tam) {
  int aux[a_tam+1][b_tam+1];
  int i, j;

  for (i = 0; i <= a_tam; i++) {
    for (j = 0; j <= b_tam; j++) {
      if (i == 0)
        aux[i][j] = j;
      else if (j == 0)
        aux[i][j] = i;

      else if (a[i-1] == b[j-1])
        aux[i][j] = aux[i-1][j-1];
      else {
        if (aux[i][j-1] > aux[i-1][j]) {
          if (aux[i-1][j] > aux[i-1][j-1]) {
            aux[i][j] = 1 + aux[i-1][j-1];
          } else {
            aux[i][j] = 1 + aux[i-1][j];
          }
        } else {
          if (aux[i][j-1] > aux[i-1][j-1]) {
            aux[i][j] = 1 + aux[i-1][j-1];
          } else {
            aux[i][j] = 1 + aux[i][j-1];
          }
        }
      }
    }
  }

  return aux[a_tam][b_tam];
}

int min_edicoes(char *a, char *b) {
  int a_tam, b_tam;
  a_tam = strlen(a);
  b_tam = strlen(b);

  return lcs(a, b, a_tam, b_tam);
}

int main() {
  char a[TAM_MAX], b[TAM_MAX];
  memset(a, '\0', sizeof(char)*TAM_MAX); 
  memset(b, '\0', sizeof(char)*TAM_MAX);
  scanf("%s", a);
  scanf("%s", b);

  printf("%d\n", min_edicoes(a, b));
  return 0;
}
