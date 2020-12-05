/* Problema 4 - Heapsort
 * Tempo limite: 0.5s (C)
 * Gaspar Andrade Jr – R.A. 133633
 * AED II - 1.2020
 * UNIFESP - ICT
 */
#include <iostream>
 
void maxHeapify(int a[], int n, int i) { 
  int l, r, max = i;
  l = i << 1;
  r = (i << 1) + 1;
 
  if (l <= n && a[l] > a[max])
    max = l;
 
  if (r <= n && a[r] > a[max])
    max = r;
 
  if (max != i) {
    std::swap(a[i], a[max]);
    maxHeapify(a, n, max);
  }
}
 
void buildMaxHeap(int a[], int n) { 
  for (int i = n / 2; i >= 1; i--)
    maxHeapify(a, n, i);
}
 
int heapExtractMax(int a[], int n) { //erro
  int max = a[1];
  a[1] = a[n];
  maxHeapify(a, --n, 1);
 
  return max;
}
 
void imprimeVetor(int a[], const int &n) {
  for (int i = 1; i <= n; i++) 
    std::cout << a[i] << ' ';
  std::cout << '\n';
}
 
void heapSort(int a[], int n) {
  buildMaxHeap(a, n);
  imprimeVetor(a, n); // imprime vetor em MaxHeap
 
  for (int i = n; i >= 1; i--) // ordena o novo vetor V em ordem decrescente
    a[i] = heapExtractMax(a, i);
  
  imprimeVetor(a, n); // imprime vetor em ordem crescente
}
 
int main() {
  int n;
  std::cin >> n;
 
  int a[n + 1];
  for (int i = 1; i <= n; i++)
    std::cin >> a[i];
 
  heapSort(a, n);
  return 0;
}
