/* Problema 3 - Quicksort é estável? 
 *  Tempo limite: 20.0s (C)
 * Desenvolvido por: Gaspar Andrade   R.A.: 133633 * UC: AED2N      Prof. Dr. Alvaro Luiz Fazenda
 * UNIFESP - ICT
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp; 
}
 
// trocar o conteudo de dois vetores de array
void swapChar(char **a, char **b) {
  char *tmp = *a;
  *a = *b;
  *b = tmp;
}
 
int partition(int arr[], int p, int r, char **sArr) {
  int meio = (p + r) / 2, medianaIndice = 0;
  int a = arr[p], b = arr[meio], c = arr[r];
 
  if (a < b) {
    if (b < c) 
      medianaIndice = meio;
    else {
      if (a < c)
        medianaIndice = r;
      else
        medianaIndice = p;
    }
  } else {
      if (c < b)
        medianaIndice = meio;
      else {
        if (c < a)
          medianaIndice = r;
        else
          medianaIndice = p;
      }
  }
      
  swap(&arr[medianaIndice], &arr[r]);
  swapChar(&sArr[medianaIndice], &sArr[r]); // muda posicao do nome para manter a mesma posicao que o vetor idade
 
  int *pivot = &arr[r];
  char **pivotAux = &sArr[r]; // pivo auxiliar para no final alterar posicao do nome tambem
 
  int i = p - 1, j;
  for (j = p; j < r; ++j)
    if (arr[j] <= *pivot) {
      i++;
      swap(&arr[i], &arr[j]);
      swapChar(&sArr[i], &sArr[j]);
    }
 
  swap(&arr[i + 1], &(*pivot));
  swapChar(&sArr[i + 1], &(*pivotAux));
 
  return (i + 1);
}
 
void quickSort(int a[], int p, int r, char **c) {
  if (p < r) {
    int q = partition(a, p, r, c);
    quickSort(a, p, q - 1, c);
    quickSort(a, q + 1, r, c);
  }
}
 
void merge(int *array, int p, int q, int r, char **sArr) {
  int i, j, k, n1, n2;
  n1 = q - p + 1; n2 = r-q;
  int L[n1], R[n2];
 
  char sL[n1][15], sR[n2][15];
  for(i = 0; i<n1; i++) {
    L[i] = array[p+i];
    //std::copy(sL[i], sL[i] + 15, sArr[p + i]);
    strcpy(sL[i], sArr[p + i]);
  }
  for(j = 0; j<n2; j++) {
    R[j] = array[q + 1 + j];
    strcpy(sR[j], sArr[q + 1 + j]);
    //std::copy(sR[j], sR[j] + 15, sArr[q+1+j]);
  }
 
  i = 0; j = 0; k = p;
  while(i < n1 && j < n2) {
    if(L[i] <= R[j]) {
       array[k] = L[i];
       //sArr[k] = sL[i];
       strcpy(sArr[k], sL[i]);
       i++;
    } else {
       array[k] = R[j];
       //sArr[k] = sR[j];
       strcpy(sArr[k], sR[j]);
       j++;
    }
    k++;
  }
 
  while(i < n1) {      
    array[k] = L[i];
    //sArr[k] = sL[i];
    strcpy(sArr[k], sL[i]);
    i++; k++;
  }
  while(j < n2) {     
    array[k] = R[j];
    //sArr[k] = sR[j];
    strcpy(sArr[k], sR[j]);
    j++; k++;
  }
}
 
void mergeSort(int arr[], int p, int r, char **c) {
    if (p < r) {
        int q = (p + r) / 2;
    mergeSort(arr, p, q, c);
    mergeSort(arr, q + 1, r, c);
    merge(arr, p, q, r, c);
  }
}
 
// verifica se a ordem de alguem com a mesma idade foi alterada
int verificaAlteracoes(char **c, char **cCopia, int n) {
  int i;
  for (i = 0; i < n; i++)
    if (strcmp(c[i], cCopia[i])) // ordem foi alterada
      return 0;
 
  return 1;
}
 
int main() {
  int n, m, p;
  scanf("%d", &n);
  // aloca memoria matriz de char Nx15
  char **nome = (char**) malloc(n * sizeof(char*));
  char **nomeCopia = (char**) malloc(n * sizeof(char*));
  int i;
  for (i = 0; i < n; i++) {
    nome[i] = (char*) malloc(15 * sizeof(char));
    nomeCopia[i] = (char*) malloc(15 * sizeof(char));
  } 
  int idade[n], idadeCopia[n];
  for (i = 0; i < n; i++)
    scanf("%s %i", nome[i], &idade[i]);
  scanf("%d %d", &p, &m);
 
  // copia dos dois arrays para comparacao
  for (i = 0; i < n; i++)
    strcpy(nomeCopia[i], nome[i]); 
  for (i = 0; i < n; i++)
    idadeCopia[i] = idade[i];
 
  quickSort(idade, 0, n - 1, nome); // ordenada os dois arrays com base na idade
  // - funcionando
  mergeSort(idadeCopia, 0, n - 1, nomeCopia); // mergeSort eh estavel
 
  if (verificaAlteracoes(nome, nomeCopia, n))
    printf("yes\n");
  else
    printf("no\n");
 
  // imprime nome e idade de p - 1, ate (p - 1) + m
  while (m--) {
    printf("%s %i\n", nome[p - 1], idade[p - 1]);
    p++;
  }
 
  // desaloca memoria
  for (i = 0; i < n; i++) {
    free(nome[i]);
    free(nomeCopia[i]);
  }
  free(nome);
  free(nomeCopia);
  return 0;
}
