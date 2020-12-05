/* Disciplina: AED2 (Noturno) 1sem - 2020, Universidade Federal de Sao Paulo
 * Desenvolvido por: Gaspar Andrade Jr
 *
 * Tarefa 01 AED2 - 2020 - Mesclar vetores ordenados
*/
#include <iostream>
 
int *mesclar(int a1[], int a2[], int n1, int n2) {
  // aloca na memoria heap espaco para o terceiro vetor
  int *p = new int[n1 + n2];
 
  int i, j;
  i = j = 0;
 
  // ira verificar o final de cada vetor
  // e apos uma comparacao o elento sera colocado no novo vetor
  while(n1 > i || n2 > j) {
    if(a1[i] <= a2[j] && n1 > i) {
      p[i + j] = a1[i];
      ++i;
    }
    else {
      p[i + j] = a2[j];
      ++j;
    }
  }
 
  return p;
}
 
// algoritmo de ordenacao insertionSort
void insertionSort(int arr[], int size) {
  int i, j, key;
 
  for(i = 0; i < size; i++) {
    j = i - 1;
    key = arr[i];
 
    while(j >= 0 && key < arr[j]) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
 
    arr[j + 1] = key;
  }
}
 
int main() {
  // entrada do primeiro vetor
  int nA;
  std::cin >> nA;
  int vetA[nA];
  for(int i = 0; i < nA; ++i)
    std::cin >> vetA[i];
  
  // entrada do segundo vetor
  int nB;
  std::cin >> nB;
  int vetB[nB];
  for(int i = 0; i < nB; ++i)
    std::cin >> vetB[i];
 
  // ordenada os dois primeiro vetores utilizando insertionSort
  insertionSort(vetA, nA);
  insertionSort(vetB, nB);
 
  // imprimi os valores do terceiro vetor
  int *vetC = mesclar(vetA, vetB, nA, nB);
  for(int i = 0; i < nA + nB; ++i)
    std::cout << vetC[i] << " "; 
  std::cout << std::endl;
 
  // desaloca o terceiro vetor da memoria heap
  delete[] vetC;
  return 0;
}
