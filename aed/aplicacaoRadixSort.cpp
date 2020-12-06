/* Gaspar Andrade – 133633
 * UC: AED2 Prof. Dr. Álvaro Luiz Fazenda
 * UNIFESP – ICT
 * Atividade 5
*/
#include <iostream>
#include <stdio.h>
#include <cctype>
#include <ctype.h>
#include <cstring>

// pega o maior vetor com caracteres em uma matriz
int getMaior(char **a, const int &n) { 
  int ret = 0;
  for (int i = 0; i < n; i++)
    if (ret < strlen(a[i]))
      ret = strlen(a[i]);

  return ret; // retorna o maior tamanho
}

// seta todos os caracteres minusculo
void setMinuscula(char **a, const int &n) {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      a[i][j] = tolower(a[i][j]);
}

void imprimeVetor(int *c, int n) {
  for (int i = 0; i < n; i++)
    std::cout << c[i] << ' ';
  std::cout << '\n';
}

void countingSort(char **a, char **b, int n, int k, int pos) {
  int c[k];
  for (int i = 0; i < k; i++)
    c[i] = 0;
  int p0 = 'a' - 1; // p0 posicao inicial no alfabeto

  for (int j = 0; j < n; j++)
    if (a[j][pos] == '\0')
      c[0] += 1;
    else
      c[a[j][pos] - p0] += 1;

  for (int i = 1; i < k; i++)
    c[i] += c[i - 1];
  imprimeVetor(c, 27);
  
  // copia vetor na posicao j para a nova posicao ordenada
  for (int j = n - 1; j >= 0; j--) {
    if (a[j][pos] == '\0') {
      c[0]--; // vai antes da copia pois ha diferenca nos indices
      strncpy(b[c[0]], a[j], 15);
    } else {
      c[a[j][pos] - p0]--; // vai antes da copia pois ha diferenca nos indices
      strncpy(b[c[a[j][pos] - p0]], a[j], 15); 
    }
  }
  for (int i = 0; i < n; i++)
    strncpy(a[i], b[i], 15);
}

void radixSort(char **a, int n, int d) {
  char **b = new char*[n];
  for (int i = 0; i < n; i++)
    b[i] = new char[15];

  for (int i = d - 1; i >= 0; i--){ 
    countingSort(a, b, n, 27, i);
    // copia os valores ordenados da matriz auxiliar para a matriz 'a'
  }

  for (int i = 0; i < n; i++)
    delete[] b[i];
  delete[] b;
}

int main() {
  int n, p, m;
  std::cin >> n; 
  std::cin.ignore();

  // aloca matriz de caracteres
  char **a = new char*[n];
  for (int i = 0; i < n; i++)
    a[i] = new char[15];

  for (int i = 0; i < n; i++)
    scanf("%s", a[i]);
  std::cin >> p >> m;

  int maior = getMaior(a, n);

  radixSort(a, n, maior);

  for (int i = p - 1; m > 0; i++, m--)
    std::cout << a[i] << '\n';

  // desaloca matriz de caracteres
  for (int i = 0; i < n; i++)
    delete[] a[i];
  delete[] a;
  return 0;
}
